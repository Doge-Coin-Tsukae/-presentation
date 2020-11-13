#pragma once

#include "gameobject.h"

class CSelectItem :public CGameObject
{
private:
	CPolygon *m_under;			//下地
	CSelectpointer *m_pointer;	//現在指しているカーソルのボタン
	CChip *m_chip[4][2];		//アイテムを切り替えるボタン
	CMODECHIP *m_modechip[2];
	CCARSOR *m_carsor;

	D3DXVECTOR2 min;
	D3DXVECTOR2 max;

	bool click;

	bool ClickItemBox();
	void WorldObject();
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};