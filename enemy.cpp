//****************************************
//�G
//****************************************

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "scene.h"

#include "human.h"
#include "Vector.h"
#include "model.h"
#include "animationmodel.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "player.h"
#include "enemy.h"

class CModel* CEnemy::m_Model;

void CEnemy::Load()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\plauyer1.obj");
}

void CEnemy::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void CEnemy::Init()
{
	m_Sight = new CSIGHT();
	m_Sight->Init();
	m_Sight->Setparent(this);		//�Ə��̐e��������

	m_Weapon = new CWEAPON();
	m_Weapon->Init();
	m_Weapon->Setparent(this);

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.3f, 1.3f, 1.3f);
	m_TeamNumber = TEAM_ENEMY;		//�`�[���ݒ�
}

void CEnemy::Uninit()
{
	m_Weapon->Uninit();
	delete m_Weapon;

	m_Sight->Uninit();
	delete m_Sight;
}

void CEnemy::Update()
{
	//�w���p�[�֐�
	Update_AI();
	//�v���C���[�ɓ����Ă���N���X�̍X�V����
	m_Sight->Update();
	m_Weapon->Update();

}

void CEnemy::Update_AI()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	//�����蔻��
	D3DXVECTOR3 direction = m_Position - pPlayer->GetPosition();
	float length = D3DXVec3Length(&direction);

	LookPlayer();

	//�͈͓��ɂȂ�����ڋ߂���
	if (length < 100.0f)
	{
		if (length > 20.0f)
		{
			D3DXVECTOR3 Velocity = GetVector(m_Position, pPlayer->GetPosition());
			m_Position += Velocity / 10;
		}
		else
		{
			m_Weapon->Shoot(m_Sight->GetPosition(), m_TeamNumber);
		}
	}

	if (m_Weapon->GetAmmo() <= 0)
	{
		m_Weapon->Reload();
	}
}

void CEnemy::Draw()
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

	m_Model->Draw();
}

void CEnemy::LookPlayer()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	D3DXVECTOR3 Velocity = GetVector(m_Position, pPlayer->GetPosition());
	D3DXVECTOR3 Velocity2 = GetVector(m_Position,m_Sight->GetPosition());
	m_Rotation.x += (Velocity.x * Velocity2.x+ Velocity.z*Velocity2.z) / (sqrt((Velocity.x*Velocity.x) + (Velocity.z*Velocity.z))*sqrt((Velocity2.x*Velocity2.x) + (Velocity2.z*Velocity2.z)));
	m_Rotation.x -= 1.0f;
}