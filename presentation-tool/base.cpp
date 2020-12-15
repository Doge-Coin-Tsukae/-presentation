//
//拠点オブジェクト(陣取り出来る)
//
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Vector.h"
#include "meshfield.h"
#include "game.h"
#include "human.h"
#include "model.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "player.h"
#include "base.h"

CBase::CBase()
{
	//旗の設定
	m_Flag = new CModel();
	m_Flag->Load("asset\\model\\flag.obj");

	//当たり判定の設定
	m_Zone = new CCOLIDER_CIRCLE();
	m_Zone->Init();
	m_Zone->SetScale(D3DXVECTOR3(10.0f, 10.0f, 10.0f));
}
void CBase::Init()
{
	//自身の変数の設定
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void CBase::Uninit()
{
	//当たり判定の削除
	m_Zone->Uninit();
	delete m_Zone;

	//旗の削除
	m_Flag->Unload();
	delete m_Flag;
}


void CBase::Update()
{
	m_Zone->SetPosition(m_Position);		//座標の設定

	//メッシュフィールド高さ取得
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);

}

void CBase::Draw()
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

	m_Flag->Draw();		//旗の描画
	m_Zone->Draw();		//当たり判定の描画
}

void CBase::Save(FILE* fp)
{
	//座標
	fprintf(fp, "%f ", m_Position.x);
	fprintf(fp, "%f ", m_Position.y);
	fprintf(fp, "%f\n", m_Position.z);
	//角度
	fprintf(fp, "%f ", m_Rotation.x);
	fprintf(fp, "%f ", m_Rotation.y);
	fprintf(fp, "%f\n", m_Rotation.z);
	//大きさ
	fprintf(fp, "%f ", m_Scale.x);
	fprintf(fp, "%f ", m_Scale.y);
	fprintf(fp, "%f\n", m_Scale.z);
}

void CBase::Load(FILE*fp, int line)
{
	for (int i = 0; i < line * 3; i++)
	{
		fscanf(fp, "");
	}

	fscanf(fp, "%f%f%f", &m_Position.x, &m_Position.y, &m_Position.z);
	fscanf(fp, "%f%f%f", &m_Rotation.x, &m_Rotation.y, &m_Rotation.z);
	fscanf(fp, "%f%f%f", &m_Scale.x, &m_Scale.y, &m_Scale.z);
}