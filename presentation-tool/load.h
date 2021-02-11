#pragma once

#include"gameobject.h"

class CLOAD : public CGameObject
{
private:
	std::string assetpass;

	template<typename T>
	void GameObjectLoad(T* savedata, std::string fullname, std::string data);		//�P���̃I�u�W�F�N�g�����[�h����
	template<typename T>
	void GameObjectsLoad(T* savedata, std::string fullname, std::string data, std::string total);	//�����̃I�u�W�F�N�g�����[�h����
public:
	void Uninit();			//�I������
	void Update();			//�X�V����
	void Data_Load();		//�t�@�C������f�[�^�����[�h����
	void Data_Destroy();	//�Q�[���I�u�W�F�N�g�̍폜
	TCHAR* PassAsset(TCHAR path[300]);		//�t���p�X������s�t�@�C���̒��ɂ���Asset�t�H���_����̃p�X�ɕύX
};