//=====================================
//
//  �L�����N�^�[�����˂���e
//  written by Y.Okubo
//
//=====================================
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "Vector.h"
#include "sound.h"
#include "model.h"
#include "camera.h"
#include "explosion.h"
#include "human.h"
#include "animationmodel.h"
#include "behavior.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "enemy.h"
#include "friend.h"
#include "player.h"
#include "bullet.h"
#include "bunker.h"
class CModel* CBullet::m_Model;

void CBullet::Load()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\bullet.obj");
}

void CBullet::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void CBullet::Init()
{
	DeleteTime = 8.0f;
	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_Colision = new CCOLIDER_CIRCLE();
	m_Colision->Init();
	m_Colision->SetScale(D3DXVECTOR3(3.0f, 3.0f,3.0f));
}

void CBullet::Uninit()
{
	m_Colision->Uninit();
	delete m_Colision;
}

void CBullet::Update()
{
	//���Ԃ�0�ɂȂ�����폜
	if (DeleteTime <=0.0f)
	{
		SetDestroy();
		return;
	}

	Update_Collision();	//�����蔻��
	Update_Varios();	//���W�̍X�V
}

void CBullet::Update_Varios()
{
	m_Position += m_Velocity * 5.0f;
	DeleteTime -= 0.1f;
}

void CBullet::Update_Collision()
{
	//�����蔻��X�V
	m_Colision->Update();
	m_Colision->SetPosition(m_Position);

	CScene* scene = CManager::GetScene();

	//�e�������̕���������
	if (m_TeamNumber == TEAM_FRIENDRY)
	{
		std::vector<CEnemy*> enemyList = scene->GetGameObjects<CEnemy>(1);

		//���ׂĂ̓G�Ƃ̓����蔻��𒲂ׂ�
		for (CEnemy* enemy : enemyList)
		{	//�e�ƓG�̓����蔻��
			if (m_Colision->GetColider(enemy->GetPosition()))
			{
				scene->AddGameObject<CExplosion>(2)->SetPosition(m_Position);	//��ʂɔ����̃e�N�X�`���\��������
				enemy->Death();													//�G�����S������
				SetDestroy();													//���g������
				return;
			}
		}
	}

	//�e���G�̕��������ꍇ
	if (m_TeamNumber == TEAM_ENEMY)
	{
		std::vector<CFriend*> friendList = scene->GetGameObjects<CFriend>(1);
		CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

		//�v���C���[�̓����蔻��
		if (m_Colision->GetColider(pPlayer->GetPosition()))
		{
			pPlayer->Damage();
			SetDestroy();
			return;
		}

		//���ׂĂ̖����Ƃ̓����蔻��𒲂ׂ�
		for (CFriend* friends : friendList)
		{
			if (m_Colision->GetColider(friends->GetPosition()))
			{
				scene->AddGameObject<CExplosion>(2)->SetPosition(m_Position);	//��ʂɔ����̃e�N�X�`���\��������
				friends->Death();												//�G�����S������
				SetDestroy();
				return;
			}
		}
	}
}

void CBullet::Draw()
{
	CScene* scene = CManager::GetScene();
	CCamera* camera = scene->GetGameObject <CCamera>(0);

	//��ʂ���͂ݏo�Ă���\�����s��Ȃ�
	if (!camera->CheckView(m_Position))
		return;

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

void  CBullet::Set(D3DXVECTOR3 SetPos, D3DXVECTOR3 SetSight,TEAM_NUMBER SetNUMBER)
{
	m_Position = SetPos;
	m_Velocity = GetNorm(SetPos,SetSight);
	m_TeamNumber = SetNUMBER;
}