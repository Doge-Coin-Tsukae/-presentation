#pragma once

#include "scene.h"

class CGame : public CScene
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	//drawは何も書かない場合、Sceneから呼び出される。
};