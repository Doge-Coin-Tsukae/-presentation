#pragma once

#include "gameobject.h"

#define MAXSHADER  1

class CPlayer : public CGameObject	//継承(インヘリタンス)
{
private:
	CAnimationModel* m_Animodel;	//3Dアニメーションモデルクラス
	CSIGHT* m_Sight;			//照準
	CWEAPON* m_Weapon;			//所持武器
	OBB*  m_Obb;
	D3DXVECTOR3		m_ModelRot;		//モデルの角度(モデルが真っ直ぐにならないから入れた)
	D3DXVECTOR3		m_Velocity;		//行き先座標
	TEAM_NUMBER		m_TeamNumber;	//味方か敵かの識別
	int				m_Hp;			//体力
	float			m_speed;		//足の速さ
	bool			m_Death;		//死亡フラグ
	bool			m_ready;		//構えているか
	char*			m_OldAnimationChara;	//アニメーションの名前の旧名
	char*			m_NowAnimationChara;	//現在のアニメーションの名前
	float m_Frame = 0;				//アニメーションのフレーム
	float rate = 0;					//アニメーションブレンドのレート

	//ロード
	int m_Weapontype;
	std::string m_Modelpass;

	void Update_Controll();		//キー入力
public:
	CPlayer(){}
	~CPlayer(){}

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(m_Position),
			CEREAL_NVP(m_Rotation),
			CEREAL_NVP(m_Scale),
			CEREAL_NVP(m_Weapontype),
			CEREAL_NVP(m_Modelpass));
	}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Death();		//死亡処理
	void Damage();		//ダメージ
	void ChangeAnimation(char* Name);		//アニメーション変更

	void ResetVelocity() { m_Velocity = m_Position; }
	CWEAPON* GetWeapon(){return m_Weapon;}
	bool	 isDeath() { return m_Death; }
	int Getm_Hp() { return m_Hp; }
	int GetWeapontype() { return m_Weapontype; }
	void FileLoad();	//セーブファイルからロードする
};