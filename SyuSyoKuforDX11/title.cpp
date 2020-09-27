//=====================================
//
//  タイトルシーン
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
#include "fade.h"
#include "input.h"
#include "human.h"

#include "gameobject.h"
#include "camera.h"
#include "field.h"
#include "model.h"
#include "colider.h"
#include "sight.h"
#include "weapon.h"

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

	CDEADTREE::Load();	//枯れ木のモデルを呼び出す

	AddGameObject<CCamera>(0);

	AddGameObject<CSKYDOME>(1);

	//地面
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			AddGameObject<CField>(1)->SetPosition(D3DXVECTOR3(-400 + i * 100, 0, -400 + j * 100));
		}
	}

	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(30.0f, 0.0f, 0.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(45.0f, 0.0f, 10.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(30.0f, 0.0f, -5.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(35.0f, 0.0f, 5.0f));

	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(30.0f, 0.0f, 30.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(45.0f, 0.0f, 20.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(30.0f, 0.0f, -25.0f));
	AddGameObject<CDEADTREE>(1)->SetPosition(D3DXVECTOR3(35.0f, 0.0f, -40.0f));



	AddGameObject<CTITLE2D>(4);

	//PlaySound(SOUND_BGM_BGM001);

}

void CTitle::Update()
{
	CScene::Update();

	if (CInput::GetKeyTrigger(VK_SPACE))
	{
		m_Clik = true;
		//PlaySound(SOUND_SE_CLICK);
		CFADE::SetTexture((char*)"asset/texture/fade.png");
		CFADE::Fade_Start(true, 60, D3DCOLOR());
	}

	if (m_Clik == false) return;
	if (CFADE::Fade_IsFade() == false)
	{
		StopSound();
		CManager::SetScene<CTutorial>();
	}
}