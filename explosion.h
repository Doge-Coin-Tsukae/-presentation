#pragma once

#include "gameobject.h"

class CExplosion : public CGameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = nullptr;
	static ID3D11ShaderResourceView*	m_Texture;

	int m_Count;

public:
	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};