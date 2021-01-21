#pragma once

#include "gameobject.h"

class CPlayer : public CGameObject	//�p��(�C���w���^���X)
{
private:
	CModel* m_Model;			//3D���f���N���X
	AABB* m_Colider;

	D3DXMATRIX  scale, rot, trans, world;
	float matrixTranslation[3], matrixRotation[3], matrixScale[3];
	int m_Weapontype = WEAPON_RIFLE;		//����̎��

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