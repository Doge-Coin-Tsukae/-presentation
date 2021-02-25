//=====================================
//
//  キャラクターが発射する弾
//  written by Y.Okubo
//
//=====================================
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "Vector.h"
#include "sound.h"
#include "model.h"
#include "camera.h"
#include "explosion.h"
#include "human.h"
#include "animationmodel.h"
#include "behavior.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "enemy.h"
#include "friend.h"
#include "player.h"
#include "bullet.h"
#include "bunker.h"
class CModel* CBullet::m_Model;

void CBullet::Load()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\bullet.obj");
}

void CBullet::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void CBullet::Init()
{
	DeleteTime = 8.0f;
	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_Colision = new CCOLIDER_CIRCLE();
	m_Colision->Init();
	m_Colision->SetScale(D3DXVECTOR3(3.0f, 3.0f,3.0f));
}

void CBullet::Uninit()
{
	m_Colision->Uninit();
	delete m_Colision;
}

void CBullet::Update()
{
	//時間が0になったら削除
	if (DeleteTime <=0.0f)
	{
		SetDestroy();
		return;
	}

	Update_Collision();	//当たり判定
	Update_Varios();	//座標の更新
}

void CBullet::Update_Varios()
{
	m_Position += m_Velocity * 5.0f;
	DeleteTime -= 0.1f;
}

void CBullet::Update_Collision()
{
	//当たり判定更新
	m_Colision->Update();
	m_Colision->SetPosition(m_Position);

	CScene* scene = CManager::GetScene();

	//弾が味方の物だった時
	if (m_TeamNumber == TEAM_FRIENDRY)
	{
		std::vector<CEnemy*> enemyList = scene->GetGameObjects<CEnemy>(1);

		//すべての敵との当たり判定を調べる
		for (CEnemy* enemy : enemyList)
		{	//弾と敵の当たり判定
			if (m_Colision->GetColider(enemy->GetPosition()))
			{
				scene->AddGameObject<CExplosion>(2)->SetPosition(m_Position);	//画面に爆発のテクスチャ表示させる
				enemy->Death();													//敵を死亡させる
				SetDestroy();													//自身を消す
				return;
			}
		}
	}

	//弾が敵の物だった場合
	if (m_TeamNumber == TEAM_ENEMY)
	{
		std::vector<CFriend*> friendList = scene->GetGameObjects<CFriend>(1);
		CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

		//プレイヤーの当たり判定
		if (m_Colision->GetColider(pPlayer->GetPosition()))
		{
			pPlayer->Damage();
			SetDestroy();
			return;
		}

		//すべての味方との当たり判定を調べる
		for (CFriend* friends : friendList)
		{
			if (m_Colision->GetColider(friends->GetPosition()))
			{
				scene->AddGameObject<CExplosion>(2)->SetPosition(m_Position);	//画面に爆発のテクスチャ表示させる
				friends->Death();												//敵を死亡させる
				SetDestroy();
				return;
			}
		}
	}
}

void CBullet::Draw()
{
	CScene* scene = CManager::GetScene();
	CCamera* camera = scene->GetGameObject <CCamera>(0);

	//画面からはみ出てたら表示を行わない
	if (!camera->CheckView(m_Position))
		return;

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

void  CBullet::Set(D3DXVECTOR3 SetPos, D3DXVECTOR3 SetSight,TEAM_NUMBER SetNUMBER)
{
	m_Position = SetPos;
	m_Velocity = GetNorm(SetPos,SetSight);
	m_TeamNumber = SetNUMBER;
}