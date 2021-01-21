#pragma once

#include "gameobject.h"

class CTriangle : public CGameObject	//継承(インヘリタンス)
{
private:
	CModel* m_Model;			//3Dモデルクラス

public:
	CTriangle() {}
	~CTriangle() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();
};