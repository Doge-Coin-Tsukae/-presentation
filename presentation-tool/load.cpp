#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene.h"

#include"tree.h"
#include "meshfield.h"
#include "human.h"
#include "model.h"
#include "carsor.h"
#include "colider.h"
#include "sight.h"
#include "weapon.h"
#include "player.h"
#include "enemy.h"
#include "deadtree.h"
#include "bunker.h"
#include "base.h"
#include "load.h"

void CLOAD::Uninit()
{

}

void CLOAD::Update()
{
	if (CInput::GetKeyTrigger('I'))
		Data_Load();
}

void CLOAD::Data_Load()
{
	FILE *SaveFile;
	CScene* scene = CManager::GetScene();

	//プレイヤーの情報をファイルから読み込む
	{
		SaveFile = fopen("asset/savedata/playerdata.txt", "r");

		if (SaveFile == NULL)           // オープンに失敗した場合
			return;                         // 異常終了
		//プレイヤーの情報をファイルから持ってくる
		CPlayer* pPlayer = new CPlayer();
		pPlayer->Init();
		pPlayer->Load(SaveFile);
		scene->AddArgumentGameObject(pPlayer,1);

		fclose(SaveFile);
	}

	//敵の情報をファイルに書き込む
	{
		SaveFile = fopen("asset/savedata/enemydata.txt", "r");

		if (SaveFile == NULL)           // オープンに失敗した場合
			return;                         // 異常終了
		//プレイヤーの情報をファイルから持ってくる
		for (int i = 0; i < 3; i++)
		{
			CEnemy* pEnemy = new CEnemy();
			pEnemy->Init();
			pEnemy->Load(SaveFile,i);
			scene->AddArgumentGameObject(pEnemy, 1);
		}

		fclose(SaveFile);
	}

	//バンカー情報をファイルに書き込む
	{
		SaveFile = fopen("asset/savedata/bunkerdata.txt", "r");
		if (SaveFile == NULL)	// オープンに失敗した場合
			return;				// 異常終了
		//情報を書き込む
		for (int i = 0; i < 3; i++)
		{
			CBUNKER* pBunker = new CBUNKER();
			pBunker->Init();
			pBunker->Load(SaveFile, i);
			scene->AddArgumentGameObject(pBunker, 1);
		}

		fclose(SaveFile);
	}
	//拠点情報を書き込む
	{
		SaveFile = fopen("asset/savedata/basedata.txt", "r");
		if (SaveFile == NULL)	// オープンに失敗した場合
			return;             // 異常終了
		//情報を書き込む
		for (int i = 0; i < 3; i++)
		{
			CBASE* pBase = new CBASE();
			pBase->Init();
			pBase->Load(SaveFile, i);
			scene->AddArgumentGameObject(pBase, 1);
		}

		fclose(SaveFile);
	}
	//木情報を書き込む
	{
		SaveFile = fopen("asset/savedata/treedata.txt", "r");
		if (SaveFile == NULL)	// オープンに失敗した場合
			return;				// 異常終了
		//情報を書き込む
		for (int i = 0; i < 10; i++)
		{
			CTREE* pTree = new CTREE();
			pTree->Init();
			pTree->Load(SaveFile, i);
			scene->AddArgumentGameObject(pTree, 1);
		}

		fclose(SaveFile);
	}
	//枯れ木情報を書き込む
	{
		SaveFile = fopen("asset/savedata/deadtreedata.txt", "r");
		if (SaveFile == NULL)	// オープンに失敗した場合
			return;				// 異常終了
		//情報を書き込む
		for (int i = 0; i < 10; i++)
		{
			CDEADTREE* pDeadTree = new CDEADTREE();
			pDeadTree->Init();
			pDeadTree->Load(SaveFile, i);
			scene->AddArgumentGameObject(pDeadTree, 1);
		}

		fclose(SaveFile);
	}
	//地形情報をファイルに書き込む
	{
		SaveFile = fopen("asset/savedata/field.txt", "r");
		if (SaveFile == NULL)	// オープンに失敗した場合
			return;				// 異常終了
		CMeshField* pMeshField = scene->GetGameObject<CMeshField>(1);
		
		fclose(SaveFile);
	}
}
