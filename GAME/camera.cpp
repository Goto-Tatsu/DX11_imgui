
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "gameobject.h"
#include "camera.h"




void CCamera::Init()
{

	m_Position = XMFLOAT3(0.0f, 7.0f, -15.0f);
	m_Rotation = XMFLOAT3(0.5f, 0.0f, 0.0f);


	m_Viewport.left = 0;
	m_Viewport.top = 0;
	m_Viewport.right = SCREEN_WIDTH;
	m_Viewport.bottom = SCREEN_HEIGHT;

}


void CCamera::Uninit()
{


}


void CCamera::Update()
{
	if (CInput::GetKeyPress('A')) {		// 左
		m_Position.x -= 0.5f;
	}
	if (CInput::GetKeyPress('D')) {		// 右
		m_Position.x += 0.5f;
	}
	if (CInput::GetKeyPress('W')) {		// 前方
		m_Position.z += 0.5f;
	}
	if (CInput::GetKeyPress('S')) {		// 後方
		m_Position.z -= 0.5f;
	}

}



void CCamera::Draw()
{

	XMMATRIX	m_ViewMatrix;
	XMMATRIX	m_InvViewMatrix;
	XMMATRIX	m_ProjectionMatrix;



	// ビューポート設定
	D3D11_VIEWPORT dxViewport;
	dxViewport.Width = (float)(m_Viewport.right - m_Viewport.left);
	dxViewport.Height = (float)(m_Viewport.bottom - m_Viewport.top);
	dxViewport.MinDepth = 0.0f;
	dxViewport.MaxDepth = 1.0f;
	dxViewport.TopLeftX = (float)m_Viewport.left;
	dxViewport.TopLeftY = (float)m_Viewport.top;

	CRenderer::GetDeviceContext()->RSSetViewports(1, &dxViewport);



	// ビューマトリクス設定
	m_InvViewMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	m_InvViewMatrix *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	XMVECTOR det;
	m_ViewMatrix = XMMatrixInverse(&det, m_InvViewMatrix);

	CRenderer::SetViewMatrix(&m_ViewMatrix);



	// プロジェクションマトリクス設定
	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(1.0f, dxViewport.Width / dxViewport.Height, 1.0f, 1000.0f);

	CRenderer::SetProjectionMatrix(&m_ProjectionMatrix);



}

