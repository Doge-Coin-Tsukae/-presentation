#pragma once

#include "gameobject.h"

class CWEAPON : public CGameObject	//�p��(�C���w���^���X)
{
protected:
	int Ammo;		//�e��
	int MaxAmmo;	//�ő吔
	int ReloadTime;	//���U����
	int NextShootTime;//�e���ߎ���

	int MaxReloadTime;
	int MaxNextShootTime;
private:

	static CAnimationModel* m_AniModel;		//3D���f��
	CGameObject* m_parent;		//�e�̃A�h���X������

	char* m_OldAnimationChara;	//�A�j���[�V�����̖��O�̋���
	char* m_NowAnimationChara;	//���݂̃A�j���[�V�����̖��O
	float	m_Frame = 0;			//�A�j���[�V�����̃t���[��
	float	rate = 0;				//�A�j���[�V�����u�����h�̃��[�g

	bool isReload;	//���U����
	bool isNextShoot;	//�e�����߂Ă邩

	void NextShoot();	//���̒e���o��܂ł̏���

public:
	CWEAPON() {}
	~CWEAPON() {}

	static void Load();
	static void UnLoad();
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	void Reload();	//�đ��U
	void Shoot(D3DXVECTOR3 SPos, TEAM_NUMBER SetTeamNumber);	//�e����(�v���C���[�̍��W,�Ə��̍��W)

	int GetAmmo()	{ return Ammo; }
	int GetMaxAmmo(){ return MaxAmmo; }
	int GetReloadTime() { return ReloadTime; }
	bool GetNextShoot() { return isNextShoot; }
	void Setparent(CGameObject* object) { m_parent = object; }	//�Ə��̐e�̃A�h���X�̃Z�b�g
};