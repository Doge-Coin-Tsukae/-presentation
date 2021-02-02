//=====================================
//
// 敵のビヘイビアAI
//  written by Y.Okubo
//
//=====================================
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "gameobject.h"

//#include "model.h"
//#include "animationmodel.h"
//#include "sight.h"
//#include "weapon.h"
//#include "player.h"
#include "behavior.h"
#include "enemybehavior.h"

void CEnemyAIRoot::Init()
{
	m_child_Node[0] = new CEnemySequence;
	m_child_Node[1] = new CEnemySelector;
}

RESULT CEnemyAIRoot::Update()
{
	if (parent == nullptr) return;

	//CScene* scene = CManager::GetScene();
	//CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	//プレイヤーから離れていたら移動
	//近かったら攻撃
	//死亡したら何も行わない

	RESULT ret = m_child_Node[m_Index]->Update();

	switch (ret)
	{
	case RESULT_PROGRESS:
		return RESULT_PROGRESS;
	case RESULT_SUCCEEDED:
		m_Index++;

	case RESULT_FAILED:
		m_Index--;
	}



}

void CEnemyAIRoot::SetParent(CGameObject* parentenemy)
{
	parent = parentenemy;
}