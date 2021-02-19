#pragma once

#include "gameobject.h"

class CFriendAIRoot;

class CFriend : public CGameObject	//継承(インヘリタンス)
{
private:
	static CAnimationModel* m_Animodel;	//3Dアニメーションモデルクラス
	D3DXVECTOR3		m_ModelRot;
	CSIGHT* m_Sight;			//照準
	CWEAPON* m_Weapon;			//所持武器
	CFriendAIRoot* m_AI;		//ビヘイビアツリー
	CGameObject* LockOnEnemy;		//現在ターゲットにしている敵の情報
	TEAM_NUMBER		m_TeamNumber;	//味方か敵かの識別

	char*	m_OldAnimationChara;	//アニメーションの名前の旧名
	char*	m_NowAnimationChara;	//現在のアニメーションの名前
	float	m_Frame = 0;			//アニメーションのフレーム
	float	rate = 0;				//アニメーションブレンドのレート
	bool	m_Death;				//死亡フラグ

	//ヘルパー関数
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

	void LookEnemy();			//狙っている敵の方向を見る
	void SetLockOnEnemy(CGameObject* enemy);		//ロックオンする敵をセット
	CGameObject* GetLockOnEnemy() {return LockOnEnemy;}
	void Death();
	void ChangeAnimation(char* Name);

	bool Shoot();			//攻撃する
	void Reload();			//銃を装填する
	bool isOverReload();	//装填完了したか
	bool isDeath() { return m_Death; }			//死んでいるか
};


//AIRoot
class CFriendAIRoot :public CNode
{
private:
	CFriend* parent;	//付属する味方
	int m_Index = m_Index;
public:
	void   Init(CFriend* parent);
	RESULT Update();
};

//ビヘイビアのセレクター
class CFriendSelector :public CNodeSelector
{
private:
	CFriend* m_parent;	//付属する味方
public:
	CFriendSelector(CFriend* parent);
	RESULT Update();
};

//ビヘイビアのシークエンス
class CFriendSequence :public CNodeSequence
{
private:
	CFriend* m_parent;	//付属する味方
public:
	CFriendSequence(CFriend* parent);
};

//ビヘイビアのノード(探す)
class CFriendSearchNode :public CNode
{
private:
	CFriend* m_parent;	//付属する味方
public:
	CFriendSearchNode(CFriend* parent);
	RESULT Update();
};

//ビヘイビアのノード(歩く)
class CFriendWalkNode :public CNode
{
private:
	CFriend* m_parent;	//付属する味方
public:
	CFriendWalkNode(CFriend* parent);
	RESULT Update();
};

//ビヘイビアのノード(撃つ)
class CFriendShootNode :public CNode
{
private:
	CFriend* m_parent;	//付属する味方
public:
	CFriendShootNode(CFriend* parent);
	RESULT Update();
};

//ビヘイビアのノード(リロード)
class CFriendReloadNode :public CNode
{
private:
	CFriend* m_parent;	//付属する味方
public:
	CFriendReloadNode(CFriend* parent);
	RESULT Update();
};