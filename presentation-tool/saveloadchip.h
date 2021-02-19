#pragma once

#include "gameobject.h"

//------------------------------------------------------
//
//	�Z�[�u���[�h�{�^���̃`�b�v
//
//------------------------------------------------------


class CSaveLoadChip :public CGameObject
{
private:
	CChip *m_SaveLoadChip[2];	//�Z�[�u&���[�h�{�^��
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool ClickSaveLoad();
};