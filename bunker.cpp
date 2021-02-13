#include "main.h"
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "model.h"
#include "camera.h"
#include "meshfield.h"
#include "colider.h"
#include "bunker.h"

class CModel* CBUNKER::m_Model;

void CBUNKER::Load()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\bunker.obj");
}

void CBUNKER::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void CBUNKER::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_Obb = new OBB;
	m_Obb->Init();
	m_Obb->parent(m_Position, m_Rotation, m_Scale);
	m_Obb->SetScale(D3DXVECTOR3(24,1,15));
}

void CBUNKER::Uninit()
{
}
void CBUNKER::Update()
{

	//���b�V���t�B�[���h�����擾
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);

}
void CBUNKER::Draw()
{
	CScene* scene = CManager::GetScene();
	CCamera* camera = scene->GetGameObject <CCamera>(0);

	if (!camera->CheckView(m_Position))
		return;

	//�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans, shadow, modelshadow;
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

void CBUNKER::FileLoad()
{

}