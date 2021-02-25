//
//�f�[�^�̃Z�[�u
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

	//�t���p�X���Ƃ�
	_tcscpy_s(def_dir, sizeof(def_dir) / sizeof(TCHAR), _TEXT("D:"));
	if (GetDir(GetWindow(), def_dir, path) == false)
		return;

	assetpass = PassAsset(path);//�t�@�C���̃p�X��asset�t�H���_����ɂ���
	Save();						//�ۑ�
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

	//�����o��
	outputFile << ss.str();
	//����
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
	//�f�[�^���������ޏ���(���ʂň͂�Ȃ��ƃt�@�C��������ɍ쐬����Ȃ�)
	{
		cereal::JSONOutputArchive o_archive(ss);

		//�G�̑������v��
		for (T* Gameobject : savedata)
		{
			i++;
		}
		o_archive(cereal::make_nvp(total, i));		//��������������
		i = 1;

		//�G�̏�����������
		for (T* Gameobject : savedata)
		{
			tmp = data;
			tmp += i;
			o_archive(cereal::make_nvp(tmp, *Gameobject));
			i++;
		}
	}

	std::ofstream outputFile(fullpath, std::ios::out);
	//�����o��
	outputFile << ss.str();
	//����
	outputFile.close();
	ss.clear();
	return;
}

void CSAVE::Save()
{
	CScene* scene = CManager::GetScene();
	//�v���C���[�̏����t�@�C���ɏ�������
	{
		//�v���C���[�̏��������o��
		CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);
		std::string playerpass = "/playerdata.json";	//json�t�@�C����
		std::string playerdata = "playerdata";		//json�t�@�C���ɏ������ގ��̃f�[�^�̖��O

		GameObjectSave(pPlayer, playerpass, playerdata);
	}

	//�G�̏����t�@�C���ɏ�������
	{
		std::vector<CEnemy*> enemylist = scene->GetGameObjects<CEnemy>(1);
		std::string enemypass = "/enemydata.json";	//json�t�@�C����
		std::string enemydata = "enemydata";		//json�t�@�C���ɏ������ގ��̃f�[�^�̖��O
		std::string enemynum = "totalenemy";		//������json�t�@�C���ɏ������ގ��̖��O

		GameObjectsSave(enemylist, enemypass, enemydata, enemynum);		//������������
	}

	//���������t�@�C���ɏ�������
	{
		std::vector<CFriend*> friendlist = scene->GetGameObjects<CFriend>(1);
		std::string friendpass = "/frienddata.json";	//json�t�@�C����
		std::string frienddata = "frienddata";		//json�t�@�C���ɏ������ގ��̃f�[�^�̖��O
		std::string friendnum = "totalfriend";		//������json�t�@�C���ɏ������ގ��̖��O

		GameObjectsSave(friendlist, friendpass, frienddata, friendnum);		//������������
	}

	//�o���J�[�����t�@�C���ɏ�������
	{
		std::vector<CBUNKER*> bunkerlist = scene->GetGameObjects<CBUNKER>(1);

		std::string bunkerpass = "/bunkerdata.json";	//json�t�@�C����
		std::string bunkerdata = "bunkerdata";		//json�t�@�C���ɏ������ގ��̃f�[�^�̖��O
		std::string bunkernum = "totalbunker";		//������json�t�@�C���ɏ������ގ��̖��O

		GameObjectsSave(bunkerlist, bunkerpass, bunkerdata, bunkernum);		//������������
	}

	//���_������������
	{
		std::vector<CBase*> baselist = scene->GetGameObjects<CBase>(1);

		std::string basepass = "/basedata.json";	//json�t�@�C����
		std::string basedata = "basedata";		//json�t�@�C���ɏ������ގ��̃f�[�^�̖��O
		std::string basenum = "totalbase";		//������json�t�@�C���ɏ������ގ��̖��O

		GameObjectsSave(baselist, basepass, basedata, basenum);		//������������
	}

	//�؏�����������
	{
		std::vector<CTREE*> treelist = scene->GetGameObjects<CTREE>(1);

		std::string treepass = "/treedata.json";	//json�t�@�C����
		std::string treedata = "treedata";		//json�t�@�C���ɏ������ގ��̃f�[�^�̖��O
		std::string treenum = "totaltree";		//������json�t�@�C���ɏ������ގ��̖��O

		GameObjectsSave(treelist, treepass, treedata, treenum);		//������������
	}

	//�͂�؏�����������
	{
		std::vector<CDEADTREE*> deadtreelist = scene->GetGameObjects<CDEADTREE>(1);

		std::string deadtreepass = "/deadtreedata.json";	//json�t�@�C����
		std::string deadtreedata = "deadtreedata";		//json�t�@�C���ɏ������ގ��̃f�[�^�̖��O
		std::string deadtreenum = "totaldeadtree";		//������json�t�@�C���ɏ������ގ��̖��O

		GameObjectsSave(deadtreelist, deadtreepass, deadtreedata, deadtreenum);		//������������
	}

	//�X�|�[�������t�@�C���ɏ�������
	{
		std::vector<CSpownPoint*> spownpointlist = scene->GetGameObjects<CSpownPoint>(1);

		std::string spownpointpass = "/spownpointdata.json";	//json�t�@�C����
		std::string spownpointdata = "spownpointdata";		//json�t�@�C���ɏ������ގ��̃f�[�^�̖��O
		std::string spownpointnum = "totalspownpoint";		//������json�t�@�C���ɏ������ގ��̖��O

		GameObjectsSave(spownpointlist, spownpointpass, spownpointdata, spownpointnum);		//������������
	}

	//�n�`�����t�@�C���ɏ�������
	{
		CMeshField* pMeshField = scene->GetGameObject<CMeshField>(1);
		std::string meshfieldpass = "/field.json";	//json�t�@�C����
		std::string meshfielddata = "meshfielddata";		//json�t�@�C���ɏ������ގ��̃f�[�^�̖��O

		GameObjectSave(pMeshField, meshfieldpass, meshfielddata);
	}
}

void CSAVE::TestData_Save()
{
	assetpass = "asset/testsavedata";		//�e�X�g�f�[�^�p�̃p�X��p��
	Save();									//�ۑ�
}