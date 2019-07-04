#include <list>

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "gameobject.h"
#include "polygon.h"
#include "camera.h"
#include "field.h"

#include "model.h"		// �O��"renderer.h"���K�v
#include "player.h"
#include "enemy.h"
#include "bullet.h"


#include "scene.h"

void CPlayer::Init()
{
	m_pModel = new CModel();
	m_pModel->Load("asset/model/miku_01.obj");
	m_Position = XMFLOAT3(0.0f, 1.0f, -5.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
}

void CPlayer::Uninit()
{
	m_pModel->Unload();
	delete m_pModel;
}

void CPlayer::Update()
{
	// �e
	if (CInput::GetKeyTrigger(VK_SPACE)) {
		CScene* scene = CManager::GetScene();
		CBullet* bullet = scene->AddGameObject<CBullet>(LAYER_3DMODELS);
		bullet->SetPosition(m_Position);
	}

	// �ړ�
	if (CInput::GetKeyPress('A')) {		// ��
		m_Position.x -= 0.5f;
	}
	if (CInput::GetKeyPress('D')) {		// �E
		m_Position.x += 0.5f;
	}
	if (CInput::GetKeyPress('W')) {		// �O��
		m_Position.z += 0.5f;
	}
	if (CInput::GetKeyPress('S')) {		// ���
		m_Position.z -= 0.5f;
	}

	// ����
	if (CInput::GetKeyPress(VK_RIGHT)) {
		m_Rotation.y += 0.01f;
		//m_fCameraAngle += 0.01f;
	}
	else if (CInput::GetKeyPress(VK_LEFT)) {
		m_Rotation.y -= 0.01f;
		//m_fCameraAngle -= 0.01f;
	}
}

void CPlayer::Draw()
{
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	CRenderer::SetWorldMatrix(&world);
	
	m_pModel->Draw();
}