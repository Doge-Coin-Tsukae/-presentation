#pragma once

#include "gameobject.h"

//------------------------------------------------------
//
//	���[�h�ؑւ��s���`�b�v
//
//------------------------------------------------------

class CMODECHIP :public CGameObject
{
private:
	int id;						//�I�u�W�F�N�g�̎��
	bool m_SelectMode;			//���݂��̃��[�h���ǂ���
	CSplitPolygon *m_polygon;	//
	D3DXVECTOR2 m_Size;			//

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool Colision(POINT pos);
	void SetMode();
	void SetPolygon(char* name, D3DXVECTOR2 Size);
	void Setid(int ids) { id = ids; }

	int GetId() { return id; }
	bool GetSelectMode() { return m_SelectMode; }
};