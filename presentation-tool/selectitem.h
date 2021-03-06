#pragma once

#include "gameobject.h"

class CSelectItem :public CGameObject
{
private:
	CGameObject *m_EditGameObject;	//現在編集中のゲームオブジェクト

	CPolygon *m_under;			//下地
	CSelectpointer *m_pointer;	//現在指しているカーソルのボタン
	CChip *m_chip[4][2];		//アイテムを切り替えるボタン
	CMODECHIP *m_modechip[2];	//編集モードを切替ボタン
	CCARSOR *m_carsor;			//カーソル
	CSaveLoadChip *m_SaveLoadChip;
	CTestPlayButton* m_TestPlayButton;
	CTriangle* m_Triangle;
	CSetImGui* m_SetImGui;

	D3DXVECTOR2 min;
	D3DXVECTOR2 max;

	int NowMode;			//現在の編集モード

	bool click;
	bool isEnemy;			//設置キャラは敵NPCなのか?

	bool ClickItemBox();	//アイテムボタンをクリックしたとき
	bool ClikEditBox();		//編集ボタンをクリックしたとき
	void ClickColider();	//ゲームオブジェクトとカーソルの当たり判定
	void WorldObject();		//ワールド座標にオブジェクトを配置する
	void UpdateControll();	//input処理
	void ImGuiSetMode();

	void SetObject();		//設置するオブジェクト設定
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};