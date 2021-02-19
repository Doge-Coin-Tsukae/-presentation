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
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "sound.h"
#include "fade.h"
#include "input.h"

#include "gameobject.h"

#include "gamemaneger.h"
#include "Game.h"
#include "Title.h"

void CTitle::Init()
{
}

void CTitle::Uninit()
{
}

void CTitle::Update()
{
	CScene::Update();

	CManager::SetScene<CGame>();
}