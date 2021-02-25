#pragma once

#include "gameobject.h"

//NPCの所属
enum TEAM_NUMBER{
	TEAM_FRIENDRY,		//味方チーム
	TEAM_ENEMY,			//敵チーム
};

//NPCを共通化する
class Human : public CGameObject
{
	void ChangeAnimation(char* Name);

protected:
	virtual void Update_AI() {}
public:
	static void Load();
	static void Unload();

	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	virtual void Death();
};