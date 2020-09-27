//****************************************
//敵
//****************************************

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "scene.h"

#include "human.h"
#include "Vector.h"
#include "model.h"
#include "animationmodel.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "player.h"
#include "enemy.h"

class CModel* CEnemy::m_Model;

void CEnemy::Load()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\plauyer1.obj");
}

void CEnemy::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void CEnemy::Init()
{
	m_Sight = new CSIGHT();
	m_Sight->Init();
	m_Sight->Setparent(this);		//照準の親を自分に

	m_Weapon = new CWEAPON();
	m_Weapon->Init();
	m_Weapon->Setparent(this);

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.3f, 1.3f, 1.3f);
	m_TeamNumber = TEAM_ENEMY;		//チーム設定
}

void CEnemy::Uninit()
{
	m_Weapon->Uninit();
	delete m_Weapon;

	m_Sight->Uninit();
	delete m_Sight;
}

void CEnemy::Update()
{
	//ヘルパー関数
	Update_AI();
	//プレイヤーに入っているクラスの更新処理
	m_Sight->Update();
	m_Weapon->Update();

}

void CEnemy::Update_AI()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	//当たり判定
	D3DXVECTOR3 direction = m_Position - pPlayer->GetPosition();
	float length = D3DXVec3Length(&direction);

	LookPlayer();

	//範囲内になったら接近する
	if (length < 100.0f)
	{
		if (length > 20.0f)
		{
			D3DXVECTOR3 Velocity = GetVector(m_Position, pPlayer->GetPosition());
			m_Position += Velocity / 10;
		}
		else
		{
			m_Weapon->Shoot(m_Sight->GetPosition(), m_TeamNumber);
		}
	}

	if (m_Weapon->GetAmmo() <= 0)
	{
		m_Weapon->Reload();
	}
}

void CEnemy::Draw()
{
	//内部クラスから
	m_Weapon->Draw();
	m_Sight->Draw();

	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	//拡大縮小のマトリクス
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//ヨーピッチロールのマトリクス
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	//位置マトリクス
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	CRenderer::SetWorldMatrix(&world);

	m_Model->Draw();
}

void CEnemy::LookPlayer()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	D3DXVECTOR3 Velocity = GetVector(m_Position, pPlayer->GetPosition());
	D3DXVECTOR3 Velocity2 = GetVector(m_Position,m_Sight->GetPosition());
	m_Rotation.x += (Velocity.x * Velocity2.x+ Velocity.z*Velocity2.z) / (sqrt((Velocity.x*Velocity.x) + (Velocity.z*Velocity.z))*sqrt((Velocity2.x*Velocity2.x) + (Velocity2.z*Velocity2.z)));
	m_Rotation.x -= 1.0f;
}