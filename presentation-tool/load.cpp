//
//�f�[�^�̃��[�h
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
	//I���������Ƃ��Ƀt�@�C����ǂݍ��ޏ���������(�V���[�g�J�b�g)
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
	//asset��������Ȃ�����
	MessageBox(GetWindow(), "asset�t�H���_��������܂���B", "���[�h���s!", MB_ICONSTOP);
	return NULL;
}

void CLOAD::Data_Load()
{
	TCHAR def_dir[100], path[300];
	//�t�@�C���Q�Ƃ̃_�C�A���O�{�b�N�X�\��
	_tcscpy_s(def_dir, sizeof(def_dir) / sizeof(TCHAR), _TEXT("D:"));
	if (GetDir(GetWindow(), def_dir, path) == false)
		return;

	Data_Destroy();	//���[�h����O�ɂ���܂łɔz�u����Ă����I�u�W�F�N�g���폜����
	assetpass = PassAsset(path);//�t�@�C���̃p�X��asset�t�H���_����ɂ���

	//�p�X�ύX�Ɏ��s������I��
	if (!assetpass.c_str())	return;

	//�v���C���[�̏����t�@�C������ǂݍ���
	{
		CPlayer* pplayer = new CPlayer;
		std::string playerpass = "/playerdata.json";	//json�t�@�C����
		std::string playerdata = "playerdata";		//json�t�@�C���ɓǂݍ��ގ��̃f�[�^�̖��O
		GameObjectLoad(pplayer, playerpass, playerdata);
		delete pplayer;
	}

	//�G�̏����t�@�C������ǂݍ���
	{
		CEnemy* penemy = new CEnemy;
		std::string enemypass = "/enemydata.json";	//json�t�@�C����
		std::string enemydata = "enemydata";		//json�t�@�C���ɓǂݍ��ގ��̃f�[�^�̖��O
		std::string enemynum = "totalenemy";		//������json�t�@�C���ɓǂݍ��ގ��̖��O
		GameObjectsLoad(penemy, enemypass,enemydata,enemynum);
		delete penemy;
	}

	//���������t�@�C������ǂݍ���
	{
		CFriend* pfriend = new CFriend;
		std::string enemypass = "/frienddata.json";	//json�t�@�C����
		std::string enemydata = "frienddata";		//json�t�@�C���ɓǂݍ��ގ��̃f�[�^�̖��O
		std::string enemynum = "totalfriend";		//������json�t�@�C���ɓǂݍ��ގ��̖��O
		GameObjectsLoad(pfriend, enemypass, enemydata, enemynum);
		delete pfriend;
	}

	//�o���J�[�����t�@�C������ǂݍ���
	{
		CBUNKER* pbunker = new CBUNKER;
		std::string bunkerpass = "/bunkerdata.json";	//json�t�@�C����
		std::string bunkerdata = "bunkerdata";			//json�t�@�C���ɓǂݍ��ގ��̃f�[�^�̖��O
		std::string bunkernum = "totalbunker";			//������json�t�@�C���ɓǂݍ��ގ��̖��O
		GameObjectsLoad(pbunker, bunkerpass, bunkerdata, bunkernum);
		delete pbunker;
	}

	//���_�����t�@�C������ǂݍ���
	{
		CBase* pbase = new CBase;
		std::string basepass = "/basedata.json";	//json�t�@�C����
		std::string basedata = "basedata";			//json�t�@�C���ɓǂݍ��ގ��̃f�[�^�̖��O
		std::string basenum = "totalbase";			//������json�t�@�C���ɓǂݍ��ގ��̖��O
		GameObjectsLoad(pbase, basepass, basedata, basenum);
		delete pbase;
	}

	//�؏����t�@�C������ǂݍ���
	{
		CTREE* ptree = new CTREE;
		std::string treepass = "/treedata.json";	//json�t�@�C����
		std::string treedata = "treedata";			//json�t�@�C���ɓǂݍ��ގ��̃f�[�^�̖��O
		std::string treenum = "totaltree";			//������json�t�@�C���ɏ������ގ��̖��O
		GameObjectsLoad(ptree, treepass, treedata, treenum);
		delete ptree;
	}

	//�͂�؏����t�@�C������ǂݍ���
	{
		CDEADTREE* pdeadtree = new CDEADTREE;
		std::string deadtreepass = "/deadtreedata.json";	//json�t�@�C����
		std::string deadtreedata = "deadtreedata";			//json�t�@�C���ɓǂݍ��ގ��̃f�[�^�̖��O
		std::string deadtreenum = "totaldeadtree";			//������json�t�@�C���ɓǂݍ��ގ��̖��O
		GameObjectsLoad(pdeadtree, deadtreepass, deadtreedata, deadtreenum);
		delete pdeadtree;
	}

	//�X�|�[���|�C���g�����t�@�C������ǂݍ���
	{
		CSpownPoint* pspownpoint = new CSpownPoint;
		std::string spownpointpass = "/spownpointdata.json";	//json�t�@�C����
		std::string spownpointdata = "spownpointdata";			//json�t�@�C������ǂݍ��ގ��̃f�[�^�̖��O
		std::string spownpointnum = "totalspownpoint";			//������json�t�@�C���ɓǂݍ��ގ��̖��O
		GameObjectsLoad(pspownpoint, spownpointpass, spownpointdata, spownpointnum);
		delete pspownpoint;
	}

	//�n�`�����t�@�C������ǂݍ���
	{
		CMeshField* pmeshfield = new CMeshField;
		std::string fieldpass = "/field.json";	//json�t�@�C����
		std::string fielddata = "meshfielddata";		//json�t�@�C���ɓǂݍ��ގ��̃f�[�^�̖��O
		GameObjectLoad(pmeshfield, fieldpass, fielddata);
		delete pmeshfield;
	}
}

void CLOAD::Data_Destroy()
{
	CScene* scene = CManager::GetScene();

	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);
	if(pPlayer  != nullptr)		//�v���C���[��񂪂������Ƃ���������
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
	if (pMeshField != nullptr)		//���b�V���t�B�[���h��񂪂������Ƃ���������
		pMeshField->SetDestroy();
}

template<typename T>
void CLOAD::GameObjectLoad(T* savedata, std::string fullname, std::string data)		//�P���̃I�u�W�F�N�g�����[�h����
{
	T* pclass = new T();
	pclass->Init();
	std::string path = assetpass;
	path += fullname;

	std::stringstream stream;
	//�t�@�C�����̓X�g���[���쐬
	std::ifstream inputFile(path, std::ios::in);
	//���̓f�[�^��S��������stream�ɓ�����
	stream << inputFile.rdbuf();
	//json�����[�h
	cereal::JSONInputArchive jsonInputArchive(stream);

	jsonInputArchive(cereal::make_nvp(data, *pclass));

	CScene* scene = CManager::GetScene();
	scene->AddArgumentGameObject(pclass, 1);

	stream.clear();
	inputFile.close();
	path.clear();
}

template<typename T>
void CLOAD::GameObjectsLoad(T* savedata, std::string fullname, std::string data, std::string total)	//�����̃I�u�W�F�N�g�����[�h
{
		int totalnumber = 0;	//�G�̑���
		std::string tmp;					//json�̓G�f�[�^�̍�ƃt�@�C��

		std::string path = assetpass;
		path += fullname;
		std::stringstream stream;

		//�t�@�C�����̓X�g���[���쐬
		std::ifstream inputFile(path, std::ios::in);
		//���̓f�[�^��S��������stream�ɓ�����
		stream << inputFile.rdbuf();

		//json�����[�h
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