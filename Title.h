#pragma once

#include "scene.h"

class CTitle : public CScene
{
private:
	bool m_Clik;		//エンター押されたか

	void Update_InPut();		//入力情報を纏める
	void isFade();		//フェード中か
public:

	void Init();
	void Uninit();
	void Update();

};