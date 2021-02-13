//=====================================
//
// ビヘイビアAI
//  written by Y.Okubo
//
//=====================================
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "behavior.h"

RESULT CNode::Update()
{
	m_child_Node[0]->Update();
	m_child_Node[1]->Update();

	return RESULT_PROGRESS;
}

RESULT CNodeSequence::Update()
{
	RESULT ret = m_child_Node[m_Index]->Update();

	switch (ret)
	{
	case RESULT_PROGRESS:
		return RESULT_PROGRESS;
	case RESULT_SUCCEEDED:
		m_Index++;
		if (m_Index > 1)
		{
			m_Index = 0;
			return RESULT_SUCCEEDED;
		}

	case RESULT_FAILED:
		return RESULT_FAILED;
	}
}

RESULT CNodeSelector::Update()
{
	RESULT ret = m_child_Node[m_Index]->Update();

	switch (ret)
	{
	case RESULT_PROGRESS:
		return RESULT_PROGRESS;
	case RESULT_SUCCEEDED:
			return RESULT_SUCCEEDED;

	case RESULT_FAILED:
		return RESULT_FAILED;
	}
}