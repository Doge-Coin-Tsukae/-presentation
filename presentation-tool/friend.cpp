//****************************************
//����
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
#include "weapon.h"
#include "colider.h"
#include "player.h"
#include "friend.h"

class CAnimationModel* CFriend::m_AnimationModel;

void CFriend::Load()
{
	m_AnimationModel = new CAnimationModel();
	m_AnimationModel->Load("asset/model/player/chara.fbx");
}

void CFriend::Unload()
{
	m_AnimationModel->Unload();
	delete m_AnimationModel;
}

void CFriend::Init()
{
	m_Sight = new CSIGHT();
	m_Sight->Init();
	m_Sight->Setparent(this);		//�Ə��̐e��������

	m_Weapon = new CWEAPON();
	m_Weapon->Init();
	m_Weapon->Setparent(this);

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_TeamNumber = TEAM_ENEMY;		//�`�[���ݒ�

		//���b�V���t�B�[���h�����擾

	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);

}

void CFriend::Uninit()
{
	m_Weapon->Uninit();
	delete m_Weapon;

	m_Sight->Uninit();
	delete m_Sight;
}

void CFriend::Update()
{
}

void CFriend::Draw()
{
	//�����N���X����
	m_Weapon->Draw();
	m_Sight->Draw();

	//�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	//�g��k���̃}�g���N�X
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//���[�s�b�`���[���̃}�g���N�X
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	//�ʒu�}�g���N�X
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	CRenderer::SetWorldMatrix(&world);

	m_AnimationModel->Draw();
}

void CFriend::Save(FILE* fp)
{
	//���W
	fprintf(fp, "%f ", m_Position.x);
	fprintf(fp, "%f ", m_Position.y);
	fprintf(fp, "%f\n", m_Position.z);
	//�p�x
	fprintf(fp, "%f ", m_Rotation.x);
	fprintf(fp, "%f ", m_Rotation.y);
	fprintf(fp, "%f\n", m_Rotation.z);
	//�傫��
	fprintf(fp, "%f ", m_Scale.x);
	fprintf(fp, "%f ", m_Scale.y);
	fprintf(fp, "%f\n", m_Scale.z);
}

void CFriend::Load(FILE* fp, int line)
{
	for (int i = 0; i < line * 3; i++)
	{
		fscanf(fp, "");
	}

	fscanf(fp, "%f%f%f", &m_Position.x, &m_Position.y, &m_Position.z);
	fscanf(fp, "%f%f%f", &m_Rotation.x, &m_Rotation.y, &m_Rotation.z);
	fscanf(fp, "%f%f%f", &m_Scale.x, &m_Scale.y, &m_Scale.z);
}

void CFriend::SetImGui()
{
	CCamera* camera = CManager::GetScene()->GetGameObject<CCamera>(0);
	D3DXVECTOR3 camerapos = camera->GetPosition();
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(GetWindow(), &pos);

	float cameralength = D3DXVec3Dot(&m_Position, &camerapos);
	const char* listbox_items[] = { "Rifle", "SMG" };

	ImGui::Text("FriendNPC");
	ImGui::SliderFloat("rotation", &m_Rotation.x, 0, 10);
	ImGui::ListBox("weaponbox", &m_Weapontype, listbox_items, IM_ARRAYSIZE(listbox_items), 2);
	ImGui::Checkbox("delete", &m_Destroy);

	float matrixTranslation[3], matrixRotation[3], matrixScale[3];
	//ImGuizmo::DecomposeMatrixToComponents(world, matrixTranslation, matrixRotation, matrixScale);
	//ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, world);
	//ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, SCREEN_WIDTH, SCREEN_HEIGHT);
	//ImGuizmo::Manipulate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), ImGuizmo::ROTATE, ImGuizmo::LOCAL, &world._11);
	//ImGuizmo::ViewManipulate(camera->GetViewMatrix(), cameralength, ImVec2(ImGui::GetWindowPos().x - 128, ImGui::GetWindowPos().y), ImVec2(128, 128), 0x10101010);
}