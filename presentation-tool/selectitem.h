#pragma once

#include "gameobject.h"

class CSelectItem :public CGameObject
{
private:
	CPolygon *m_under;
	CSelectpointer *m_pointer;
	CChip *m_chip[4][2];		//ƒ{ƒ^ƒ“

	D3DXVECTOR2 min;
	D3DXVECTOR2 max;

	bool click;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};