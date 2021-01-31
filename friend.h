#pragma once

#include "gameobject.h"

class CFriend : public CGameObject	//�p��(�C���w���^���X)
{
private:
	static CAnimationModel* m_Animodel;	//3D�A�j���[�V�������f���N���X
	D3DXVECTOR3		m_ModelRot;
	CSIGHT* m_Sight;			//�Ə�
	CWEAPON* m_Weapon;			//��������

	TEAM_NUMBER		m_TeamNumber;			//�������G���̎���

	char*	m_OldAnimationChara;	//�A�j���[�V�����̖��O�̋���
	char*	m_NowAnimationChara;	//���݂̃A�j���[�V�����̖��O
	float		m_Frame = 0;			//�A�j���[�V�����̃t���[��
	float	rate = 0;				//�A�j���[�V�����u�����h�̃��[�g

	//�w���p�[�֐�
	void Update_AI();

	void ChangeAnimation(char* Name);
public:
	CFriend() {}
	~CFriend() {}

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(m_Position),
			CEREAL_NVP(m_Rotation),
			CEREAL_NVP(m_Scale));
	}

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void LookEnemy(CEnemy *enemy);		//�v���C���[������
	void Death();
};