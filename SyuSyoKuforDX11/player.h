#pragma once

#include "gameobject.h"

class CPlayer : public CGameObject	//継承(インヘリタンス)
{
private:
	CAnimationModel* m_Animodel;	//3Dアニメーションモデルクラス
	CSIGHT* m_Sight;			//照準
	CWEAPON* m_Weapon;			//所持武器
	AABB m_Colider;				//当たり判定(AABB)

	D3DXVECTOR3		m_ModelRot;		//モデルの角度(モデルが真っ直ぐにならないから入れた)
	D3DXVECTOR3		m_Velocity;		//行き先座標
	TEAM_NUMBER		m_TeamNumber;	//味方か敵かの識別
	int				m_Hp;			//体力
	float			m_speed;		//足の速さ
	bool			m_Death;		//死亡フラグ
	bool			m_ready;		//構えているか
	char*			m_OldAnimationChara;	//アニメーションの名前の旧名
	char*			m_NowAnimationChara;	//現在のアニメーションの名前
	int m_Frame = 0;				//アニメーションのフレーム
	float rate = 0;					//アニメーションブレンドのレート



	void Update_Controll();		//キー入力
public:
	CPlayer(){}
	~CPlayer(){}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Death();		//死亡処理
	void Damage();		//ダメージ
	void ChangeAnimation(char* Name);		//アニメーション変更

	CWEAPON* GetWeapon(){return m_Weapon;}
	bool	 isDeath() { return m_Death; }
	int Getm_Hp() { return m_Hp; }
};