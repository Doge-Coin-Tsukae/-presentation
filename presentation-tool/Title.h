#pragma once

#include "scene.h"

class CTitle : public CScene
{
private:
	int count;	//操作しなくても一定秒数後に勝手に起動させる
public:
	void Init();
	void Update();

};