//
//データのセーブ
//

#include "main.h"
#include <iostream>
#include <tchar.h>
#include <string>
#include <fstream>
#include <sstream>
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include "filewinapi.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "input.h"

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
#include "save.h"

void CSAVE::Uninit()
{

}

void CSAVE::Update()
{
	if (CInput::GetKeyTrigger('U'))
		Data_Save();
}


TCHAR* CSAVE::PassAsset(TCHAR path[300])
{
	for (int i = 0; i < 300; i++)
	{
		if (path[i] == 'a')
		{
			if (path[i + 1] == 's')
			{
				if (path[i + 2] == 's')
				{
					if (path[i + 3] == 'e')
					{
						if (path[i + 4] == 't')
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
	return NULL;
}


void CSAVE::Data_Save()
{
	TCHAR def_dir[100], path[300];

	//フルパスをとる
	_tcscpy_s(def_dir, sizeof(def_dir) / sizeof(TCHAR), _TEXT("D:"));
	if (GetDir(GetWindow(), def_dir, path) == false)
		return;

	assetpass = PassAsset(path);//ファイルのパスをassetフォルダからにする
	Save();						//保存
}

template<typename T>
void CSAVE::GameObjectSave(T* savedata, std::string fullename, std::string data)
{
	std::stringstream ss;
	std::string path = assetpass;
	path += fullename;

	{
		cereal::JSONOutputArchive o_archive(ss);
		o_archive(cereal::make_nvp(data, *savedata));
	}
	std::ofstream outputFile(path, std::ios::out);

	//書き出す
	outputFile << ss.str();
	//閉じる
	outputFile.close();
	ss.clear();
}

template<typename T>
void CSAVE::GameObjectsSave(std::vector<T*> savedata, std::string fullename, std::string data, std::string total)
{
	std::stringstream ss;
	std::string fullpath = assetpass;
	fullpath += fullename;
	int  i = 1;

	std::string tmp;
	//データを書き込む準備(括弧で囲わないとファイルが正常に作成されない)
	{
		cereal::JSONOutputArchive o_archive(ss);

		//敵の総数を計測
		for (T* Gameobject : savedata)
		{
			i++;
		}
		o_archive(cereal::make_nvp(total, i));		//総数を書き込む
		i = 1;

		//敵の情報を書き込む
		for (T* Gameobject : savedata)
		{
			tmp = data;
			tmp += i;
			o_archive(cereal::make_nvp(tmp, *Gameobject));
			i++;
		}
	}

	std::ofstream outputFile(fullpath, std::ios::out);
	//書き出す
	outputFile << ss.str();
	//閉じる
	outputFile.close();
	ss.clear();
	return;
}

void CSAVE::Save()
{
	CScene* scene = CManager::GetScene();
	//プレイヤーの情報をファイルに書き込む
	{
		//プレイヤーの情報を書き出す
		CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);
		std::string playerpass = "/playerdata.json";	//jsonファイル名
		std::string playerdata = "playerdata";		//jsonファイルに書き込む時のデータの名前

		GameObjectSave(pPlayer, playerpass, playerdata);
	}

	//敵の情報をファイルに書き込む
	{
		std::vector<CEnemy*> enemylist = scene->GetGameObjects<CEnemy>(1);
		std::string enemypass = "/enemydata.json";	//jsonファイル名
		std::string enemydata = "enemydata";		//jsonファイルに書き込む時のデータの名前
		std::string enemynum = "totalenemy";		//総数をjsonファイルに書き込む時の名前

		GameObjectsSave(enemylist, enemypass, enemydata, enemynum);		//情報を書き込む
	}

	//味方情報をファイルに書き込む
	{
		std::vector<CFriend*> friendlist = scene->GetGameObjects<CFriend>(1);
		std::string friendpass = "/frienddata.json";	//jsonファイル名
		std::string frienddata = "frienddata";		//jsonファイルに書き込む時のデータの名前
		std::string friendnum = "totalfriend";		//総数をjsonファイルに書き込む時の名前

		GameObjectsSave(friendlist, friendpass, frienddata, friendnum);		//情報を書き込む
	}

	//バンカー情報をファイルに書き込む
	{
		std::vector<CBUNKER*> bunkerlist = scene->GetGameObjects<CBUNKER>(1);

		std::string bunkerpass = "/bunkerdata.json";	//jsonファイル名
		std::string bunkerdata = "bunkerdata";		//jsonファイルに書き込む時のデータの名前
		std::string bunkernum = "totalbunker";		//総数をjsonファイルに書き込む時の名前

		GameObjectsSave(bunkerlist, bunkerpass, bunkerdata, bunkernum);		//情報を書き込む
	}

	//拠点情報を書き込む
	{
		std::vector<CBase*> baselist = scene->GetGameObjects<CBase>(1);

		std::string basepass = "/basedata.json";	//jsonファイル名
		std::string basedata = "basedata";		//jsonファイルに書き込む時のデータの名前
		std::string basenum = "totalbase";		//総数をjsonファイルに書き込む時の名前

		GameObjectsSave(baselist, basepass, basedata, basenum);		//情報を書き込む
	}

	//木情報を書き込む
	{
		std::vector<CTREE*> treelist = scene->GetGameObjects<CTREE>(1);

		std::string treepass = "/treedata.json";	//jsonファイル名
		std::string treedata = "treedata";		//jsonファイルに書き込む時のデータの名前
		std::string treenum = "totaltree";		//総数をjsonファイルに書き込む時の名前

		GameObjectsSave(treelist, treepass, treedata, treenum);		//情報を書き込む
	}

	//枯れ木情報を書き込む
	{
		std::vector<CDEADTREE*> deadtreelist = scene->GetGameObjects<CDEADTREE>(1);

		std::string deadtreepass = "/deadtreedata.json";	//jsonファイル名
		std::string deadtreedata = "deadtreedata";		//jsonファイルに書き込む時のデータの名前
		std::string deadtreenum = "totaldeadtree";		//総数をjsonファイルに書き込む時の名前

		GameObjectsSave(deadtreelist, deadtreepass, deadtreedata, deadtreenum);		//情報を書き込む
	}

	//スポーン情報をファイルに書き込む
	{
		std::vector<CSpownPoint*> spownpointlist = scene->GetGameObjects<CSpownPoint>(1);

		std::string spownpointpass = "/spownpointdata.json";	//jsonファイル名
		std::string spownpointdata = "spownpointdata";		//jsonファイルに書き込む時のデータの名前
		std::string spownpointnum = "totalspownpoint";		//総数をjsonファイルに書き込む時の名前

		GameObjectsSave(spownpointlist, spownpointpass, spownpointdata, spownpointnum);		//情報を書き込む
	}

	//地形情報をファイルに書き込む
	{
		CMeshField* pMeshField = scene->GetGameObject<CMeshField>(1);
		std::string meshfieldpass = "/field.json";	//jsonファイル名
		std::string meshfielddata = "meshfielddata";		//jsonファイルに書き込む時のデータの名前

		GameObjectSave(pMeshField, meshfieldpass, meshfielddata);
	}
}

void CSAVE::TestData_Save()
{
	assetpass = "asset/testsavedata";		//テストデータ用のパスを用意
	Save();									//保存
}