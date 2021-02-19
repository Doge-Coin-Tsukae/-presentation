//プレイヤー共通の部分をクラス化したい
#pragma once

#include "gameobject.h"

enum TEAM_NUMBER{
	TEAM_FRIENDRY,
	TEAM_ENEMY,
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