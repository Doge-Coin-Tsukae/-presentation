//=====================================
//
//  �`���[�g���A���V�[��
//  written by Y.Okubo
//
//=====================================
#include <list>
#include <vector>
#include <typeinfo>
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "gamemaneger.h"
#include "Game.h"
#include "tutorial.h"

#include "gameobject.h"
#include "camera.h"
#include "meshfield.h"
#include "human.h"
#include "model.h"
#include "animationmodel.h"
#include "colider.h"
#include "sight.h"
#include "weapon.h"
#include "behavior.h"

#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "bunker.h"
#include "polygon.h"
#include "skydome.h"
#include "base.h"
#include "deadtree.h"

#include "explosion.h"
#include "smoke.h"
#include "tree.h"
#include "number.h"
#include "gauge.h"
#include "weapon2d.h"
#include "captureui.h"
#include "playerui.h"
#include "tutorial2D.h"

void CTutorial::Init()
{
	m_Clik = false;

	//�e�N�X�`�� + ���f�����[�h
	CBullet::Load();			//�e�̃��f�����Ăяo��
	CBUNKER::Load();			//�o���J�[�̃��f�����Ăяo��
	CWEAPON::Load();			//�e�̃��f�����Ăяo��
	CSMOKE::Load();				//���̉摜���Ăяo��


	m_GameManeger = new CGAME_MANEGER;		
	m_GameManeger->Init(GAME_RULE_TUTORIAL);		//���[���ݒ�

	//�g���Q�[���I�u�W�F�N�g�Ăяo��
	//�J����0�� 3D���f��1�� 3D���f��(�������̃I�u�W�F�N�g)2�� �r���{�[�h(��)��3�� 2D���f��4��
	AddGameObject<CCamera>(0);		//�J����

	AddGameObject<CSKYDOME>(1);		//�X�J�C�h�[��
	AddGameObject<CMeshField>(1)->flatworld();		//���b�V���t�B�[���h(�`���[�g���A���l�ɐ^�����ɂ���)
	AddGameObject<CPlayer>(1)->SetPosition(D3DXVECTOR3(350.0f, 1.0f,  -200.0f));	//�v���C���[(�`���[�g���A���p)

	AddGameObject<CBASE>(2)->SetPosition(D3DXVECTOR3(300.0f, 0.0f,-200.0f));		//���_(�`���[�g���A���p)

	AddGameObject<CWEAPON2D>(4);
	AddGameObject<CPLAYERUI>(4);

	CFADE::Fade_Start(false, 60);		//�t�F�[�h(���񂾂�Ɖ�ʂɏo��)
}

void CTutorial::Uninit()
{
	//���X�g�ɓ����Ă���Q�[���I�u�W�F�N�g���폜
	CScene::Uninit();

	//�e�N�X�`���A�����[�h
	CSMOKE::Unload();
	CWEAPON::UnLoad();
	CBullet::Unload();
	CBUNKER::Unload();

	m_GameManeger->Uninit();
	delete m_GameManeger;

	StopSound();		//���y�ƌ��ʉ����~�߂�
}

void CTutorial::Update()
{
	CScene::Update();	//���X�g�ɓ����Ă���Q�[���I�u�W�F�N�g���Ăяo��

	//�X�y�[�X�L�[�ŏI���悤�ɂ���
	if (CInput::GetKeyTrigger(VK_SPACE))
	{
		m_Clik = true;
		CFADE::Fade_Start(true, 60);	//�t�F�[�h������
	}

	m_GameManeger->Update();


	if (m_Clik == false) { return; }
	if (CFADE::Fade_IsFade() == false)
	{
		CManager::SetScene<CGame>();
	}
}