//=====================================
//
//  ゲームルールとルール
//  written by Y.Okubo
//
//=====================================
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "title.h"
#include "human.h"

#include "polygon.h"
#include "model.h"
#include "animationmodel.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "player.h"
#include "base.h"
#include "vicordef.h"
#include "tutorial2D.h"

#include "gamemaneger.h"



//ルール(コンクエスト)
void CConquest::Init()
{
	m_deleted = false;
	m_Defeat = false;
	m_Victory = false;
}
void CConquest::Uninit()
{

}
void CConquest::Update()
{
	Conditions();	//勝敗条件をチェックする
	GameOver();		//シーンを変える処理

	//勝利条件を満たしたとき
	if (m_Victory == true)
	{
		
		return;
	}
	//敗北条件を満たしたとき
	if (m_Defeat == true)
	{
		
		return;
	}
}

void CConquest::GameOver()
{
	//勝敗が決まっていなければ処理終了
	if (m_Victory == false && m_Defeat == false) return;

	//フェード終わったら消す
	if (m_deleted == true)
	{
		if (CFADE::Fade_IsFade() == false)
		{
			StopSound();						//音を止める
			CManager::SetScene<CTitle>();		///タイトルに戻る
			return;
		}
	}

	Fade_On();		//フェードするか決める
}
void CConquest::Fade_On()
{
	//画面から勝敗の表示が消えたら
	CScene* scene = CManager::GetScene();
	VICORDEF* vic = scene->GetGameObject<VICORDEF>(4);

	//画面表示が消えていたら
	if (vic->GetDelete() == false) return;

	CFADE::SetTexture((char*)"asset/texture/fade.png");
	CFADE::Fade_Start(true, 90);
	m_deleted = true;
}

void CConquest::Conditions()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);
	std::vector<CBASE*> baseList = scene->GetGameObjects<CBASE>(2);

	//リセット
	for (int i = 0; i < 2; i++)
	{
		m_BaseCaptcha[i] = 0;
	}

	//敗北条件
	if (pPlayer->isDeath() == true)
	{
		scene->AddGameObject<VICORDEF>(4)->Set(false);
		m_Defeat = true;
		return;
	}


	//以下勝利条件
	int BaseCount = 0;
	for (CBASE* base : baseList)
	{
		if (base->GetTerritory() == FRIENDRY_ZONE) { m_BaseCaptcha[0]++; }
		if (base->GetTerritory() == ENEMY_ZONE) { m_BaseCaptcha[1]++; }
		BaseCount++;
	}
	//拠点全部取ったら勝ちにする
	if (m_BaseCaptcha[0] >= BaseCount)
	{
		scene->AddGameObject<VICORDEF>(4)->Set(true);
		m_Victory = true;
		return;
	}
}



//チュートリアルのルール
void CRULE_TUTORIAL::Init()
 {
	CScene* scene = CManager::GetScene();
	scene->AddGameObject<CTUTORIAL2D>(4);

	//変数初期化
	for (int i = 0; i < 6; i++)
	{
		m_Tutorial[i] = false;
	}
	m_NowTurorial = 0;
	m_Defeat = false;
	m_Victory = false;
}
void CRULE_TUTORIAL::Uninit()
{
}
void CRULE_TUTORIAL::Update()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);
	CBASE* pBase = scene->GetGameObject<CBASE>(2);
	CWEAPON* pWeapon = pPlayer->GetWeapon();

	Conditions();

	//現在の進行具合によって変える
	switch (m_NowTurorial)
	{
	case 0:
		//クリア条件満たしたら
		if (CInput::GetKeyPress('W'))						//前進
			LevelUp();	//段階を上げる
		break;

	case 1:
		//クリア条件満たしたら
		if (CInput::GetKeyPress(VK_RBUTTON))				//視点変更
			LevelUp();	//段階を上げる
		break;

	case 2:
		//クリア条件満たしたら
		if (CInput::GetKeyPress(VK_LBUTTON))				//発砲
			LevelUp();	//段階を上げる
		break;

	case 3:

		//クリア条件満たしたら
		if (pWeapon->GetAmmo() == pWeapon->GetMaxAmmo())	//現在の弾と最大弾数が同じになったら
			LevelUp();	//段階を上げる
		break;

	case 4:
		if (pBase->GetTerritory() == FRIENDRY_ZONE)		//拠点占領
			LevelUp();
		break;
	default:
		break;
	}
}
void CRULE_TUTORIAL::Conditions()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	//チュートリアルの最後をクリアしたら終わる
	if(m_Tutorial[4] == true)
		m_Victory = true;

	//チュートリアルで死んだら終わる
	if (pPlayer->isDeath() == true)
		m_Defeat = true;
}
void CRULE_TUTORIAL::LevelUp()
{
	m_Tutorial[m_NowTurorial] = true;		//現在のチュートリアルをクリアにする
	m_NowTurorial++;						//チュートリアルを一段回上げる

	CScene* scene = CManager::GetScene();
	CTUTORIAL2D* ptuto = scene->GetGameObject<CTUTORIAL2D>(4);

	//現在の進行具合によってテクスチャを変える
	switch (m_NowTurorial)
	{
	case 1:
		ptuto->ChangeTexture((char*)"asset/texture/tutorial/tutorial_viewpoint.png");
		break;
	case 2:
		ptuto->ChangeTexture((char*)"asset/texture/tutorial/tutorial_shoot.png");
		break;
	case 3:
		ptuto->ChangeTexture((char*)"asset/texture/tutorial/tutorial_reload.png");
		break;
	case 4:
		ptuto->ChangeTexture((char*)"asset/texture/tutorial/tutorial_captcha.png");
		break;
	case 5:
		ptuto->ChangeTexture((char*)"asset/texture/tutorial/tutorial_end.png");
		break;
	default:
		break;
	}
}

//ルールを束ねるマネージャー
void CGAME_MANEGER::Init(GAME_RULE SetRule)
{
	m_GameMode = SetRule;

	//選ばれたルールによって代入するクラスを変更する
	switch (m_GameMode)
	{
	case GAME_RULE_CONQUEST:
		m_Rule = new CConquest;
		break;
	case GAME_RULE_TUTORIAL:
		m_Rule = new CRULE_TUTORIAL;
		break;
	default:
		break;
	}

	m_Rule->Init();
}
void CGAME_MANEGER::Uninit()
{
	m_Rule->Uninit();
	delete m_Rule;
}
void CGAME_MANEGER::Update()
{
	m_Rule->Update();
}