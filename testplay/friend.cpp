//****************************************
//味方NPC
//****************************************

#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "sound.h"
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include "model.h"
#include "camera.h"
#include "human.h"
#include "Vector.h"
#include "model.h"
#include "animationmodel.h"
#include "sight.h"
#include "weapon.h"
#include "rifle.h"
#include "colider.h"
#include "behavior.h"
#include "player.h"
#include "meshfield.h"
#include "enemy.h"
#include "friend.h"

class CAnimationModel* CFriend::m_Animodel;

#define		ANIMEBLENDSPEED	0.1f

typedef struct
{
	char *pFilename;	// ファイル名
} ANIMENAME3;

ANIMENAME3 g_aParam2[5] =
{
	{(char *)"idle"},				// 待機
	{(char *)"ready"},				// 構える
	{(char *)"run"},				// 走る
	{(char *)"fire"},				//発射
	{(char *)"Death"},
};

void CFriend::Load()
{
	m_Animodel = new CAnimationModel();
	m_Animodel->Load("asset\\model\\player\\chara.fbx");					//モデルのロード(ボーン付き)
	m_Animodel->LoadAnimation("asset\\model\\player\\idle.fbx", g_aParam2[0].pFilename);		//アニメーション
	m_Animodel->LoadAnimation("asset\\model\\player\\ready.fbx", g_aParam2[1].pFilename);		//アニメーション
	m_Animodel->LoadAnimation("asset\\model\\player\\run.fbx", g_aParam2[2].pFilename);		//アニメーション
	m_Animodel->LoadAnimation("asset\\model\\player\\fire.fbx", g_aParam2[3].pFilename);
	m_Animodel->LoadAnimation("asset\\model\\player\\Death.fbx", g_aParam2[4].pFilename);
}

void CFriend::Unload()
{
	m_Animodel->Unload();
	delete m_Animodel;
}

void CFriend::Init()
{
	m_Sight = new CSIGHT();
	m_Sight->Init();
	m_Sight->Setparent(this);		//照準の親を自分に

	m_Weapon = new Crifle();
	m_Weapon->Init();
	m_Weapon->Setparent(this);		//武器の親を自分に

	m_AI = new CFriendAIRoot();
	m_AI->Init(this);

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_ModelRot = D3DXVECTOR3(1.6f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.3f, 1.3f, 1.3f);
	m_TeamNumber = TEAM_FRIENDRY;		//チーム設定

	//アニメーション
	m_NowAnimationChara = g_aParam2[0].pFilename;
	m_OldAnimationChara = g_aParam2[1].pFilename;
	m_Frame = 0;
	rate = 0;
}

void CFriend::Uninit()
{
	delete m_AI;

	m_Weapon->Uninit();
	delete m_Weapon;

	m_Sight->Uninit();
	delete m_Sight;
}

void CFriend::Update()
{
	rate = std::min(rate, 1.0f);
	rate = std::max(rate, 0.0f);

	//ヘルパー関数
	Update_AI();
	//プレイヤーに入っているクラスの更新処理
	m_Sight->Update();
	m_Weapon->Update();

	rate += ANIMEBLENDSPEED;
	m_Frame+=0.3f;

	//ちんだ時の処理
	if (m_Death == true)
	{
		m_OldAnimationChara = (char*)"Death";
		m_NowAnimationChara = (char*)"Death";

		m_Frame += 0.7f;
		if (m_Frame > 177)	//一定のフレーム数に達したらワールドから削除
			SetDestroy();
	}

	//メッシュフィールド高さ取得
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);
}

void CFriend::Update_AI()
{
	if (m_Death == true) return;
	m_AI->Update();
}

void CFriend::Draw()
{
	CScene* scene = CManager::GetScene();
	CCamera* camera = scene->GetGameObject <CCamera>(0);

	if (!camera->CheckView(m_Position))
		return;

	//内部クラスから
	//m_Weapon->Draw();
	m_Sight->Draw();

	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	//拡大縮小のマトリクス
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//ヨーピッチロールのマトリクス
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y + m_ModelRot.x, -m_Rotation.x - m_ModelRot.z, m_Rotation.z + m_ModelRot.y);
	//位置マトリクス
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	CRenderer::SetWorldMatrix(&world);

	m_Animodel->Update(m_OldAnimationChara, m_NowAnimationChara, m_Frame, rate);
	m_Animodel->Draw();
}

void CFriend::LookEnemy()
{
	if (LockOnEnemy == nullptr)return;

	D3DXVECTOR3 Velocity = GetNorm(m_Position, LockOnEnemy->GetPosition());
	D3DXVECTOR3 Velocity2 = GetNorm(m_Position, m_Sight->GetPosition());
	m_Rotation.y += (Velocity.x * Velocity2.x + Velocity.z*Velocity2.z) / (sqrt((Velocity.x*Velocity.x) + (Velocity.z*Velocity.z))*sqrt((Velocity2.x*Velocity2.x) + (Velocity2.z*Velocity2.z)));
	m_Rotation.y -= 1.0f;
}

void CFriend::SetLockOnEnemy(CGameObject* enemy)
{
	LockOnEnemy = enemy;
}

void CFriend::ChangeAnimation(char* Name)
{
	if (m_NowAnimationChara == Name)return;	//今のアニメーションと次のアニメーションが一緒なら
	m_OldAnimationChara = m_NowAnimationChara;		//新しいアニメーションデータを古いアニメーションデータにする
	m_NowAnimationChara = Name;						//新しいアニメーションデータを入れる
	rate = 0.0f;									//ブレンド値をリセット
}

void CFriend::Death()
{
	if (m_Death == true) return;
	PlaySound(SOUND_SE_DEATH);
	m_Death = true;
	m_Frame = 1;
}


