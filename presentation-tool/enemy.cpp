//****************************************
//敵
//****************************************

#include "main.h"
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "model.h"
#include "animationmodel.h"
#include "meshfield.h"
#include "camera.h"
#include "human.h"
#include "Vector.h"
#include "model.h"
#include "sight.h"
#include "colider.h"
#include "player.h"
#include "enemy.h"
class CAnimationModel* CEnemy::m_AnimationModel;
typedef struct
{
	char* pFilename;	// ファイル名
} ANIMENAME;

ANIMENAME g_aParam[1] =
{
	{(char*)"ready"},				// 構える
};

void CEnemy::Load()
{
	m_AnimationModel = new CAnimationModel();
	m_AnimationModel->Load("asset/model/player/chara2.fbx");
	m_AnimationModel->LoadAnimation("asset\\model\\player\\ready.fbx", g_aParam[0].pFilename);		//アニメーション
}

void CEnemy::Unload()
{
	m_AnimationModel->Unload();
	delete m_AnimationModel;
}

void CEnemy::Init()
{
	m_Sight = new CSIGHT();
	m_Sight->Init();
	m_Sight->Setparent(this);		//照準の親を自分に

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_TeamNumber = TEAM_ENEMY;		//チーム設定

		//メッシュフィールド高さ取得

	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);

}

void CEnemy::Uninit()
{

	m_Sight->Uninit();
	delete m_Sight;
}

void CEnemy::Update()
{
	m_AnimationModel->Update(g_aParam[0].pFilename, g_aParam[0].pFilename, 0, 1);
}

void CEnemy::Draw()
{
	//内部クラスから
	m_Sight->Draw();

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

	m_AnimationModel->Draw();
}

void CEnemy::SetImGui()
{
	CCamera* camera = CManager::GetScene()->GetGameObject<CCamera>(0);
	D3DXVECTOR3 camerapos = camera->GetPosition();
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(GetWindow(), &pos);

	float cameralength = D3DXVec3Dot(&m_Position, &camerapos);
	const char* listbox_items[] = { "Rifle", "SMG" };

	ImGui::Text("EnemyNPC");
	ImGui::SliderFloat("rotation", &m_Rotation.y, 0, 10);
	ImGui::ListBox("weaponbox", &m_Weapontype, listbox_items, IM_ARRAYSIZE(listbox_items), 2);
	ImGui::Checkbox("delete", &m_Destroy);
	ImGui::End();
}