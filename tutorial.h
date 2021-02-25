#pragma once

#include "scene.h"

class CTutorial : public CScene
{
private:
	CGAME_MANEGER* m_GameManeger;	//ゲームのルールのクラス
	bool m_Clik;					//スペースキーが押されたか

public:
	void Init();
	void Uninit();
	void Update();
	//drawは何も書かない場合、Sceneから呼び出される。
};