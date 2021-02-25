#pragma once

#include "gameobject.h"

//ポリゴン(画像を動かせない)
class CPolygon : public  CGameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;
	float m_len;		//縦の長さ
	float m_wid;		//横の長さ

public:
	void Init(D3DXVECTOR3 Pos);		//初期処理(画像を動かせないので、必ずここで座標の場所の指定を行うこと)
	void Uninit();
	void Update();
	void Draw();

	void SetTexture(char* name);									//テクスチャの読込
	void SetSize(float len, float wid) { m_len = len; m_wid=wid; }	//ポリゴンの大きさ指定(必ずInitの前に行うこと)
};

//ポリゴン(画像を動かせる) *更新処理に負荷がかかるので、動かす必要のない2Dポリゴンは上のクラスを使うこと
class CMovePolygon : public  CGameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;
	float m_len;		//縦の長さ
	float m_wid;		//横の長さ

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetTexture(char* name);										//テクスチャの読込
	void SetSize(float len, float wid) { m_len = len; m_wid = wid; }	//ポリゴンの大きさ指定
};