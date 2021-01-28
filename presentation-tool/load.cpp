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
#include "animationmodel.h"
#include "carsor.h"
#include "colider.h"
#include "sight.h"
#include "weapon.h"
#include "player.h"
#include "enemy.h"
#include "friend.h"
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
	path2 = PassAsset(path);//ファイルのパスをassetフォルダからにする

	//パス変更に失敗したら終了
	if (!path2)
		return;

	//プレイヤーの情報をファイルから読み込む
	{
		CPlayer* pPlayer = new CPlayer();
		pPlayer->Init();
		std::string path = path2;
		path += "/playerdata.json";

		std::stringstream stream;
		//ファイル入力ストリーム作成
		std::ifstream inputFile(path, std::ios::in);
		//入力データを全部文字列streamに投げる
		stream << inputFile.rdbuf();
		//jsonをロード
		cereal::JSONInputArchive jsonInputArchive(stream);

		jsonInputArchive(cereal::make_nvp("playerdata", *pPlayer));
		scene->AddArgumentGameObject(pPlayer,1);

		stream.clear();
		inputFile.close();
		path.clear();
	}

	//敵の情報をファイルから読み込む
	{

		int totalnumber = 0;	//敵の総数
		std::string moji = "enemydata";		//jsonの敵データ
		std::string tmp;					//jsonの敵データの作業ファイル

		std::string path = path2;
		path += "/enemydata.json";
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
		path.clear();
		stream.clear();
	}

	//味方情報をファイルから読み込む
	{

		int totalnumber = 0;	//敵の総数
		std::string moji = "frienddata";		//jsonの敵データ
		std::string tmp;					//jsonの敵データの作業ファイル

		std::string path = path2;
		path += "/frienddata.json";
		std::stringstream stream;

		//ファイル入力ストリーム作成
		std::ifstream inputFile(path, std::ios::in);
		//入力データを全部文字列streamに投げる
		stream << inputFile.rdbuf();

		//jsonをロード
		cereal::JSONInputArchive jsonInputArchive(stream);
		jsonInputArchive(cereal::make_nvp("totalfriend", totalnumber));

		for (int i = 1; i < totalnumber; i++)
		{
			CFriend* pFrined = new CFriend;
			pFrined->Init();

			tmp = moji;
			tmp += i;
			jsonInputArchive(cereal::make_nvp(tmp, *pFrined));
			scene->AddArgumentGameObject(pFrined, 1);
		}

		inputFile.close();
		moji.clear();
		path.clear();
		stream.clear();
	}

	//バンカー情報をファイルから読み込む
	{
		int totalnumber = 0;	//敵の総数
		std::string moji = "bunkerdata";		//jsonの敵データ
		std::string tmp;					//jsonの敵データの作業ファイル

		std::string path = path2;
		path += "/bunkerdata.json";
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
	{
		int totalnumber = 0;	//敵の総数
		std::string moji = "basedata";		//jsonの敵データ
		std::string tmp;					//jsonの敵データの作業ファイル

		std::string path = path2;
		path += "/basedata.json";
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
			CBase* pBase = new CBase;
			pBase->Init();

			tmp = moji;
			tmp += i;
			jsonInputArchive(cereal::make_nvp(tmp, *pBase));
			scene->AddArgumentGameObject(pBase, 1);
		}

		inputFile.close();
	}

	//木情報をファイルから読み込む
	{
		int totalnumber = 0;	//敵の総数
		std::string moji = "treedata";		//jsonの敵データ
		std::string tmp;					//jsonの敵データの作業ファイル

		std::string path = path2;
		path += "/treedata.json";
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
	{
		int totalnumber = 0;	//敵の総数
		std::string moji = "deadtreedata";		//jsonの敵データ
		std::string tmp;					//jsonの敵データの作業ファイル

		std::string path = path2;
		path += "/deadtreedata.json";
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
		strcat(path2, "/field.txt");
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