#pragma once

#include"gameobject.h"

class CLOAD : public CGameObject
{
private:
	std::string assetpass;

	template<typename T>
	void GameObjectLoad(T* savedata, std::string fullname, std::string data);		//単数のオブジェクトをロードする
	template<typename T>
	void GameObjectsLoad(T* savedata, std::string fullname, std::string data, std::string total);	//複数のオブジェクトをロードする
public:
	void Uninit();			//終了処理
	void Update();			//更新処理
	void Data_Load();		//ファイルからデータをロードする
	void Data_Destroy();	//ゲームオブジェクトの削除
	TCHAR* PassAsset(TCHAR path[300]);		//フルパスから実行ファイルの中にあるAssetフォルダからのパスに変更
};