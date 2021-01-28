#pragma once

#include "gameobject.h"

class CBUNKER : public CGameObject
{
private:
	static CModel* m_Model;		//3D���f���N���X
	static CModel* m_ShadowModel;
	AABB m_Colider;
	OBB*  m_Obb;
	ID3D11VertexShader* m_VertexShader[2];		//���_�V�F�[�_
	ID3D11PixelShader* m_PixelShader[2];		//�s�N�Z���V�F�[�_
	ID3D11InputLayout* m_VertexLayout;

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

	void Load(FILE*fp, int line);

	AABB GetColider() { return m_Colider; }
};