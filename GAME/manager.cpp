
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

// Our state
bool show_demo_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

CScene* CManager::m_pScene = NULL;
//CScene* g_Scene = NULL;
CPlayer* player;



void CManager::Init()
{
	// Rendererの初期化
	CRenderer::Init();

	// Inputの初期化
	CInput::Init();

	// Sceneの初期化
	m_pScene = new CScene();
	m_pScene->Init();

	player = new CPlayer();
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

void CManager::Gui_Show()
{
	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)& clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");

		ImGui::Text("position X : %.1f", player->GetPositionX());

		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}
	/* ================================================================================================ */

}
