#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene.h"

#include"tree.h"
#include "meshfield.h"
#include "human.h"
#include "model.h"
#include "carsor.h"
#include "colider.h"
#include "sight.h"
#include "weapon.h"
#include "player.h"
#include "enemy.h"
#include "deadtree.h"
#include "bunker.h"
#include "base.h"
#include "save.h"

void CSAVE::Uninit()
{

}

void CSAVE::Update()
{
	if (CInput::GetKeyTrigger('U'))
		Data_Save();
}

void CSAVE::Data_Save()
{
	FILE *SaveFile;
	CScene* scene = CManager::GetScene();

	//�v���C���[�̏����t�@�C���ɏ�������
	{
		SaveFile = fopen("asset/savedata/playerdata.txt", "w");

		if (SaveFile == NULL)           // �I�[�v���Ɏ��s�����ꍇ
			return;                         // �ُ�I��
		//�v���C���[�̏��������o��
		CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);
		pPlayer->Save(SaveFile);
		fclose(SaveFile);
	}

	//�G�̏����t�@�C���ɏ�������
	{
		SaveFile = fopen("asset/savedata/enemydata.txt", "w");

		if (SaveFile == NULL)           // �I�[�v���Ɏ��s�����ꍇ
			return;                         // �ُ�I��
		//�G�̏��������o��

		std::vector<CEnemy*> enemylist = scene->GetGameObjects<CEnemy>(1);

		//����ۑ�����
		fprintf(SaveFile, "%d\n");

		for (CEnemy* enemy : enemylist)
		{
			enemy->Save(SaveFile);
		}

		fclose(SaveFile);
	}

	//�o���J�[�����t�@�C���ɏ�������
	{
		SaveFile = fopen("asset/savedata/bunkerdata.txt", "w");
		if (SaveFile == NULL)	// �I�[�v���Ɏ��s�����ꍇ
			return;				// �ُ�I��
		//������������
		std::vector<CBUNKER*> bunkerlist = scene->GetGameObjects<CBUNKER>(1);
		for (CBUNKER* bunker : bunkerlist)
		{
			bunker->Save(SaveFile);
		}

		fclose(SaveFile);
	}
	//���_������������
	{
		SaveFile = fopen("asset/savedata/basedata.txt", "w");
		if (SaveFile == NULL)	// �I�[�v���Ɏ��s�����ꍇ
			return;             // �ُ�I��
		//������������
		std::vector<CBASE*> baselist = scene->GetGameObjects<CBASE>(1);
		for (CBASE* base : baselist)
		{
			base->Save(SaveFile);
		}

		fclose(SaveFile);
	}
	//�؏�����������
	{
		SaveFile = fopen("asset/savedata/treedata.txt", "w");
		if (SaveFile == NULL)	// �I�[�v���Ɏ��s�����ꍇ
			return;				// �ُ�I��
		//������������
		std::vector<CTREE*> treelist = scene->GetGameObjects<CTREE>(1);
		for (CTREE* tree : treelist)
		{
			tree->Save(SaveFile);
		}

		fclose(SaveFile);
	}
	//�͂�؏�����������
	{
		SaveFile = fopen("asset/savedata/deadtreedata.txt", "w");
		if (SaveFile == NULL)	// �I�[�v���Ɏ��s�����ꍇ
			return;				// �ُ�I��
		//������������
		std::vector<CDEADTREE*> deadtreelist = scene->GetGameObjects<CDEADTREE>(1);
		for (CDEADTREE* deadtree : deadtreelist)
		{
			deadtree->Save(SaveFile);
		}

		fclose(SaveFile);
	}
	//�n�`�����t�@�C���ɏ�������
	{
		SaveFile = fopen("asset/savedata/field.txt", "w");
		if (SaveFile == NULL)	// �I�[�v���Ɏ��s�����ꍇ
			return;				// �ُ�I��
		CMeshField* pMeshField = scene->GetGameObject<CMeshField>(1);
		pMeshField->Save(SaveFile);
		fclose(SaveFile);
	}
}
