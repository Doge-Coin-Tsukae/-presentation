#pragma once

#include "scene.h"

class CGame : public CScene
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	//draw‚Í‰½‚à‘‚©‚È‚¢ê‡AScene‚©‚çŒÄ‚Ño‚³‚ê‚éB
};