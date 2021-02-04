#pragma once
#include "gameobject.h"

enum SPOWNTYPE
{
	NONE_SPOWN,			//どちらの領地ではない
	FRIENDRY_SPOWN,		//友軍の領地
	ENEMY_SPOWN,			//敵の領地
};

class CSpownPoint : public CGameObject	//継承(インヘリタンス)
{
private:
	int			m_spowninterval = 1000;	//スポーン間隔
	int			m_time;			//現在の時刻
	int			m_Max;			//上限(-1の場合、無限沸き)
	int			m_SpownedNum;	//沸いた数
	bool		m_Spownlicense;	//沸くことを許可するか
	SPOWNTYPE	m_SpownType;	//敵味方識別
	CModel* m_Model;			//旗モデル

	void Spown();
	bool SpownConditions();		//スポーンの条件(trueの時、沸くように)
public:
	CSpownPoint() {}
	~CSpownPoint() {}

	//cerialでロードする項目
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(m_Position),
			CEREAL_NVP(m_Rotation),
			CEREAL_NVP(m_Scale),
			CEREAL_NVP(m_SpownType),
			CEREAL_NVP(m_Max),
			CEREAL_NVP(m_Spownlicense));
	}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	SPOWNTYPE GetTerritory() { return m_SpownType; }
	void	  SetSpowntype(SPOWNTYPE set) { m_SpownType = set; }
	void	  ChengeSpownlicense() { m_Spownlicense = 1 - m_Spownlicense; }		//許可設定の反転
};