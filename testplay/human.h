//�v���C���[���ʂ̕������N���X��������
#pragma once

#include "gameobject.h"

enum TEAM_NUMBER{
	TEAM_FRIENDRY,
	TEAM_ENEMY,
};

//NPC�����ʉ�����
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