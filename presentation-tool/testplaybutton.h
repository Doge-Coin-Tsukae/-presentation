#pragma once

#include "gameobject.h"

//------------------------------------------------------
//
//	ここを押すとテストプレイ
//
//------------------------------------------------------

class CTestPlayButton :public CGameObject
{
private:
	CMovePolygon *m_polygon;	//
	D3DXVECTOR2 m_Size;			//

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool Colision(POINT pos);
};


//関数宣言
void ClickTestBotton();		//テストモードを起動する