bool CFriend::Shoot()
{
	if (m_Weapon->GetAmmo() <= 0) return false;

	m_Weapon->Shoot(m_Sight->GetPosition(), m_TeamNumber);
	ChangeAnimation((char*)"fire");
	return true;
}

void CFriend::Reload()
{
	m_Weapon->Reload();
}

bool CFriend::isOverReload()
{
	return m_Weapon->GetAmmo() > 0;
}



//ここから下はビヘイビアツリーの処理
void CFriendAIRoot::Init(CFriend* Sparent)
{
	parent = Sparent;
	m_Index = 0;
	m_child_Node[0] = new CFriendSequence(Sparent);
	m_child_Node[1] = new CFriendSelector(Sparent);
}

RESULT CFriendAIRoot::Update()
{
	if (parent == nullptr) return RESULT_FAILED;

	//プレイヤーから離れていたら移動
	//近かったら攻撃
	//死亡したら何も行わない

	RESULT ret = m_child_Node[m_Index]->Update();

	//ロックオンしていた敵が死んだらもう一度捜索ノードを起動する
	if (parent->GetLockOnEnemy() != nullptr)
	{
		//if (parent->GetLockOnEnemy()->isDeath() == true)
			m_Index = 0;
	}

	switch (ret)
	{
	case RESULT_PROGRESS:
		return RESULT_PROGRESS;
	case RESULT_SUCCEEDED:
		if (m_Index == 0) m_Index = 1;
		return RESULT_SUCCEEDED;
	case RESULT_FAILED:
		m_Index = 0;
		return RESULT_FAILED;
	}
}


CFriendSelector::CFriendSelector(CFriend* parent)
{
	m_parent = parent;
	m_child_Node[0] = new CFriendShootNode(m_parent);
	m_child_Node[1] = new CFriendReloadNode(m_parent);
}

RESULT CFriendSelector::Update()
{
	RESULT ret = m_child_Node[m_Index]->Update();

	switch (ret)
	{
	case RESULT_PROGRESS:
		return RESULT_PROGRESS;
	case RESULT_SUCCEEDED:
		m_Index--;
		return RESULT_SUCCEEDED;

	case RESULT_FAILED:
		if (m_parent->isOverReload() == false)
		{
			m_Index++;
			return RESULT_PROGRESS;
		}
		return RESULT_FAILED;
	}
}

CFriendSequence::CFriendSequence(CFriend* parent)
{
	m_parent = parent;
	m_child_Node[0] = new CFriendSearchNode(m_parent);
	m_child_Node[1] = new CFriendWalkNode(m_parent);
}

CFriendSearchNode::CFriendSearchNode(CFriend* parent)
{
	m_parent = parent;
}

RESULT CFriendSearchNode::Update()
{
	CScene* scene = CManager::GetScene();
	std::vector<CEnemy*> enemyList = scene->GetGameObjects<CEnemy>(1);
	CEnemy* NearEnemy = nullptr;		//自分に一番近い敵
	float nearlength, enemylength;


	//一番近い敵を探索する
	for (CEnemy* enemy : enemyList)
	{
		if(enemy->isDeath() == false)		//生きている敵のみ探索
		{
			D3DXVECTOR3 direction = m_parent->GetPosition() - enemy->GetPosition();
			enemylength = D3DXVec3Length(&direction);

			if (NearEnemy == nullptr || nearlength > enemylength)
			{
				NearEnemy = enemy;
				nearlength = enemylength;
			}
		}
	}

	//発見できなかったとき、そのまま
	if (NearEnemy == nullptr)
	{
		m_parent->ChangeAnimation((char*)"idle");
		return RESULT_PROGRESS;
	}

	m_parent->SetLockOnEnemy(NearEnemy);	//一番近かった敵を入れる

	return RESULT_SUCCEEDED;
}

CFriendWalkNode::CFriendWalkNode(CFriend* parent)
{
	m_parent = parent;
}

RESULT CFriendWalkNode::Update()
{
	D3DXVECTOR3 Velocity = GetNorm(m_parent->GetPosition(), m_parent->GetLockOnEnemy()->GetPosition());
	D3DXVECTOR3 Position = m_parent->GetPosition() + Velocity / 15;

	m_parent->LookEnemy();
	m_parent->ChangeAnimation((char*)"run");
	m_parent->SetPosition(Position);

	//当たり判定
	D3DXVECTOR3 direction = m_parent->GetPosition() - m_parent->GetLockOnEnemy()->GetPosition();
	float length = D3DXVec3Length(&direction);
	if (length < 30.0f) 
		return RESULT_SUCCEEDED;

	return RESULT_PROGRESS;
}

CFriendShootNode::CFriendShootNode(CFriend* parent)
{
	m_parent = parent;
}

RESULT CFriendShootNode::Update()
{
	//当たり判定
	D3DXVECTOR3 direction = m_parent->GetPosition() - m_parent->GetLockOnEnemy()->GetPosition();
	float length = D3DXVec3Length(&direction);
	m_parent->LookEnemy();

	if (length > 60.0f) return RESULT_FAILED;					//ロックオンしていたキャラが範囲外に逃げたら
	if (m_parent->Shoot() == false) return RESULT_FAILED;		//弾切れだったら

	return RESULT_PROGRESS;
}

CFriendReloadNode::CFriendReloadNode(CFriend* parent)
{
	m_parent = parent;
}

RESULT CFriendReloadNode::Update()
{
	if (m_parent->isOverReload() == true) return RESULT_SUCCEEDED;

	m_parent->Reload();

	return RESULT_PROGRESS;
}