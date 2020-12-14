#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <tchar.h>

#include <shlobj.h>

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
#include "load.h"

int __stdcall BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
bool GetDir(HWND hWnd, TCHAR* def_dir, TCHAR* path);

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
	TCHAR temp[300];
	path2 = PassAsset(path);//�t�@�C���̃p�X��asset�t�H���_����ɂ���
	strcpy(temp, path2);

	//�v���C���[�̏����t�@�C������ǂݍ���
	{
		strcat(path2,"//playerdata.txt");
		SaveFile = fopen(path2, "r");
		if (SaveFile == NULL)           // �I�[�v���Ɏ��s�����ꍇ
			return;

		CPlayer* pPlayer = new CPlayer();
		pPlayer->Init();
		pPlayer->Load(SaveFile);
		scene->AddArgumentGameObject(pPlayer,1);

		fclose(SaveFile);
	}

	//�G�̏����t�@�C������ǂݍ���
	{
		strcpy(path2,temp);
		strcat(path2, "//enemydata.txt");
		SaveFile = fopen(path2, "r");
		if (SaveFile == NULL)           // �I�[�v���Ɏ��s�����ꍇ
			return;

		for (int i = 0; i < 3; i++)
		{
			CEnemy* pEnemy = new CEnemy();
			pEnemy->Init();
			pEnemy->Load(SaveFile,i);
			scene->AddArgumentGameObject(pEnemy, 1);
		}

		fclose(SaveFile);
	}

	//�o���J�[�����t�@�C������ǂݍ���
	{
		strcpy(path2, temp);
		strcat(path2, "//bunkerdata.txt");

		SaveFile = fopen(path2, "r");
		if (SaveFile == NULL)	// �I�[�v���Ɏ��s�����ꍇ
			return;

		for (int i = 0; i < 3; i++)
		{
			CBUNKER* pBunker = new CBUNKER();
			pBunker->Init();
			pBunker->Load(SaveFile, i);
			scene->AddArgumentGameObject(pBunker, 1);
		}

		fclose(SaveFile);
	}

	//���_�����t�@�C������ǂݍ���
	{
		strcpy(path2, temp);
		strcat(path2, "//basedata.txt");
		SaveFile = fopen(path2, "r");
		if (SaveFile == NULL)	// �I�[�v���Ɏ��s�����ꍇ
			return;

		for (int i = 0; i < 3; i++)
		{
			CBASE* pBase = new CBASE();
			pBase->Init();
			pBase->Load(SaveFile, i);
			scene->AddArgumentGameObject(pBase, 1);
		}

		fclose(SaveFile);
	}

	//�؏����t�@�C������ǂݍ���
	{
		strcpy(path2, temp);
		strcat(path2, "//treedata.txt");
		SaveFile = fopen(path2, "r");
		if (SaveFile == NULL)	// �I�[�v���Ɏ��s�����ꍇ
			return;

		for (int i = 0; i < 10; i++)
		{
			CTREE* pTree = new CTREE();
			pTree->Init();
			pTree->Load(SaveFile, i);
			scene->AddArgumentGameObject(pTree, 1);
		}

		fclose(SaveFile);
	}

	//�͂�؏����t�@�C������ǂݍ���
	{
		strcpy(path2, temp);
		strcat(path2, "//deadtreedata.txt");
		SaveFile = fopen(path2, "r");
		if (SaveFile == NULL)	// �I�[�v���Ɏ��s�����ꍇ
			return;

		for (int i = 0; i < 10; i++)
		{
			CDEADTREE* pDeadTree = new CDEADTREE();
			pDeadTree->Init();
			pDeadTree->Load(SaveFile, i);
			scene->AddArgumentGameObject(pDeadTree, 1);
		}

		fclose(SaveFile);
	}

	//�n�`�����t�@�C������ǂݍ���
	{
		strcpy(path2, temp);
		strcat(path2, "//field.txt");
		SaveFile = fopen(path2, "r");
		if (SaveFile == NULL)	// �I�[�v���Ɏ��s�����ꍇ
			return;

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

	std::vector<CBASE*> baselist = scene->GetGameObjects<CBASE>(1);
	for (CBASE* base : baselist)
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

bool GetDir(HWND hWnd, TCHAR* def_dir, TCHAR* path) {
	BROWSEINFO bInfo;
	LPITEMIDLIST pIDList;

	memset(&bInfo, 0, sizeof(bInfo));
	bInfo.hwndOwner = hWnd; // �_�C�A���O�̐e�E�C���h�E�̃n���h�� 
	bInfo.pidlRoot = NULL; // ���[�g�t�H���_���f�X�N�g�b�v�t�H���_�Ƃ��� 
	bInfo.pszDisplayName = path; //�t�H���_�����󂯎��o�b�t�@�ւ̃|�C���^ 
	bInfo.lpszTitle = TEXT("�t�H���_�̑I��"); // �c���[�r���[�̏㕔�ɕ\������镶���� 
	bInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_VALIDATE | BIF_NEWDIALOGSTYLE; // �\�������t�H���_�̎�ނ������t���O 
	bInfo.lpfn = BrowseCallbackProc; // BrowseCallbackProc�֐��̃|�C���^ 
	bInfo.lParam = (LPARAM)def_dir;
	pIDList = SHBrowseForFolder(&bInfo);
	if (pIDList == NULL) {
		path[0] = _TEXT('\0');
		return false; //�����I������Ȃ������ꍇ 
	}
	else {
		if (!SHGetPathFromIDList(pIDList, path))
			return false;//�ϊ��Ɏ��s 
		CoTaskMemFree(pIDList);// pIDList�̃��������J�� 
		return true;
	}
}

int __stdcall BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData) {
	TCHAR dir[MAX_PATH];
	ITEMIDLIST *lpid;
	HWND hEdit;

	switch (uMsg) {
	case BFFM_INITIALIZED:  //      �_�C�A���O�{�b�N�X��������
		SendMessage(hWnd, BFFM_SETSELECTION, (WPARAM)TRUE, lpData);     //      �R�����_�C�A���O�̏����f�B���N�g��
		break;
	case BFFM_VALIDATEFAILED:       //      �����ȃt�H���_�[�������͂��ꂽ
		MessageBox(hWnd, (TCHAR*)lParam, _TEXT("�����ȃt�H���_�[�������͂���܂���"), MB_OK);
		hEdit = FindWindowEx(hWnd, NULL, _TEXT("EDIT"), NULL);     //      �G�f�B�b�g�{�b�N�X�̃n���h�����擾����
		SetWindowText(hEdit, _TEXT(""));
		return 1;       //      �_�C�A���O�{�b�N�X����Ȃ�
		break;
	case BFFM_IUNKNOWN:
		break;
	case BFFM_SELCHANGED:   //      �I���t�H���_�[���ω������ꍇ
		lpid = (ITEMIDLIST *)lParam;
		SHGetPathFromIDList(lpid, dir);
		hEdit = FindWindowEx(hWnd, NULL, _TEXT("EDIT"), NULL);     //      �G�f�B�b�g�{�b�N�X�̃n���h�����擾����
		SetWindowText(hEdit, dir);
		break;
	}
	return 0;
}