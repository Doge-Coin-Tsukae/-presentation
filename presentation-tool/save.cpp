//
//�f�[�^�̃Z�[�u
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
	path2 = PassAsset(path);//�t�@�C���̃p�X��asset�t�H���_����ɂ���
	strcpy(temp, path2);

	//�v���C���[�̏����t�@�C���ɏ�������
	{
		//�v���C���[�̏��������o��
		CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);
		std::stringstream ss;
		std::string path = path2;
		path += "/playerdata.json";
		{
			cereal::JSONOutputArchive o_archive(ss);
			o_archive(cereal::make_nvp("playerdata", *pPlayer));
		}
		std::ofstream outputFile(path, std::ios::out);
			//�����o��
		outputFile << ss.str();
			//����
		outputFile.close();
		ss.clear();
	}

	//�G�̏����t�@�C���ɏ�������
	{
		std::vector<CEnemy*> enemylist = scene->GetGameObjects<CEnemy>(1);
		
		std::stringstream ss;
		std::string filename = path2;
		filename += "/enemydata.json";

		int  i = 1;
		std::string moji = "enemydata";
		std::string tmp;
		//�f�[�^���������ޏ���(���ʂň͂�Ȃ��ƃt�@�C��������ɍ쐬����Ȃ�)
		{
			cereal::JSONOutputArchive o_archive(ss);

			//�G�̑������v��
			for (CEnemy* enemy : enemylist)
			{
				i++;
			}
			o_archive(cereal::make_nvp("totalenemy", i));		//�G�̑�������������
			i = 1;

			//�G�̏�����������
			for (CEnemy* enemy : enemylist)
			{
				tmp = moji;
				tmp += i;
				o_archive(cereal::make_nvp(tmp, *enemy));
				i++;
			}
		}
		std::ofstream outputFile(filename, std::ios::out);
		//�����o��
		outputFile << ss.str();
		//����
		outputFile.close();
		ss.clear();
	}

	//���������t�@�C���ɏ�������
	{
		std::vector<CFriend*> friendlist = scene->GetGameObjects<CFriend>(1);

		std::stringstream ss;
		std::string filename = path2;
		filename += "/frienddata.json";

		int  i = 1;
		std::string moji = "frienddata";
		std::string tmp;
		//�f�[�^���������ޏ���(���ʂň͂�Ȃ��ƃt�@�C��������ɍ쐬����Ȃ�)
		{
			cereal::JSONOutputArchive o_archive(ss);

			//�G�̑������v��
			for (CFriend* friends : friendlist)
			{
				i++;
			}
			o_archive(cereal::make_nvp("totalfriend", i));		//�G�̑�������������
			i = 1;

			//�G�̏�����������
			for (CFriend* friends : friendlist)
			{
				tmp = moji;
				tmp += i;
				o_archive(cereal::make_nvp(tmp, *friends));
				i++;
			}
		}
		std::ofstream outputFile(filename, std::ios::out);
		//�����o��
		outputFile << ss.str();
		//����
		outputFile.close();
		ss.clear();
	}

	//�o���J�[�����t�@�C���ɏ�������
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

			//�G�̑������v��
			for (CBUNKER* bunker : bunkerlist)
			{
				i++;
			}
			o_archive(cereal::make_nvp("totalbunker", i));		//�����̑�������������
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
		//�����o��
		outputFile << ss.str();
		//����
		outputFile.close();
		ss.clear();
	}
	//���_������������
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
			//�G�̑������v��
			for (CBase* base : baselist)
			{
				i++;
			}
			o_archive(cereal::make_nvp("totalbase", i));		//��n�̑�������������
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
		//�����o��
		outputFile << ss.str();
		//����
		outputFile.close();
		ss.clear();
	}
	//�؏�����������
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
			o_archive(cereal::make_nvp("totaltree", i));		//�؂̑�������������
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
		//�����o��
		outputFile << ss.str();
		//����
		outputFile.close();
		ss.clear();
	}
	//�͂�؏�����������
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
			o_archive(cereal::make_nvp("totaldeadtree", i));		//�؂̑�������������
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
		//�����o��
		outputFile << ss.str();
		//����
		outputFile.close();
		ss.clear();
	}

	//�X�|�[�������t�@�C���ɏ�������
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

			//���[���h�ɐݒu���Ă��鐔���v��
			for (CSpownPoint* spownpoint : spownpointlist)
			{
				i++;
			}

			o_archive(cereal::make_nvp("totalspownpoint", i));		//�؂̑�������������
			i = 1;		//������(json�ɏ������ޓs����1����)

			for (CSpownPoint* spownpoint : spownpointlist)
			{
				tmp = moji;
				tmp += i;
				o_archive(cereal::make_nvp(tmp, *spownpoint));
				i++;
			}
		}

		std::ofstream outputFile(filename, std::ios::out);
		//�����o��
		outputFile << ss.str();
		//����
		outputFile.close();
		ss.clear();
	}

	//�n�`�����t�@�C���ɏ�������
	{
		strcpy(path2, temp);
		strcat(path2, "/field.txt");
		SaveFile = fopen(path2, "w");
		if (SaveFile == NULL)	// �I�[�v���Ɏ��s�����ꍇ
			return;				// �ُ�I��
		CMeshField* pMeshField = scene->GetGameObject<CMeshField>(1);
		pMeshField->Save(SaveFile);
		fclose(SaveFile);
	}
}