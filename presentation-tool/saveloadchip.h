#pragma once

#include "gameobject.h"

//------------------------------------------------------
//
//	セーブロードボタンのチップ
//
//------------------------------------------------------


class CSaveLoadChip :public CGameObject
{
private:
	CChip *m_SaveLoadChip[2];	//セーブ&ロードボタン
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool ClickSaveLoad();
};