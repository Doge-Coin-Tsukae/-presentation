#pragma once

#include "gameobject.h"

class CSelectpointer :public CGameObject
{
private:
	CPolygon *m_point;

	D3DXVECTOR2 Pointpos;	//���݂̃|�C���^�̈ʒu

	bool click;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};