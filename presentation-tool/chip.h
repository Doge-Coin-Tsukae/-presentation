#pragma once

#include "gameobject.h"

class CChip:public CGameObject
{
private:
	int id;			//オブジェクトの種類
	CSplitPolygon *m_polygon;
	D3DXVECTOR2 m_Size;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool Colision(POINT pos);
	void SetPolygon(char* name, D3DXVECTOR2 Size, D3DXVECTOR2 Split, D3DXVECTOR2 Splitend);
};