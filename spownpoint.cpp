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

#include "human.h"
#include "animationmodel.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "behavior.h"
#include "enemy.h"
#include "friend.h"

#include "spownpoint.h"


void CSpownPoint::Init()
{
	//���g�̕ϐ��̐ݒ�
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_SpownType = FRIENDRY_SPOWN;
	m_SpownedNum = 0;
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

	m_time++;
	if (m_spowninterval <= m_time)
	{
		Spown();
		m_time = 0;
	}
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
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	//�ʒu�}�g���N�X
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	CRenderer::SetWorldMatrix(&world);

	m_Model->Draw();		//���̕`��
}

void CSpownPoint::Spown()
{
	CScene* scene = CManager::GetScene();
	if (SpownConditions() == false) return;		//�����������Ȃ��Ƃ��͕������Ȃ�

	if (m_SpownType == ENEMY_SPOWN)
	{
		scene->AddGameObject<CEnemy>(1)->SetPosition(m_Position);
		m_SpownedNum++;
		return;
	}

	if (m_SpownType == FRIENDRY_SPOWN)
	{
		scene->AddGameObject<CFriend>(1)->SetPosition(m_Position);
		m_SpownedNum++;
		return;
	}
}

bool CSpownPoint::SpownConditions()
{
	//�������̂Ƃ��A�������ŃN���A
	if (m_Max == -1)  return true;

	//����ɒB���Ă��Ȃ��Ƃ��͕���
	if (m_SpownedNum < m_Max) return true;

	//���ݒ肪�ɂȂ����畦��
	if (m_Spownlicense == true) return true;
	//����ȊO�͕������Ȃ�
	return false;
}