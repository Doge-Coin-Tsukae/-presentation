#pragma once

#include "gameobject.h"

class CPLAYERUI : public  CGameObject
{
private:
	CGAUGE*				m_HpGauge;		//体力のゲージ
	CPolygon*			m_Sight;		//サイトの表示を行う
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};