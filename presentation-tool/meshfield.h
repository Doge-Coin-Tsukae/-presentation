#pragma once

#include "gameobject.h"

#define FIELDX 300			//フィールドの横方向の大きさ
#define FIELDY 300			//フィールドの縦方向の大きさ

//メッシュフィールド
class CMeshField : public CGameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = nullptr;
	ID3D11Buffer*				m_IndexBuffer = nullptr;
	ID3D11ShaderResourceView*	m_Texture = nullptr;

	VERTEX_3D					m_Vertex[FIELDX][FIELDY];

	int seed;				//地形シード値
	int oldseed;			//ImGuiで地形シード値の健康を特定するのに使う

	//メンバ関数
	void Automaticallygenerated();		//自動生成処理
	void UpdateSeed();		//ImGuiで地形の再生成
	void SetImGui();
public:
	CMeshField() {}
	~CMeshField() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Save(FILE* fp);						//データのセーブ
	float GetHeight(D3DXVECTOR3 Position);		//座標の習得
};

//ダイアモンドスクエアの自動生成
class CDiamondSquare
{
private:
	void squareStep(float Array[FIELDX][FIELDY], int x, int z, int reach);		//スクエア
	void diamondStep(float Array[FIELDX][FIELDY], int x, int z, int reach);		//ダイアモンド
	float random(int range);													//メッシュフィールドの高さ指定
public:
	void diamondSquare(float Array[FIELDX][FIELDY], int size);					//ダイアモンドスクエア(使用するときはこれのみ呼ぶ)
};