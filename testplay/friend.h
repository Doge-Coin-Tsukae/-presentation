#pragma once

#include "gameobject.h"

class CFriendAIRoot;

class CFriend : public CGameObject	//�p��(�C���w���^���X)
{
private:
	static CAnimationModel* m_Animodel;	//3D�A�j���[�V�������f���N���X
	D3DXVECTOR3		m_ModelRot;
	CSIGHT* m_Sight;			//�Ə�
	CWEAPON* m_Weapon;			//��������
	CFriendAIRoot* m_AI;		//�r�w�C�r�A�c���[
	CGameObject* LockOnEnemy;		//���݃^�[�Q�b�g�ɂ��Ă���G�̏��
	TEAM_NUMBER		m_TeamNumber;	//�������G���̎���

	char*	m_OldAnimationChara;	//�A�j���[�V�����̖��O�̋���
	char*	m_NowAnimationChara;	//���݂̃A�j���[�V�����̖��O
	float	m_Frame = 0;			//�A�j���[�V�����̃t���[��
	float	rate = 0;				//�A�j���[�V�����u�����h�̃��[�g
	bool	m_Death;				//���S�t���O

	//�w���p�[�֐�
	void Update_AI();

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

	void LookEnemy();			//�_���Ă���G�̕���������
	void SetLockOnEnemy(CGameObject* enemy);		//���b�N�I������G���Z�b�g
	CGameObject* GetLockOnEnemy() {return LockOnEnemy;}
	void Death();
	void ChangeAnimation(char* Name);

	bool Shoot();			//�U������
	void Reload();			//�e�𑕓U����
	bool isOverReload();	//���U����������
	bool isDeath() { return m_Death; }			//����ł��邩
};


//AIRoot
class CFriendAIRoot :public CNode
{
private:
	CFriend* parent;	//�t�����閡��
	int m_Index = m_Index;
public:
	void   Init(CFriend* parent);
	RESULT Update();
};

//�r�w�C�r�A�̃Z���N�^�[
class CFriendSelector :public CNodeSelector
{
private:
	CFriend* m_parent;	//�t�����閡��
public:
	CFriendSelector(CFriend* parent);
	RESULT Update();
};

//�r�w�C�r�A�̃V�[�N�G���X
class CFriendSequence :public CNodeSequence
{
private:
	CFriend* m_parent;	//�t�����閡��
public:
	CFriendSequence(CFriend* parent);
};

//�r�w�C�r�A�̃m�[�h(�T��)
class CFriendSearchNode :public CNode
{
private:
	CFriend* m_parent;	//�t�����閡��
public:
	CFriendSearchNode(CFriend* parent);
	RESULT Update();
};

//�r�w�C�r�A�̃m�[�h(����)
class CFriendWalkNode :public CNode
{
private:
	CFriend* m_parent;	//�t�����閡��
public:
	CFriendWalkNode(CFriend* parent);
	RESULT Update();
};

//�r�w�C�r�A�̃m�[�h(����)
class CFriendShootNode :public CNode
{
private:
	CFriend* m_parent;	//�t�����閡��
public:
	CFriendShootNode(CFriend* parent);
	RESULT Update();
};

//�r�w�C�r�A�̃m�[�h(�����[�h)
class CFriendReloadNode :public CNode
{
private:
	CFriend* m_parent;	//�t�����閡��
public:
	CFriendReloadNode(CFriend* parent);
	RESULT Update();
};