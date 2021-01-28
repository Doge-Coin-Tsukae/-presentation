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
	//I���������Ƃ��Ƀt�@�C����ǂݍ��ޏ���������
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
	ShowCursor(TRUE);
	FILE *SaveFile;//�t�@�C���|�C���^
	CScene* scene = CManager::GetScene();	

	TCHAR def_dir[100] , path[300] ;

	_tcscpy_s(def_dir, sizeof(def_dir) / sizeof(TCHAR), _TEXT("D:"));
	if (GetDir(GetWindow(), def_dir, path) == false)
		return;

	ShowCursor(FALSE);
	Data_Destroy();	//���[�h����O�ɂ���܂łɔz�u����Ă����I�u�W�F�N�g���폜����
	
	TCHAR *path2 = NULL;
	path2 = PassAsset(path);//�t�@�C���̃p�X��asset�t�H���_����ɂ���

	//�p�X�ύX�Ɏ��s������I��
	if (!path2)
		return;

	//�v���C���[�̏����t�@�C������ǂݍ���
	{
		CPlayer* pPlayer = new CPlayer();
		pPlayer->Init();
		std::string path = path2;
		path += "/playerdata.json";

		std::stringstream stream;
		//�t�@�C�����̓X�g���[���쐬
		std::ifstream inputFile(path, std::ios::in);
		//���̓f�[�^��S��������stream�ɓ�����
		stream << inputFile.rdbuf();
		//json�����[�h
		cereal::JSONInputArchive jsonInputArchive(stream);

		jsonInputArchive(cereal::make_nvp("playerdata", *pPlayer));
		scene->AddArgumentGameObject(pPlayer,1);

		stream.clear();
		inputFile.close();
		path.clear();
	}

	//�G�̏����t�@�C������ǂݍ���
	{

		int totalnumber = 0;	//�G�̑���
		std::string moji = "enemydata";		//json�̓G�f�[�^
		std::string tmp;					//json�̓G�f�[�^�̍�ƃt�@�C��

		std::string path = path2;
		path += "/enemydata.json";
		std::stringstream stream;

		//�t�@�C�����̓X�g���[���쐬
		std::ifstream inputFile(path, std::ios::in);
		//���̓f�[�^��S��������stream�ɓ�����
		stream << inputFile.rdbuf();

		//json�����[�h
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

	//���������t�@�C������ǂݍ���
	{

		int totalnumber = 0;	//�G�̑���
		std::string moji = "frienddata";		//json�̓G�f�[�^
		std::string tmp;					//json�̓G�f�[�^�̍�ƃt�@�C��

		std::string path = path2;
		path += "/frienddata.json";
		std::stringstream stream;

		//�t�@�C�����̓X�g���[���쐬
		std::ifstream inputFile(path, std::ios::in);
		//���̓f�[�^��S��������stream�ɓ�����
		stream << inputFile.rdbuf();

		//json�����[�h
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

	//�o���J�[�����t�@�C������ǂݍ���
	{
		int totalnumber = 0;	//�G�̑���
		std::string moji = "bunkerdata";		//json�̓G�f�[�^
		std::string tmp;					//json�̓G�f�[�^�̍�ƃt�@�C��

		std::string path = path2;
		path += "/bunkerdata.json";
		std::stringstream stream;

		//�t�@�C�����̓X�g���[���쐬
		std::ifstream inputFile(path, std::ios::in);
		//���̓f�[�^��S��������stream�ɓ�����
		stream << inputFile.rdbuf();

		//json�����[�h
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

	//���_�����t�@�C������ǂݍ���
	{
		int totalnumber = 0;	//�G�̑���
		std::string moji = "basedata";		//json�̓G�f�[�^
		std::string tmp;					//json�̓G�f�[�^�̍�ƃt�@�C��

		std::string path = path2;
		path += "/basedata.json";
		std::stringstream stream;

		//�t�@�C�����̓X�g���[���쐬
		std::ifstream inputFile(path, std::ios::in);
		//���̓f�[�^��S��������stream�ɓ�����
		stream << inputFile.rdbuf();

		//json�����[�h
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

	//�؏����t�@�C������ǂݍ���
	{
		int totalnumber = 0;	//�G�̑���
		std::string moji = "treedata";		//json�̓G�f�[�^
		std::string tmp;					//json�̓G�f�[�^�̍�ƃt�@�C��

		std::string path = path2;
		path += "/treedata.json";
		std::stringstream stream;

		//�t�@�C�����̓X�g���[���쐬
		std::ifstream inputFile(path, std::ios::in);
		//���̓f�[�^��S��������stream�ɓ�����
		stream << inputFile.rdbuf();

		//json�����[�h
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

	//�͂�؏����t�@�C������ǂݍ���
	{
		int totalnumber = 0;	//�G�̑���
		std::string moji = "deadtreedata";		//json�̓G�f�[�^
		std::string tmp;					//json�̓G�f�[�^�̍�ƃt�@�C��

		std::string path = path2;
		path += "/deadtreedata.json";
		std::stringstream stream;

		//�t�@�C�����̓X�g���[���쐬
		std::ifstream inputFile(path, std::ios::in);
		//���̓f�[�^��S��������stream�ɓ�����
		stream << inputFile.rdbuf();

		//json�����[�h
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

	//�n�`�����t�@�C������ǂݍ���
	{
		strcat(path2, "/field.txt");
		SaveFile = fopen(path2, "r");
		if(SaveFile == NULL)           // �I�[�v���Ɏ��s�����ꍇ
		{
			MessageBox(GetWindow(), "�n�`�̃f�[�^��������܂���", "���[�h���s!", MB_ICONWARNING);
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
}