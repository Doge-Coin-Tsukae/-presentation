#pragma once

#include "gameobject.h"

class CEnemy : public CGameObject	//継承(インヘリタンス)
{
private:
	static CAnimationModel* m_Animodel;	//3Dアニメーションモデルクラス
	D3DXVECTOR3		m_ModelRot;
	CSIGHT* m_Sight;			//照準
	CWEAPON* m_Weapon;			//所持武器

	TEAM_NUMBER		m_TeamNumber;			//味方か敵かの識別

	char*	m_OldAnimationChara;	//アニメーションの名前の旧名
	char*	m_NowAnimationChara;	//現在のアニメーションの名前
	float	m_Frame = 0;			//アニメーションのフレーム
	float	rate = 0;				//アニメーションブレンドのレート
	bool	m_Death;		//死亡フラグ

	ID3D11VertexShader* m_VertexShader[2];		//頂点シェーダ
	ID3D11PixelShader* m_PixelShader[2];		//ピクセルシェーダ
	ID3D11InputLayout* m_VertexLayout;

	//ヘルパー関数
	void Update_AI();

	void ChangeAnimation(char* Name);
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
	bool isOverReload();		//装填完了したか
};