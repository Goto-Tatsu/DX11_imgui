
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

#define POLYGON_TEXTURE_MAX	(1)
#define FIELD_TEXTURE_MAX	(1)
#define MODEL_MAX			(1)

CScene* CManager::m_pScene = NULL;
//CScene* g_Scene = NULL;



void CManager::Init()
{
	// Rendererの初期化
	CRenderer::Init();

	// Inputの初期化
	CInput::Init();

	// Sceneの初期化
	m_pScene = new CScene();
	m_pScene->Init();

}

void CManager::Uninit()		// Initの中身と逆に終了記述して！
{
	// Cleanup 
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	// Sceneのシュウリョウショリ
	m_pScene->Uninit();
	delete m_pScene;

	// Rendererの終了処理
	CRenderer::Uninit();
}

void CManager::Update()
{
	// Input入力
	CInput::Update();

	// SceneのUpdate
	m_pScene->Update();

}

void CManager::Draw()
{
	// Rendererはじめ
	CRenderer::Begin();

	// Sceneの描画
	m_pScene->Draw();

	// IMGUIの描画(Render)
	ImGui::Render();										// 設定したIMGUIの諸々を描画してくれる命令。
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());	// 何かよくわかんない
	
	// Rendererおわり
	CRenderer::End();
}

CScene* CManager::GetScene()
{
	return m_pScene;
}