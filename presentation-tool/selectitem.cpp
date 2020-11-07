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
#include "colider.h"
#include "bunker.h"
#include"selectpointer.h"

#include "selectitem.h"

void CSelectItem::Init()
{
	m_Position = D3DXVECTOR3(800.0f, 5.0f, 0.0f);

	m_under = new CPolygon;
	m_under->SetSize(300.0f,150.0f);
	m_under->SetTexture((char*)"asset/texture/selectitem/under2.png");
	m_under->Init(m_Position);

	m_pointer = new CSelectpointer;
	m_pointer->Init();

	//縦方向
	for (int h = 0; h < 4;h++)
	{
		//横方向
		for (int w = 0; w < 2; w++)
		{
			m_chip[h][w] = new CChip;
			m_chip[h][w]->Init();
			m_chip[h][w]->SetPosition(D3DXVECTOR3(m_Position.x+1 + 75 * w, m_Position.y+25+ 69 * h, 0.0f));
			m_chip[h][w]->SetPolygon((char*)"asset/texture/selectitem/chip2.png",
				D3DXVECTOR2(73.0f,68.0f),
				D3DXVECTOR2(0.5f*w, 0.25f*h), D3DXVECTOR2(0.5f + (0.5f * w), 0.25 + (0.25*h)));
		}
	}

	min = D3DXVECTOR2(0,0);
	max = D3DXVECTOR2(150.0f, 300.0f);
}

void CSelectItem::Uninit()
{
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

	//カーソル動かす
	if (CInput::GetKeyTrigger(VK_UP))	 m_pointer->move_up();
	if (CInput::GetKeyTrigger(VK_DOWN))  m_pointer->move_down();
	if (CInput::GetKeyTrigger(VK_LEFT))  m_pointer->move_left();
	if (CInput::GetKeyTrigger(VK_RIGHT)) m_pointer->move_right();

	//ボックスをクリックされた時の動き
	if (CInput::GetKeyPress(VK_LBUTTON))
	{
		POINT pos;
		GetCursorPos(&pos);		//現在のカーソルのポジション取得
		ScreenToClient(GetWindow(), &pos);

		//カーソルがボックスの範囲内だったら
		if (pos.x < m_Position.x + min.x)return;
		if (pos.x > m_Position.x + max.x)return;
		if (pos.y < m_Position.y + min.y)return;
		if (pos.y > m_Position.y + max.y)return;

		//SetDestroy();
		//チップの当たり判定
			//縦方向
		for (int h = 0; h < 4; h++)
		{
			//横方向
			for (int w = 0; w < 2; w++)
			{
				if (m_chip[h][w]->Colision(pos) == true)
				{
					CScene* scene = CManager::GetScene();
					scene->AddGameObject<CBUNKER>(1)->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
			}
		}
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
}