#include "main.h"
#include <tchar.h>
#include <fstream>
#include <iostream>
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "input.h"
#include"tree.h"
#include "meshfield.h"
#include "human.h"
#include "model.h"
#include "colider.h"
#include "sight.h"
#include "animationmodel.h"
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
}

void CLOAD::Data_Load()
{
	FILE *SaveFile;//ファイルポインタ
	CScene* scene = CManager::GetScene();	

	Data_Destroy();	//ロードする前にそれまでに配置されていたオブジェクトを削除する

	std::string path;

		//プレイヤーの情報をファイルから読み込む
	{
		CPlayer* pPlayer = new CPlayer();
		pPlayer->Init();
		path = "asset/savedata/playerdata.json";

		std::stringstream stream;
		//ファイル入力ストリーム作成
		std::ifstream inputFile(path, std::ios::in);
		//入力データを全部文字列streamに投げる
		stream << inputFile.rdbuf();
		//jsonをロード
		cereal::JSONInputArchive jsonInputArchive(stream);

		jsonInputArchive(cereal::make_nvp("playerdata", *pPlayer));
		pPlayer->ResetVelocity();
		scene->AddArgumentGameObject(pPlayer, 1);

		stream.clear();
		inputFile.close();
	}

	//プレイヤーの情報をファイルから読み込む
	//{
	//	SaveFile = fopen("asset/savedata/playerdata.txt", "r");
	//	if (SaveFile == NULL)           // オープンに失敗した場合
	//		return;

	//	CPlayer* pPlayer = new CPlayer();
	//	pPlayer->Init();
	//	pPlayer->Load(SaveFile);
	//	scene->AddArgumentGameObject(pPlayer,1);

	//	fclose(SaveFile);
	//}

	//敵の情報をファイルから読み込む
	//{
	//	SaveFile = fopen("asset/savedata/enemydata.txt", "r");
	//	if (SaveFile == NULL)           // オープンに失敗した場合
	//		return;

	//	for (int i = 0; i < 3; i++)
	//	{
	//		CEnemy* pEnemy = new CEnemy();
	//		pEnemy->Init();
	//		pEnemy->Load(SaveFile,i);
	//		scene->AddArgumentGameObject(pEnemy, 1);
	//	}

	//	fclose(SaveFile);
	//}

	{
		int totalnumber = 0;	//敵の総数
		std::string moji = "enemydata";		//jsonの敵データ
		std::string tmp;					//jsonの敵データの作業ファイル

		path = "asset/savedata/enemydata.json";
		std::stringstream stream;

		//ファイル入力ストリーム作成
		std::ifstream inputFile(path, std::ios::in);
		//入力データを全部文字列streamに投げる
		stream << inputFile.rdbuf();

		//jsonをロード
		cereal::JSONInputArchive jsonInputArchive(stream);
		jsonInputArchive(cereal::make_nvp("totalenemy", totalnumber));

		for (int i = 1; i < totalnumber; i++)
		{
			CEnemy* pEnemy = new CEnemy;
			pEnemy->Init();

			tmp = moji;
			tmp += i;
			jsonInputArchive(cereal::make_nvp(tmp, *pEnemy));
			scene->AddArgumentGameObject(pEnemy, 1);
		}

		inputFile.close();
		moji.clear();
		stream.clear();
		tmp.clear();
	}

	//バンカー情報をファイルから読み込む
	//{
	//	SaveFile = fopen("asset/savedata/bunkerdata.txt", "r");
	//	if (SaveFile == NULL)	// オープンに失敗した場合
	//		return;

	//	for (int i = 0; i < 3; i++)
	//	{
	//		CBUNKER* pBunker = new CBUNKER();
	//		pBunker->Init();
	//		pBunker->Load(SaveFile, i);
	//		scene->AddArgumentGameObject(pBunker, 1);
	//	}

	//	fclose(SaveFile);
	//}

	{
		int totalnumber = 0;	//敵の総数
		std::string moji = "bunkerdata";		//jsonの敵データ
		std::string tmp;					//jsonの敵データの作業ファイル

		path = "asset/savedata/bunkerdata.json";
		std::stringstream stream;

		//ファイル入力ストリーム作成
		std::ifstream inputFile(path, std::ios::in);
		//入力データを全部文字列streamに投げる
		stream << inputFile.rdbuf();

		//jsonをロード
		cereal::JSONInputArchive jsonInputArchive(stream);
		jsonInputArchive(cereal::make_nvp("totalbunker", totalnumber));

		for (int i = 1; i < totalnumber; i++)
		{
			CBUNKER* pBunker = new CBUNKER;
			pBunker->Init();

			tmp = moji;
			tmp += i;
			jsonInputArchive(cereal::make_nvp(tmp, *pBunker));
			scene->AddArgumentGameObject(pBunker, 1);
		}

		inputFile.close();
	}

	//拠点情報をファイルから読み込む
	//{
	//	SaveFile = fopen("asset/savedata/basedata.txt", "r");
	//	if (SaveFile == NULL)	// オープンに失敗した場合
	//		return;

	//	for (int i = 0; i < 3; i++)
	//	{
	//		CBASE* pBase = new CBASE();
	//		pBase->Init();
	//		pBase->Load(SaveFile, i);
	//		scene->AddArgumentGameObject(pBase, 2);
	//	}

	//	fclose(SaveFile);
	//}

	{
		int totalnumber = 0;	//敵の総数
		std::string moji = "basedata";		//jsonの敵データ
		std::string tmp;					//jsonの敵データの作業ファイル

		path = "asset/savedata/basedata.json";
		std::stringstream stream;

		//ファイル入力ストリーム作成
		std::ifstream inputFile(path, std::ios::in);
		//入力データを全部文字列streamに投げる
		stream << inputFile.rdbuf();

		//jsonをロード
		cereal::JSONInputArchive jsonInputArchive(stream);
		jsonInputArchive(cereal::make_nvp("totalbase", totalnumber));

		for (int i = 1; i < totalnumber; i++)
		{
			CBASE* pBase = new CBASE;
			pBase->Init();

			tmp = moji;
			tmp += i;
			jsonInputArchive(cereal::make_nvp(tmp, *pBase));
			scene->AddArgumentGameObject(pBase, 2);
		}

		inputFile.close();
	}

	//木情報をファイルから読み込む
	//{
	//	SaveFile = fopen("asset/savedata/treedata.txt", "r");
	//	if (SaveFile == NULL)	// オープンに失敗した場合
	//		return;

	//	for (int i = 0; i < 10; i++)
	//	{
	//		CTREE* pTree = new CTREE();
	//		pTree->Init();
	//		pTree->Load(SaveFile, i);
	//		scene->AddArgumentGameObject(pTree, 3);
	//	}

	//	fclose(SaveFile);
	//}

	{
		int totalnumber = 0;	//敵の総数
		std::string moji = "treedata";		//jsonの敵データ
		std::string tmp;					//jsonの敵データの作業ファイル

		path = "asset/savedata/treedata.json";
		std::stringstream stream;

		//ファイル入力ストリーム作成
		std::ifstream inputFile(path, std::ios::in);
		//入力データを全部文字列streamに投げる
		stream << inputFile.rdbuf();

		//jsonをロード
		cereal::JSONInputArchive jsonInputArchive(stream);
		jsonInputArchive(cereal::make_nvp("totaltree", totalnumber));

		for (int i = 1; i < totalnumber; i++)
		{
			CTREE* pTree = new CTREE;
			pTree->Init();

			tmp = moji;
			tmp += i;
			jsonInputArchive(cereal::make_nvp(tmp, *pTree));
			scene->AddArgumentGameObject(pTree, 1);
		}

		inputFile.close();
	}

	//枯れ木情報をファイルから読み込む
	//{
	//	SaveFile = fopen("asset/savedata/deadtreedata.txt", "r");
	//	if (SaveFile == NULL)	// オープンに失敗した場合
	//		return;

	//	for (int i = 0; i < 10; i++)
	//	{
	//		CDEADTREE* pDeadTree = new CDEADTREE();
	//		pDeadTree->Init();
	//		pDeadTree->Load(SaveFile, i);
	//		scene->AddArgumentGameObject(pDeadTree, 1);
	//	}

	//	fclose(SaveFile);
	//}

	{
		int totalnumber = 0;	//敵の総数
		std::string moji = "deadtreedata";		//jsonの敵データ
		std::string tmp;					//jsonの敵データの作業ファイル

		path = "asset/savedata/deadtreedata.json";
		std::stringstream stream;

		//ファイル入力ストリーム作成
		std::ifstream inputFile(path, std::ios::in);
		//入力データを全部文字列streamに投げる
		stream << inputFile.rdbuf();

		//jsonをロード
		cereal::JSONInputArchive jsonInputArchive(stream);
		jsonInputArchive(cereal::make_nvp("totaldeadtree", totalnumber));

		for (int i = 1; i < totalnumber; i++)
		{
			CDEADTREE* pDeadTree = new CDEADTREE;
			pDeadTree->Init();

			tmp = moji;
			tmp += i;
			jsonInputArchive(cereal::make_nvp(tmp, *pDeadTree));
			scene->AddArgumentGameObject(pDeadTree, 1);
		}

		inputFile.close();
	}

	//地形情報をファイルから読み込む
	{
		SaveFile = fopen("asset/savedata/field.txt", "r");
		if (SaveFile == NULL)	// オープンに失敗した場合
			return;

		CMeshField* pMeshField = scene->GetGameObject<CMeshField>(1);
		
		fclose(SaveFile);
	}
}

