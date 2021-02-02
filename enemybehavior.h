#pragma once

class CEnemyAIRoot :public CNode
{
private:
	CGameObject* parent;	//•t‘®‚·‚é“G
	int m_Index = m_Index;
public:
	void   Init();
	RESULT Update();

	void SetParent(CGameObject* parentenemy);
};

class CEnemySelector :public CNodeSelector
{
private:
	CGameObject* parent;	//•t‘®‚·‚é“G
public:
	CEnemySelector()
	{
		m_child_Node[0];
		m_child_Node[1];
	}

	void SetParent(CGameObject* parentenemy)
	{
		parent = parentenemy;
	}
};

class CEnemySequence :public CNodeSequence
{
private:
	CGameObject* parent;	//•t‘®‚·‚é“G
public:
	CEnemySequence()
	{
		m_child_Node[0];
		m_child_Node[1];
	}

	void SetParent(CGameObject* parentenemy)
	{
		parent = parentenemy;
	}
};