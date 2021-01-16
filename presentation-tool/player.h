#pragma once

#include "gameobject.h"

class CPlayer : public CGameObject	//継承(インヘリタンス)
{
private:
	CModel* m_Model;			//3Dモデルクラス
	AABB* m_Colider;

	D3DXMATRIX  scale, rot, trans, world;

public:

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(m_Position),
			    CEREAL_NVP(m_Rotation),
			    CEREAL_NVP(m_Scale) );
	}

	CPlayer(){}
	~CPlayer(){}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Save(FILE* fp);
	void Load(FILE* fp);

	void SetImGui();
};