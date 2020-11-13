//---------------------------------
//
//画面右にオブジェクト一覧を作る
//
//---------------------------------

#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"

#include "input.h"
#include "scene.h"
#include "polygon.h"
#include "chip.h"
#include "model.h"
#include "human.h"
#include "carsor.h"
#include "colider.h"
#include "bunker.h"
#include "sight.h"
#include "weapon.h"
#include "player.h"
#include "enemy.h"
#include "base.h"
#include "deadtree.h"
#include "tree.h"

#include"selectpointer.h"
#include"modechip.h"

#include "selectitem.h"

void CSelectItem::Init()
{
	m_Position = D3DXVECTOR3(800.0f, 40.0f, 0.0f);

	m_under = new CPolygon;
	m_under->SetSize(300.0f,150.0f);
	m_under->SetTexture((char*)"asset/texture/selectitem/under2.png");
	m_under->Init(m_Position);

	m_pointer = new CSelectpointer;
	m_pointer->Init();
	m_pointer->SetPosition(m_Position = D3DXVECTOR3(m_Position.x+ 3.0f, m_Position.y+ 28.0f, 0.0f));

	//縦方向
	for (int h = 0; h < 4;h++)
	{
		//横方向
		for (int w = 0; w < 2; w++)
		{
			m_chip[h][w] = new CChip;
			m_chip[h][w]->Init();
			m_chip[h][w]->SetPosition(D3DXVECTOR3(m_Position.x -2 + 75 * w, m_Position.y - 2 + 69 * h, 0.0f));
			m_chip[h][w]->SetPolygon((char*)"asset/texture/selectitem/chip2.png",
				D3DXVECTOR2(73.0f,68.0f),
				D3DXVECTOR2(0.5f*w, 0.25f*h), D3DXVECTOR2(0.5f + (0.5f * w), 0.25 + (0.25*h)));

			m_chip[h][w]->Setid((h*2)+ w);
		}
	}

	//モードチップの数分ループ
	for (int h = 0; h < 2; h++)
	{
		m_modechip[h] = new CMODECHIP;
		m_modechip[h]->Init();
		m_modechip[h]->SetPosition(D3DXVECTOR3(m_Position.x-2 + 78 * h, m_Position.y -53, 0.0f));
		m_modechip[h]->SetPolygon((char*)"asset/texture/selectitem/button-mode-edit.png",
			D3DXVECTOR2(70.0f, 25.0f));
		m_modechip[h]->Setid(h);
	}

	m_carsor = new CCARSOR;
	m_carsor->Init();

	min = D3DXVECTOR2(0,0);
	max = D3DXVECTOR2(150.0f, 300.0f);
}

void CSelectItem::Uninit()
{
	m_carsor->Uninit();
	delete m_carsor;

	for (int h = 0; h < 2; h++)
	{
		m_modechip[h]->Uninit();
		delete m_modechip[h];
	}

	//縦方向
	for (int h = 0; h < 4; h++)
	{
		//横方向
		for (int w = 0; w < 2; w++)
		{
			m_chip[h][w]->Uninit();
			delete m_chip[h][w];
		}
	}

	m_pointer->Uninit();
	delete m_pointer;
	m_under->Uninit();
	delete m_under;
}

void CSelectItem::Update()
{

	//m_Rotation.z = min(m_Rotation.z, 0.0f);
	//m_Rotation.z = max(m_Rotation.z, -0.5f);
	//m_Rotation.z = min(m_Rotation.z, 0.0f);
	//m_Rotation.z = max(m_Rotation.z, -0.5f);

	m_under->Update();
	m_pointer->Update();
	//縦方向
	for (int h = 0; h < 4; h++)
	{
		//横方向
		for (int w = 0; w < 2; w++)
		{
			m_chip[h][w]->Update();
		}
	}

	for (int h = 0; h < 2; h++)
	{
		m_modechip[h]->Update();
	}

	m_carsor->Update();

	//カーソル動かす
	if (CInput::GetKeyTrigger(VK_UP))	 m_pointer->move_up();
	if (CInput::GetKeyTrigger(VK_DOWN))  m_pointer->move_down();
	if (CInput::GetKeyTrigger(VK_LEFT))  m_pointer->move_left();
	if (CInput::GetKeyTrigger(VK_RIGHT)) m_pointer->move_right();

	//右クリックした時の動き
	if (CInput::GetKeyTrigger(VK_LBUTTON))
	{
		//アイテムボックスをクリックしてなかったらワールドにオブジェクト配置
		if(ClickItemBox()==false) WorldObject();
	}
}

void CSelectItem::Draw()
{
	m_under->Draw();
	m_pointer->Draw();

	//縦方向
	for (int h = 0; h < 4; h++)
	{
		//横方向
		for (int w = 0; w < 2; w++)
		{
			m_chip[h][w]->Draw();
		}
	}

	for (int h = 0; h < 2; h++)
	{
		m_modechip[h]->Draw();
	}

	m_carsor->Draw();
}

bool CSelectItem::ClickItemBox()
{
	POINT pos;
	GetCursorPos(&pos);		//現在のカーソルのポジション取得
	ScreenToClient(GetWindow(), &pos);

	//カーソルがボックスの範囲外だったらループ抜ける
	if (pos.x < m_Position.x + min.x)return false;
	if (pos.x > m_Position.x + max.x)return false;
	if (pos.y < m_Position.y + min.y)return false;
	if (pos.y > m_Position.y + max.y)return false;

	//チップの当たり判定
		//縦方向
	for (int h = 0; h < 4; h++)
	{
		//横方向
		for (int w = 0; w < 2; w++)
		{
			if (m_chip[h][w]->Colision(pos) == true)
			{
				m_pointer->SetPos(D3DXVECTOR2(w,h));	//ポインターの位置をカーソルがさしたところに
				return true;
			}
		}
	}

	return false;
}

void CSelectItem::WorldObject()
{
	CScene* scene = CManager::GetScene();

	switch (m_chip[(int)m_pointer->GetPos().y][(int)m_pointer->GetPos().x]->GetId())
	{
	case 0:
		scene->AddGameObject<CPlayer>(1)->SetPosition(m_carsor->GetPosition());
		break;
	case 1:
		scene->AddGameObject<CEnemy>(1)->SetPosition(m_carsor->GetPosition());
		break;
	case 2:
		scene->AddGameObject<CBASE>(1)->SetPosition(m_carsor->GetPosition());
		break;
	case 3:
		scene->AddGameObject<CDEADTREE>(1)->SetPosition(m_carsor->GetPosition());
		break;
	case 4:
		scene->AddGameObject<CTREE>(1)->SetPosition(m_carsor->GetPosition());
		break;
	case 5:
		scene->AddGameObject<CBUNKER>(1)->SetPosition(m_carsor->GetPosition());
		break;
	default:
		scene->AddGameObject<CPlayer>(1)->SetPosition(m_carsor->GetPosition());
		break;
	}
}