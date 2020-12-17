#pragma once

#include "gameobject.h"

class CPlayer : public CGameObject	//�p��(�C���w���^���X)
{
private:
	CModel* m_Model;			//3D���f���N���X
	AABB* m_Colider;

	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(m_Model);
	}

public:
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