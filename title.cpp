//=====================================
//
//  �^�C�g���V�[��
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
#include "fade.h"
#include "input.h"

#include "gameobject.h"
#include "camera.h"
#include "meshfield.h"
#include "model.h"
#include "titleeffectmanager.h"

#include "shellexplosion.h"

#include"colider.h"
#include "bunker.h"
#include "polygon.h"
#include "skydome.h"
#include "base.h"
#include "deadtree.h"
#include "tree.h"

#include "polygon.h"
#include "gamemaneger.h"
#include "title2D.h"
#include "Title.h"
#include "tutorial.h"

void CTitle::Init()
{
	m_Clik = false;

	CDEADTREE::Load();	//�͂�؂̃��f�����Ăяo��
	CBUNKER::Load();	//�o���J�[�̃��f�����Ăяo��
	CShellExplosion::LoadTexture();		//�e�N�X�`���Z�b�g

	//�I�u�W�F�N�g�ݒu
	AddGameObject<CCamera>(0);

	AddGameObject<CSKYDOME>(1);
	AddGameObject<CMeshField>(1)->flatworld();

	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(30.0f, 0.0f, -150.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(45.0f, 0.0f, -160.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(30.0f, 0.0f, -155.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(35.0f, 0.0f, -135.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(30.0f, 0.0f, -120.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(45.0f, 0.0f, -130.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(30.0f, 0.0f, -175.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(35.0f, 0.0f, -180.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(70.0f, 0.0f, -165.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(75.0f, 0.0f, -125.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(80.0f, 0.0f, -175.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(95.0f, 0.0f, -135.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(70.0f, 0.0f, -120.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(95.0f, 0.0f, -130.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(80.0f, 0.0f, -175.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(65.0f, 0.0f, -160.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(95.0f, 0.0f, -150.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(120.0f, 0.0f, -175.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(150.0f, 0.0f, -160.0f));
	AddGameObject<CBUNKER>(1)->SetPosition(D3DXVECTOR3(160.0f, 0.0f, -240.0f));

	AddGameObject<Title_Effect_Manager>(2);

	AddGameObject<CTITLE2D>(4);

	CScene* scene = CManager::GetScene();
	CBUNKER*  bunker = scene->GetGameObject<CBUNKER>(1);
	bunker->SetRotation(D3DXVECTOR3(0.0f,-2.5f,0.0f));			//�p�x�w��

}

void CTitle::Uninit()
{
	//�������J��
	CDEADTREE::Unload();
	CBUNKER::Unload();
	CShellExplosion::UnLoadTexture();
}

void CTitle::Update()
{
	CScene::Update();

	Update_InPut();
	isFade();
}

void CTitle::isFade()
{
	if (m_Clik == false) return;		//��x���N���b�N����Ă��Ȃ��ꍇ�͏������s��Ȃ�
	if (CFADE::Fade_IsFade() == false)
	{
		StopSound();						//����Ă��鉹�y���~�߂�
		CManager::SetScene<CTutorial>();	//�`���[�g���A����ʂɑJ��
	}
}

void CTitle::Update_InPut()
{
	//�X�y�[�X�L�[����������
	if (CInput::GetKeyTrigger(VK_SPACE) && m_Clik == false)
	{
		m_Clik = true;				//���N���b�N���ꂽ
		PlaySound(SOUND_SE_CLICK);	//�N���b�N��
		CFADE::SetTexture((char*)"asset/texture/fade.png");		//�t�F�[�h�̃e�N�X�`���Z�b�g
		CFADE::Fade_Start(true, 60);
	}
}