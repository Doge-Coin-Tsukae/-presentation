#pragma once

#include "gameobject.h"

class CFriend : public CGameObject	//継承(インヘリタンス)
{
private:
	static CAnimationModel* m_Animodel;	//3Dアニメーションモデルクラス
	D3DXVECTOR3		m_ModelRot;
	CSIGHT* m_Sight;			//照準
	CWEAPON* m_Weapon;			//所持武器

	TEAM_NUMBER		m_TeamNumber;			//味方か敵かの識別

	char*	m_OldAnimationChara;	//アニメーションの名前の旧名
	char*	m_NowAnimationChara;	//現在のアニメーションの名前
	float		m_Frame = 0;			//アニメーションのフレーム
	float	rate = 0;				//アニメーションブレンドのレート

	//ヘルパー関数
	void Update_AI();

	void ChangeAnimation(char* Name);
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

	void LookEnemy(CEnemy *enemy);		//プレイヤーを見る
	void Death();
};