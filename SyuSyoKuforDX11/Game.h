#pragma once

#include "scene.h"

class CGame : public CScene
{
private:
	CGAME_MANEGER* m_GameManeger;
public:
	void Init();
	void Uninit();
	void Update();
	//drawは何も書かない場合、Sceneから呼び出される。
};