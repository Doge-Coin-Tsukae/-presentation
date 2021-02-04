//=====================================
//
// “G‚ÌƒrƒwƒCƒrƒAAI
//  written by Y.Okubo
//
//=====================================
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "gameobject.h"
#include "Vector.h"

#include "model.h"
#include "human.h"
#include "colider.h"
#include "animationmodel.h"
#include "sight.h"
#include "weapon.h"
#include "player.h"
#include "behavior.h"
#include "enemybehavior.h"

void CEnemyAIRoot::Init(CEnemy* parent)
{
	m_child_Node[0] = new CEnemySequence(parent);
	m_child_Node[1] = new CEnemySelector(parent);
}

RESULT CEnemyAIRoot::Update()
{
	if (parent == nullptr) return RESULT_FAILED;

	//ƒvƒŒƒCƒ„[‚©‚ç—£‚ê‚Ä‚¢‚½‚çˆÚ“®
	//‹ß‚©‚Á‚½‚çUŒ‚
	//Ž€–S‚µ‚½‚ç‰½‚às‚í‚È‚¢

	RESULT ret = m_child_Node[m_Index]->Update();

	switch (ret)
	{
	case RESULT_PROGRESS:
		return RESULT_PROGRESS;
	case RESULT_SUCCEEDED:
		if (m_Index == 0) m_Index = 1;
		return RESULT_SUCCEEDED;
	case RESULT_FAILED:
		return RESULT_FAILED;
	}
}


CEnemySelector::CEnemySelector(CEnemy* parent)
{
	m_parent = parent;
	m_child_Node[0] = new CEnemyShootNode(m_parent);
	m_child_Node[1] = new CEnemyReloadNode(m_parent);
}

RESULT CEnemySelector::Update()
{
	RESULT ret = m_child_Node[m_Index]->Update();

	switch (ret)
	{
	case RESULT_PROGRESS:
		return RESULT_PROGRESS;
	case RESULT_SUCCEEDED:
		m_Index--;
		return RESULT_SUCCEEDED;

	case RESULT_FAILED:
		if (m_parent->isOverReload() == false)
		{
			m_Index++;
			return RESULT_PROGRESS;
		}
		return RESULT_FAILED;
	}
}

CEnemySequence::CEnemySequence(CEnemy* parent)
{
	m_parent = parent;
	m_child_Node[0] = new CEnemyRunNode(m_parent);
	m_child_Node[1] = new CEnemyWalkNode(m_parent);
}

CEnemyRunNode::CEnemyRunNode(CEnemy* parent)
{
	m_parent = parent;
}

RESULT CEnemyRunNode::Update()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	//‹——£‚ð}‚é
	D3DXVECTOR3 direction = m_parent->GetPosition() - pPlayer->GetPosition();
	float length = D3DXVec3Length(&direction);

	if (length > 50.0f) return RESULT_SUCCEEDED;

	D3DXVECTOR3 Velocity = GetNorm(m_parent->GetPosition(), pPlayer->GetPosition());
	D3DXVECTOR3 Position = m_parent->GetPosition() + Velocity / 10;

	m_parent->SetPosition(Position);

	return RESULT_PROGRESS;
}

CEnemyWalkNode::CEnemyWalkNode(CEnemy* parent)
{
	m_parent = parent;
}

RESULT CEnemyWalkNode::Update()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	D3DXVECTOR3 Velocity = GetNorm(m_parent->GetPosition(), pPlayer->GetPosition());
	D3DXVECTOR3 Position = m_parent->GetPosition() + Velocity / 15;

	m_parent->SetPosition(Position);


	//“–‚½‚è”»’è
	D3DXVECTOR3 direction = m_parent->GetPosition() - pPlayer->GetPosition();
	float length = D3DXVec3Length(&direction);
	if (length > 30.0f) return RESULT_SUCCEEDED;

	return RESULT_PROGRESS;
}

CEnemyShootNode::CEnemyShootNode(CEnemy* parent)
{
	m_parent = parent;
}

RESULT CEnemyShootNode::Update()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	//“–‚½‚è”»’è
	D3DXVECTOR3 direction = m_parent->GetPosition() - pPlayer->GetPosition();
	float length = D3DXVec3Length(&direction);

	if (length > 60.0f) return RESULT_FAILED;					//ƒƒbƒNƒIƒ“‚µ‚Ä‚¢‚½ƒLƒƒƒ‰‚ª”ÍˆÍŠO‚É“¦‚°‚½‚ç
	if (m_parent->Shoot() == false) return RESULT_FAILED;		//’eØ‚ê‚¾‚Á‚½‚ç

	return RESULT_PROGRESS;
}

CEnemyReloadNode::CEnemyReloadNode(CEnemy* parent)
{
	m_parent = parent;
}

RESULT CEnemyReloadNode::Update()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	//“–‚½‚è”»’è
	D3DXVECTOR3 direction = m_parent->GetPosition() - pPlayer->GetPosition();
	float length = D3DXVec3Length(&direction);

	if (m_parent->isOverReload() == true) return RESULT_SUCCEEDED;

	m_parent->Reload();

	return RESULT_PROGRESS;
}