#pragma once

#include "gameobject.h"

class CEnemy : public CGameObject	//�p��(�C���w���^���X)
{
private:
	static CModel* m_Model;			//3D���f���N���X
	CSIGHT* m_Sight;			//�Ə�
	CWEAPON* m_Weapon;			//��������

	TEAM_NUMBER		m_TeamNumber;			//�������G���̎���

	//�w���p�[�֐�
	void Update_AI();
public:
	CEnemy() {}
	~CEnemy() {}

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void LookPlayer();		//�v���C���[������
};