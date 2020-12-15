#pragma once

#include "gameobject.h"

#define FIELDX 300			//�t�B�[���h�̉������̑傫��
#define FIELDY 300			//�t�B�[���h�̏c�����̑傫��

//���b�V���t�B�[���h
class CMeshField : public CGameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = nullptr;
	ID3D11Buffer*				m_IndexBuffer = nullptr;
	ID3D11ShaderResourceView*	m_Texture = nullptr;

	VERTEX_3D					m_Vertex[FIELDX][FIELDY];

	int seed;				//�n�`�V�[�h�l
	int oldseed;			//ImGui�Œn�`�V�[�h�l�̌��N����肷��̂Ɏg��

	//�����o�֐�
	void Automaticallygenerated();		//������������
	void UpdateSeed();		//ImGui�Œn�`�̍Đ���
	void SetImGui();
public:
	CMeshField() {}
	~CMeshField() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Save(FILE* fp);						//�f�[�^�̃Z�[�u
	float GetHeight(D3DXVECTOR3 Position);		//���W�̏K��
};

//�_�C�A�����h�X�N�G�A�̎�������
class CDiamondSquare
{
private:
	void squareStep(float Array[FIELDX][FIELDY], int x, int z, int reach);		//�X�N�G�A
	void diamondStep(float Array[FIELDX][FIELDY], int x, int z, int reach);		//�_�C�A�����h
	float random(int range);													//���b�V���t�B�[���h�̍����w��
public:
	void diamondSquare(float Array[FIELDX][FIELDY], int size);					//�_�C�A�����h�X�N�G�A(�g�p����Ƃ��͂���̂݌Ă�)
};