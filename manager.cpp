#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "sound.h"
#include "input.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "gamemaneger.h"
#include "Game.h"
#include "Title.h"
#include "fade.h"

CScene* CManager::m_Scene = NULL;

void CManager::Init()
{
	ShowCursor(FALSE);	//カーソルを消す

	CRenderer::Init();
	CInput::Init();
	CFADE::Init();

	InitSound(GetWindow());

	SetScene<CTitle>();
}

void CManager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;
	
	UninitSound();
	CFADE::Uninit();
	CInput::Uninit();
	CRenderer::Uninit();
}

void CManager::Update()
{
	CInput::Update();
	CFADE::Update();
	m_Scene->Update();
}

void CManager::Draw()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	LIGHT light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 0.5f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	
	CRenderer::SetLight(light);

	CRenderer::Begin();

	//カメラ->3Dポリゴン->2Dポリゴンの順番で描画する
	m_Scene->Draw();

	CFADE::Draw();

	//FPS表示
	ImGui::SetNextWindowSize(ImVec2(80, 50));
	ImGui::Begin("FPS");

	ImGui::Text("fps: %d",GetFPS());

	ImGui::End();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	CRenderer::End();
}
