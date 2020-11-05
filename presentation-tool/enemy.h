#pragma once

#include "gameobject.h"

class CEnemy : public CGameObject	//継承(インヘリタンス)
{
private:
	static CModel* m_Model;			//3Dモデルクラス
	CSIGHT* m_Sight;			//照準
	CWEAPON* m_Weapon;			//所持武器

	TEAM_NUMBER		m_TeamNumber;			//味方か敵かの識別

	//ヘルパー関数
	void Update_AI();
public:
	CEnemy() {}
	~CEnemy() {}

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void LookPlayer();		//プレイヤーを見る
};