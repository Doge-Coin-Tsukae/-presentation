#pragma once

#include "gameobject.h"

class CEnemyAIRoot;

class CEnemy : public CGameObject	//継承(インヘリタンス)
{
private:
	static CAnimationModel* m_Animodel;	//3Dアニメーションモデルクラス
	D3DXVECTOR3		m_ModelRot;
	CSIGHT* m_Sight;			//照準
	CWEAPON* m_Weapon;			//所持武器
	CEnemyAIRoot* m_AI;			//ビヘイビアツリーで動く
	CGameObject* LockOnEnemy;			//現在ターゲットにしている敵の情報
	TEAM_NUMBER		m_TeamNumber;			//味方か敵かの識別

	char*	m_OldAnimationChara;	//アニメーションの名前の旧名
	char*	m_NowAnimationChara;	//現在のアニメーションの名前
	float	m_Frame = 0;			//アニメーションのフレーム
	float	rate = 0;				//アニメーションブレンドのレート
	bool	m_Death;		//死亡フラグ

	//ヘルパー関数
	void Update_AI();

public:
	CEnemy() {}
	~CEnemy() {}

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

	void LookPlayer();		//プレイヤーを見る
	void Death();
	
	bool Shoot();			//攻撃する
	void Reload();			//銃を装填する
	bool isOverReload();	//装填完了したか
	bool isDeath() { return m_Death; }			//死んでいるか

	void SetLockOnEnemy(CGameObject* enemy) { LockOnEnemy = enemy; }		//ロックオンする敵をセット
	CGameObject* GetLockOnEnemy() { return LockOnEnemy; }

	void ChangeAnimation(char* Name);		//アニメーション変更
};

//AIRoot
class CEnemyAIRoot :public CNode
{
private:
	CEnemy* parent;	//付属する敵
	int m_Index = m_Index;
public:
	void   Init(CEnemy* parent);
	RESULT Update();
};

//ビヘイビアのセレクター
class CEnemySelector :public CNodeSelector
{
private:
	CEnemy* m_parent;	//付属する敵
public:
	CEnemySelector(CEnemy* parent);
	RESULT Update();
};

//ビヘイビアのシークエンス
class CEnemySequence :public CNodeSequence
{
private:
	CEnemy* m_parent;	//付属する敵
public:
	CEnemySequence(CEnemy* parent);
};

//ビヘイビアのノード(探す)
class CEnemySearchNode :public CNode
{
private:
	CEnemy* m_parent;	//付属する敵
public:
	CEnemySearchNode(CEnemy* parent);
	RESULT Update();
};

//ビヘイビアのノード(歩く)
class CEnemyWalkNode :public CNode
{
private:
	CEnemy* m_parent;	//付属する敵
public:
	CEnemyWalkNode(CEnemy* parent);
	RESULT Update();
};

//ビヘイビアのノード(撃つ)
class CEnemyShootNode :public CNode
{
private:
	CEnemy* m_parent;	//付属する敵
public:
	CEnemyShootNode(CEnemy* parent);
	RESULT Update();
};

//ビヘイビアのノード(リロード)
class CEnemyReloadNode :public CNode
{
private:
	CEnemy* m_parent;	//付属する敵
public:
	CEnemyReloadNode(CEnemy* parent);
	RESULT Update();
};