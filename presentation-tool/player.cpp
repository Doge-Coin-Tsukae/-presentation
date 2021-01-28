//****************************************
//�v���C���[
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
#include "weapon.h"
#include "colider.h"
#include "player.h"
#include "bunker.h"

#define		NORMALSPEED 0.5f		//�ʏ펞�̃X�s�[�h
#define		SLOWSPEED	0.1f		//�U�������ۂ̃X�s�[�h

void CPlayer::Init()
{
	//�L�������f��
	//m_Model = new CModel();
	//m_Model->Load("asset\\model\\ningen.obj");

	m_AnimationModel = new CAnimationModel();
	m_AnimationModel->Load("asset/model/player/chara.fbx");

	//�����蔻��
	m_Colider = new AABB;
	m_Colider->Init(m_Position + D3DXVECTOR3(-1.0f, 0.0f, -1.0f), m_Position + D3DXVECTOR3(1.0f, 2.0f, 1.0f), m_Position);

	//�����o�ϐ�������
	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_AnimationModeltype = 0;
	m_AnimationModeltype = m_AnimationModeltypeold;
}

void CPlayer::Uninit()
{
	m_AnimationModel->Unload();
	delete m_AnimationModel;
}

void CPlayer::Update()
{
	//ImGui�ŃX�P�[���������Ă������傫����ۂ�
	m_Scale.y = m_Scale.x;
	m_Scale.z = m_Scale.x;

	UpdateAnimationModel();

	//���b�V���t�B�[���h�����擾
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);	//���b�V���t�B�[���h�̍����Ƀv���C���[�����킹��
}

void CPlayer::Draw()
{
	//�g��k���̃}�g���N�X
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//���[�s�b�`���[���̃}�g���N�X
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	//�ʒu�}�g���N�X
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	CRenderer::SetWorldMatrix(&world);
	ImGuizmo::DecomposeMatrixToComponents(world, matrixTranslation, matrixRotation, matrixScale);

	//m_Model->Draw();
	m_AnimationModel->Draw();
}

void CPlayer::Save(FILE* fp)
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
	const char* listbox_animodels[] = { "chara1","chara2" };
	ImGui::Text("Player");
	ImGui::SliderFloat("rotation", &m_Rotation.x, 0, 10);
	ImGui::SliderFloat("scale", &m_Scale.x, 0.1, 10);
	ImGui::ListBox("CharactorModel",&m_AnimationModeltype, listbox_animodels,IM_ARRAYSIZE(listbox_animodels),1);
	ImGui::ListBox("Weapon",&m_Weapontype, listbox_items, IM_ARRAYSIZE(listbox_items), 2);
	ImGui::Checkbox("delete", &m_Destroy);
	ImGui::End();

	ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, SCREEN_WIDTH, SCREEN_HEIGHT);
	ImGuizmo::Manipulate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), ImGuizmo::ROTATE, ImGuizmo::LOCAL, world);
	ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, world);
	ImGuizmo::ViewManipulate(camera->GetViewMatrix(), cameralength,ImVec2(ImGui::GetWindowPos().x -128, ImGui::GetWindowPos().y), ImVec2(128,128), 0x10101010);
}

void CPlayer::UpdateAnimationModel()
{
	//
	if (m_AnimationModeltype == m_AnimationModeltypeold) return;

	switch (m_AnimationModeltype)
	{
	case 0:
		m_AnimationModel->Load("asset/model/player/chara.fbx");
		break;
	case 1:
		m_AnimationModel->Load("asset/model/player/chara2.fbx");
		break;
	}
	m_AnimationModeltypeold = m_AnimationModeltype;
}