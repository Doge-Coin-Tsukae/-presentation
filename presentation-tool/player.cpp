//****************************************
//プレイヤー
//****************************************

#include "main.h"
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "camera.h"
#include "Vector.h"
#include "meshfield.h"
#include "input.h"
#include "human.h"
#include "model.h"
#include "animationmodel.h"
#include "sight.h"
#include "colider.h"
#include "player.h"
#include "bunker.h"

#define		NORMALSPEED 0.5f		//通常時のスピード
#define		SLOWSPEED	0.1f		//攻撃した際のスピード

typedef struct
{
	char* pFilename;	// ファイル名
} ANIMENAME2;

ANIMENAME2 g_aParam[1] =
{
	{(char*)"ready"},				// 構える
};

void CPlayer::Init()
{
	//キャラモデル
	m_Modelpass = "asset/model/player/chara.fbx";
	m_AnimationModel = new CAnimationModel();
	m_AnimationModel->Load(m_Modelpass.c_str());
	m_AnimationModel->LoadAnimation("asset\\model\\player\\ready.fbx", g_aParam[0].pFilename);		//アニメーション

	//当たり判定
	m_Colider = new AABB;
	m_Colider->Init(m_Position + D3DXVECTOR3(-1.0f, 0.0f, -1.0f), m_Position + D3DXVECTOR3(1.0f, 2.0f, 1.0f), m_Position);

	//メンバ変数初期化
	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_AnimationModeltype = 0;
	m_AnimationModeltype = m_AnimationModeltypeold;
}

void CPlayer::Uninit()
{
	m_AnimationModel->Unload();
	m_AnimationModel->UnloadAnimation();
	delete m_AnimationModel;
}

void CPlayer::Update()
{
	//ImGuiでスケールいじっても同じ大きさを保つ
	m_Scale.y = m_Scale.x;
	m_Scale.z = m_Scale.x;

	UpdateAnimationModel();
	m_AnimationModel->Update(g_aParam[0].pFilename, g_aParam[0].pFilename, 0, 1);

	//メッシュフィールド高さ取得
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);	//メッシュフィールドの高さにプレイヤーを合わせる
}

void CPlayer::Draw()
{
	//拡大縮小のマトリクス
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//ヨーピッチロールのマトリクス
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	//位置マトリクス
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	CRenderer::SetWorldMatrix(&world);
	ImGuizmo::DecomposeMatrixToComponents(world, matrixTranslation, matrixRotation, matrixScale);

	//m_Model->Draw();
	m_AnimationModel->Draw();
}

void CPlayer::SetImGui()
{
	CCamera* camera = CManager::GetScene()->GetGameObject<CCamera>(0);
	D3DXVECTOR3 camerapos = camera->GetPosition();
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(GetWindow(), &pos);

	float cameralength = D3DXVec3Dot(&m_Position, &camerapos);
	const char* listbox_items[] = { "Rifle", "SMG" };
	const char* listbox_animodels[] = { "chara1","chara2" };
	ImGui::Text("Player");
	ImGui::SliderFloat("rotation", &m_Rotation.y, 0, 10);
	ImGui::SliderFloat("scale", &m_Scale.x, 0.1, 10);
	ImGui::ListBox("CharactorModel",&m_AnimationModeltype, listbox_animodels,IM_ARRAYSIZE(listbox_animodels),1);
	ImGui::ListBox("Weapon",&m_Weapontype, listbox_items, IM_ARRAYSIZE(listbox_items), 2);
	ImGui::Checkbox("delete", &m_Destroy);
	ImGui::End();
}

void CPlayer::UpdateAnimationModel()
{
	//アニメーション変更されているかどうか
	if (m_AnimationModeltype == m_AnimationModeltypeold) return;

	m_AnimationModel->Unload();
	delete m_AnimationModel;
	m_AnimationModel = new CAnimationModel();

	switch (m_AnimationModeltype)
	{
	case 0:
		m_Modelpass = "asset/model/player/chara.fbx";
		m_AnimationModel->Load(m_Modelpass.c_str());
		break;
	case 1:
		m_Modelpass = "asset/model/player/chara2.fbx";
		m_AnimationModel->Load(m_Modelpass.c_str());
		break;
	}

	m_AnimationModel->LoadAnimation("asset\\model\\player\\ready.fbx", g_aParam[0].pFilename);
	m_AnimationModeltypeold = m_AnimationModeltype;
}