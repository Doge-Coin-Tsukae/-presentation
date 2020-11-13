#include <list>
#include <vector>
#include <typeinfo>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#include "input.h"
#include "scene.h"
#include "gamemaneger.h"
#include "Game.h"
#include "Result.h"

#include "gameobject.h"
#include "camera.h"
#include "field.h"
#include "meshfield.h"
#include "human.h"
#include "model.h"
#include "carsor.h"
#include "colider.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "base.h"
#include "player.h"
#include "enemy.h"
#include "enemycommander.h"
#include "enemyrespornpoint.h"
#include "bunker.h"
#include "polygon.h"
#include "skydome.h"
#include "deadtree.h"

#include "tree.h"
#include "number.h"
#include "gauge.h"
#include "carsor.h"
#include "chip.h"
#include "modechip.h"
#include "selectpointer.h"
#include "selectitem.h"

void CGame::Init()
{
	//テクスチャ + モデルロード
	CBUNKER::Load();
	CEnemy::Load();
	CEnemyRespornPoint::Load();
	CWEAPON::Load();
	CDEADTREE::Load();

	m_GameManeger = new CGAME_MANEGER;
	m_GameManeger->Init();

	//使うゲームオブジェクト呼び出し
	//カメラ0番 3Dモデル1番 2Dモデル番
	AddGameObject<CCamera>(0);

	AddGameObject<CCARSOR>(1);
	AddGameObject<CSKYDOME>(1);

	//AddGameObject<CField>(1);
	AddGameObject<CMeshField>(1);

	AddGameObject<CPlayer>(1)->SetPosition(D3DXVECTOR3(0.0f, 1.0f, -200.0f));

	AddGameObject<CENEMY_COMMANDER>(1);

	AddGameObject<CEnemy>(1)->SetPosition(D3DXVECTOR3(5.0f, 1.0f, 0.0f));
	AddGameObject<CEnemy>(1)->SetPosition(D3DXVECTOR3(10.0f, 1.0f, 0.0f));
	AddGameObject<CEnemy>(1)->SetPosition(D3DXVECTOR3(12.0f, 1.0f, 0.0f));

	AddGameObject<CBASE>(1)->SetPosition(D3DXVECTOR3(50.0f, 0.0f, -100.0f));
	AddGameObject<CBASE>(1)->SetPosition(D3DXVECTOR3(-50.0f, 0.0f, 0.0f));

	AddGameObject<CEnemyRespornPoint>(1)->SetPosition(D3DXVECTOR3(200.0f, 0.0f, -100.0f));
	AddGameObject<CEnemyRespornPoint>(1)->SetPosition(D3DXVECTOR3(100.0f, 0.0f, -100.0f));

	AddGameObject<CBUNKER>(1)->SetPosition(D3DXVECTOR3(20.0f, 0.0f, -130.0f));
	AddGameObject<CBUNKER>(1)->SetPosition(D3DXVECTOR3(-20.0f, 0.0f, -130.0f));

	AddGameObject<CTREE>(1)->SetPosition(D3DXVECTOR3(-50.0f, 5.0f, -150.0f));
	AddGameObject<CTREE>(1)->SetPosition(D3DXVECTOR3(-30.0f, 5.0f, -170.0f));
	AddGameObject<CTREE>(1)->SetPosition(D3DXVECTOR3(30.0f, 5.0f, -180.0f));
	AddGameObject<CTREE>(1)->SetPosition(D3DXVECTOR3(20.0f, 5.0f, -160.0f));
	AddGameObject<CTREE>(1)->SetPosition(D3DXVECTOR3(-15.0f, 5.0f, -150.0f));

	AddGameObject<CSelectItem>(2);
	//AddGameObject<CPolygon>(2);
}

void CGame::Uninit()
{
	//リストに入っているゲームオブジェクトを削除
	CScene::Uninit();

	//テクスチャアンロード
	CDEADTREE::Unload();
	CWEAPON::UnLoad();
	CEnemyRespornPoint::Unload();
	CEnemy::Unload();
	CBUNKER::Unload();

	m_GameManeger->Uninit();
	delete m_GameManeger;
}

void CGame::Update()
{
	CScene::Update();	//リストに入っているゲームオブジェクトを呼び出す

	m_GameManeger->Update();

	//リターンキーでリザルト画面へ
	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		CManager::SetScene<CResult>();
	}

}

void CGame::Draw()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	CScene::Draw();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}