//=====================================
//
//  ベクトルを使う関数
//  written by Y.Okubo
//
//=====================================
#include "main.h"
#include "Vector.h"

//単位ベクトルを取得する
D3DXVECTOR3 GetNorm(D3DXVECTOR3 start, D3DXVECTOR3 end)
{
	D3DXVECTOR3 Vector;

	D3DXVECTOR3 xyz = start - end;

	//ベクトルを取る
	double l = sqrt((xyz.x*xyz.x) + (xyz.y*xyz.y) + (xyz.z*xyz.z));

	//単位ベクトルを取る
	Vector = -(xyz / l);

	return Vector;
}

//距離をとる
float GetVector(D3DXVECTOR3 start, D3DXVECTOR3 end)
{
	D3DXVECTOR3 xyz = start - end;

	//ベクトルを取る
	float l = sqrt((xyz.x * xyz.x) + (xyz.y * xyz.y) + (xyz.z * xyz.z));

	return l;
}

// 壁ずりベクトル
//
// out : 正規化壁ずりベクトル（戻り値）
// front : 進行ベクトル
// normal: 衝突点での法線ベクトル
D3DXVECTOR3* calcWallScratchVector(D3DXVECTOR3* out, const D3DXVECTOR3& front, const D3DXVECTOR3& normal) {
	D3DXVECTOR3 normal_n;
	D3DXVec3Normalize(&normal_n, &normal);
	D3DXVECTOR3 pV = (front - D3DXVec3Dot(&front, &normal_n) * normal_n);
	out = D3DXVec3Normalize(out, &pV);
	return out;
}
