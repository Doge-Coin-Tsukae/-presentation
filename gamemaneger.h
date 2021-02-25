#pragma once

#include "gameobject.h"

//ルールの列挙型
enum GAME_RULE
{
	GAME_RULE_CONQUEST,		//コンクエスト
	GAME_RULE_TUTORIAL,		//チュートリアル
};

//ルールの基底クラス
class CRule :public CGameObject
{
protected:
	virtual void Conditions() {}	//勝敗判定

	bool m_Defeat;		//敗北条件を満たしたとき
	bool m_Victory;		//勝利条件を満たしたとき

public:
	virtual void Init(){}
	virtual void Uninit() {}
	virtual void Update() {}
};


//ルールクラス(複数作る)
//コンクエスト
class CConquest :public CRule
{
private:
	bool m_deleted;		//画面表示が削除されたか

	int  m_BaseCaptcha[2];

	void 	Conditions();	//勝敗判定
	void	GameOver();		//ゲームを終了して次のシーンに移行
	void	Fade_On();		//フェードをつけるか
public:
	void Init();
	void Uninit();
	void Update();
};

//チュートリアル
class CRULE_TUTORIAL :public CRule
{
private:
	bool m_Tutorial[6];	//目標達成数
	int m_NowTurorial;	//現在のチュートリアルの場面

	void 	Conditions();	//勝敗判定
	void	LevelUp();		//チュートリアルの段階を上げる
public:
	void Init();
	void Uninit();
	void Update();
};



//ゲーム側に実装するプログラム(ルールをする格納)
class CGAME_MANEGER : public CGameObject
{
private:
	CRule		*m_Rule;			//ルールクラスを入れる
	GAME_RULE    m_GameMode;		//ゲームモードを入れるenum
public:
	void Init(GAME_RULE SetRule);
	void Uninit();
	void Update();
};
