#pragma once

#include "gameobject.h"

class CPlayer : public CGameObject	//継承(インヘリタンス)
{
private:
	CModel* m_Model;			//3Dモデルクラス
	AABB* m_Colider;

	D3DXMATRIX  scale, rot, trans, world;
	float matrixTranslation[3], matrixRotation[3], matrixScale[3];
	int m_Weapontype = WEAPON_RIFLE;		//武器の種類

public:

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(m_Position),
			    CEREAL_NVP(m_Rotation),
			    CEREAL_NVP(m_Scale), 
				CEREAL_NVP(m_Weapontype));
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