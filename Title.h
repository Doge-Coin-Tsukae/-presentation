#pragma once

#include "scene.h"

class CTitle : public CScene
{
private:
	bool m_Clik;		//�G���^�[�����ꂽ��

	void Update_InPut();		//���͏���Z�߂�
	void isFade();		//�t�F�[�h����
public:

	void Init();
	void Uninit();
	void Update();

};