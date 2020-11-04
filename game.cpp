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
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "input.h"
#include "scene.h"
#include "fade.h"
#include "gamemaneger.h"
#include "Game.h"
#include "Result.h"

#include "gameobject.h"
#include "camera.h"
#include "field.h"
#include "meshfield.h"
#include "animationmodel.h"
#include "human.h"
#include "model.h"
#include "colider.h"
#include "sight.h"
#include "weapon.h"

#include "player.h"
#include "enemy.h"
#include "friend.h"
#include "enemycommander.h"
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

void CGame::Init()
{
	//�e�N�X�`�� + ���f�����[�h
	CBullet::Load();	//�e�̃��f�����Ăяo��
	CBUNKER::Load();	//�o���J�[�̃��f�����Ăяo��
	CEnemy::Load();		//�G�̃��f�����Ăяo��
	CFriend::Load();
	CWEAPON::Load();	//�e�̃��f�����Ăяo��
	CDEADTREE::Load();	//�͂�؂̃��f�����Ăяo��
	CSMOKE::Load();		//���̉摜���Ăяo��

	m_GameManeger = new CGAME_MANEGER;
	m_GameManeger->Init(GAME_RULE_CONQUEST);

	//�g���Q�[���I�u�W�F�N�g�Ăяo��
	//�J����0�� 3D���f��1�� 3D���f��(�����蔻��̂��)2�� �r���{�[�h(��)��3�� 2D���f��4��
	AddGameObject<CCamera>(0);

	AddGameObject<CSKYDOME>(1);

	//�n��
	//AddGameObject<CMeshField>(1);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			AddGameObject<CField>(1)->SetPosition(D3DXVECTOR3(-400 + i * 100, 0, -400 + j * 100));
		}
	}

	AddGameObject<CPlayer>(1)->SetPosition(D3DXVECTOR3(0.0f, 1.0f, -200.0f));

	AddGameObject<CENEMY_COMMANDER>(1);

	AddGameObject<CEnemy>(1)->SetPosition(D3DXVECTOR3(5.0f, 1.0f, 0.0f));
	AddGameObject<CEnemy>(1)->SetPosition(D3DXVECTOR3(10.0f, 1.0f, 0.0f));
	AddGameObject<CEnemy>(1)->SetPosition(D3DXVECTOR3(12.0f, 1.0f, 0.0f));
	AddGameObject<CEnemy>(1)->SetPosition(D3DXVECTOR3(5.0f, 1.0f, -100.0f));
	AddGameObject<CEnemy>(1)->SetPosition(D3DXVECTOR3(10.0f, 1.0f,-100.0f));
	AddGameObject<CEnemy>(1)->SetPosition(D3DXVECTOR3(12.0f, 1.0f,-100.0f));

	AddGameObject<CFriend>(1)->SetPosition(D3DXVECTOR3(12.0f, 1.0f, -200.0f));

	AddGameObject<CBUNKER>(1)->SetPosition(D3DXVECTOR3(40.0f, 0.0f, -130.0f));
	AddGameObject<CBUNKER>(1)->SetPosition(D3DXVECTOR3(-40.0f, 0.0f, -130.0f));

	CScene* scene = CManager::GetScene();
	std::vector<CBUNKER*> bunkerList = scene->GetGameObjects<CBUNKER>(1);
	for (CBUNKER* Bunker : bunkerList)
	{
		Bunker->SetRotation(D3DXVECTOR3(3.2f,0.0f,0.0f));
	}
	AddGameObject<CBUNKER>(1)->SetPosition(D3DXVECTOR3(40.0f, 0.0f,  30.0f));
	AddGameObject<CBUNKER>(1)->SetPosition(D3DXVECTOR3(-40.0f, 0.0f, 30.0f));

	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(-40.0f, 0.0f, 0.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(-60.0f, 0.0f, 10.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(-70.0f, 0.0f, -5.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(-50.0f, 0.0f, 5.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3( 30.0f, 0.0f, -50.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(-30.0f, 0.0f, -60.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3( 0.0f, 0.0f, -40.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3( 20.0f, 0.0f,-20.0f));

	AddGameObject<CBASE>(2)->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -70.0f));
	AddGameObject<CBASE>(2)->SetPosition(D3DXVECTOR3(-50.0f, 0.0f, 90.0f));

	AddGameObject<CTREE>(2)->SetPosition(D3DXVECTOR3(-50.0f, 5.0f, -150.0f));
	AddGameObject<CTREE>(2)->SetPosition(D3DXVECTOR3(-15.0f, 5.0f, -150.0f));
	AddGameObject<CTREE>(2)->SetPosition(D3DXVECTOR3(20.0f, 5.0f, -160.0f));
	AddGameObject<CTREE>(2)->SetPosition(D3DXVECTOR3(-30.0f, 5.0f, -170.0f));
	AddGameObject<CTREE>(2)->SetPosition(D3DXVECTOR3(30.0f, 5.0f, -180.0f));

	AddGameObject<CWEAPON2D>(4);
	AddGameObject<CPLAYERUI>(4);

	//PlaySound(SOUND_BGM_BGM002);

	CFADE::SetTexture((char*)"asset/texture/fade.png");
	CFADE::Fade_Start(false,60,D3DCOLOR());
}

void CGame::Uninit()
{
	//���X�g�ɓ����Ă���Q�[���I�u�W�F�N�g���폜
	CScene::Uninit();

	//�e�N�X�`���A�����[�h
	CDEADTREE::Unload();
	CSMOKE::Unload();
	CWEAPON::UnLoad();
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