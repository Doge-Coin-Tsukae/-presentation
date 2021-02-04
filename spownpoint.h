#pragma once
#include "gameobject.h"

enum SPOWNTYPE
{
	NONE_SPOWN,			//�ǂ���̗̒n�ł͂Ȃ�
	FRIENDRY_SPOWN,		//�F�R�̗̒n
	ENEMY_SPOWN,			//�G�̗̒n
};

class CSpownPoint : public CGameObject	//�p��(�C���w���^���X)
{
private:
	int			m_spowninterval = 1000;	//�X�|�[���Ԋu
	int			m_time;			//���݂̎���
	int			m_Max;			//���(-1�̏ꍇ�A��������)
	int			m_SpownedNum;	//��������
	bool		m_Spownlicense;	//�������Ƃ������邩
	SPOWNTYPE	m_SpownType;	//�G��������
	CModel* m_Model;			//�����f��

	void Spown();
	bool SpownConditions();		//�X�|�[���̏���(true�̎��A�����悤��)
public:
	CSpownPoint() {}
	~CSpownPoint() {}

	//cerial�Ń��[�h���鍀��
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(m_Position),
			CEREAL_NVP(m_Rotation),
			CEREAL_NVP(m_Scale),
			CEREAL_NVP(m_SpownType),
			CEREAL_NVP(m_Max),
			CEREAL_NVP(m_Spownlicense));
	}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	SPOWNTYPE GetTerritory() { return m_SpownType; }
	void	  SetSpowntype(SPOWNTYPE set) { m_SpownType = set; }
	void	  ChengeSpownlicense() { m_Spownlicense = 1 - m_Spownlicense; }		//���ݒ�̔��]
};