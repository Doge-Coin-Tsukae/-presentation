#pragma once

#include"gameobject.h"

class CSAVE : public CGameObject
{
private:
	std::string filename;
	std::string assetpass;
	template<typename T>
	void GameObjectSave(T* savedata, std::string fullename, std::string data);		//�P���̃I�u�W�F�N�g���Z�[�u����
	template<typename T>
	void GameObjectsSave(std::vector<T*> savedata,std::string fullename,std::string data,std::string total);	//�����̃I�u�W�F�N�g���Z�[�u����
public:
	void Uninit();
	void Update();
	void Data_Save();
	TCHAR* PassAsset(TCHAR path[300]);
};