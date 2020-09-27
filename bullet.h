#pragma once

#include "gameobject.h"

class CBullet : public CGameObject
{
private:
	static CModel* m_Model;		//3D���f���N���X
	CCOLIDER_CIRCLE*	m_Zone;		//�����蔻��

	D3DXVECTOR3 m_Dir;
	float DeleteTime;		//�I�u�W�F�N�g��������
	TEAM_NUMBER m_TeamNumber;	//�������l���G������������
public:
	CBullet() {}
	~CBullet() {}

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Update_Collision();
	void Draw();

	void Set(D3DXVECTOR3 SetPos, D3DXVECTOR3 SetSight, TEAM_NUMBER SetNUMBER);
};
