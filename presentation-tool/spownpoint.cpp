//=====================================
//
// �X�|�[���|�C���g(NPC������)
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

#include "spownpoint.h"


void CSpownPoint::Init()
{
	//���g�̕ϐ��̐ݒ�
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_SpownType = FRIENDRY_SPOWN;
	m_Max = -1;
	m_Spownlicense = true;
	//���̐ݒ�
	m_Model = new CModel();
	m_Model->Load("asset\\model\\flag.obj");
}

void CSpownPoint::Uninit()
{
	//���̍폜
	m_Model->Unload();
	delete m_Model;
}

void CSpownPoint::Update()
{
		//���b�V���t�B�[���h�����擾
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);
}

void CSpownPoint::Draw()
{
	//�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	//�g��k���̃}�g���N�X
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//���[�s�b�`���[���̃}�g���N�X
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	//�ʒu�}�g���N�X
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	CRenderer::SetWorldMatrix(&world);

	m_Model->Draw();		//���̕`��
}
void CSpownPoint::SetImGui()
{
	const char* listbox_items[] = { "NONE", "FRIEND","ENEMY" };

	ImGui::Text("SpownPoint");
	ImGui::SliderFloat("rotation", &m_Rotation.x, 0, 10);
	ImGui::SliderFloat("scale", &m_Scale.x, 0.1, 10);
	ImGui::SliderInt("Spown_Interval", &m_spowninterval, 0, 1000);
	ImGui::SliderInt("Spown_Max(-1 = unlimited)", &m_Max, -1, 30);
	ImGui::ListBox("Spown_Type", &m_SpownType, listbox_items, IM_ARRAYSIZE(listbox_items), 3);
	ImGui::Checkbox("Spown_License",&m_Spownlicense);
	ImGui::Checkbox("delete", &m_Destroy);
	ImGui::End();
}