#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "sound.h"
#include "input.h"
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

	LIGHT light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 0.5f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//-----------ライトをカメラとみなした行列を作成
	D3DXVECTOR3 pEye(350.0f, 10.0f, -200.0f), pAt(0.0f, 0.0f, 0.0f), pUp(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&light.ViewMatrix, &pEye,
		&pAt, &pUp);
	//-----------ライト用のプロジェクション行列を作成
	D3DXMatrixPerspectiveFovLH(&light.ProjectionMatrix, 1.0f,
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, 5.0f, 30.0f);
	CRenderer::SetLight(light);
	CRenderer::BeginDepth();//追加-シャドウバッファを深度バッファへ設定等
	CRenderer::SetViewMatrix(&light.ViewMatrix);//追加-カメラへライト用行列セット
	CRenderer::SetProjectionMatrix(&light.ProjectionMatrix);//追加-プロジェクションへライト用行列をセッ

	m_Scene->ShadowDraw();

	CRenderer::Begin();

	//カメラ->3Dポリゴン->2Dポリゴンの順番で描画する
	m_Scene->Draw();

	CFADE::Draw();

	CRenderer::End();
}
