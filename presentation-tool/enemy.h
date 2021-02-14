#pragma once

#include "gameobject.h"

class CEnemy : public CGameObject	//継承(インヘリタンス)
{
private:
	static CAnimationModel* m_AnimationModel;	//3Dモデルクラス

	CSIGHT* m_Sight;			//照準

	TEAM_NUMBER		m_TeamNumber;			//味方か敵かの識別
	int m_Weapontype = WEAPON_RIFLE;		//武器の番号

public:

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(m_Position),
			CEREAL_NVP(m_Rotation),
			CEREAL_NVP(m_Scale),
			CEREAL_NVP(m_Weapontype));
	}
	CEnemy() {}
	~CEnemy() {}

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetImGui();
};