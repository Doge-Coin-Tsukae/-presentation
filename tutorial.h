#pragma once

#include "scene.h"

class CTutorial : public CScene
{
private:
	CGAME_MANEGER* m_GameManeger;	//�Q�[���̃��[���̃N���X
	bool m_Clik;					//�X�y�[�X�L�[�������ꂽ��

public:
	void Init();
	void Uninit();
	void Update();
	//draw�͉��������Ȃ��ꍇ�AScene����Ăяo�����B
};