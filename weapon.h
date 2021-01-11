#pragma once

#include "gameobject.h"

class CWEAPON : public CGameObject	//�p��(�C���w���^���X)
{
private:
	//static CModel* m_Model;			//3D���f���N���X
	static CAnimationModel* m_AniModel;
	CGameObject* m_parent;		//�e�̃A�h���X������

	int Ammo;		//�e��
	int MaxAmmo;	//�ő吔
	int ReloadTime;	//���U����
	int NextShootTime;//�e���ߎ���

	char* m_OldAnimationChara;	//�A�j���[�V�����̖��O�̋���
	char* m_NowAnimationChara;	//���݂̃A�j���[�V�����̖��O
	float		m_Frame = 0;			//�A�j���[�V�����̃t���[��
	float	rate = 0;				//�A�j���[�V�����u�����h�̃��[�g

	bool isReload;	//���U����
	bool isNextShoot;	//�e�����߂Ă邩

	void NextShoot();	//���̒e���o��܂ł̏�

public:
	CWEAPON() {}
	~CWEAPON() {}

	static void Load();
	static void UnLoad();
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Reload();	//�đ��U
	void Shoot(D3DXVECTOR3 SPos, TEAM_NUMBER SetTeamNumber);	//�e����(�v���C���[�̍��W,�Ə��̍��W)

	int GetAmmo()	{ return Ammo; }
	int GetMaxAmmo(){ return MaxAmmo; }
	int GetReloadTime() { return ReloadTime; }
	bool GetNextShoot() { return isNextShoot; }
	void Setparent(CGameObject* object) { m_parent = object; }	//�Ə��̐e�̃A�h���X�̃Z�b�g
};