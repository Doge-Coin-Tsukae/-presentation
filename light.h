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
	void SetDirection(D3DXVECTOR4 SDirection);		//Directionデータ
	void SetAmbient(D3DXCOLOR SAmbient);			//Ambientデータ
	void SetDiffuse(D3DXCOLOR SDiffuse);			//Diffuseデータ

	void EnableLight();		//ライトオン
	void DisbleLight();		//ライトオフ
};