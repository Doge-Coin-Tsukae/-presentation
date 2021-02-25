#include <direct.h>
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "polygon.h"

#include "gameobject.h"
#include "save.h"

#include "model.h"
#include "animationmodel.h"
#include "sight.h"
#include "colider.h"
#include "human.h"
#include "player.h"

#include "testplaybutton.h"

void CTestPlayButton::Init()
{
	m_Position = D3DXVECTOR3(800.0f, 340.0f, 0.0f);
	m_Size = D3DXVECTOR2(150.0f, 70.0f);

	m_polygon = new CMovePolygon;
	m_polygon->Init();
	m_polygon->SetTexture((char*)"asset/texture/testplay/testplay.png");
	m_polygon->SetSize(m_Size.y, m_Size.x);
	m_polygon->SetPosition(m_Position);
}
void CTestPlayButton::Uninit()
{
	m_polygon->Uninit();
	delete m_polygon;
}
void CTestPlayButton::Update()
{
	m_polygon->Update();
}
void CTestPlayButton::Draw()
{
	m_polygon->Draw();
}

bool CTestPlayButton::Colision(POINT pos)
{
	if (m_Position.x > pos.x)return false;
	if (m_Position.x + m_Size.x < pos.x)return false;
	if (m_Position.y > pos.y)return false;
	if (m_Position.y + m_Size.y < pos.y)return false;

	return true;
}


//関数宣言

void ClickTestBotton()
{
	//ステージにプレイヤーが設置されていなければ、エラーメッセージを表示
	CPlayer* pPlayer = CManager::GetScene()->GetGameObject<CPlayer>(1);
	if (pPlayer == nullptr)
	{
		MessageBox(GetWindow(), "プレイヤーが配置されていません", "テストプレイ失敗", MB_ICONERROR);
		return;
	}

	_mkdir("asset/testsavedata");	//テストセーブデータのフォルダを作成
	CManager::GetScene()->GetGameObject<CSAVE>(0)->TestData_Save();		//テストデータの保存
	system("TestPlay.exe");		//exe起動
}