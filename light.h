#pragma once

#include "gameobject.h"

class CLight : public CGameObject
{
	LIGHT light;

public:
	CLight();
	CLight(D3DXVECTOR4 SDirection, D3DXCOLOR SAmbient, D3DXCOLOR SDiffuse);
	void Uninit();
	void Update();
	void SetDirection(D3DXVECTOR4 SDirection);		//Direction�f�[�^
	void SetAmbient(D3DXCOLOR SAmbient);			//Ambient�f�[�^
	void SetDiffuse(D3DXCOLOR SDiffuse);			//Diffuse�f�[�^

	void EnableLight();		//���C�g�I��
	void DisbleLight();		//���C�g�I�t
};