//=====================================
//
//  チュートリアルシーン
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
#include "fade.h"
#include "gamemaneger.h"
#include "Game.h"
#include "tutorial.h"

#include "gameobject.h"
#include "camera.h"
#include "meshfield.h"
#include "human.h"
#include "model.h"
#include "animationmodel.h"
#include "colider.h"
#include "sight.h"
#include "weapon.h"
#include "behavior.h"

#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "bunker.h"
#include "polygon.h"
#include "skydome.h"
#include "base.h"
#include "deadtree.h"

#include "explosion.h"
#include "smoke.h"
#include "tree.h"
#include "number.h"
#include "gauge.h"
#include "weapon2d.h"
#include "captureui.h"
#include "playerui.h"
#include "tutorial2D.h"

void CTutorial::Init()
{
	m_Clik = false;

	//テクスチャ + モデルロード
	CBullet::Load();			//弾のモデルを呼び出す
	CBUNKER::Load();			//バンカーのモデルを呼び出す
	CWEAPON::Load();			//銃のモデルを呼び出す
	CSMOKE::Load();				//煙の画像を呼び出す


	m_GameManeger = new CGAME_MANEGER;		
	m_GameManeger->Init(GAME_RULE_TUTORIAL);		//ルール設定

	//使うゲームオブジェクト呼び出し
	//カメラ0番 3Dモデル1番 3Dモデル(半透明のオブジェクト)2番 ビルボード(煙)の3番 2Dモデル4番
	AddGameObject<CCamera>(0);		//カメラ

	AddGameObject<CSKYDOME>(1);		//スカイドーム
	AddGameObject<CMeshField>(1)->flatworld();		//メッシュフィールド(チュートリアル様に真っ平にする)
	AddGameObject<CPlayer>(1)->SetPosition(D3DXVECTOR3(350.0f, 1.0f,  -200.0f));	//プレイヤー(チュートリアル用)

	AddGameObject<CBASE>(2)->SetPosition(D3DXVECTOR3(300.0f, 0.0f,-200.0f));		//拠点(チュートリアル用)

	AddGameObject<CWEAPON2D>(4);
	AddGameObject<CPLAYERUI>(4);

	CFADE::Fade_Start(false, 60);		//フェード(だんだんと画面に出る)
}

void CTutorial::Uninit()
{
	//リストに入っているゲームオブジェクトを削除
	CScene::Uninit();

	//テクスチャアンロード
	CSMOKE::Unload();
	CWEAPON::UnLoad();
	CBullet::Unload();
	CBUNKER::Unload();

	m_GameManeger->Uninit();
	delete m_GameManeger;

	StopSound();		//音楽と効果音を止める
}

void CTutorial::Update()
{
	CScene::Update();	//リストに入っているゲームオブジェクトを呼び出す

	//スペースキーで終わるようにする
	if (CInput::GetKeyTrigger(VK_SPACE))
	{
		m_Clik = true;
		CFADE::Fade_Start(true, 60);	//フェードをつける
	}

	m_GameManeger->Update();


	if (m_Clik == false) { return; }
	if (CFADE::Fade_IsFade() == false)
	{
		CManager::SetScene<CGame>();
	}
}