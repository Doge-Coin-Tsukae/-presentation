//�v���C���[���ʂ̕������N���X��������
#pragma once

enum TEAM_NUMBER{
	TEAM_FRIENDRY,
	TEAM_ENEMY,
};

//NPC�����ʉ�����
class Human : public CGameObject
{
	static CAnimationModel* m_Animodel;	//3D�A�j���[�V�������f���N���X
	D3DXVECTOR3		m_ModelRot;
	CSIGHT* m_Sight;			//�Ə�
	CWEAPON* m_Weapon;			//��������

	TEAM_NUMBER		m_TeamNumber;			//�������G���̎���

	char* m_OldAnimationChara;	//�A�j���[�V�����̖��O�̋���
	char* m_NowAnimationChara;	//���݂̃A�j���[�V�����̖��O
	float	m_Frame = 0;		//�A�j���[�V�����̃t���[��
	float	rate = 0;			//�A�j���[�V�����u�����h�̃��[�g
	bool	m_Death;			//���S�t���O

public:
	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};