#pragma once

#include "gameobject.h"

//���_�̐�̌�ɕ\�����錾�t
class CCAPTUREUI :public CGameObject
{
private:
	CPolygon *Line;

	int DeleteTime;			//�I�u�W�F�N�g���폜�����܂ł̎���
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

//���_�ɐN�������Ƃ��̐�̃Q�[�W
class CCAPTUREGAUGE :public CGameObject
{
private:
	CGAUGE *m_Gauge;	//�\�������錾�t
	CBASE *m_parent;	//�e

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Setparent(CBASE* object) { m_parent = object; }		//�e�̐ݒ�
};