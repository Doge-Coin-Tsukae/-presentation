#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "polygon.h"
#include "modechip.h"

void CMODECHIP::Init()
{
	m_polygon = new CSplitPolygon;
	m_polygon->Init();
}
void CMODECHIP::Uninit()
{
	m_polygon->Uninit();
	delete m_polygon;
}
void CMODECHIP::Update()
{
	m_polygon->Update();
}
void CMODECHIP::Draw()
{
	D3DXVECTOR2 start(0,0);
	D3DXVECTOR2 end(1.0f,1.0f);
	if (m_SelectMode == true)
	{
		end.y = 0.5f;
		m_polygon->SetSplit(start, end);
		m_polygon->Draw();
	}
	else
	{
		start.y = 0.5f;
		m_polygon->SetSplit(start, end);
		m_polygon->Draw();
	}
}

void CMODECHIP::SetPolygon(char* name, D3DXVECTOR2 Size)
{
	m_Size = Size;

	m_polygon->SetSize(m_Size.y, m_Size.x);
	m_polygon->SetTexture(name);
	m_polygon->SetPosition(m_Position);
}

void CMODECHIP::SetMode()
{
	if (m_SelectMode == false)
	{
		m_SelectMode = true;

	}
	else
	{
		m_SelectMode = false;
	}


}

bool CMODECHIP::Colision(POINT pos)
{
	if (m_Position.x > pos.x)return false;
	if (m_Position.x + m_Size.x < pos.x)return false;
	if (m_Position.y > pos.y)return false;
	if (m_Position.y + m_Size.y < pos.y)return false;

	return true;
}