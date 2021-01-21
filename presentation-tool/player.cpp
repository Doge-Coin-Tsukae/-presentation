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
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "player.h"
#include "bunker.h"

#define		NORMALSPEED 0.5f		//通常時のスピード
#define		SLOWSPEED	0.1f		//攻撃した際のスピード

void CPlayer::Init()
{
	//キャラモデル
	m_Model = new CModel();
	m_Model->Load("asset\\model\\ningen.obj");

	//当たり判定
	m_Colider = new AABB;
	m_Colider->Init(m_Position + D3DXVECTOR3(-1.0f, 0.0f, -1.0f), m_Position + D3DXVECTOR3(1.0f, 2.0f, 1.0f), m_Position);

	//メンバ変数初期化
	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void CPlayer::Uninit()
{
	m_Model->Unload();
	delete m_Model;
}

void CPlayer::Update()
{
	//メッシュフィールド高さ取得
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);	//メッシュフィールドの高さにプレイヤーを合わせる
}

void CPlayer::Draw()
{
	//拡大縮小のマトリクス
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//ヨーピッチロールのマトリクス
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	//位置マトリクス
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	CRenderer::SetWorldMatrix(&world);
	ImGuizmo::DecomposeMatrixToComponents(world, matrixTranslation, matrixRotation, matrixScale);

	m_Model->Draw();
}

void CPlayer::Save(FILE* fp)
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

	fputs("end\n", fp);
}

void CPlayer::Load(FILE* fp)
{
	fscanf(fp,"%f%f%f", &m_Position.x, &m_Position.y, &m_Position.z);
	fscanf(fp, "%f%f%f", &m_Rotation.x, &m_Rotation.y, &m_Rotation.z);
	fscanf(fp, "%f%f%f", &m_Scale.x, &m_Scale.y, &m_Scale.z);
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

	ImGui::Text("SetMode");
	ImGui::SliderFloat("rotation", &m_Rotation.x, 0, 10);
	ImGui::ListBox("weaponbox",&m_Weapontype, listbox_items, IM_ARRAYSIZE(listbox_items), 2);
	ImGui::Checkbox("delete", &m_Destroy);
	ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, SCREEN_WIDTH, SCREEN_HEIGHT);
	ImGuizmo::Manipulate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), ImGuizmo::ROTATE, ImGuizmo::LOCAL, &world._11);
	ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, world);
	ImGuizmo::ViewManipulate(camera->GetViewMatrix(), cameralength,ImVec2(ImGui::GetWindowPos().x -128, ImGui::GetWindowPos().y), ImVec2(128,128), 0x10101010);
}