//=====================================
//
//  �x�N�g�����g���֐�
//  written by Y.Okubo
//
//=====================================
#include "main.h"
#include "Vector.h"

//�P�ʃx�N�g�����擾����
D3DXVECTOR3 GetNorm(D3DXVECTOR3 start, D3DXVECTOR3 end)
{
	D3DXVECTOR3 Vector;

	D3DXVECTOR3 xyz = start - end;

	//�x�N�g�������
	double l = sqrt((xyz.x*xyz.x) + (xyz.y*xyz.y) + (xyz.z*xyz.z));

	//�P�ʃx�N�g�������
	Vector = -(xyz / l);

	return Vector;
}

//�������Ƃ�
float GetVector(D3DXVECTOR3 start, D3DXVECTOR3 end)
{
	D3DXVECTOR3 xyz = start - end;

	//�x�N�g�������
	float l = sqrt((xyz.x * xyz.x) + (xyz.y * xyz.y) + (xyz.z * xyz.z));

	return l;
}

// �ǂ���x�N�g��
//
// out : ���K���ǂ���x�N�g���i�߂�l�j
// front : �i�s�x�N�g��
// normal: �Փ˓_�ł̖@���x�N�g��
D3DXVECTOR3* calcWallScratchVector(D3DXVECTOR3* out, const D3DXVECTOR3& front, const D3DXVECTOR3& normal) {
	D3DXVECTOR3 normal_n;
	D3DXVec3Normalize(&normal_n, &normal);
	D3DXVECTOR3 pV = (front - D3DXVec3Dot(&front, &normal_n) * normal_n);
	out = D3DXVec3Normalize(out, &pV);
	return out;
}
