#pragma once

#include "gameobject.h"

class Title_Effect_Manager : public CGameObject	//�p��(�C���w���^���X)
{
private:
	CShellExplosion* m_ShellExplosion[5];

public:
	Title_Effect_Manager() {}
	~Title_Effect_Manager() {}

	void Init();
	void Uninit();
	void Update();
};