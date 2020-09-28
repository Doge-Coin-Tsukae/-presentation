#pragma once

#include "gameobject.h"

#define FIELDX 21
#define FIELDY 21

class CMeshField : public CGameObject
{
private:

	ID3D11Buffer*				m_VertexBuffer = nullptr;
	ID3D11Buffer*				m_IndexBuffer = nullptr;
	ID3D11ShaderResourceView*	m_Texture = nullptr;

	VERTEX_3D					m_Vertex[FIELDX][FIELDY];

public:
	CMeshField() {}
	~CMeshField() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	float GetHeight(D3DXVECTOR3 Position);
	void TyutenHenni(int centerx, int centery);
};