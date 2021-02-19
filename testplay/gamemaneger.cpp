//=====================================
//
//  �Q�[�����[���ƃ��[�������锠
//  written by Y.Okubo
//
//=====================================
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "title.h"
#include "human.h"

#include "polygon.h"
#include "model.h"
#include "animationmodel.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "player.h"
#include "base.h"
#include "vicordef.h"

#include "gamemaneger.h"



//���[��(�R���N�G�X�g)
void CConquest::Init()
{
	m_deleted = false;
	m_Defeat = false;
	m_Victory = false;
}
void CConquest::Uninit()
{

}
void CConquest::Update()
{
	VictoryOrDefeatConditions();	//���s�������`�F�b�N����

	CScene* scene = CManager::GetScene();

	//���U���g��ʂɈڍs����
	VICORDEF* vic = scene->GetGameObject<VICORDEF>(4);
	if (vic != nullptr)
	{
		//�t�F�[�h�I����������
		if (m_deleted == true)
		{
			if (CFADE::Fade_IsFade() == false)
			{
				StopSound();
				CManager::SetScene<CTitle>();
				return;
			}
		}
		if (vic->GetDelete())
		{
			//�t�F�[�h�̎��s
			if (m_deleted == true)return;
			CFADE::SetTexture((char*)"asset/texture/fade.png");
			CFADE::Fade_Start(true, 90, D3DCOLOR());

			m_deleted = true;
		}
	}

	//���������𖞂������Ƃ�
	if (m_Victory == true)
	{
		scene->AddGameObject<VICORDEF>(4)->Set(true);
		return;
	}
	//�s�k�����𖞂������Ƃ�
	if (m_Defeat == true)
	{
		scene->AddGameObject<VICORDEF>(4)->Set(false);
		return;
	}
}
void CConquest::VictoryOrDefeatConditions()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);
	std::vector<CBASE*> baseList = scene->GetGameObjects<CBASE>(2);

	//���Z�b�g
	for (int i = 0; i < 2; i++)
	{
		m_BaseCaptcha[i] = 0;
	}

	//�v���C���[�����񂾂畉���ɂ���
	if (pPlayer->isDeath() == true)
		m_Defeat = true;

	int BaseCount = 0;

	//�ȉ���������
	for (CBASE* base : baseList)
	{
		if (base->GetTerritory() == FRIENDRY_ZONE) { m_BaseCaptcha[0]++; }
		if (base->GetTerritory() == ENEMY_ZONE) { m_BaseCaptcha[1]++; }
		BaseCount++;
	}
	//���_�S��������珟���ɂ���
	if (m_BaseCaptcha[0] >= BaseCount)
		m_Victory = true;
}

//���[���𑩂˂�}�l�[�W���[
void CGAME_MANEGER::Init(GAME_RULE SetRule)
{
	m_GameMode = SetRule;

	//�I�΂ꂽ���[���ɂ���đ������N���X��ύX����
	switch (m_GameMode)
	{
	case GAME_RULE_CONQUEST:
		m_Rule = new CConquest;
		break;
	case GAME_RULE_DEATHMATH:
		break;
	default:
		break;
	}

	m_Rule->Init();
}
void CGAME_MANEGER::Uninit()
{
	m_Rule->Uninit();
	delete m_Rule;
}
void CGAME_MANEGER::Update()
{
	m_Rule->Update();
}