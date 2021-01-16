#include <list>
#include <vector>
#include <typeinfo>
#include<string>
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
#include "field.h"
#include "meshfield.h"
#include "human.h"
#include "model.h"
#include "carsor.h"
#include "colider.h"
#include "sight.h"
#include "weapon.h"
#include "base.h"
#include "player.h"
#include "enemy.h"
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
#include "selectitem.h"

void CGame::Init()
{
	//テクスチャ + モデルロード
	CBUNKER::Load();
	CEnemy::Load();
	CWEAPON::Load();
	CDEADTREE::Load();

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
	CWEAPON::UnLoad();
	CEnemy::Unload();
	CBUNKER::Unload();
}

void CGame::Update()
{
	CScene::Update();	//リストに入っているゲームオブジェクトを呼び出す
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