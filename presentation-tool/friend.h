#pragma once

#include "gameobject.h"

class CFriend : public CGameObject	//継承(インヘリタンス)
{
private:
	static CModel* m_Model;			//3Dモデルクラス
	static CAnimationModel* m_AnimationModel;

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
	CFriend() {}
	~CFriend() {}

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetImGui();
};