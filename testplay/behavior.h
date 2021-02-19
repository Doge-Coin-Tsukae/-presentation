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

//�V�[�N�G���X
class CNodeSequence :public  CNode
{
protected:
	int m_Index;
	virtual RESULT Update();
};

//�Z���N�^�[
class CNodeSelector :public CNode
{
protected:
	int m_Index;
	virtual RESULT Update();

};