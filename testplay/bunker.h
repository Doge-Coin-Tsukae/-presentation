#pragma once

#include "gameobject.h"

class CBUNKER : public CGameObject
{
private:
	static CModel* m_Model;		//3Dモデルクラス
	static CModel* m_ShadowModel;
	OBB*  m_Obb;

public:
	CBUNKER(){}
	~CBUNKER(){}

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

	void FileLoad();	//セーブファイルからロードする

	OBB* GetObb() { return m_Obb; }

};