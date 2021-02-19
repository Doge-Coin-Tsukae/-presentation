#include <list>
#include <vector>
#include <typeinfo>
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "input.h"
#include "Title.h"
#include "Game.h"

#include "gameobject.h"
#include "human.h"
#include "model.h"
#include "animationmodel.h"
#include "colider.h"
#include "sight.h"

#include "bunker.h"
#include "enemy.h"
#include "friend.h"
#include "deadtree.h"

void CTitle::Init()
{
	//�c�[���Ŏg���f�[�^�������Ń��[�h
	CBUNKER::Load();
	CEnemy::Load();
	CFriend::Load();
	CDEADTREE::Load();

	count = 0;
}

void CTitle::Update()
{

	CScene::Update();

	//�G���^�[�L�[�ŃQ�[����ʂ�

	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		CManager::SetScene<CGame>();
	}

	if(count >=50)
		CManager::SetScene<CGame>();

	count++;
}