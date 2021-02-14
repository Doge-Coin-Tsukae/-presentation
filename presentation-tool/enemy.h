#pragma once

#include "gameobject.h"

class CEnemy : public CGameObject	//�p��(�C���w���^���X)
{
private:
	static CAnimationModel* m_AnimationModel;	//3D���f���N���X

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