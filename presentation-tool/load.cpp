//
//データのロード
//

#include "main.h"
#include <tchar.h>
#include <fstream>
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "input.h"
#include "filewinapi.h"

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
	//Iを押したときにファイルを読み込む処理を入れる
	if (CInput::GetKeyTrigger('I'))
		Data_Load();
}

TCHAR* CLOAD::PassAsset(TCHAR path[300])
{
	for (int i = 0; i < 300; i++)
	{
		if(path[i] == 'a')
		{
			if (path[i+1] == 's')
			{
				if (path[i+2] == 's')
				{
					if (path[i+3] == 'e')
					{
						if (path[i+4] == 't')
						{
							TCHAR temp[300];
							for (int j = 0; j < 300; j++)
							{
								temp[j] = path[j + i];
							}
							return temp;
						}
					}
				}
			}
		}
	}
	//assetが見つからなかった
	MessageBox(GetWindow(), "assetフォルダが見つかりません。", "ロード失敗!", MB_ICONSTOP);
	return NULL;
}

void CLOAD::Data_Load()
{
	ShowCursor(TRUE);
	FILE *SaveFile;//ファイルポインタ
	CScene* scene = CManager::GetScene();	

	TCHAR def_dir[100] , path[300] ;

	_tcscpy_s(def_dir, sizeof(def_dir) / sizeof(TCHAR), _TEXT("D:"));
	if (GetDir(GetWindow(), def_dir, path) == false)
		return;

	ShowCursor(FALSE);
	Data_Destroy();	//ロードする前にそれまでに配置されていたオブジェクトを削除する
	
	TCHAR *path2 = NULL;
	TCHAR temp[300];
	path2 = PassAsset(path);//ファイルのパスをassetフォルダからにする

	//パス変更に失敗したら終了
	if (!path2)
		return;

	strcpy(temp, path2);	//コピーを作る(後でパスを戻すのに使う)

	//プレイヤーの情報をファイルから読み込む
	{
		//strcat(path2,"//playerdata.txt");
		//SaveFile = fopen(path2, "r");
		//if (SaveFile == NULL)           // オープンに失敗した場合
		//{
		//	MessageBox(GetWindow(), "プレイヤーのデータが見つかりません", "ロード失敗!", MB_ICONWARNING);
		//	return;
		//}
		CPlayer* pPlayer = new CPlayer();
		pPlayer->Init();
		std::string ss ="playerdata.json";
		std::stringstream stream;
		//ファイル入力ストリーム作成
		std::ifstream inputFile(ss, std::ios::in);
		//入力データを全部文字列streamに投げる
		stream << inputFile.rdbuf();
		//jsonをロード
		cereal::JSONInputArchive jsonInputArchive(stream);

		jsonInputArchive(cereal::make_nvp("playerdata", *pPlayer));
		//pPlayer->Init();
		//pPlayer->Load(SaveFile);
		scene->AddArgumentGameObject(pPlayer,1);

		//fclose(SaveFile);
	}

	//敵の情報をファイルから読み込む
	{
		strcpy(path2,temp);
		strcat(path2, "//enemydata.txt");
		SaveFile = fopen(path2, "r");
		if (SaveFile == NULL)           // オープンに失敗した場合
		{
			MessageBox(GetWindow(), "敵のデータが見つかりません", "ロード失敗!", MB_ICONWARNING);
			return;
		}

		for (int i = 0; i < 3; i++)
		{
			CEnemy* pEnemy = new CEnemy();
			pEnemy->Init();
			pEnemy->Load(SaveFile,i);
			scene->AddArgumentGameObject(pEnemy, 1);
		}

		fclose(SaveFile);
	}

	//バンカー情報をファイルから読み込む
	{
		strcpy(path2, temp);
		strcat(path2, "//bunkerdata.txt");

		SaveFile = fopen(path2, "r");
		if (SaveFile == NULL)           // オープンに失敗した場合
		{
			MessageBox(GetWindow(), "バンカーのデータが見つかりません", "ロード失敗!", MB_ICONWARNING);
			return;
		}

		for (int i = 0; i < 3; i++)
		{
			CBUNKER* pBunker = new CBUNKER();
			pBunker->Init();
			pBunker->Load(SaveFile, i);
			scene->AddArgumentGameObject(pBunker, 1);
		}

		fclose(SaveFile);
	}

	//拠点情報をファイルから読み込む
	{
		strcpy(path2, temp);
		strcat(path2, "//basedata.txt");
		SaveFile = fopen(path2, "r");
		if (SaveFile == NULL)           // オープンに失敗した場合
		{
			MessageBox(GetWindow(), "拠点のデータが見つかりません", "ロード失敗!", MB_ICONWARNING);
			return;
		}

		for (int i = 0; i < 3; i++)
		{
			CBase* pBase = new CBase();
			pBase->Init();
			pBase->Load(SaveFile, i);
			scene->AddArgumentGameObject(pBase, 1);
		}

		fclose(SaveFile);
	}

	//木情報をファイルから読み込む
	{
		strcpy(path2, temp);
		strcat(path2, "//treedata.txt");
		SaveFile = fopen(path2, "r");
		if (SaveFile == NULL)           // オープンに失敗した場合
		{
			MessageBox(GetWindow(), "木のデータが見つかりません", "ロード失敗!", MB_ICONWARNING);
			return;
		}

		for (int i = 0; i < 10; i++)
		{
			CTREE* pTree = new CTREE();
			pTree->Init();
			pTree->Load(SaveFile, i);
			scene->AddArgumentGameObject(pTree, 1);
		}

		fclose(SaveFile);
	}

	//枯れ木情報をファイルから読み込む
	{
		strcpy(path2, temp);
		strcat(path2, "//deadtreedata.txt");
		SaveFile = fopen(path2, "r");
		if (SaveFile == NULL)           // オープンに失敗した場合
		{
			MessageBox(GetWindow(), "枯れ木のデータが見つかりません", "ロード失敗!", MB_ICONWARNING);
			return;
		}

		for (int i = 0; i < 14; i++)
		{
			CDEADTREE* pDeadTree = new CDEADTREE();
			pDeadTree->Init();
			pDeadTree->Load(SaveFile, i);
			scene->AddArgumentGameObject(pDeadTree, 1);
		}

		fclose(SaveFile);
	}

	//地形情報をファイルから読み込む
	{
		strcpy(path2, temp);
		strcat(path2, "//field.txt");
		SaveFile = fopen(path2, "r");
		if(SaveFile == NULL)           // オープンに失敗した場合
		{
			MessageBox(GetWindow(), "地形のデータが見つかりません", "ロード失敗!", MB_ICONWARNING);
			return;
		}

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

	std::vector<CEnemy*> enemylist = scene->GetGameObjects<CEnemy>(1);
	for (CEnemy* enemy : enemylist)
	{
		enemy->SetDestroy();
	}

	std::vector<CBUNKER*> bunkerlist = scene->GetGameObjects<CBUNKER>(1);
	for (CBUNKER* bunker : bunkerlist)
	{
		bunker->SetDestroy();
	}

	std::vector<CBase*> baselist = scene->GetGameObjects<CBase>(1);
	for (CBase* base : baselist)
	{
		base->SetDestroy();
	}

	std::vector<CTREE*> treelist = scene->GetGameObjects<CTREE>(1);
	for (CTREE* tree : treelist)
	{
		tree->SetDestroy();
	}

	std::vector<CDEADTREE*> deadtreelist = scene->GetGameObjects<CDEADTREE>(1);
	for (CDEADTREE* deadtree : deadtreelist)
	{
		deadtree->SetDestroy();
	}
}