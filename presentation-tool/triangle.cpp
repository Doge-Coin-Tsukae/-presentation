//****************************************
//�I�������I�u�W�F�N�g�̓���ɋt�O�p�`��\��
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
	//�L�������f��
	m_Model = new CModel();
	m_Model->Load("asset\\model\\tryangle.obj");

	//�����o�ϐ�������
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
	m_Rotation.y += 0.05f;	//���邭���]
}

void CTriangle::Draw()
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

	m_Model->Draw();
}
