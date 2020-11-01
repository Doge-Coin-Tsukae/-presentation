//****************************************
//カメラ操作
//****************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "input.h"

#include "scene.h"

#include "human.h"
#include "animationmodel.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "player.h"
#include"camera.h"

void CCamera::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	m_Target = D3DXVECTOR3(1.0f, 3.0f, 0.0f);
	m_zoom = false;
}

void CCamera::Uninit()
{

}

void CCamera::Update()
{
	//カメラ取得
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	if (!pPlayer) return;

	//プレイヤーを追いかける
	m_Target = pPlayer->GetPosition();		//注視点をプレイヤーに
	m_Target.y += 8.0f;						//カメラを少し上に

	//プレイヤーの後ろに回り込むようにする
	m_Position.x = m_Target.x + 12.0f *cos(pPlayer->GetRotation().x)*cos(pPlayer->GetRotation().z);	//座標
	m_Position.y = m_Target.y + 12.0f *sin(pPlayer->GetRotation().z);
	m_Position.z = m_Target.z + 12.0f *-sin(pPlayer->GetRotation().x)*cos(pPlayer->GetRotation().z);	//座標

	//ズーム
	if (m_zoom == true)
	{
		m_Target.y -= 3.0f;
		m_Target.x = m_Target.x + 1.4f *sin(pPlayer->GetRotation().x)*cos(pPlayer->GetRotation().z);	//座標
		m_Target.y = m_Target.y + 1.4f *sin(pPlayer->GetRotation().z);
		m_Target.z = m_Target.z + 1.4f *cos(pPlayer->GetRotation().x)*cos(pPlayer->GetRotation().z);	//座標

		m_Position.x = m_Target.x + 4.0f *cos(pPlayer->GetRotation().x)*cos(pPlayer->GetRotation().z);	//座標
		m_Position.y = m_Target.y + 4.0f *sin(pPlayer->GetRotation().z);
		m_Position.z = m_Target.z + 4.0f *-sin(pPlayer->GetRotation().x)*cos(pPlayer->GetRotation().z);	//座標
	}
}

void CCamera::Draw()
{
	//ビューマトリクス設定
	D3DXMatrixLookAtLH(&viewMatrix,&m_Position,&m_Target,&D3DXVECTOR3(0.0f,1.0f,0.0f));

	CRenderer::SetViewMatrix(&viewMatrix);		//Direct9のSetTransformに近い

	//プロジェクションマトリクス設定
	D3DXMatrixPerspectiveFovLH(&projectionMatrix,1.0f,(float)SCREEN_WIDTH/SCREEN_HEIGHT,1.0f,1000.0f);

	CRenderer::SetProjectionMatrix(&projectionMatrix);
}