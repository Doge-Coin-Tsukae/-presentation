#pragma once

#include "scene.h"

class CTitle : public CScene
{
private:
	bool m_Clik;		//エンター押されたか
public:

	void Init();
	void Update();

};