#pragma once

//基底クラス
class CSetImGui
{
public:
	virtual void Update() {}
	virtual void SetImGui() = 0;		//設置モードのに表示を入れる
	virtual void SetObject(D3DXVECTOR3 pos) = 0;		//objectの配置スポーンポジション
};

//プレイヤーを設置するときのImGUI
class CSetPlayerImGui :public CSetImGui
{
private:
	int weapondata;							//武器データ
	int m_AnimationModeltype;				//ImGUIで使うアニメーションモデル(listで使う)
	int m_AnimationModeltypeold;			//ImGUIでアニメーションモデルが変更になったか調べる
	std::string m_Modelpass;				//現在のモデルのパス


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

//NPCを設置するときのImGUI
class CSetNPCImGui :public CSetImGui
{
private:
	bool isEnemy;							//敵か味方か
	int weapondata;							//武器データ


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

//拠点を設置するときのImGUI
class CSetBaseImGui :public CSetImGui
{
private:
	bool isEnemy;							//敵か味方か
	int weapondata;							//武器データ


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

//木を設置するときのImGUI
class CSetTreeImGui :public CSetImGui
{
private:
	bool isEnemy;							//敵か味方か
	int weapondata;							//武器データ


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

//枯れ木を設置するときのImGUI
class CSetDeadTreeImGui :public CSetImGui
{
private:
	bool isEnemy;							//敵か味方か
	int weapondata;							//武器データ


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

//建物を設置するときのImGUI
class CSeBunkerImGui :public CSetImGui
{
private:
	bool isEnemy;							//敵か味方か
	int weapondata;							//武器データ


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

//スポーンポイントを設置するときのImGUI
class CSetSpownPointImGui :public CSetImGui
{
private:
	bool isEnemy;							//敵か味方か
	int weapondata;							//武器データ


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
