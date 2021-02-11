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
#include "player.h"
#include "enemy.h"
#include "friend.h"
#include "deadtree.h"
#include "bunker.h"
#include "base.h"
#include "spownpoint.h"
#include "load.h"


void CLOAD::Uninit()
{

}

void CLOAD::Update()
{
	//Iを押したときにファイルを読み込む処理を入れる(ショートカット)
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
	TCHAR def_dir[100], path[300];
	//ファイル参照のダイアログボックス表示
	_tcscpy_s(def_dir, sizeof(def_dir) / sizeof(TCHAR), _TEXT("D:"));
	if (GetDir(GetWindow(), def_dir, path) == false)
		return;

	Data_Destroy();	//ロードする前にそれまでに配置されていたオブジェクトを削除する
	assetpass = PassAsset(path);//ファイルのパスをassetフォルダからにする

	//パス変更に失敗したら終了
	if (!assetpass.c_str())	return;

	//プレイヤーの情報をファイルから読み込む
	{
		CPlayer* pplayer = new CPlayer;
		std::string playerpass = "/playerdata.json";	//jsonファイル名
		std::string playerdata = "playerdata";		//jsonファイルに読み込む時のデータの名前
		GameObjectLoad(pplayer, playerpass, playerdata);
		delete pplayer;
	}

	//敵の情報をファイルから読み込む
	{
		CEnemy* penemy = new CEnemy;
		std::string enemypass = "/enemydata.json";	//jsonファイル名
		std::string enemydata = "enemydata";		//jsonファイルに読み込む時のデータの名前
		std::string enemynum = "totalenemy";		//総数をjsonファイルに読み込む時の名前
		GameObjectsLoad(penemy, enemypass,enemydata,enemynum);
		delete penemy;
	}

	//味方情報をファイルから読み込む
	{
		CFriend* pfriend = new CFriend;
		std::string enemypass = "/frienddata.json";	//jsonファイル名
		std::string enemydata = "frienddata";		//jsonファイルに読み込む時のデータの名前
		std::string enemynum = "totalfriend";		//総数をjsonファイルに読み込む時の名前
		GameObjectsLoad(pfriend, enemypass, enemydata, enemynum);
		delete pfriend;
	}

	//バンカー情報をファイルから読み込む
	{
		CBUNKER* pbunker = new CBUNKER;
		std::string bunkerpass = "/bunkerdata.json";	//jsonファイル名
		std::string bunkerdata = "bunkerdata";			//jsonファイルに読み込む時のデータの名前
		std::string bunkernum = "totalbunker";			//総数をjsonファイルに読み込む時の名前
		GameObjectsLoad(pbunker, bunkerpass, bunkerdata, bunkernum);
		delete pbunker;
	}

	//拠点情報をファイルから読み込む
	{
		CBase* pbase = new CBase;
		std::string basepass = "/basedata.json";	//jsonファイル名
		std::string basedata = "basedata";			//jsonファイルに読み込む時のデータの名前
		std::string basenum = "totalbase";			//総数をjsonファイルに読み込む時の名前
		GameObjectsLoad(pbase, basepass, basedata, basenum);
		delete pbase;
	}

	//木情報をファイルから読み込む
	{
		CTREE* ptree = new CTREE;
		std::string treepass = "/treedata.json";	//jsonファイル名
		std::string treedata = "treedata";			//jsonファイルに読み込む時のデータの名前
		std::string treenum = "totaltree";			//総数をjsonファイルに書き込む時の名前
		GameObjectsLoad(ptree, treepass, treedata, treenum);
		delete ptree;
	}

	//枯れ木情報をファイルから読み込む
	{
		CDEADTREE* pdeadtree = new CDEADTREE;
		std::string deadtreepass = "/deadtreedata.json";	//jsonファイル名
		std::string deadtreedata = "deadtreedata";			//jsonファイルに読み込む時のデータの名前
		std::string deadtreenum = "totaldeadtree";			//総数をjsonファイルに読み込む時の名前
		GameObjectsLoad(pdeadtree, deadtreepass, deadtreedata, deadtreenum);
		delete pdeadtree;
	}

	//スポーンポイント情報をファイルから読み込む
	{
		CSpownPoint* pspownpoint = new CSpownPoint;
		std::string spownpointpass = "/spownpointdata.json";	//jsonファイル名
		std::string spownpointdata = "spownpointdata";			//jsonファイルから読み込む時のデータの名前
		std::string spownpointnum = "totalspownpoint";			//総数をjsonファイルに読み込む時の名前
		GameObjectsLoad(pspownpoint, spownpointpass, spownpointdata, spownpointnum);
		delete pspownpoint;
	}

	//地形情報をファイルから読み込む
	{
		CMeshField* pmeshfield = new CMeshField;
		std::string fieldpass = "/field.json";	//jsonファイル名
		std::string fielddata = "meshfielddata";		//jsonファイルに読み込む時のデータの名前
		GameObjectLoad(pmeshfield, fieldpass, fielddata);
		delete pmeshfield;
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

	std::vector<CSpownPoint*> spownpointlist = scene->GetGameObjects<CSpownPoint>(1);
	for (CSpownPoint* spownpoint : spownpointlist)
	{
		spownpoint->SetDestroy();
	}

	CMeshField* pMeshField = scene->GetGameObject<CMeshField>(1);
	if (pMeshField != nullptr)		//メッシュフィールド情報があったときだけ消す
		pMeshField->SetDestroy();
}

template<typename T>
void CLOAD::GameObjectLoad(T* savedata, std::string fullname, std::string data)		//単数のオブジェクトをロードする
{
	T* pclass = new T();
	pclass->Init();
	std::string path = assetpass;
	path += fullname;

	std::stringstream stream;
	//ファイル入力ストリーム作成
	std::ifstream inputFile(path, std::ios::in);
	//入力データを全部文字列streamに投げる
	stream << inputFile.rdbuf();
	//jsonをロード
	cereal::JSONInputArchive jsonInputArchive(stream);

	jsonInputArchive(cereal::make_nvp(data, *pclass));

	CScene* scene = CManager::GetScene();
	scene->AddArgumentGameObject(pclass, 1);

	stream.clear();
	inputFile.close();
	path.clear();
}

template<typename T>
void CLOAD::GameObjectsLoad(T* savedata, std::string fullname, std::string data, std::string total)	//複数のオブジェクトをロード
{
		int totalnumber = 0;	//敵の総数
		std::string tmp;					//jsonの敵データの作業ファイル

		std::string path = assetpass;
		path += fullname;
		std::stringstream stream;

		//ファイル入力ストリーム作成
		std::ifstream inputFile(path, std::ios::in);
		//入力データを全部文字列streamに投げる
		stream << inputFile.rdbuf();

		//jsonをロード
		cereal::JSONInputArchive jsonInputArchive(stream);
		jsonInputArchive(cereal::make_nvp(total, totalnumber));

		for (int i = 1; i < totalnumber; i++)
		{
			T* pclass = new T;
			pclass->Init();

			tmp = data;
			tmp += i;
			jsonInputArchive(cereal::make_nvp(tmp, *pclass));

			CScene* scene = CManager::GetScene();
			scene->AddArgumentGameObject(pclass, 1);
		}

		inputFile.close();
		path.clear();
		stream.clear();
}