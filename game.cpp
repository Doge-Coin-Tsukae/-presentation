//=====================================
//
//  �Q�[���V�[��
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
#include "scene.h"
#include "fade.h"
#include "gamemaneger.h"
#include "Game.h"

#include "gameobject.h"
#include "load.h"
#include "camera.h"
#include "meshfield.h"
#include "animationmodel.h"
#include "human.h"
#include "model.h"
#include "colider.h"
#include "behavior.h"
#include "sight.h"
#include "weapon.h"

#include "player.h"
#include "enemy.h"
#include "friend.h"
#include "bullet.h"
#include "bunker.h"
#include "polygon.h"
#include "skydome.h"
#include "base.h"
#include "deadtree.h"
#include "spownpoint.h"

#include "explosion.h"
#include "smoke.h"
#include "tree.h"
#include "number.h"
#include "gauge.h"
#include "weapon2d.h"
#include "captureui.h"
#include "playerui.h"

void CGame::Init()
{
	//�e�N�X�`�� + ���f�����[�h
	CBullet::Load();			//�e�̃��f�����Ăяo��
	CBUNKER::Load();			//�o���J�[�̃��f�����Ăяo��
	CEnemy::Load();				//�G�̃��f�����Ăяo��
	CFriend::Load();			//�����̃��f�����Ăяo��
	CWEAPON::Load();			//�e�̃��f�����Ăяo��
	CDEADTREE::Load();			//�͂�؂̃��f�����Ăяo��
	CSMOKE::Load();				//���̉摜���Ăяo��
	CExplosion::Load();			//�����̃��f�����Ăяo��

	m_GameManeger = new CGAME_MANEGER;
	m_GameManeger->Init(GAME_RULE_CONQUEST);		//���[���ݒ�

	//�g��(���[�h����K�v�̂Ȃ�)�Q�[���I�u�W�F�N�g�Ăяo��
	//�J����0�� 3D���f��1�� 3D���f��(�������̃I�u�W�F�N�g)2�� �r���{�[�h(��)��3�� 2D���f��4��
	AddGameObject<CCamera>(0);		//�J����

	AddGameObject<CLOAD>(0)->Data_Load();	//�f�[�^�̃��[�h

	AddGameObject<CSKYDOME>(1);		//�X�J�C�h�[��
	AddGameObject<CMeshField>(1);	//�n��
	AddGameObject<CWEAPON2D>(4);	//�����UI
	AddGameObject<CPLAYERUI>(4);	//�v���C���[��UI

	CFADE::SetTexture((char*)"asset/texture/fade.png");
	CFADE::Fade_Start(false,60);
}

void CGame::Uninit()
{
	//���X�g�ɓ����Ă���Q�[���I�u�W�F�N�g���폜
	CScene::Uninit();

	//�e�N�X�`���A�����[�h
	CDEADTREE::Unload();
	CExplosion::Unload();
	CSMOKE::Unload();
	CWEAPON::UnLoad();
	CFriend::Unload();
	CEnemy::Unload();
	CBUNKER::Unload();
	CBullet::Unload();

	m_GameManeger->Uninit();
	delete m_GameManeger;

	StopSound();
}

void CGame::Update()
{
	CScene::Update();	//���X�g�ɓ����Ă���Q�[���I�u�W�F�N�g���Ăяo��

	m_GameManeger->Update();
}