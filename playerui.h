#pragma once

#include "gameobject.h"

class CPLAYERUI : public  CGameObject
{
private:
	CGAUGE*				m_HpGauge;		//�̗͂̃Q�[�W
	CPolygon*			m_Sight;		//�T�C�g�̕\�����s��
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};