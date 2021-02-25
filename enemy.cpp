//=====================================
//
//	�GNPC
//  written by Y.Okubo
//
//=====================================

#include "main.h"
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "model.h"
#include "human.h"

#include "Vector.h"
#include "sound.h"
#include "camera.h"
#include "animationmodel.h"
#include "sight.h"
#include "weapon.h"
#include "rifle.h"
#include "colider.h"
#include "behavior.h"
#include "player.h"
#include "friend.h"
#include "meshfield.h"
#include "enemy.h"

class CAnimationModel* CEnemy::m_Animodel;

#define		ANIMEBLENDSPEED	0.1f

typedef struct
{
	char *pFilename;	// �t�@�C����
} ANIMENAME2;

ANIMENAME2 g_aParam2[5] =
{
	{(char *)"idle"},				// �ҋ@
	{(char *)"ready"},				// �\����
	{(char *)"run"},				// ����
	{(char *)"fire"},				//����
	{(char *)"Death"},
};

void CEnemy::Load()
{
	m_Animodel = new CAnimationModel();
	m_Animodel->Load("asset\\model\\player\\chara2.fbx");									//���f���̃��[�h(�{�[���t��)
	m_Animodel->LoadAnimation("asset\\model\\player\\idle.fbx", g_aParam2[0].pFilename);	//�A�j���[�V����
	m_Animodel->LoadAnimation("asset\\model\\player\\ready.fbx", g_aParam2[1].pFilename);
	m_Animodel->LoadAnimation("asset\\model\\player\\run.fbx", g_aParam2[2].pFilename);
	m_Animodel->LoadAnimation("asset\\model\\player\\fire.fbx", g_aParam2[3].pFilename);
	m_Animodel->LoadAnimation("asset\\model\\player\\Death.fbx", g_aParam2[4].pFilename);
}

void CEnemy::Unload()
{
	m_Animodel->Unload();
	m_Animodel->UnloadAnimation();
	delete m_Animodel;
}

void CEnemy::Init()
{
	
	m_Sight = new CSIGHT();
	m_Sight->Init();
	m_Sight->Setparent(this);		//�Ə��̐e��������

	m_Weapon = new Crifle();
	m_Weapon->Init();
	m_Weapon->Setparent(this);		//����̐e��������

	m_AI = new CEnemyAIRoot();
	m_AI->Init(this);

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_ModelRot = D3DXVECTOR3(1.6f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.3f, 1.3f, 1.3f);
	m_TeamNumber = TEAM_ENEMY;		//�`�[���ݒ�
	m_Death = false;

	//�A�j���[�V����
	m_NowAnimationChara = g_aParam2[0].pFilename;
	m_OldAnimationChara = g_aParam2[1].pFilename;
	m_Frame = 0;
	rate = 0;
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
	rate = std::min(rate, 1.0f);
	rate = std::max(rate, 0.0f);

	//�w���p�[�֐�
	Update_AI();
	//�v���C���[�ɓ����Ă���N���X�̍X�V����
	m_Sight->Update();
	m_Weapon->Update();

	rate += ANIMEBLENDSPEED;
	m_Frame+=0.3f;

	//���b�V���t�B�[���h�����擾
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);

	//���񂾎��̏���
	if (m_Death == true)
	{
		m_OldAnimationChara = (char*)"Death";
		m_NowAnimationChara = (char*)"Death";

		m_Frame += 0.7f;
		if (m_Frame > 177)
			SetDestroy();
	}
}

void CEnemy::Update_AI()
{
	if (m_Death) return;

	m_AI->Update();

}

void CEnemy::Draw()
{
	
	CScene* scene = CManager::GetScene();
	CCamera* camera = scene->GetGameObject <CCamera>(0);

	if (!camera->CheckView(m_Position))
		return;

	//m_Weapon->Draw();

	//�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	//�g��k���̃}�g���N�X
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//���[�s�b�`���[���̃}�g���N�X
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y + m_ModelRot.x, -m_Rotation.x - m_ModelRot.z, m_Rotation.z + m_ModelRot.y);
	//�ʒu�}�g���N�X
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	CRenderer::SetWorldMatrix(&world);

	m_Animodel->Update(m_OldAnimationChara, m_NowAnimationChara, m_Frame, rate);
	m_Animodel->Draw();
}

void CEnemy::LookPlayer()
{
	if (LockOnEnemy == nullptr)return;

	D3DXVECTOR3 Velocity = GetNorm(m_Position, LockOnEnemy->GetPosition());
	D3DXVECTOR3 Velocity2 = GetNorm(m_Position, m_Sight->GetPosition());
	m_Rotation.y += (Velocity.x * Velocity2.x + Velocity.z * Velocity2.z) / (sqrt((Velocity.x * Velocity.x) + (Velocity.z * Velocity.z)) * sqrt((Velocity2.x * Velocity2.x) + (Velocity2.z * Velocity2.z)));
	m_Rotation.y -= 1.0f;
}

