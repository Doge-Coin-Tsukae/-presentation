#pragma once

#include "gameobject.h"

class CWEAPON : public CGameObject	//継承(インヘリタンス)
{
protected:
	int Ammo;		//弾数
	int MaxAmmo;	//最大数
	int ReloadTime;	//装填時間
	int NextShootTime;//弾込め時間

	int MaxReloadTime;
	int MaxNextShootTime;
private:

	static CAnimationModel* m_AniModel;		//3Dモデル
	CGameObject* m_parent;		//親のアドレスを入れる

	char* m_OldAnimationChara;	//アニメーションの名前の旧名
	char* m_NowAnimationChara;	//現在のアニメーションの名前
	float	m_Frame = 0;			//アニメーションのフレーム
	float	rate = 0;				//アニメーションブレンドのレート

	bool isReload;	//装填中か
	bool isNextShoot;	//弾を込めてるか

	void NextShoot();	//次の弾が出るまでの処理

public:
	CWEAPON() {}
	~CWEAPON() {}

	static void Load();
	static void UnLoad();
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	void Reload();	//再装填
	void Shoot(D3DXVECTOR3 SPos, TEAM_NUMBER SetTeamNumber);	//弾発射(プレイヤーの座標,照準の座標)

	int GetAmmo()	{ return Ammo; }
	int GetMaxAmmo(){ return MaxAmmo; }
	int GetReloadTime() { return ReloadTime; }
	bool GetNextShoot() { return isNextShoot; }
	void Setparent(CGameObject* object) { m_parent = object; }	//照準の親のアドレスのセット
};