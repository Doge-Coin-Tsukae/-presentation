#pragma once

#include"gameobject.h"

class CLOAD : public CGameObject
{
	void Data_Destroy();	//ゲームオブジェクトの削除
public:
	void Uninit();			//終了処理
	void Update();			//更新処理
	void Data_Load();		//ファイルからデータをロードする
};