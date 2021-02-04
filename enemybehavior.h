#pragma once

#include "gameobject.h"
#include "enemy.h"

class CEnemyAIRoot :public CNode
{
private:
	CEnemy* parent;	//•t‘®‚·‚é“G
	int m_Index = m_Index;
public:
	void   Init(CEnemy* parent);
	RESULT Update();
};

class CEnemySelector :public CNodeSelector
{
private:
	CEnemy* m_parent;	//•t‘®‚·‚é“G
public:
	CEnemySelector(CEnemy* parent);
	RESULT Update();
};

class CEnemySequence :public CNodeSequence
{
private:
	CEnemy* m_parent;	//•t‘®‚·‚é“G
public:
	CEnemySequence(CEnemy* parent);
};


class CEnemyRunNode :public CNode
{
private:
	CEnemy* m_parent;	//•t‘®‚·‚é“G
public:
	CEnemyRunNode(CEnemy* parent);
	RESULT Update();
};

class CEnemyWalkNode :public CNode
{
private:
	CEnemy* m_parent;	//•t‘®‚·‚é“G
public:
	CEnemyWalkNode(CEnemy* parent);
	RESULT Update();
};

class CEnemyShootNode :public CNode
{
private:
	CEnemy* m_parent;	//•t‘®‚·‚é“G
public:
	CEnemyShootNode(CEnemy* parent);
	RESULT Update();
};

class CEnemyReloadNode :public CNode
{
private:
	CEnemy* m_parent;	//•t‘®‚·‚é“G
public:
	CEnemyReloadNode(CEnemy* parent);
	RESULT Update();
};