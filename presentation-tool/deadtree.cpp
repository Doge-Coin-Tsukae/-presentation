#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "scene.h"

#include "colider.h"
#include "deadtree.h"

class CModel* CDEADTREE::m_Model;

void CDEADTREE::Load()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\deadtree.obj");
}

void CDEADTREE::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void CDEADTREE::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void CDEADTREE::Uninit()
{
}
void CDEADTREE::Update()
{
}
void CDEADTREE::Draw()
{
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

	m_Model->Draw();
}