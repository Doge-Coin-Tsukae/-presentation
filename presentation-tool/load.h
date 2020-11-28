#pragma once

#include"gameobject.h"

class CLOAD : public CGameObject
{
private:
	std::string filename;

public:
	void Uninit();
	void Update();
	void Data_Load();
};