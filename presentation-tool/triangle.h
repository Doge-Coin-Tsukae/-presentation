#pragma once

#include "gameobject.h"

class CTriangle : public CGameObject	//�p��(�C���w���^���X)
{
private:
	CModel* m_Model;			//3D���f���N���X

public:
	CTriangle() {}
	~CTriangle() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();
};