void CEnemy::ChangeAnimation(char* Name)
{
	if (m_NowAnimationChara == Name)return;	//���̃A�j���[�V�����Ǝ��̃A�j���[�V�������ꏏ�Ȃ�
	m_OldAnimationChara = m_NowAnimationChara;		//�V�����A�j���[�V�����f�[�^���Â��A�j���[�V�����f�[�^�ɂ���
	m_NowAnimationChara = Name;						//�V�����A�j���[�V�����f�[�^������
	rate = 0.0f;									//�u�����h�l�����Z�b�g
}

void CEnemy::Death()
{
	if (m_Death == true) return;
	PlaySound(SOUND_SE_DEATH);
	m_Death = true;
	m_Frame = 1;
}

bool CEnemy::Shoot()
{
	if (m_Weapon->GetAmmo() <= 0) return false;

	m_Weapon->Shoot(m_Sight->GetPosition(), m_TeamNumber);
	ChangeAnimation((char*)"fire");
	return true;
}

void CEnemy::Reload()
{
	m_Weapon->Reload();
}

bool CEnemy::isOverReload()
{
	return m_Weapon->GetAmmo() > 0;
}



void CEnemyAIRoot::Init(CEnemy* Sparent)
{
	parent = Sparent;
	m_Index = 0;
	m_child_Node[0] = new CEnemySequence(Sparent);
	m_child_Node[1] = new CEnemySelector(Sparent);
}

RESULT CEnemyAIRoot::Update()
{
	if (parent == nullptr) return RESULT_FAILED;

	//�v���C���[���痣��Ă�����ړ�
	//�߂�������U��
	//���S�����牽���s��Ȃ�

	RESULT ret = m_child_Node[m_Index]->Update();

	switch (ret)
	{
	case RESULT_PROGRESS:
		return RESULT_PROGRESS;
	case RESULT_SUCCEEDED:
		if (m_Index == 0) m_Index = 1;
		return RESULT_SUCCEEDED;
	case RESULT_FAILED:
		m_Index = 0;
		return RESULT_FAILED;
	}
}


CEnemySelector::CEnemySelector(CEnemy* parent)
{
	m_parent = parent;
	m_child_Node[0] = new CEnemyShootNode(m_parent);
	m_child_Node[1] = new CEnemyReloadNode(m_parent);
}

RESULT CEnemySelector::Update()
{
	RESULT ret = m_child_Node[m_Index]->Update();

	switch (ret)
	{
	case RESULT_PROGRESS:
		return RESULT_PROGRESS;
	case RESULT_SUCCEEDED:
		m_Index--;
		return RESULT_SUCCEEDED;

	case RESULT_FAILED:
		if (m_parent->isOverReload() == false)
		{
			m_Index++;
			return RESULT_PROGRESS;
		}
		return RESULT_FAILED;
	}
}

CEnemySequence::CEnemySequence(CEnemy* parent)
{
	m_parent = parent;
	m_child_Node[0] = new CEnemySearchNode(m_parent);
	m_child_Node[1] = new CEnemyWalkNode(m_parent);
}

CEnemySearchNode::CEnemySearchNode(CEnemy* parent)
{
	m_parent = parent;
}

RESULT CEnemySearchNode::Update()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	m_parent->SetLockOnEnemy(pPlayer);		//�v���C���[�����b�N�I��

	return RESULT_SUCCEEDED;
}

CEnemyWalkNode::CEnemyWalkNode(CEnemy* parent)
{
	m_parent = parent;
}

RESULT CEnemyWalkNode::Update()
{
	;
	D3DXVECTOR3 Velocity = GetNorm(m_parent->GetPosition(), m_parent->GetLockOnEnemy()->GetPosition());
	D3DXVECTOR3 Position = m_parent->GetPosition() + Velocity / 15;

	m_parent->LookPlayer();
	m_parent->ChangeAnimation((char*)"run");
	m_parent->SetPosition(Position);

	//�����蔻��
	D3DXVECTOR3 direction = m_parent->GetPosition() - m_parent->GetLockOnEnemy()->GetPosition();
	float length = D3DXVec3Length(&direction);
	if (length < 30.0f) return RESULT_SUCCEEDED;

	return RESULT_PROGRESS;
}

CEnemyShootNode::CEnemyShootNode(CEnemy* parent)
{
	m_parent = parent;
}

RESULT CEnemyShootNode::Update()
{
	//�����蔻��
	D3DXVECTOR3 direction = m_parent->GetPosition() - m_parent->GetLockOnEnemy()->GetPosition();
	float length = D3DXVec3Length(&direction);
	m_parent->LookPlayer();

	if (length > 60.0f) return RESULT_FAILED;					//���b�N�I�����Ă����L�������͈͊O�ɓ�������
	if (m_parent->Shoot() == false) return RESULT_FAILED;		//�e�؂ꂾ������

	return RESULT_PROGRESS;
}

CEnemyReloadNode::CEnemyReloadNode(CEnemy* parent)
{
	m_parent = parent;
}

RESULT CEnemyReloadNode::Update()
{
	if (m_parent->isOverReload() == true) return RESULT_SUCCEEDED;

	m_parent->Reload();

	return RESULT_PROGRESS;
}