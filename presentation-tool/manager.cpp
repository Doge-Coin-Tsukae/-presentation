#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "input.h"
#include "scene.h"
#include "Game.h"
#include "Title.h"

CScene* CManager::m_Scene = NULL;

void CManager::Init()
{
	CRenderer::Init();
	CInput::Init();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui_ImplWin32_Init(GetWindow());
	ImGui_ImplDX11_Init(CRenderer::GetDevice(), CRenderer::GetDeviceContext());

	SetScene<CTitle>();
}

void CManager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;

	ImGui_ImplDX11_Shutdown();

	CInput::Uninit();
	CRenderer::Uninit();
}

void CManager::Update()
{
	CInput::Update();
	m_Scene->Update();
}

void CManager::Draw()
{

	CRenderer::Begin();

	LIGHT light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f,1.0f, 1.0f, 1.0f);
	CRenderer::SetLight(light);

	//ƒJƒƒ‰->3Dƒ|ƒŠƒSƒ“->2Dƒ|ƒŠƒSƒ“‚Ì‡”Ô‚Å•`‰æ‚·‚é

	m_Scene->Draw();

	CRenderer::End();
}
