//
//���_�I�u�W�F�N�g(�w���o����)
//
#include "main.h"
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "Vector.h"
#include "meshfield.h"
#include "game.h"
#include "animationmodel.h"
#include "model.h"
#include "colider.h"
#include "base.h"

CBase::CBase()
{
	//���̐ݒ�
	m_Flag = new CModel();
	m_Flag->Load("asset\\model\\flag.obj");

	//�����蔻��̐ݒ�
	m_Zone = new CCOLIDER_CIRCLE();
	m_Zone->Init();
	m_Zone->SetScale(D3DXVECTOR3(10.0f, 10.0f, 10.0f));
}
void CBase::Init()
{
	//���g�̕ϐ��̐ݒ�
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void CBase::Uninit()
{
	//�����蔻��̍폜
	m_Zone->Uninit();
	delete m_Zone;

	//���̍폜
	m_Flag->Unload();
	delete m_Flag;
}


void CBase::Update()
{
	m_Zone->SetPosition(m_Position);		//���W�̐ݒ�

	//���b�V���t�B�[���h�����擾
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);

}

void CBase::Draw()
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

	m_Flag->Draw();		//���̕`��
	m_Zone->Draw();		//�����蔻��̕`��
}