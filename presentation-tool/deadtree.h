#pragma once

#include "gameobject.h"

class CDEADTREE : public CGameObject
{
private:
	static CModel* m_Model;		//3Dƒ‚ƒfƒ‹ƒNƒ‰ƒX
	AABB m_Colider;
public:
	CDEADTREE() {}
	~CDEADTREE() {}

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

	AABB GetColider() { return m_Colider; }
};