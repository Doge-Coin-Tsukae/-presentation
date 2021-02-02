#pragma once

enum RESULT
{
	RESULT_PROGRESS,
	RESULT_SUCCEEDED,
	RESULT_FAILED
};
class  CNode
{
protected:
	CNode* m_child_Node[2];
public:
	virtual  RESULT Update();
};

//シークエンス
class CNodeSequence :public  CNode
{
	int m_Index;
	RESULT Update();
};

//セレクター
class CNodeSelector :public CNode
{
	int m_Index;
	RESULT Update();
};