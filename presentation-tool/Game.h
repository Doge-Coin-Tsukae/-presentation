#pragma once

#include "scene.h"

class CGame : public CScene
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	//draw�͉��������Ȃ��ꍇ�AScene����Ăяo�����B
};