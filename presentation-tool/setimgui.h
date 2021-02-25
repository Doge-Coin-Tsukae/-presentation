#pragma once

//���N���X
class CSetImGui
{
public:
	virtual void Update() {}
	virtual void SetImGui() = 0;		//�ݒu���[�h�̂ɕ\��������
	virtual void SetObject(D3DXVECTOR3 pos) = 0;		//object�̔z�u�X�|�[���|�W�V����
};

//�v���C���[��ݒu����Ƃ���ImGUI
class CSetPlayerImGui :public CSetImGui
{
private:
	int weapondata;							//����f�[�^
	int m_AnimationModeltype;				//ImGUI�Ŏg���A�j���[�V�������f��(list�Ŏg��)
	int m_AnimationModeltypeold;			//ImGUI�ŃA�j���[�V�������f�����ύX�ɂȂ��������ׂ�
	std::string m_Modelpass;				//���݂̃��f���̃p�X


public:
	CSetPlayerImGui()
	{
		weapondata = WEAPON_RIFLE;
		m_AnimationModeltype = 0;
		m_AnimationModeltypeold = 0;
		m_Modelpass = "asset/model/player/chara.fbx";
	}
	~CSetPlayerImGui()
	{

	}
	void Update();
	void SetImGui();
	void SetObject(D3DXVECTOR3 pos);
};

//NPC��ݒu����Ƃ���ImGUI
class CSetNPCImGui :public CSetImGui
{
private:
	bool isEnemy;							//�G��������
	int weapondata;							//����f�[�^


public:
	CSetNPCImGui()
	{
		isEnemy = false;
		weapondata = WEAPON_RIFLE;
	}
	~CSetNPCImGui()
	{

	}
	void Update();
	void SetImGui();
	void SetObject(D3DXVECTOR3 pos);
};

//���_��ݒu����Ƃ���ImGUI
class CSetBaseImGui :public CSetImGui
{
private:
	bool isEnemy;							//�G��������
	int weapondata;							//����f�[�^


public:
	CSetBaseImGui()
	{
		isEnemy = false;
		weapondata = WEAPON_RIFLE;
	}
	~CSetBaseImGui()
	{

	}
	void Update();
	void SetImGui();
	void SetObject(D3DXVECTOR3 pos);
};

//�؂�ݒu����Ƃ���ImGUI
class CSetTreeImGui :public CSetImGui
{
private:
	bool isEnemy;							//�G��������
	int weapondata;							//����f�[�^


public:
	CSetTreeImGui()
	{
		isEnemy = false;
		weapondata = WEAPON_RIFLE;
	}
	~CSetTreeImGui()
	{

	}
	void Update();
	void SetImGui();
	void SetObject(D3DXVECTOR3 pos);
};

//�͂�؂�ݒu����Ƃ���ImGUI
class CSetDeadTreeImGui :public CSetImGui
{
private:
	bool isEnemy;							//�G��������
	int weapondata;							//����f�[�^


public:
	CSetDeadTreeImGui()
	{
		isEnemy = false;
		weapondata = WEAPON_RIFLE;
	}
	~CSetDeadTreeImGui()
	{

	}
	void Update();
	void SetImGui();
	void SetObject(D3DXVECTOR3 pos);
};

//������ݒu����Ƃ���ImGUI
class CSeBunkerImGui :public CSetImGui
{
private:
	bool isEnemy;							//�G��������
	int weapondata;							//����f�[�^


public:
	CSeBunkerImGui()
	{
		isEnemy = false;
		weapondata = WEAPON_RIFLE;
	}
	~CSeBunkerImGui()
	{

	}
	void Update();
	void SetImGui();
	void SetObject(D3DXVECTOR3 pos);
};

//�X�|�[���|�C���g��ݒu����Ƃ���ImGUI
class CSetSpownPointImGui :public CSetImGui
{
private:
	bool isEnemy;							//�G��������
	int weapondata;							//����f�[�^


public:
	CSetSpownPointImGui()
	{
		isEnemy = false;
		weapondata = WEAPON_RIFLE;
	}
	~CSetSpownPointImGui()
	{

	}
	void Update();
	void SetImGui();
	void SetObject(D3DXVECTOR3 pos);
};
