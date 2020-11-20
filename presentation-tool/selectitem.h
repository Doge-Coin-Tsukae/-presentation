#pragma once

#include "gameobject.h"

class CSelectItem :public CGameObject
{
private:
	CGameObject *m_EditGameObject;	//���ݕҏW���̃Q�[���I�u�W�F�N�g

	CPolygon *m_under;			//���n
	CSelectpointer *m_pointer;	//���ݎw���Ă���J�[�\���̃{�^��
	CChip *m_chip[4][2];		//�A�C�e����؂�ւ���{�^��
	CMODECHIP *m_modechip[2];	//�ҏW���[�h��ؑփ{�^��
	CCARSOR *m_carsor;			//�J�[�\��

	D3DXVECTOR2 min;
	D3DXVECTOR2 max;

	int NowMode;			//���݂̕ҏW���[�h

	bool click;

	bool ClickItemBox();	//�A�C�e���{�^�����N���b�N�����Ƃ�
	bool ClikEditBox();		//�ҏW�{�^�����N���b�N�����Ƃ�
	void WorldObject();		//���[���h���W�ɃI�u�W�F�N�g��z�u����
	void UpdateControll();
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};