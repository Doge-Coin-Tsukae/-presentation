#pragma once

#include "gameobject.h"

class CWEAPON2D : public  CGameObject
{
private:
	CNUMBER*			m_MaxAnmo[2];		//Å‘å’e”
	CNUMBER*			m_Anmo[2];			//Œ»İ‚Ì’e”

	CPolygon*			m_slash;			//ƒXƒ‰ƒbƒVƒ…
	CPolygon*			m_Under;			//e‚ÌŠG
	CGAUGE*				m_Gauge;			//’e‚ÌƒQ[ƒW

	void Advance();		//“ñŒ…•\¦
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void ChengeWeaponTexture(int id);

};