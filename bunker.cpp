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

	m_Colider.Init(m_Position + D3DXVECTOR3(-10.0f, 0.0f, -8.0f), m_Position+ D3DXVECTOR3(10.0f, 2.0f, 8.0f), m_Position);

	CRenderer::CreateVertexShader(&m_VertexShader[0], &m_VertexLayout,"vertexShader.cso");

	//�s�N�Z���V�F�[�_�[�t�@�C���̃��[�h���I�u�W�F�N�g�쐬
	CRenderer::CreatePixelShader(&m_PixelShader[0],"pixelShader.cso");

	CRenderer::CreateVertexShader(&m_VertexShader[1], &m_VertexLayout, "vertexShader.cso");

	//�s�N�Z���V�F�[�_�[�t�@�C���̃��[�h���I�u�W�F�N�g�쐬
	CRenderer::CreatePixelShader(&m_PixelShader[1], "pixelShader.cso");
}

void CBUNKER::Uninit()
{
}
void CBUNKER::Update()
{
	m_Colider.update(m_Position);

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

	//�C���v�b�g���C�A�E�g�̃Z�b�g(DirectX�֒��_�̍\����������)
	CRenderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	//�o�[�e�b�N�X�V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g
	CRenderer::GetDeviceContext()->VSSetShader(m_VertexShader[0], NULL, 0);
	//�s�N�Z���V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g
	CRenderer::GetDeviceContext()->PSSetShader(m_PixelShader[0], NULL, 0);

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

	ID3D11ShaderResourceView* shadowDepthTexture = CRenderer::GetShadowDepthTexture();//-�ǉ�
	CRenderer::GetDeviceContext()->PSSetShaderResources(1, 1, &shadowDepthTexture);//-�ǉ�

	m_Model->Draw();

	//�C���v�b�g���C�A�E�g�̃Z�b�g(DirectX�֒��_�̍\����������)
	CRenderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	//�o�[�e�b�N�X�V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g
	CRenderer::GetDeviceContext()->VSSetShader(m_VertexShader[1], NULL, 0);
	//�s�N�Z���V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g
	CRenderer::GetDeviceContext()->PSSetShader(m_PixelShader[1], NULL, 0);

}

void CBUNKER::Load(FILE*fp, int line)
{
	for (int i = 0; i < line * 3; i++)
	{
		fscanf(fp, "");
	}

	fscanf(fp, "%f%f%f", &m_Position.x, &m_Position.y, &m_Position.z);
	fscanf(fp, "%f%f%f", &m_Rotation.x, &m_Rotation.y, &m_Rotation.z);
	fscanf(fp, "%f%f%f", &m_Scale.x, &m_Scale.y, &m_Scale.z);
}