#pragma once

#include "gameobject.h"

#define MAXSHADER  1

class CPlayer : public CGameObject	//�p��(�C���w���^���X)
{
private:
	CAnimationModel* m_Animodel;	//3D�A�j���[�V�������f���N���X
	CSIGHT* m_Sight;			//�Ə�
	CWEAPON* m_Weapon;			//��������
	OBB*  m_Obb;
	D3DXVECTOR3		m_ModelRot;		//���f���̊p�x(���f�����^�������ɂȂ�Ȃ�������ꂽ)
	D3DXVECTOR3		m_Velocity;		//�s������W
	TEAM_NUMBER		m_TeamNumber;	//�������G���̎���
	int				m_Hp;			//�̗�
	float			m_speed;		//���̑���
	bool			m_Death;		//���S�t���O
	bool			m_ready;		//�\���Ă��邩
	char*			m_OldAnimationChara;	//�A�j���[�V�����̖��O�̋���
	char*			m_NowAnimationChara;	//���݂̃A�j���[�V�����̖��O
	float m_Frame = 0;				//�A�j���[�V�����̃t���[��
	float rate = 0;					//�A�j���[�V�����u�����h�̃��[�g

	//���[�h
	int m_Weapontype;
	std::string m_Modelpass;

	void Update_Controll();		//�L�[����
public:
	CPlayer(){}
	~CPlayer(){}

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(m_Position),
			CEREAL_NVP(m_Rotation),
			CEREAL_NVP(m_Scale),
			CEREAL_NVP(m_Weapontype),
			CEREAL_NVP(m_Modelpass));
	}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Death();		//���S����
	void Damage();		//�_���[�W
	void ChangeAnimation(char* Name);		//�A�j���[�V�����ύX

	void ResetVelocity() { m_Velocity = m_Position; }
	CWEAPON* GetWeapon(){return m_Weapon;}
	bool	 isDeath() { return m_Death; }
	int Getm_Hp() { return m_Hp; }
	int GetWeapontype() { return m_Weapontype; }
	void FileLoad();	//�Z�[�u�t�@�C�����烍�[�h����
};