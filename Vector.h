#pragma once
//********************************************************************************
//プロトタイプ宣言
//********************************************************************************
D3DXVECTOR3 GetNorm(D3DXVECTOR3 start, D3DXVECTOR3 end);

float GetVector(D3DXVECTOR3 start, D3DXVECTOR3 end);

D3DXVECTOR3* calcWallScratchVector(D3DXVECTOR3* out, const D3DXVECTOR3& front, const D3DXVECTOR3& normal);