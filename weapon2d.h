#pragma once

#include "gameobject.h"

class CWEAPON2D : public  CGameObject
{
private:
	CNUMBER*			m_MaxAnmo[2];		//最大弾数
	CNUMBER*			m_Anmo[2];			//現在の弾数

	CPolygon*			m_slash;			//スラッシュ
	CPolygon*			m_Under;			//銃の絵
	CGAUGE*				m_Gauge;			//弾のゲージ

	void Advance();		//二桁表示
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void ChengeWeaponTexture(int id);

};