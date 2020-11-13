#pragma once

#include "gameobject.h"

class CDEADTREE : public CGameObject
{
private:
	static CModel* m_Model;		//3D���f���N���X
	AABB m_Colider;
public:
	CDEADTREE() {}
	~CDEADTREE() {}

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
	AABB GetColider() { return m_Colider; }
};