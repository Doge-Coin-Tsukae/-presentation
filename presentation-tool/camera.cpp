//****************************************
//カメラ操作
//****************************************
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "input.h"

#include "model.h"
#include "carsor.h"
#include"camera.h"

#define CARSOR_SEBSITIVITY 1
void CCamera::Init()
{
	m_Position = D3DXVECTOR3(10.0f,120.0f, -30.0f);
	m_Target = D3DXVECTOR3(10.0f, 115.0f, -32.0f);
	m_speed = 0.5f;

	anglez= 0.5f;
}

void CCamera::Uninit()
{
}

void CCamera::Update()
{
	Controll_Update();	//操作
}
void CCamera::Controll_Update()
{
	m_Velocity = D3DXVECTOR3(0,0,0);

	//キー入力で移動
	if (CInput::GetKeyPress('D'))
	{
		m_Velocity.x += sin(anglex) * m_speed;
		m_Velocity.z += cos(anglex) * m_speed;
	}
	if (CInput::GetKeyPress('A'))
	{
		m_Velocity.x -= sin(anglex) * m_speed;
		m_Velocity.z -= cos(anglex) * m_speed;
		
	}
	if (CInput::GetKeyPress('S'))
	{
		m_Velocity.z -= sin(anglex) * m_speed;
		m_Velocity.x += cos(anglex) * m_speed;

	}
	if (CInput::GetKeyPress('W'))
	{
		m_Velocity.z += sin(anglex) * m_speed;
		m_Velocity.x -= cos(anglex) * m_speed;

	}

	if (CInput::GetKeyPress('Z'))
		m_Velocity.y -= 0.1f;
	if (CInput::GetKeyPress('C'))
		m_Velocity.y += 0.1f;

	m_Position += m_Velocity;
	m_Target += m_Velocity;

	m_Target.x = m_Position.x - 5.0f * cos(anglex) * cos(anglez);	//座標
	m_Target.y = (m_Position.y + 1.0f) - 5.0f * sin(anglez);
	m_Target.z = m_Position.z - 5.0f * -sin(anglex) * cos(anglez);	//座標
}
void CCamera::Draw()
{
	D3DXVECTOR3 pUp(0.0f,1.0f,0.0f);
	//ビューマトリクス設定
	D3DXMatrixLookAtLH(&viewMatrix,&m_Position,&m_Target,&pUp);

	CRenderer::SetViewMatrix(&viewMatrix);		//Direct9のSetTransformに近い

	//プロジェクションマトリクス設定
	D3DXMatrixPerspectiveFovLH(&projectionMatrix,1.0f,(float)SCREEN_WIDTH/SCREEN_HEIGHT,1.0f,1000.0f);

	CRenderer::SetProjectionMatrix(&projectionMatrix);
}

void CCamera::CameraMouseMove()
{
	m_Position.x -= CInput::GetMousedDfference().x / CARSOR_SEBSITIVITY;
	m_Target.x -= CInput::GetMousedDfference().x / CARSOR_SEBSITIVITY;
	m_Position.z += CInput::GetMousedDfference().y / CARSOR_SEBSITIVITY;
	m_Target.z += CInput::GetMousedDfference().y / CARSOR_SEBSITIVITY;
}
void CCamera::CameraMouseRotate()
{
	anglex += CInput::GetMousedDfference().x / 100;
	anglez += CInput::GetMousedDfference().y / 100;
}

void CCamera::ZoomCamera()
{

}