void CLOAD::Data_Destroy()
{
	CScene* scene = CManager::GetScene();

	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);
	if(pPlayer  != nullptr)		//プレイヤー情報があったときだけ消す
		pPlayer->SetDestroy();

	//リストからピックアップしてデータ削除
	std::vector<CEnemy*> enemylist = scene->GetGameObjects<CEnemy>(1);
	for (CEnemy* enemy : enemylist)
	{
		enemy->SetDestroy();
	}

	//リストからピックアップしてデータ削除
	std::vector<CBUNKER*> bunkerlist = scene->GetGameObjects<CBUNKER>(1);
	for (CBUNKER* bunker : bunkerlist)
	{
		bunker->SetDestroy();
	}

	//リストからピックアップしてデータ削除
	std::vector<CBASE*> baselist = scene->GetGameObjects<CBASE>(1);
	for (CBASE* base : baselist)
	{
		base->SetDestroy();
	}

	//リストからピックアップしてデータ削除
	std::vector<CTREE*> treelist = scene->GetGameObjects<CTREE>(3);
	for (CTREE* tree : treelist)
	{
		tree->SetDestroy();
	}

	//リストからピックアップしてデータ削除
	std::vector<CDEADTREE*> deadtreelist = scene->GetGameObjects<CDEADTREE>(1);
	for (CDEADTREE* deadtree : deadtreelist)
	{
		deadtree->SetDestroy();
	}
}