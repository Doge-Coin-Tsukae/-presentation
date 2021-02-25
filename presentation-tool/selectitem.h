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
	CSaveLoadChip *m_SaveLoadChip;
	CTestPlayButton* m_TestPlayButton;
	CTriangle* m_Triangle;
	CSetImGui* m_SetImGui;

	D3DXVECTOR2 min;
	D3DXVECTOR2 max;

	int NowMode;			//���݂̕ҏW���[�h

	bool click;
	bool isEnemy;			//�ݒu�L�����͓GNPC�Ȃ̂�?

	bool ClickItemBox();	//�A�C�e���{�^�����N���b�N�����Ƃ�
	bool ClikEditBox();		//�ҏW�{�^�����N���b�N�����Ƃ�
	void ClickColider();	//�Q�[���I�u�W�F�N�g�ƃJ�[�\���̓����蔻��
	void WorldObject();		//���[���h���W�ɃI�u�W�F�N�g��z�u����
	void UpdateControll();	//input����
	void ImGuiSetMode();

	void SetObject();		//�ݒu����I�u�W�F�N�g�ݒ�
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};