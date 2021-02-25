//=====================================
//
//  ロードを行う
//  written by Y.Okubo
//
//=====================================

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
#include "behavior.h"
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
}

void CLOAD::Data_Load()
{
	Data_Destroy();	//ロードする前にそれまでに配置されていたオブジェクトを削除する


	//プレイヤーの情報をファイルから読み込む
	{
		CPlayer* pplayer = new CPlayer;
		std::string playerpass = "asset/savedata/playerdata.json";	//jsonファイル名
		std::string playerdata = "playerdata";		//jsonファイルに読み込む時のデータの名前
		GameObjectLoad(pplayer, playerpass, playerdata);

		delete pplayer;
	}

	//敵の情報をファイルから読み込む
	{
		CEnemy* penemy = new CEnemy;
		std::string enemypass = "asset/savedata/enemydata.json";	//jsonファイル名
		std::string enemydata = "enemydata";		//jsonファイルに読み込む時のデータの名前
		std::string enemynum = "totalenemy";		//総数をjsonファイルに読み込む時の名前
		GameObjectsLoad(penemy, enemypass, enemydata, enemynum,1);
		delete penemy;
	}

	//味方情報をファイルから読み込む
	{
		CFriend* pfriend = new CFriend;
		std::string enemypass = "asset/savedata/frienddata.json";	//jsonファイル名
		std::string enemydata = "frienddata";		//jsonファイルに読み込む時のデータの名前
		std::string enemynum = "totalfriend";		//総数をjsonファイルに読み込む時の名前
		GameObjectsLoad(pfriend, enemypass, enemydata, enemynum,1);
		delete pfriend;
	}

	//バンカー情報をファイルから読み込む
	{
		CBUNKER* pbunker = new CBUNKER;
		std::string bunkerpass = "asset/savedata/bunkerdata.json";	//jsonファイル名
		std::string bunkerdata = "bunkerdata";			//jsonファイルに読み込む時のデータの名前
		std::string bunkernum = "totalbunker";			//総数をjsonファイルに読み込む時の名前
		GameObjectsLoad(pbunker, bunkerpass, bunkerdata, bunkernum,1);
		delete pbunker;
	}

	//拠点情報をファイルから読み込む
	{
		CBASE* pbase = new CBASE;
		std::string basepass = "asset/savedata/basedata.json";	//jsonファイル名
		std::string basedata = "basedata";			//jsonファイルに読み込む時のデータの名前
		std::string basenum = "totalbase";			//総数をjsonファイルに読み込む時の名前
		GameObjectsLoad(pbase, basepass, basedata, basenum,2);
		delete pbase;
	}

	//木情報をファイルから読み込む
	{
		CTREE* ptree = new CTREE;
		std::string treepass = "asset/savedata/treedata.json";	//jsonファイル名
		std::string treedata = "treedata";			//jsonファイルに読み込む時のデータの名前
		std::string treenum = "totaltree";			//総数をjsonファイルに書き込む時の名前
		GameObjectsLoad(ptree, treepass, treedata, treenum,3);
		delete ptree;
	}

	//枯れ木情報をファイルから読み込む
	{
		CDEADTREE* pdeadtree = new CDEADTREE;
		std::string deadtreepass = "asset/savedata/deadtreedata.json";	//jsonファイル名
		std::string deadtreedata = "deadtreedata";			//jsonファイルに読み込む時のデータの名前
		std::string deadtreenum = "totaldeadtree";			//総数をjsonファイルに読み込む時の名前
		GameObjectsLoad(pdeadtree, deadtreepass, deadtreedata, deadtreenum,1);
		delete pdeadtree;
	}

	//スポーンポイント情報をファイルから読み込む
	{
		CSpownPoint* pspownpoint = new CSpownPoint;
		std::string spownpointpass = "asset/savedata/spownpointdata.json";	//jsonファイル名
		std::string spownpointdata = "spownpointdata";			//jsonファイルから読み込む時のデータの名前
		std::string spownpointnum = "totalspownpoint";			//総数をjsonファイルに読み込む時の名前
		GameObjectsLoad(pspownpoint, spownpointpass, spownpointdata, spownpointnum,1);
		delete pspownpoint;
	}

	//地形情報をファイルから読み込む
	{
		CMeshField* pmeshfield = new CMeshField;
		std::string fieldpass = "asset/savedata/field.json";	//jsonファイル名
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
	std::vector<CBASE*> baselist = scene->GetGameObjects<CBASE>(2);
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


template<typename T>
void CLOAD::GameObjectLoad(T* savedata, std::string fullname, std::string data)		//単数のオブジェクトをロードする
{
	T* pclass = new T();
	pclass->Init();

	std::stringstream stream;
	//ファイル入力ストリーム作成
	std::ifstream inputFile(fullname, std::ios::in);
	//入力データを全部文字列streamに投げる
	stream << inputFile.rdbuf();
	//jsonをロード
	cereal::JSONInputArchive jsonInputArchive(stream);

	jsonInputArchive(cereal::make_nvp(data, *pclass));

	CScene* scene = CManager::GetScene();
	pclass->FileLoad();
	scene->AddArgumentGameObject(pclass, 1);

	stream.clear();
	inputFile.close();
}

template<typename T>
void CLOAD::GameObjectsLoad(T* savedata, std::string fullname, std::string data, std::string total, int layer)	//複数のオブジェクトをロード
{
	int totalnumber = 0;		//敵の総数
	std::string tmp;			//jsonの敵データの作業ファイル
	std::stringstream stream;

	//ファイル入力ストリーム作成
	std::ifstream inputFile(fullname, std::ios::in);
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
		pclass->FileLoad();
		scene->AddArgumentGameObject(pclass, layer);
	}

	inputFile.close();
	stream.clear();
}