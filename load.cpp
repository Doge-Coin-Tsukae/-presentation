//=====================================
//
//  ���[�h���s��
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
	Data_Destroy();	//���[�h����O�ɂ���܂łɔz�u����Ă����I�u�W�F�N�g���폜����


	//�v���C���[�̏����t�@�C������ǂݍ���
	{
		CPlayer* pplayer = new CPlayer;
		std::string playerpass = "asset/savedata/playerdata.json";	//json�t�@�C����
		std::string playerdata = "playerdata";		//json�t�@�C���ɓǂݍ��ގ��̃f�[�^�̖��O
		GameObjectLoad(pplayer, playerpass, playerdata);

		delete pplayer;
	}

	//�G�̏����t�@�C������ǂݍ���
	{
		CEnemy* penemy = new CEnemy;
		std::string enemypass = "asset/savedata/enemydata.json";	//json�t�@�C����
		std::string enemydata = "enemydata";		//json�t�@�C���ɓǂݍ��ގ��̃f�[�^�̖��O
		std::string enemynum = "totalenemy";		//������json�t�@�C���ɓǂݍ��ގ��̖��O
		GameObjectsLoad(penemy, enemypass, enemydata, enemynum,1);
		delete penemy;
	}

	//���������t�@�C������ǂݍ���
	{
		CFriend* pfriend = new CFriend;
		std::string enemypass = "asset/savedata/frienddata.json";	//json�t�@�C����
		std::string enemydata = "frienddata";		//json�t�@�C���ɓǂݍ��ގ��̃f�[�^�̖��O
		std::string enemynum = "totalfriend";		//������json�t�@�C���ɓǂݍ��ގ��̖��O
		GameObjectsLoad(pfriend, enemypass, enemydata, enemynum,1);
		delete pfriend;
	}

	//�o���J�[�����t�@�C������ǂݍ���
	{
		CBUNKER* pbunker = new CBUNKER;
		std::string bunkerpass = "asset/savedata/bunkerdata.json";	//json�t�@�C����
		std::string bunkerdata = "bunkerdata";			//json�t�@�C���ɓǂݍ��ގ��̃f�[�^�̖��O
		std::string bunkernum = "totalbunker";			//������json�t�@�C���ɓǂݍ��ގ��̖��O
		GameObjectsLoad(pbunker, bunkerpass, bunkerdata, bunkernum,1);
		delete pbunker;
	}

	//���_�����t�@�C������ǂݍ���
	{
		CBASE* pbase = new CBASE;
		std::string basepass = "asset/savedata/basedata.json";	//json�t�@�C����
		std::string basedata = "basedata";			//json�t�@�C���ɓǂݍ��ގ��̃f�[�^�̖��O
		std::string basenum = "totalbase";			//������json�t�@�C���ɓǂݍ��ގ��̖��O
		GameObjectsLoad(pbase, basepass, basedata, basenum,2);
		delete pbase;
	}

	//�؏����t�@�C������ǂݍ���
	{
		CTREE* ptree = new CTREE;
		std::string treepass = "asset/savedata/treedata.json";	//json�t�@�C����
		std::string treedata = "treedata";			//json�t�@�C���ɓǂݍ��ގ��̃f�[�^�̖��O
		std::string treenum = "totaltree";			//������json�t�@�C���ɏ������ގ��̖��O
		GameObjectsLoad(ptree, treepass, treedata, treenum,3);
		delete ptree;
	}

	//�͂�؏����t�@�C������ǂݍ���
	{
		CDEADTREE* pdeadtree = new CDEADTREE;
		std::string deadtreepass = "asset/savedata/deadtreedata.json";	//json�t�@�C����
		std::string deadtreedata = "deadtreedata";			//json�t�@�C���ɓǂݍ��ގ��̃f�[�^�̖��O
		std::string deadtreenum = "totaldeadtree";			//������json�t�@�C���ɓǂݍ��ގ��̖��O
		GameObjectsLoad(pdeadtree, deadtreepass, deadtreedata, deadtreenum,1);
		delete pdeadtree;
	}

	//�X�|�[���|�C���g�����t�@�C������ǂݍ���
	{
		CSpownPoint* pspownpoint = new CSpownPoint;
		std::string spownpointpass = "asset/savedata/spownpointdata.json";	//json�t�@�C����
		std::string spownpointdata = "spownpointdata";			//json�t�@�C������ǂݍ��ގ��̃f�[�^�̖��O
		std::string spownpointnum = "totalspownpoint";			//������json�t�@�C���ɓǂݍ��ގ��̖��O
		GameObjectsLoad(pspownpoint, spownpointpass, spownpointdata, spownpointnum,1);
		delete pspownpoint;
	}

	//�n�`�����t�@�C������ǂݍ���
	{
		CMeshField* pmeshfield = new CMeshField;
		std::string fieldpass = "asset/savedata/field.json";	//json�t�@�C����
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

	//���X�g����s�b�N�A�b�v���ăf�[�^�폜
	std::vector<CEnemy*> enemylist = scene->GetGameObjects<CEnemy>(1);
	for (CEnemy* enemy : enemylist)
	{
		enemy->SetDestroy();
	}

	//���X�g����s�b�N�A�b�v���ăf�[�^�폜
	std::vector<CBUNKER*> bunkerlist = scene->GetGameObjects<CBUNKER>(1);
	for (CBUNKER* bunker : bunkerlist)
	{
		bunker->SetDestroy();
	}

	//���X�g����s�b�N�A�b�v���ăf�[�^�폜
	std::vector<CBASE*> baselist = scene->GetGameObjects<CBASE>(2);
	for (CBASE* base : baselist)
	{
		base->SetDestroy();
	}

	//���X�g����s�b�N�A�b�v���ăf�[�^�폜
	std::vector<CTREE*> treelist = scene->GetGameObjects<CTREE>(3);
	for (CTREE* tree : treelist)
	{
		tree->SetDestroy();
	}

	//���X�g����s�b�N�A�b�v���ăf�[�^�폜
	std::vector<CDEADTREE*> deadtreelist = scene->GetGameObjects<CDEADTREE>(1);
	for (CDEADTREE* deadtree : deadtreelist)
	{
		deadtree->SetDestroy();
	}
}


template<typename T>
void CLOAD::GameObjectLoad(T* savedata, std::string fullname, std::string data)		//�P���̃I�u�W�F�N�g�����[�h����
{
	T* pclass = new T();
	pclass->Init();

	std::stringstream stream;
	//�t�@�C�����̓X�g���[���쐬
	std::ifstream inputFile(fullname, std::ios::in);
	//���̓f�[�^��S��������stream�ɓ�����
	stream << inputFile.rdbuf();
	//json�����[�h
	cereal::JSONInputArchive jsonInputArchive(stream);

	jsonInputArchive(cereal::make_nvp(data, *pclass));

	CScene* scene = CManager::GetScene();
	pclass->FileLoad();
	scene->AddArgumentGameObject(pclass, 1);

	stream.clear();
	inputFile.close();
}

template<typename T>
void CLOAD::GameObjectsLoad(T* savedata, std::string fullname, std::string data, std::string total, int layer)	//�����̃I�u�W�F�N�g�����[�h
{
	int totalnumber = 0;		//�G�̑���
	std::string tmp;			//json�̓G�f�[�^�̍�ƃt�@�C��
	std::stringstream stream;

	//�t�@�C�����̓X�g���[���쐬
	std::ifstream inputFile(fullname, std::ios::in);
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
		pclass->FileLoad();
		scene->AddArgumentGameObject(pclass, layer);
	}

	inputFile.close();
	stream.clear();
}