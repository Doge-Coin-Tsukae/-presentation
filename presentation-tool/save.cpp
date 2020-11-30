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
#include "save.h"

void CSAVE::Uninit()
{

}

void CSAVE::Update()
{
	if (CInput::GetKeyTrigger('U'))
		Data_Save();
}

void CSAVE::Data_Save()
{
	FILE *SaveFile;
	CScene* scene = CManager::GetScene();

	//プレイヤーの情報をファイルに書き込む
	{
		SaveFile = fopen("asset/savedata/playerdata.txt", "w");

		if (SaveFile == NULL)           // オープンに失敗した場合
			return;                         // 異常終了
		//プレイヤーの情報を書き出す
		CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);
		pPlayer->Save(SaveFile);
		fclose(SaveFile);
	}

	//敵の情報をファイルに書き込む
	{
		SaveFile = fopen("asset/savedata/enemydata.txt", "w");

		if (SaveFile == NULL)           // オープンに失敗した場合
			return;                         // 異常終了
		//敵の情報を書き出す

		std::vector<CEnemy*> enemylist = scene->GetGameObjects<CEnemy>(1);

		//個数を保存する
		fprintf(SaveFile, "%d\n");

		for (CEnemy* enemy : enemylist)
		{
			enemy->Save(SaveFile);
		}

		fclose(SaveFile);
	}

	//バンカー情報をファイルに書き込む
	{
		SaveFile = fopen("asset/savedata/bunkerdata.txt", "w");
		if (SaveFile == NULL)	// オープンに失敗した場合
			return;				// 異常終了
		//情報を書き込む
		std::vector<CBUNKER*> bunkerlist = scene->GetGameObjects<CBUNKER>(1);
		for (CBUNKER* bunker : bunkerlist)
		{
			bunker->Save(SaveFile);
		}

		fclose(SaveFile);
	}
	//拠点情報を書き込む
	{
		SaveFile = fopen("asset/savedata/basedata.txt", "w");
		if (SaveFile == NULL)	// オープンに失敗した場合
			return;             // 異常終了
		//情報を書き込む
		std::vector<CBASE*> baselist = scene->GetGameObjects<CBASE>(1);
		for (CBASE* base : baselist)
		{
			base->Save(SaveFile);
		}

		fclose(SaveFile);
	}
	//木情報を書き込む
	{
		SaveFile = fopen("asset/savedata/treedata.txt", "w");
		if (SaveFile == NULL)	// オープンに失敗した場合
			return;				// 異常終了
		//情報を書き込む
		std::vector<CTREE*> treelist = scene->GetGameObjects<CTREE>(1);
		for (CTREE* tree : treelist)
		{
			tree->Save(SaveFile);
		}

		fclose(SaveFile);
	}
	//枯れ木情報を書き込む
	{
		SaveFile = fopen("asset/savedata/deadtreedata.txt", "w");
		if (SaveFile == NULL)	// オープンに失敗した場合
			return;				// 異常終了
		//情報を書き込む
		std::vector<CDEADTREE*> deadtreelist = scene->GetGameObjects<CDEADTREE>(1);
		for (CDEADTREE* deadtree : deadtreelist)
		{
			deadtree->Save(SaveFile);
		}

		fclose(SaveFile);
	}
	//地形情報をファイルに書き込む
	{
		SaveFile = fopen("asset/savedata/field.txt", "w");
		if (SaveFile == NULL)	// オープンに失敗した場合
			return;				// 異常終了
		CMeshField* pMeshField = scene->GetGameObject<CMeshField>(1);
		pMeshField->Save(SaveFile);
		fclose(SaveFile);
	}
}
