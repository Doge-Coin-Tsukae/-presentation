#pragma once

#include "gameobject.h"

//------------------------------------------------------
//
//	�����������ƃe�X�g�v���C
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


//�֐��錾
void ClickTestBotton();		//�e�X�g���[�h���N������