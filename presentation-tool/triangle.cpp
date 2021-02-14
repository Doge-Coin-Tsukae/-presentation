//****************************************
//選択したオブジェクトの頭上に逆三角形を表示
//****************************************

#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "camera.h"
#include "human.h"
#include "model.h"
#include "triangle.h"

void CTriangle::Init()
{
	//キャラモデル
	m_Model = new CModel();
	m_Model->Load("asset\\model\\tryangle.obj");

	//メンバ変数初期化
	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void CTriangle::Uninit()
{
	m_Model->Unload();
	delete m_Model;
}

void CTriangle::Update()
{
	m_Rotation.y += 0.05f;	//くるくる回転
}

void CTriangle::Draw()
{
	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	//拡大縮小のマトリクス
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//ヨーピッチロールのマトリクス
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	//位置マトリクス
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	CRenderer::SetWorldMatrix(&world);

	m_Model->Draw();
}
