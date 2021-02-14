#pragma once

#include "gameobject.h"

class CFriend : public CGameObject	//�p��(�C���w���^���X)
{
private:
	static CModel* m_Model;			//3D���f���N���X
	static CAnimationModel* m_AnimationModel;

	CSIGHT* m_Sight;			//�Ə�

	TEAM_NUMBER		m_TeamNumber;			//�������G���̎���
	int m_Weapontype = WEAPON_RIFLE;		//����̔ԍ�

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