#pragma once

#include "gameobject.h"

class CWEAPON2D : public  CGameObject
{
private:
	CNUMBER*			m_MaxAnmo[2];		//�ő�e��
	CNUMBER*			m_Anmo[2];			//���݂̒e��

	CPolygon*			m_slash;			//�X���b�V��
	CPolygon*			m_Under;			//�e�̊G
	CGAUGE*				m_Gauge;			//�e�̃Q�[�W

	void Advance();		//�񌅕\��
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void ChengeWeaponTexture(int id);

};