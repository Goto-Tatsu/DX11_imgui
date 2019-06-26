#include <list>

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "gameobject.h"
#include "polygon.h"
#include "camera.h"
#include "field.h"

#include "model.h"		// 前に"renderer.h"が必要
#include "player.h"
#include "enemy.h"
#include "bullet.h"


#include "scene.h"

typedef struct Distance_tag {
	float posX;
	float posY;
	float posZ;
}Distance;

float g_Radius = 2.0f;

void CBullet::Init()
{
	m_pModel = new CModel();
	m_pModel->Load("asset/model/miku_01.obj");
	m_Position = XMFLOAT3(0.0f, 1.0f, -5.0f);
	m_Rotation = XMFLOAT3(180.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
}

void CBullet::Uninit()
{
	m_pModel->Unload();
	delete m_pModel;
}

void CBullet::Update()
{
	/* 衝突判定仕込み */
	// 単体と
	CEnemy* enemy;
	enemy = CManager::GetScene()->GetGameObject<CEnemy>(LAYER_3DMODELS);
	if (enemy != nullptr) {
		XMFLOAT3 enemyPos = enemy->GetPosition();
		float x = (m_Position.x - enemyPos.x) * (m_Position.x - enemyPos.x);
		float z = (m_Position.z - enemyPos.z) * (m_Position.z - enemyPos.z);
		if ((x + z) <= (g_Radius * g_Radius)) {
			CManager::GetScene()->DestroyGameObject(enemy);
			CManager::GetScene()->DestroyGameObject(this);
			return;
		}

		// 複数の敵と。
		std::vector<CEnemy*> enemies;
		enemies = CManager::GetScene()->GetGameObjects<CEnemy>(LAYER_3DMODELS);
		for (CEnemy* enemy : enemies) {
			XMFLOAT3 enemyPos = enemy->GetPosition();
			float x = (m_Position.x - enemyPos.x) * (m_Position.x - enemyPos.x);
			float z = (m_Position.z - enemyPos.z) * (m_Position.z - enemyPos.z);
			if ((x + z) <= (g_Radius * g_Radius)) {
				if (enemy != NULL) {
					CManager::GetScene()->DestroyGameObject(enemy);
					CManager::GetScene()->DestroyGameObject(this);
					return;
				}
			}
		}
	}

	m_Position.z += 0.1f;
	m_Rotation.z += 0.1f;

	// 弾削除
	if (m_Position.z > 10.0f) {
		CManager::GetScene()->DestroyGameObject(this);
		return;
	}
}

void CBullet::Draw()
{
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	CRenderer::SetWorldMatrix(&world);

	m_pModel->Draw();
}

void CBullet::SetPosition(XMFLOAT3 position)
{
	m_Position = position;
}

XMFLOAT3 CBullet::GetPosition(void) {
	return CBullet::m_Position;
}