#pragma once

#include "gameobject.h"

class CBase : public CGameObject
{
private:
	CModel*		m_Flag;			//Šøƒ‚ƒfƒ‹
	CCOLIDER_CIRCLE*	m_Zone;
public:
	CBase();
	~CBase() {}

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(m_Position),
			CEREAL_NVP(m_Rotation),
			CEREAL_NVP(m_Scale));
	}

	void Init();
	void Uninit();
	void Update();
	void Draw();
};