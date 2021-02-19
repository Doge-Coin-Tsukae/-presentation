#pragma once

#include "gameobject.h"

class CEnemyAIRoot;

class CEnemy : public CGameObject	//�p��(�C���w���^���X)
{
private:
	static CAnimationModel* m_Animodel;	//3D�A�j���[�V�������f���N���X
	D3DXVECTOR3		m_ModelRot;
	CSIGHT* m_Sight;			//�Ə�
	CWEAPON* m_Weapon;			//��������
	CEnemyAIRoot* m_AI;			//�r�w�C�r�A�c���[�œ���
	CGameObject* LockOnEnemy;			//���݃^�[�Q�b�g�ɂ��Ă���G�̏��
	TEAM_NUMBER		m_TeamNumber;			//�������G���̎���

	char*	m_OldAnimationChara;	//�A�j���[�V�����̖��O�̋���
	char*	m_NowAnimationChara;	//���݂̃A�j���[�V�����̖��O
	float	m_Frame = 0;			//�A�j���[�V�����̃t���[��
	float	rate = 0;				//�A�j���[�V�����u�����h�̃��[�g
	bool	m_Death;		//���S�t���O

	//�w���p�[�֐�
	void Update_AI();

public:
	CEnemy() {}
	~CEnemy() {}

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

	void LookPlayer();		//�v���C���[������
	void Death();
	
	bool Shoot();			//�U������
	void Reload();			//�e�𑕓U����
	bool isOverReload();	//���U����������
	bool isDeath() { return m_Death; }			//����ł��邩

	void SetLockOnEnemy(CGameObject* enemy) { LockOnEnemy = enemy; }		//���b�N�I������G���Z�b�g
	CGameObject* GetLockOnEnemy() { return LockOnEnemy; }

	void ChangeAnimation(char* Name);		//�A�j���[�V�����ύX
};

//AIRoot
class CEnemyAIRoot :public CNode
{
private:
	CEnemy* parent;	//�t������G
	int m_Index = m_Index;
public:
	void   Init(CEnemy* parent);
	RESULT Update();
};

//�r�w�C�r�A�̃Z���N�^�[
class CEnemySelector :public CNodeSelector
{
private:
	CEnemy* m_parent;	//�t������G
public:
	CEnemySelector(CEnemy* parent);
	RESULT Update();
};

//�r�w�C�r�A�̃V�[�N�G���X
class CEnemySequence :public CNodeSequence
{
private:
	CEnemy* m_parent;	//�t������G
public:
	CEnemySequence(CEnemy* parent);
};

//�r�w�C�r�A�̃m�[�h(�T��)
class CEnemySearchNode :public CNode
{
private:
	CEnemy* m_parent;	//�t������G
public:
	CEnemySearchNode(CEnemy* parent);
	RESULT Update();
};

//�r�w�C�r�A�̃m�[�h(����)
class CEnemyWalkNode :public CNode
{
private:
	CEnemy* m_parent;	//�t������G
public:
	CEnemyWalkNode(CEnemy* parent);
	RESULT Update();
};

//�r�w�C�r�A�̃m�[�h(����)
class CEnemyShootNode :public CNode
{
private:
	CEnemy* m_parent;	//�t������G
public:
	CEnemyShootNode(CEnemy* parent);
	RESULT Update();
};

//�r�w�C�r�A�̃m�[�h(�����[�h)
class CEnemyReloadNode :public CNode
{
private:
	CEnemy* m_parent;	//�t������G
public:
	CEnemyReloadNode(CEnemy* parent);
	RESULT Update();
};