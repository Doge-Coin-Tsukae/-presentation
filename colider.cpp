//=====================================
//
//	当たり判定
//  written by Y.Okubo
//
//=====================================
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "model.h"
#include "colider.h"

void CCOLIDER_CIRCLE::Init()
{

}
void CCOLIDER_CIRCLE::Uninit()
{
	//モデルを使っていたときのみ削除を行う
	if (m_Model == nullptr) return;
	m_Model->Unload();
	delete m_Model;
}
void CCOLIDER_CIRCLE::Update()
{

}
void CCOLIDER_CIRCLE::Draw()
{
	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	//拡大縮小のマトリクス
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//ヨーピッチロールのマトリクス
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	//位置マトリクス
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	CRenderer::SetWorldMatrix(&world);

	m_Model->Draw();
}
void CCOLIDER_CIRCLE::SetModel()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\colider.obj");
}

bool CCOLIDER_CIRCLE::GetColider(D3DXVECTOR3 pPos)
{
	D3DXVECTOR3 direction = m_Position - pPos;
	float length = D3DXVec3Length(&direction);

	if (length < m_Scale.x)
	{
		return true;
	}


	return false;
}