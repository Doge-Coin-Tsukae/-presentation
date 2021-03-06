#pragma once

#include "gameobject.h"

class CCamera : public CGameObject
{
private:
	D3DXVECTOR3 m_Target;		//カメラの注視点
	D3DXVECTOR3 m_Velocity;


	float			m_speed;	//足の速さ
	float			anglex;
	float			anglez;
public:
	CCamera(){}		//コンストラクタ
	~CCamera(){}	//デストラクタ

	void Init();
	void Uninit();
	void Update();
	void Controll_Update();
	void Draw();

	D3DXMATRIX viewMatrix;		//ビューマトリクス
	D3DXMATRIX projectionMatrix;	//プロジェクションマトリクス

	D3DXMATRIX GetViewMatrix() { return viewMatrix; }
	D3DXMATRIX GetProjectionMatrix() { return projectionMatrix; }
	void CameraMouseMove();
	void CameraMouseRotate();
	void ZoomCamera();
	void ZoomOutCamera();
};