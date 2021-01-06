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

void CTitle::Init()
{

}

void CTitle::Update()
{
	CScene::Update();

	//�G���^�[�L�[�ŃQ�[����ʂ�
	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		CManager::SetScene<CGame>();
	}
}