#pragma once

#include "gameobject.h"

class CPlayer : public CGameObject	//継承(インヘリタンス)
{
private:
	CAnimationModel* m_AnimationModel;		//3Dモデルクラス
	AABB* m_Colider;


	D3DXMATRIX  scale, rot, trans, world;
	float matrixTranslation[3], matrixRotation[3], matrixScale[3];

	int m_AnimationModeltype;				//ImGUIで使うアニメーションモデル
	int m_AnimationModeltypeold;			//ImGUIでアニメーションモデルが変更になったか調べる
	std::string m_Modelpass;							//モデルのパス

	int m_Weapontype = WEAPON_RIFLE;		//武器の種類

	void UpdateAnimationModel();			//ImGUIでキャラクターモデルが変更になったら
public:

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(m_Position),
			    CEREAL_NVP(m_Rotation),
			    CEREAL_NVP(m_Scale), 
				CEREAL_NVP(m_Weapontype),
				CEREAL_NVP(m_Modelpass));
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