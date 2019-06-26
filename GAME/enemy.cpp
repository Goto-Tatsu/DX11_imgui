#include <list>
#include <time.h>

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "gameobject.h"
#include "polygon.h"
#include "camera.h"
#include "field.h"

#include "model.h"		// ‘O‚É"renderer.h"‚ª•K—v
#include "player.h"
#include "enemy.h"
#include "bullet.h"

#include "scene.h"

static int g_Random = 0;

void CEnemy::Init()
{
	//srand(time(NULL));
	//g_Random = rand() % 10 + 1;

	m_pModel = new CModel();
	m_pModel->Load("asset/model/miku_01.obj");
	m_Position = XMFLOAT3((float)g_Random, 1.0f, 6.0f);
	m_Rotation = XMFLOAT3(0.0f, 180.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	srand(time(NULL));
	g_Random += rand() % 10 + 1;
}

void CEnemy::Init(const char* pFilename, float posX, float posY, float posZ) {
	m_pModel = new CModel();
	m_pModel->Load(pFilename);
	m_Position = XMFLOAT3(posX, posY, posZ);
	m_Rotation = XMFLOAT3(0.0f, 180.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
}

void CEnemy::Uninit()
{
	m_pModel->Unload();
	delete m_pModel;
}

void CEnemy::Update()
{
	
}

void CEnemy::Draw()
{
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	CRenderer::SetWorldMatrix(&world);

	m_pModel->Draw();
}

XMFLOAT3 CEnemy::GetPosition() {
	return CEnemy::m_Position;
}
