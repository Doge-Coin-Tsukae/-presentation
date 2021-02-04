//プレイヤー共通の部分をクラス化したい
#pragma once

enum TEAM_NUMBER{
	TEAM_FRIENDRY,
	TEAM_ENEMY,
};

//NPCを共通化する
class Human : public CGameObject
{
	static CAnimationModel* m_Animodel;	//3Dアニメーションモデルクラス
	D3DXVECTOR3		m_ModelRot;
	CSIGHT* m_Sight;			//照準
	CWEAPON* m_Weapon;			//所持武器

	TEAM_NUMBER		m_TeamNumber;			//味方か敵かの識別

	char* m_OldAnimationChara;	//アニメーションの名前の旧名
	char* m_NowAnimationChara;	//現在のアニメーションの名前
	float	m_Frame = 0;		//アニメーションのフレーム
	float	rate = 0;			//アニメーションブレンドのレート
	bool	m_Death;			//死亡フラグ

public:
	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};