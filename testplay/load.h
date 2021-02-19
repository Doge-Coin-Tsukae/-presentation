#pragma once

#include"gameobject.h"

class CLOAD : public CGameObject
{
	void Data_Destroy();	//ゲームオブジェクトの削除

	template<typename T>
	void GameObjectLoad(T* savedata, std::string fullname, std::string data);		//単数のオブジェクトをロードする
	template<typename T>
	void GameObjectsLoad(T* savedata, std::string fullname, std::string data, std::string total,int layer);	//複数のオブジェクトをロードする
public:
	void Uninit();			//終了処理
	void Update();			//更新処理
	void Data_Load();		//ファイルからデータをロードする
};