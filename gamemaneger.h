#pragma once

#include "gameobject.h"

//���[���̗񋓌^
enum GAME_RULE
{
	GAME_RULE_CONQUEST,		//�R���N�G�X�g
	GAME_RULE_TUTORIAL,		//�`���[�g���A��
};

//���[���̊��N���X
class CRule :public CGameObject
{
protected:
	virtual void Conditions() {}	//���s����

	bool m_Defeat;		//�s�k�����𖞂������Ƃ�
	bool m_Victory;		//���������𖞂������Ƃ�

public:
	virtual void Init(){}
	virtual void Uninit() {}
	virtual void Update() {}
};


//���[���N���X(�������)
//�R���N�G�X�g
class CConquest :public CRule
{
private:
	bool m_deleted;		//��ʕ\�����폜���ꂽ��

	int  m_BaseCaptcha[2];

	void 	Conditions();	//���s����
	void	GameOver();		//�Q�[�����I�����Ď��̃V�[���Ɉڍs
	void	Fade_On();		//�t�F�[�h�����邩
public:
	void Init();
	void Uninit();
	void Update();
};

//�`���[�g���A��
class CRULE_TUTORIAL :public CRule
{
private:
	bool m_Tutorial[6];	//�ڕW�B����
	int m_NowTurorial;	//���݂̃`���[�g���A���̏��

	void 	Conditions();	//���s����
	void	LevelUp();		//�`���[�g���A���̒i�K���グ��
public:
	void Init();
	void Uninit();
	void Update();
};



//�Q�[�����Ɏ�������v���O����(���[��������i�[)
class CGAME_MANEGER : public CGameObject
{
private:
	CRule		*m_Rule;			//���[���N���X������
	GAME_RULE    m_GameMode;		//�Q�[�����[�h������enum
public:
	void Init(GAME_RULE SetRule);
	void Uninit();
	void Update();
};
