//=====================================
//
//  ゲームシーン
//  written by Y.Okubo
//
//=====================================
#include <list>
#include <vector>
#include <typeinfo>
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "sound.h"
#include "input.h"
#include "scene.h"
#include "fade.h"
#include "gamemaneger.h"
#include "Game.h"
#include "Result.h"

#include "gameobject.h"
#include "load.h"
#include "camera.h"
#include "meshfield.h"
#include "animationmodel.h"
#include "human.h"
#include "model.h"
#include "colider.h"
#include "behavior.h"
#include "sight.h"
#include "weapon.h"

#include "player.h"
#include "enemy.h"
#include "friend.h"
#include "enemycommander.h"
#include "bullet.h"
#include "bunker.h"
#include "polygon.h"
#include "skydome.h"
#include "base.h"
#include "deadtree.h"
#include "spownpoint.h"

#include "explosion.h"
#include "smoke.h"
#include "tree.h"
#include "number.h"
#include "gauge.h"
#include "weapon2d.h"
#include "captureui.h"
#include "playerui.h"

void CGame::Init()
{
	//テクスチャ + モデルロード
	CBullet::Load();	//弾のモデルを呼び出す
	CCOLIDER_CIRCLE::Load();
	CBUNKER::Load();	//バンカーのモデルを呼び出す
	CEnemy::Load();		//敵のモデルを呼び出す
	CFriend::Load();
	CWEAPON::Load();	//銃のモデルを呼び出す
	CDEADTREE::Load();	//枯れ木のモデルを呼び出す
	CSMOKE::Load();		//煙の画像を呼び出す
	CExplosion::Load();

	m_GameManeger = new CGAME_MANEGER;
	m_GameManeger->Init(GAME_RULE_CONQUEST);

	//使うゲームオブジェクト呼び出し
	//カメラ0番 3Dモデル1番 3Dモデル(当たり判定のやつ)2番 ビルボード(煙)の3番 2Dモデル4番
	AddGameObject<CCamera>(0);		//カメラ

	AddGameObject<CLOAD>(0)->Data_Load();	//データのロード

	AddGameObject<CSKYDOME>(1);		//スカイドーム
	AddGameObject<CMeshField>(1);	//地面
	AddGameObject<CSpownPoint>(1)->SetPosition(D3DXVECTOR3(95,0, -132));
	AddGameObject<CWEAPON2D>(4);
	AddGameObject<CPLAYERUI>(4);
	AddGameObject<CENEMY_COMMANDER>(4);

	//PlaySound(SOUND_BGM_BGM002);

	CFADE::SetTexture((char*)"asset/texture/fade.png");
	CFADE::Fade_Start(false,60,D3DCOLOR());
}

void CGame::Uninit()
{
	//リストに入っているゲームオブジェクトを削除
	CScene::Uninit();

	//テクスチャアンロード
	CDEADTREE::Unload();
	CExplosion::Unload();
	CSMOKE::Unload();
	CWEAPON::UnLoad();
	CFriend::Unload();
	CEnemy::Unload();
	CBUNKER::Unload();
	CCOLIDER_CIRCLE::Unload();
	CBullet::Unload();

	m_GameManeger->Uninit();
	delete m_GameManeger;

	StopSound();
}

void CGame::Update()
{
	CScene::Update();	//リストに入っているゲームオブジェクトを呼び出す

	m_GameManeger->Update();
}