
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

#define POLYGON_TEXTURE_MAX	(1)
#define FIELD_TEXTURE_MAX	(1)
#define MODEL_MAX			(1)

CScene* CManager::m_pScene = NULL;
//CScene* g_Scene = NULL;



void CManager::Init()
{
	// Renderer�̏�����
	CRenderer::Init();

	// Input�̏�����
	CInput::Init();

	// Scene�̏�����
	m_pScene = new CScene();
	m_pScene->Init();

}

void CManager::Uninit()		// Init�̒��g�Ƌt�ɏI���L�q���āI
{
	// Cleanup 
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	// Scene�̃V���E�����E�V����
	m_pScene->Uninit();
	delete m_pScene;

	// Renderer�̏I������
	CRenderer::Uninit();
}

void CManager::Update()
{
	// Input����
	CInput::Update();

	// Scene��Update
	m_pScene->Update();

}

void CManager::Draw()
{
	// Renderer�͂���
	CRenderer::Begin();

	// Scene�̕`��
	m_pScene->Draw();

	// IMGUI�̕`��(Render)
	ImGui::Render();										// �ݒ肵��IMGUI�̏��X��`�悵�Ă���閽�߁B
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());	// �����悭�킩��Ȃ�
	
	// Renderer�����
	CRenderer::End();
}

CScene* CManager::GetScene()
{
	return m_pScene;
}