#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "input.h"
#include "polygon.h"
#include "chip.h"
#include "model.h"
#include "animationmodel.h"
#include "human.h"
#include "carsor.h"
#include "colider.h"
#include "camera.h"
#include "bunker.h"
#include "sight.h"
#include "player.h"
#include "enemy.h"
#include "friend.h"
#include "base.h"
#include "deadtree.h"
#include "tree.h"
#include "spownpoint.h"

#include "setimgui.h"

void CSetPlayerImGui::Update()
{
	if (m_AnimationModeltype == m_AnimationModeltypeold) return;

	switch (m_AnimationModeltype)
	{
	case 0:
		m_Modelpass = "asset/model/player/chara.fbx";
		break;
	case 1:
		m_Modelpass = "asset/model/player/chara2.fbx";
		break;
	};
	m_AnimationModeltypeold = m_AnimationModeltype;
}
void CSetPlayerImGui::SetObject(D3DXVECTOR3 pos)
{
	CPlayer* m_pPlayer = new CPlayer;
	m_pPlayer->Init();

	//ワールドに追加
	m_pPlayer->SetAnimationData(m_AnimationModeltype, m_Modelpass);
	m_pPlayer->Update();
	m_pPlayer->SetWeapondata(weapondata);
	m_pPlayer->SetPosition(pos);
	CManager::GetScene()->AddArgumentGameObject(m_pPlayer, 1);
}

void CSetPlayerImGui::SetImGui()
{
	//リストボックス用の文字データ
	const char* listbox_items[] = { "Rifle", "SMG" };
	const char* listbox_animodels[] = { "chara1","chara2" };

	ImGui::Text("Player");
	//ImGui::SliderFloat("rotation", &m_Rotation.y, 0, 10);
	//ImGui::SliderFloat("scale", &m_Scale.x, 0.1, 10);
	ImGui::ListBox("CharactorModel", &m_AnimationModeltype, listbox_animodels, IM_ARRAYSIZE(listbox_animodels), 1);
	ImGui::ListBox("Weapon", &weapondata, listbox_items, IM_ARRAYSIZE(listbox_items), 2);
}



void CSetNPCImGui::SetObject(D3DXVECTOR3 pos)
{
	if (isEnemy == true)
	{
		CEnemy* pEnemy = new CEnemy;
		pEnemy->Init();
		pEnemy->SetPosition(pos);
		CManager::GetScene()->AddArgumentGameObject(pEnemy, 1);
	}
	else
	{
		CFriend* pFriend = new CFriend;
		pFriend->Init();
		pFriend->SetPosition(pos);
		CManager::GetScene()->AddArgumentGameObject(pFriend, 1);
	}
}

void CSetNPCImGui::SetImGui()
{
	//リストボックス用の文字データ
	const char* listbox_items[] = { "Rifle", "SMG" };

	ImGui::Text("NPC");
	//ImGui::SliderFloat("rotation", &m_Rotation.y, 0, 10);
	ImGui::Checkbox("enemy", &isEnemy);
	ImGui::ListBox("weaponbox", &weapondata, listbox_items, IM_ARRAYSIZE(listbox_items), 2);
}

void CSetNPCImGui::Update()
{

}



void CSetBaseImGui::SetObject(D3DXVECTOR3 pos)
{
		CBase* pBase = new CBase;
		pBase->Init();
		pBase->SetPosition(pos);
		CManager::GetScene()->AddArgumentGameObject(pBase, 1);

}

void CSetBaseImGui::SetImGui()
{
	ImGui::Text("Base");
	//ImGui::SliderFloat("rotation", &m_Rotation.y, 0, 10);
}

void CSetBaseImGui::Update()
{

}



void CSetTreeImGui::SetObject(D3DXVECTOR3 pos)
{
		CTREE* pTree = new CTREE;
		pTree->Init();
		pTree->SetPosition(pos);
		CManager::GetScene()->AddArgumentGameObject(pTree, 1);
}

void CSetTreeImGui::SetImGui()
{
	ImGui::Text("Tree");
	//ImGui::SliderFloat("rotation", &m_Rotation.y, 0, 10);
}

void CSetTreeImGui::Update()
{

}



void CSetDeadTreeImGui::SetObject(D3DXVECTOR3 pos)
{

	CDEADTREE* pDeadTree = new CDEADTREE;
	pDeadTree->Init();
	pDeadTree->SetPosition(pos);
	CManager::GetScene()->AddArgumentGameObject(pDeadTree, 1);
}

void CSetDeadTreeImGui::SetImGui()
{
	ImGui::Text("DeadTree");
	//ImGui::SliderFloat("rotation", &m_Rotation.y, 0, 10);
}

void CSetDeadTreeImGui::Update()
{

}



void CSeBunkerImGui::SetObject(D3DXVECTOR3 pos)
{
		CBUNKER* pBunker = new CBUNKER;
		pBunker->Init();
		pBunker->SetPosition(pos);
		CManager::GetScene()->AddArgumentGameObject(pBunker, 1);
}

void CSeBunkerImGui::SetImGui()
{
	ImGui::Text("bunker");
	//ImGui::SliderFloat("rotation", &m_Rotation.y, 0, 10);
}

void CSeBunkerImGui::Update()
{
}



void CSetSpownPointImGui::SetObject(D3DXVECTOR3 pos)
{
	CSpownPoint* pSpownPoint = new CSpownPoint;
	pSpownPoint->Init();
	pSpownPoint->SetPosition(pos);
	CManager::GetScene()->AddArgumentGameObject(pSpownPoint, 1);

}

void CSetSpownPointImGui::SetImGui()
{
	ImGui::Text("SpownPoint");
	//ImGui::SliderFloat("rotation", &m_Rotation.y, 0, 10);
}

void CSetSpownPointImGui::Update()
{

}