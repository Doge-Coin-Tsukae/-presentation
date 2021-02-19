#include <list>
#include <vector>
#include <typeinfo>
#include<string>
#include <direct.h>
#include "main.h"
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include "renderer.h"
#include "scene.h"
#include "manager.h"

#include "input.h"
#include "scene.h"
#include "Game.h"

#include "gameobject.h"
#include "save.h"
#include "load.h"
#include "camera.h"
#include "meshfield.h"
#include "human.h"
#include "model.h"
#include "animationmodel.h"
#include "carsor.h"
#include "colider.h"
#include "sight.h"
#include "base.h"
#include "player.h"
#include "enemy.h"
#include "friend.h"
#include "bunker.h"
#include "polygon.h"
#include "skydome.h"
#include "deadtree.h"

#include "tree.h"
#include "number.h"
#include "carsor.h"
#include "chip.h"
#include "modechip.h"
#include "selectpointer.h"
#include "saveloadchip.h"
#include "triangle.h"
#include "selectitem.h"

void CGame::Init()
{
	//テクスチャ + モデルロード


	//使うゲームオブジェクト呼び出し
	//カメラ0番 3Dモデル1番 2Dモデル番
	AddGameObject<CCamera>(0);

	AddGameObject<CSAVE>(0);
	AddGameObject<CLOAD>(0);

	AddGameObject<CCARSOR>(1);

	AddGameObject<CMeshField>(1);

	AddGameObject<CSelectItem>(2);
}

void CGame::Uninit()
{
	//リストに入っているゲームオブジェクトを削除
	CScene::Uninit();

	//テクスチャ + モデルアンロード
	CDEADTREE::Unload();
	CFriend::Unload();
	CEnemy::Unload();
	CBUNKER::Unload();
}

void CGame::Update()
{
	CScene::Update();	//リストに入っているゲームオブジェクトを呼び出す

	//Tボタンでステージテスト
	if (CInput::GetKeyTrigger('T'))
	{
		_mkdir("asset/testsavedata");	//テストセーブデータのフォルダを作成
		CScene::GetGameObject<CSAVE>(0)->TestData_Save();
		system("GM31.exe");
	}
}

void CGame::Draw()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGuizmo::BeginFrame();

	CScene::Draw();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}