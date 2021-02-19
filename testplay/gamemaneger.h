#pragma once

#include "gameobject.h"

enum GAME_RULE
{
	GAME_RULE_CONQUEST,
	GAME_RULE_DEATHMATH,
	GAME_RULE_TUTORIAL,
};

//���[���N���X(�������)
//�R���N�G�X�g
class CConquest :public CGameObject
{
private:
	bool m_deleted;		//��ʕ\�����폜���ꂽ��
	bool m_Defeat;		//�s�k�����𖞂������Ƃ�
	bool m_Victory;		//���������𖞂������Ƃ�
	int  m_BaseCaptcha[2];

	void 	VictoryOrDefeatConditions();	//���s����
public:
	void Init();
	void Uninit();
	void Update();
};

//�Q�[�����Ɏ�������v���O����(���[��������i�[)
class CGAME_MANEGER : public CGameObject
{
private:
	CGameObject *m_Rule;			//���[���N���X������
	GAME_RULE    m_GameMode;		//�Q�[�����[�h������enum
public:
	void Init(GAME_RULE SetRule);
	void Uninit();
	void Update();
};
