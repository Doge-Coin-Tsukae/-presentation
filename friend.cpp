//****************************************
//�G
//****************************************

#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "model.h"
#include "human.h"
#include "Vector.h"
#include "model.h"
#include "animationmodel.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "player.h"
#include "enemy.h"
#include "friend.h"

class CAnimationModel* CFriend::m_Animodel;

#define		ANIMEBLENDSPEED	0.1f

typedef struct
{
	char *pFilename;	// �t�@�C����
} ANIMENAME3;

ANIMENAME3 g_aParam2[5] =
{
	{(char *)"idle"},				// �ҋ@
	{(char *)"ready"},				// �\����
	{(char *)"run"},				// ����
	{(char *)"fire"},				//����
	{(char *)"Death"},
};

void CFriend::Load()
{
	m_Animodel = new CAnimationModel();
	m_Animodel->Load("asset\\model\\player\\chara.fbx");					//���f���̃��[�h(�{�[���t��)
	m_Animodel->LoadAnimation("asset\\model\\player\\idle.fbx", g_aParam2[0].pFilename);		//�A�j���[�V����
	m_Animodel->LoadAnimation("asset\\model\\player\\ready.fbx", g_aParam2[1].pFilename);		//�A�j���[�V����
	m_Animodel->LoadAnimation("asset\\model\\player\\run.fbx", g_aParam2[2].pFilename);		//�A�j���[�V����
	m_Animodel->LoadAnimation("asset\\model\\player\\fire.fbx", g_aParam2[3].pFilename);
	m_Animodel->LoadAnimation("asset\\model\\player\\Death.fbx", g_aParam2[4].pFilename);
}

void CFriend::Unload()
{
	m_Animodel->Unload();
	delete m_Animodel;
}

void CFriend::Init()
{
	m_Sight = new CSIGHT();
	m_Sight->Init();
	m_Sight->Setparent(this);		//�Ə��̐e��������

	m_Weapon = new CWEAPON();
	m_Weapon->Init();
	m_Weapon->Setparent(this);		//����̐e��������

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_ModelRot = D3DXVECTOR3(1.6f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.3f, 1.3f, 1.3f);
	m_TeamNumber = TEAM_FRIENDRY;		//�`�[���ݒ�

	//�A�j���[�V����
	m_NowAnimationChara = g_aParam2[0].pFilename;
	m_OldAnimationChara = g_aParam2[1].pFilename;
	m_Frame = 0;
	rate = 0;
}

void CFriend::Uninit()
{
	m_Weapon->Uninit();
	delete m_Weapon;

	m_Sight->Uninit();
	delete m_Sight;
}

void CFriend::Update()
{
	rate = std::min(rate, 1.0f);
	rate = std::max(rate, 0.0f);

	//�w���p�[�֐�
	Update_AI();
	//�v���C���[�ɓ����Ă���N���X�̍X�V����
	m_Sight->Update();
	m_Weapon->Update();

	rate += ANIMEBLENDSPEED;
	m_Frame+=0.3f;
}

void CFriend::Update_AI()
{
	CScene* scene = CManager::GetScene();
	std::vector<CEnemy*> enemyList = scene->GetGameObjects<CEnemy>(1);
	CEnemy* NearEnemy=nullptr;		//�����Ɉ�ԋ߂��G
	float nearlength,enemylength;


	for (CEnemy* enemy : enemyList)
	{
		D3DXVECTOR3 direction = m_Position - enemy->GetPosition();
		enemylength = D3DXVec3Length(&direction);

		if (NearEnemy == nullptr || nearlength > enemylength)
		{
			NearEnemy = enemy;
			nearlength = enemylength;
		}
	}

	LookEnemy(NearEnemy);

	//�͈͓��ɂȂ�����ڋ߂���
	if (nearlength < 100.0f)
	{
		if (nearlength > 20.0f)
		{
			D3DXVECTOR3 Velocity = GetVector(m_Position, NearEnemy->GetPosition());
			m_Position += Velocity / 10;
			ChangeAnimation((char*)"run");
		}
		else
		{
			D3DXVECTOR3 pos(0, 1.5f, 0);
			m_Weapon->Shoot(pos+m_Sight->GetPosition(), m_TeamNumber);
			ChangeAnimation((char*)"fire");
		}
	}
	else
	{
		ChangeAnimation((char*)"idle");
	}

	if (m_Weapon->GetAmmo() <= 0)
	{
		m_Weapon->Reload();
	}
}

void CFriend::Draw()
{
	//�����N���X����
	m_Weapon->Draw();
	m_Sight->Draw();

	//�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	//�g��k���̃}�g���N�X
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//���[�s�b�`���[���̃}�g���N�X
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x + m_ModelRot.x, -m_Rotation.z - m_ModelRot.z, m_Rotation.y + m_ModelRot.y);
	//�ʒu�}�g���N�X6
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	CRenderer::SetWorldMatrix(&world);

	m_Animodel->Update(m_OldAnimationChara, m_NowAnimationChara, m_Frame, rate);
	m_Animodel->Draw();
}

void CFriend::LookEnemy(CEnemy* enemy)
{
	if (enemy == nullptr)return;

	D3DXVECTOR3 Velocity = GetVector(m_Position, enemy->GetPosition());
	D3DXVECTOR3 Velocity2 = GetVector(m_Position, m_Sight->GetPosition());
	m_Rotation.x += (Velocity.x * Velocity2.x + Velocity.z*Velocity2.z) / (sqrt((Velocity.x*Velocity.x) + (Velocity.z*Velocity.z))*sqrt((Velocity2.x*Velocity2.x) + (Velocity2.z*Velocity2.z)));
	m_Rotation.x -= 1.0f;
}

void CFriend::ChangeAnimation(char* Name)
{
	if (m_NowAnimationChara == Name)return;	//���̃A�j���[�V�����Ǝ��̃A�j���[�V�������ꏏ�Ȃ�
	m_OldAnimationChara = m_NowAnimationChara;		//�V�����A�j���[�V�����f�[�^���Â��A�j���[�V�����f�[�^�ɂ���
	m_NowAnimationChara = Name;						//�V�����A�j���[�V�����f�[�^������
	rate = 0.0f;									//�u�����h�l�����Z�b�g
}