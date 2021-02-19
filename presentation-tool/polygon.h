#pragma once

#include "gameobject.h"

//------------------------------------------------------
//
//	2Dポリゴンクラス
//
//------------------------------------------------------

//ポリゴン(画像は動かない)
class CPolygon : public  CGameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;
	float m_len;		//縦の長さ
	float m_wid;		//横の長さ

public:
	void Init(D3DXVECTOR3 Pos);
	void Uninit();
	void Update();
	void Draw();

	void SetTexture(char* name);
	void SetSize(float len, float wid) { m_len = len; m_wid=wid; }
};

//ポリゴン(画像が動かせる)
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

	void SetTexture(char* name);
	void SetSize(float len, float wid) { m_len = len; m_wid = wid; }
};

//ポリゴン(画像を分割できる)
class CSplitPolygon : public  CGameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;
	float m_len;		//縦の長さ
	float m_wid;		//横の長さ

	D3DXVECTOR2 m_StartTexcoord;	//分割位置(始まり)
	D3DXVECTOR2 m_EndTexcoord;		//分割位置(終わり)

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetTexture(char* name);
	void SetSize(float len, float wid) { m_len = len; m_wid = wid; }
	void SetSplit(D3DXVECTOR2 SetStartTexcoord, D3DXVECTOR2 SetEndTexcoord) {
		m_StartTexcoord = SetStartTexcoord, m_EndTexcoord = SetEndTexcoord;}
};