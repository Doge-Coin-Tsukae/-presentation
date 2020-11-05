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

#include "selectpointer.h"

void CSelectpointer::Init()
{
	m_Position = D3DXVECTOR3(800.0f, 5.0f, 0.0f);

	m_point = new CPolygon;
	m_point->SetSize(300.0f, 150.0f);
	m_point->SetTexture((char*)"asset/texture/selectitem/cursor.png");
	m_point->Init(m_Position);

	Pointpos = D3DXVECTOR2(0.0f, 0.0f);
}

void CSelectpointer::Uninit()
{
	m_point->Uninit();
	delete m_point;
}

void CSelectpointer::Update()
{
	m_point->Update();

	
}

void CSelectpointer::Draw()
{
	m_point->Draw();
}