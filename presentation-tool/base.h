#pragma once

#include "gameobject.h"

class CBase : public CGameObject
{
private:
	CModel*		m_Flag;			//Šøƒ‚ƒfƒ‹
	CCOLIDER_CIRCLE*	m_Zone;
public:
	CBase();
	~CBase() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Save(FILE* fp);
	void Load(FILE*fp, int line);
};