
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "gameobject.h"
#include "camera.h"


void CCamera::Init()
{
	m_fCameraAngle = 0.0f;

	m_Position = XMFLOAT3(0.0f, 7.0f, -15.0f);
	m_Rotation = XMFLOAT3(0.5f, 0.0f, 0.0f);


	m_Viewport.left = 0;
	m_Viewport.top = 0;
	m_Viewport.right = SCREEN_WIDTH;
	m_Viewport.bottom = SCREEN_HEIGHT;

	m_Target = XMFLOAT3(0.0f, 1.0f, -5.0f);
}


void CCamera::Uninit()
{


}


void CCamera::Update()
{
	// �ړ�
	if (CInput::GetKeyPress('A')) {		// ��
		m_Position.x -= 0.5f;
	}
	else if (CInput::GetKeyPress('D')) {		// �E
		m_Position.x += 0.5f;
	}
	else if (CInput::GetKeyPress('W')) {		// �O��
		m_Position.z += 0.5f;
	}
	else if (CInput::GetKeyPress('S')) {		// ���
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



void CCamera::Draw()
{

	XMMATRIX	m_ViewMatrix;			// �r���[���W�s��
	XMMATRIX	m_InvViewMatrix;		// �r���[�t�s��ϊ��p�i�[�s��
	XMMATRIX	m_ProjectionMatrix;		// �v���W�F�N�V�����s��

	

	// �r���[�|�[�g�ݒ�
	D3D11_VIEWPORT dxViewport;
	dxViewport.Width = (float)(m_Viewport.right - m_Viewport.left);
	dxViewport.Height = (float)(m_Viewport.bottom - m_Viewport.top);
	dxViewport.MinDepth = 0.0f;
	dxViewport.MaxDepth = 1.0f;
	dxViewport.TopLeftX = (float)m_Viewport.left;
	dxViewport.TopLeftY = (float)m_Viewport.top;

	CRenderer::GetDeviceContext()->RSSetViewports(1, &dxViewport);



	// �r���[�}�g���N�X�ݒ�(�ړ��͂����œ���Ă�)
	m_InvViewMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);	// ����
	m_InvViewMatrix *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);			// �ړ�	// ���[�p�Ɋ|���Z���Ă�

	XMVECTOR det;
		m_ViewMatrix = XMMatrixInverse(&det, m_InvViewMatrix);	// �t�s��

	CRenderer::SetViewMatrix(&m_ViewMatrix);	// �r���[�s���n���Ă�����



	// �v���W�F�N�V�����}�g���N�X�ݒ�
	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(1.0f, dxViewport.Width / dxViewport.Height, 1.0f, 1000.0f);

	CRenderer::SetProjectionMatrix(&m_ProjectionMatrix);



}

