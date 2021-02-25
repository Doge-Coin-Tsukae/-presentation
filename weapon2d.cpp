//========================================
//
//  現在所持している武器の情報の表示を行う
//  written by Y.Okubo
//
//========================================
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "human.h"

#include "polygon.h"
#include "gauge.h"
#include "number.h"
#include "model.h"
#include "animationmodel.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "player.h"
#include "weapon2d.h"

void CWEAPON2D::Init()
{
	m_Under = new CPolygon;
	m_Under->SetSize(100,200);
	m_Under->Init(D3DXVECTOR3(0.0f, 380.0f, 0.0f));
	m_Under->SetTexture((char*)"asset/texture/weapon/rifle.png");

	m_slash = new CPolygon;
	m_slash->SetSize(100,100);
	m_slash->Init(D3DXVECTOR3(100.0f, 480.0f, 0.0f));
	m_slash->SetTexture((char*)"asset/texture/weapon/rifle.png");

	for (int i = 0; i < 2; i++)
	{
		m_MaxAnmo[i] = new CNUMBER;
		m_MaxAnmo[i]->Init();

		m_Anmo[i] = new CNUMBER;
		m_Anmo[i]->Init();

		m_MaxAnmo[i]->SetPosition(D3DXVECTOR3(150.0f - i * 30, 480.0f, 0.0f));
		m_Anmo[i]->SetPosition(D3DXVECTOR3(50.0f - i * 30, 480.0f, 0.0f));

		m_MaxAnmo[i]->SetLength(50.0f);
		m_Anmo[i]->SetLength(50.0f);

	}

	m_Gauge = new CGAUGE;
	m_Gauge->Init();
	m_Gauge->SetPosition(D3DXVECTOR3(0.0f,530.0f,0.0f));



	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);
	ChengeWeaponTexture(pPlayer->GetWeapontype());
}

void CWEAPON2D::Uninit()
{
	m_Gauge->Uninit();
	delete m_Gauge;

	for (int i = 0; i < 2; i++)
	{
		m_Anmo[i]->Uninit();
		m_MaxAnmo[i]->Uninit();
		delete m_Anmo[i];
		delete m_MaxAnmo[i];
	}
	
	m_slash->Uninit();
	delete m_slash;

	m_Under->Uninit();
	delete m_Under;
}

void CWEAPON2D::Update()
{
	m_Under->Update();
	m_slash->Update();

	Advance();

	//値のセット
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);
	CWEAPON* pWeapon = pPlayer->GetWeapon();

	int MaxGauge = 200 - pWeapon->GetReloadTime();
	m_Gauge->SetGauge(MaxGauge);
	m_Gauge->Update();

	
}

void CWEAPON2D::Draw()
{
	LIGHT light;
	light.Enable = false;
	CRenderer::SetLight(light);

	m_Under->Draw();

	for (int i = 0; i < 2; i++)
	{
		m_MaxAnmo[i]->Draw();
		m_Anmo[i]->Draw();
	}
	m_slash->Draw();
	m_Gauge->Draw();
}

void CWEAPON2D::ChengeWeaponTexture(int id)
{
	switch (id)
	{
	case 0:
		m_Under->SetTexture((char*)"asset/texture/weapon/rifle.png");
		return;
	case 1:
		m_Under->SetTexture((char*)"asset/texture/weapon/smg.png");
		return;
	}
}

void CWEAPON2D::Advance()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);
	CWEAPON* pWeapon = pPlayer->GetWeapon();

	int maxAnmo_1stline = pWeapon->GetMaxAmmo() %10;	//一桁目
	int Anmo_1stline = pWeapon->GetAmmo() % 10;		//一桁目



	//一桁目
	m_MaxAnmo[0]->SetNumber(maxAnmo_1stline);
	m_Anmo[0]->SetNumber(Anmo_1stline);

	//二桁目
	m_MaxAnmo[1]->SetNumber(pWeapon->GetMaxAmmo() /10);
	m_Anmo[1]->SetNumber(pWeapon->GetAmmo() /10);
}