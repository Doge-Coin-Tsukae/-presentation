#pragma once

#include "gameobject.h"

//拠点の占領後に表示する言葉
class CCAPTUREUI :public CGameObject
{
private:
	CPolygon *Line;

	int DeleteTime;			//オブジェクトが削除されるまでの時間
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

//拠点に侵入したときの占領ゲージ
class CCAPTUREGAUGE :public CGameObject
{
private:
	CGAUGE *m_Gauge;	//表示させる言葉
	CBASE *m_parent;	//親

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Setparent(CBASE* object) { m_parent = object; }		//親の設定
};