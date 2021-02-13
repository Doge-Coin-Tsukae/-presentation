//=====================================
//
// スポーンポイント(NPCが沸く)
//  written by Y.Okubo
//
//=====================================
#include "main.h"
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "Vector.h"
#include "model.h"
#include "meshfield.h"

#include "human.h"
#include "animationmodel.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "behavior.h"
#include "enemy.h"
#include "friend.h"

#include "spownpoint.h"


void CSpownPoint::Init()
{
	//自身の変数の設定
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_SpownType = FRIENDRY_SPOWN;
	m_SpownedNum = 0;
	m_Max = -1;
	m_Spownlicense = true;
	//旗の設定
	m_Model = new CModel();
	m_Model->Load("asset\\model\\flag.obj");
}

void CSpownPoint::Uninit()
{
	//旗の削除
	m_Model->Unload();
	delete m_Model;
}

void CSpownPoint::Update()
{

	m_time++;
	if (m_spowninterval <= m_time)
	{
		Spown();
		m_time = 0;
	}
		//メッシュフィールド高さ取得
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);
}

void CSpownPoint::Draw()
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

	m_Model->Draw();		//旗の描画
}

void CSpownPoint::Spown()
{
	CScene* scene = CManager::GetScene();
	if (SpownConditions() == false) return;		//条件満たさないときは沸かせない

	if (m_SpownType == ENEMY_SPOWN)
	{
		scene->AddGameObject<CEnemy>(1)->SetPosition(m_Position);
		m_SpownedNum++;
		return;
	}

	if (m_SpownType == FRIENDRY_SPOWN)
	{
		scene->AddGameObject<CFriend>(1)->SetPosition(m_Position);
		m_SpownedNum++;
		return;
	}
}

bool CSpownPoint::SpownConditions()
{
	//無制限のとき、無条件でクリア
	if (m_Max == -1)  return true;

	//上限に達していないときは沸く
	if (m_SpownedNum < m_Max) return true;

	//許可設定が可になったら沸く
	if (m_Spownlicense == true) return true;
	//それ以外は沸かせない
	return false;
}