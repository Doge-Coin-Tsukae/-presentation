//
//データのセーブ
//

#include "main.h"
#include <iostream>
#include <tchar.h>
#include <string>
#include <fstream>   // ifstream, ofstream
#include <sstream>   // istringstream
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
#include "weapon.h"
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
}


void CSAVE::Data_Save()
{
	ShowCursor(TRUE);

	FILE *SaveFile;
	CScene* scene = CManager::GetScene();


	TCHAR def_dir[100], path[300];

	_tcscpy_s(def_dir, sizeof(def_dir) / sizeof(TCHAR), _TEXT("D:"));
	if (GetDir(GetWindow(), def_dir, path) == false)
		return;

	ShowCursor(FALSE);

	TCHAR *path2 = NULL;
	TCHAR temp[300];
	path2 = PassAsset(path);//ファイルのパスをassetフォルダからにする
	strcpy(temp, path2);

	//プレイヤーの情報をファイルに書き込む
	{
		//プレイヤーの情報を書き出す
		CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);
		std::stringstream ss;
		std::string path = path2;
		path += "/playerdata.json";
		{
			cereal::JSONOutputArchive o_archive(ss);
			o_archive(cereal::make_nvp("playerdata", *pPlayer));
		}
		std::ofstream outputFile(path, std::ios::out);
			//書き出す
		outputFile << ss.str();
			//閉じる
		outputFile.close();
		ss.clear();
	}

	//敵の情報をファイルに書き込む
	{
		std::vector<CEnemy*> enemylist = scene->GetGameObjects<CEnemy>(1);
		
		std::stringstream ss;
		std::string filename = path2;
		filename += "/enemydata.json";

		int  i = 1;
		std::string moji = "enemydata";
		std::string tmp;
		//データを書き込む準備(括弧で囲わないとファイルが正常に作成されない)
		{
			cereal::JSONOutputArchive o_archive(ss);

			//敵の総数を計測
			for (CEnemy* enemy : enemylist)
			{
				i++;
			}
			o_archive(cereal::make_nvp("totalenemy", i));		//敵の総数を書き込む
			i = 1;

			//敵の情報を書き込む
			for (CEnemy* enemy : enemylist)
			{
				tmp = moji;
				tmp += i;
				o_archive(cereal::make_nvp(tmp, *enemy));
				i++;
			}
		}
		std::ofstream outputFile(filename, std::ios::out);
		//書き出す
		outputFile << ss.str();
		//閉じる
		outputFile.close();
		ss.clear();
	}

	//味方情報をファイルに書き込む
	{
		std::vector<CFriend*> friendlist = scene->GetGameObjects<CFriend>(1);

		std::stringstream ss;
		std::string filename = path2;
		filename += "/frienddata.json";

		int  i = 1;
		std::string moji = "frienddata";
		std::string tmp;
		//データを書き込む準備(括弧で囲わないとファイルが正常に作成されない)
		{
			cereal::JSONOutputArchive o_archive(ss);

			//敵の総数を計測
			for (CFriend* friends : friendlist)
			{
				i++;
			}
			o_archive(cereal::make_nvp("totalfriend", i));		//敵の総数を書き込む
			i = 1;

			//敵の情報を書き込む
			for (CFriend* friends : friendlist)
			{
				tmp = moji;
				tmp += i;
				o_archive(cereal::make_nvp(tmp, *friends));
				i++;
			}
		}
		std::ofstream outputFile(filename, std::ios::out);
		//書き出す
		outputFile << ss.str();
		//閉じる
		outputFile.close();
		ss.clear();
	}

	//バンカー情報をファイルに書き込む
	{
		std::vector<CBUNKER*> bunkerlist = scene->GetGameObjects<CBUNKER>(1);

		std::stringstream ss;
		std::string filename = path2;
		filename += "/bunkerdata.json";

		{
			int  i = 1;
			std::string moji = "bunkerdata";
			std::string tmp;

			cereal::JSONOutputArchive o_archive(ss);

			//敵の総数を計測
			for (CBUNKER* bunker : bunkerlist)
			{
				i++;
			}
			o_archive(cereal::make_nvp("totalbunker", i));		//建物の総数を書き込む
			i = 1;

			for (CBUNKER* bunker : bunkerlist)
			{
				tmp = moji;
				tmp += i;
				o_archive(cereal::make_nvp(tmp, *bunker));
				i++;
			}
		}

		std::ofstream outputFile(filename, std::ios::out);
		//書き出す
		outputFile << ss.str();
		//閉じる
		outputFile.close();
		ss.clear();
	}
	//拠点情報を書き込む
	{
		std::vector<CBase*> baselist = scene->GetGameObjects<CBase>(1);

		std::stringstream ss;
		std::string filename = path2;
		filename += "/basedata.json";

		{
			int  i = 1;
			std::string moji = "basedata";
			std::string tmp;
			cereal::JSONOutputArchive o_archive(ss);
			//敵の総数を計測
			for (CBase* base : baselist)
			{
				i++;
			}
			o_archive(cereal::make_nvp("totalbase", i));		//基地の総数を書き込む
			i = 1;

			for (CBase* base : baselist)
			{
				tmp = moji;
				tmp += i;
				o_archive(cereal::make_nvp(tmp, *base));
				i++;
			}
		}
		std::ofstream outputFile(filename, std::ios::out);
		//書き出す
		outputFile << ss.str();
		//閉じる
		outputFile.close();
		ss.clear();
	}
	//木情報を書き込む
	{
		std::vector<CTREE*> treelist = scene->GetGameObjects<CTREE>(1);

		std::stringstream ss;
		std::string filename = path2;
		filename += "/treedata.json";

		{
			int  i = 1;
			std::string moji = "treedata";
			std::string tmp;
			cereal::JSONOutputArchive o_archive(ss);
			for (CTREE* tree : treelist)
			{
				i++;
			}
			o_archive(cereal::make_nvp("totaltree", i));		//木の総数を書き込む
			i = 1;

			for (CTREE* tree : treelist)
			{
				tmp = moji;
				tmp += i;
				o_archive(cereal::make_nvp(tmp, *tree));
				i++;
			}
		}

		std::ofstream outputFile(filename, std::ios::out);
		//書き出す
		outputFile << ss.str();
		//閉じる
		outputFile.close();
		ss.clear();
	}
	//枯れ木情報を書き込む
	{
		std::vector<CDEADTREE*> deadtreelist = scene->GetGameObjects<CDEADTREE>(1);

		std::stringstream ss;
		std::string filename = path2;
		filename += "/deadtreedata.json";
		{
			int  i = 1;
			std::string moji = "deadtreedata";
			std::string tmp;
			cereal::JSONOutputArchive o_archive(ss);

			for (CDEADTREE* deadtree : deadtreelist)
			{
				i++;
			}
			o_archive(cereal::make_nvp("totaldeadtree", i));		//木の総数を書き込む
			i = 1;
			for (CDEADTREE* deadtree : deadtreelist)
			{
				tmp = moji;
				tmp += i;
				o_archive(cereal::make_nvp(tmp, *deadtree));
				i++;
			}
		}

		std::ofstream outputFile(filename, std::ios::out);
		//書き出す
		outputFile << ss.str();
		//閉じる
		outputFile.close();
		ss.clear();
	}

	//スポーン情報をファイルに書き込む
	{
		std::vector<CSpownPoint*> spownpointlist = scene->GetGameObjects<CSpownPoint>(1);

		std::stringstream ss;
		std::string filename = path2;
		filename += "/spownpointdata.json";
		{
			int  i = 1;
			std::string moji = "spownpointdata";
			std::string tmp;
			cereal::JSONOutputArchive o_archive(ss);

			//ワールドに設置してある数を計測
			for (CSpownPoint* spownpoint : spownpointlist)
			{
				i++;
			}

			o_archive(cereal::make_nvp("totalspownpoint", i));		//木の総数を書き込む
			i = 1;		//初期化(jsonに書き込む都合上1から)

			for (CSpownPoint* spownpoint : spownpointlist)
			{
				tmp = moji;
				tmp += i;
				o_archive(cereal::make_nvp(tmp, *spownpoint));
				i++;
			}
		}

		std::ofstream outputFile(filename, std::ios::out);
		//書き出す
		outputFile << ss.str();
		//閉じる
		outputFile.close();
		ss.clear();
	}

	//地形情報をファイルに書き込む
	{
		strcpy(path2, temp);
		strcat(path2, "/field.txt");
		SaveFile = fopen(path2, "w");
		if (SaveFile == NULL)	// オープンに失敗した場合
			return;				// 異常終了
		CMeshField* pMeshField = scene->GetGameObject<CMeshField>(1);
		pMeshField->Save(SaveFile);
		fclose(SaveFile);
	}
}