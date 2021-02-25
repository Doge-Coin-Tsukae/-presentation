//=====================================
//
//	敵NPC
//  written by Y.Okubo
//
//=====================================

#include "main.h"
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "model.h"
#include "human.h"

#include "Vector.h"
#include "sound.h"
#include "camera.h"
#include "animationmodel.h"
#include "sight.h"
#include "weapon.h"
#include "rifle.h"
#include "colider.h"
#include "behavior.h"
#include "player.h"
#include "friend.h"
#include "meshfield.h"
#include "enemy.h"

class CAnimationModel* CEnemy::m_Animodel;

#define		ANIMEBLENDSPEED	0.1f

typedef struct
{
	char *pFilename;	// ファイル名
} ANIMENAME2;

ANIMENAME2 g_aParam2[5] =
{
	{(char *)"idle"},				// 待機
	{(char *)"ready"},				// 構える
	{(char *)"run"},				// 走る
	{(char *)"fire"},				//発射
	{(char *)"Death"},
};

void CEnemy::Load()
{
	m_Animodel = new CAnimationModel();
	m_Animodel->Load("asset\\model\\player\\chara2.fbx");									//モデルのロード(ボーン付き)
	m_Animodel->LoadAnimation("asset\\model\\player\\idle.fbx", g_aParam2[0].pFilename);	//アニメーション
	m_Animodel->LoadAnimation("asset\\model\\player\\ready.fbx", g_aParam2[1].pFilename);
	m_Animodel->LoadAnimation("asset\\model\\player\\run.fbx", g_aParam2[2].pFilename);
	m_Animodel->LoadAnimation("asset\\model\\player\\fire.fbx", g_aParam2[3].pFilename);
	m_Animodel->LoadAnimation("asset\\model\\player\\Death.fbx", g_aParam2[4].pFilename);
}

void CEnemy::Unload()
{
	m_Animodel->Unload();
	m_Animodel->UnloadAnimation();
	delete m_Animodel;
}

void CEnemy::Init()
{
	
	m_Sight = new CSIGHT();
	m_Sight->Init();
	m_Sight->Setparent(this);		//照準の親を自分に

	m_Weapon = new Crifle();
	m_Weapon->Init();
	m_Weapon->Setparent(this);		//武器の親を自分に

	m_AI = new CEnemyAIRoot();
	m_AI->Init(this);

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_ModelRot = D3DXVECTOR3(1.6f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.3f, 1.3f, 1.3f);
	m_TeamNumber = TEAM_ENEMY;		//チーム設定
	m_Death = false;

	//アニメーション
	m_NowAnimationChara = g_aParam2[0].pFilename;
	m_OldAnimationChara = g_aParam2[1].pFilename;
	m_Frame = 0;
	rate = 0;
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
	rate = std::min(rate, 1.0f);
	rate = std::max(rate, 0.0f);

	//ヘルパー関数
	Update_AI();
	//プレイヤーに入っているクラスの更新処理
	m_Sight->Update();
	m_Weapon->Update();

	rate += ANIMEBLENDSPEED;
	m_Frame+=0.3f;

	//メッシュフィールド高さ取得
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);

	//ちんだ時の処理
	if (m_Death == true)
	{
		m_OldAnimationChara = (char*)"Death";
		m_NowAnimationChara = (char*)"Death";

		m_Frame += 0.7f;
		if (m_Frame > 177)
			SetDestroy();
	}
}

void CEnemy::Update_AI()
{
	if (m_Death) return;

	m_AI->Update();

}

void CEnemy::Draw()
{
	
	CScene* scene = CManager::GetScene();
	CCamera* camera = scene->GetGameObject <CCamera>(0);

	if (!camera->CheckView(m_Position))
		return;

	//m_Weapon->Draw();

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

void CEnemy::LookPlayer()
{
	if (LockOnEnemy == nullptr)return;

	D3DXVECTOR3 Velocity = GetNorm(m_Position, LockOnEnemy->GetPosition());
	D3DXVECTOR3 Velocity2 = GetNorm(m_Position, m_Sight->GetPosition());
	m_Rotation.y += (Velocity.x * Velocity2.x + Velocity.z * Velocity2.z) / (sqrt((Velocity.x * Velocity.x) + (Velocity.z * Velocity.z)) * sqrt((Velocity2.x * Velocity2.x) + (Velocity2.z * Velocity2.z)));
	m_Rotation.y -= 1.0f;
}

void CEnemy::ChangeAnimation(char* Name)
{
	if (m_NowAnimationChara == Name)return;	//今のアニメーションと次のアニメーションが一緒なら
	m_OldAnimationChara = m_NowAnimationChara;		//新しいアニメーションデータを古いアニメーションデータにする
	m_NowAnimationChara = Name;						//新しいアニメーションデータを入れる
	rate = 0.0f;									//ブレンド値をリセット
}

void CEnemy::Death()
{
	if (m_Death == true) return;
	PlaySound(SOUND_SE_DEATH);
	m_Death = true;
	m_Frame = 1;
}

bool CEnemy::Shoot()
{
	if (m_Weapon->GetAmmo() <= 0) return false;

	m_Weapon->Shoot(m_Sight->GetPosition(), m_TeamNumber);
	ChangeAnimation((char*)"fire");
	return true;
}

void CEnemy::Reload()
{
	m_Weapon->Reload();
}

bool CEnemy::isOverReload()
{
	return m_Weapon->GetAmmo() > 0;
}



void CEnemyAIRoot::Init(CEnemy* Sparent)
{
	parent = Sparent;
	m_Index = 0;
	m_child_Node[0] = new CEnemySequence(Sparent);
	m_child_Node[1] = new CEnemySelector(Sparent);
}

RESULT CEnemyAIRoot::Update()
{
	if (parent == nullptr) return RESULT_FAILED;

	//プレイヤーから離れていたら移動
	//近かったら攻撃
	//死亡したら何も行わない

	RESULT ret = m_child_Node[m_Index]->Update();

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


CEnemySelector::CEnemySelector(CEnemy* parent)
{
	m_parent = parent;
	m_child_Node[0] = new CEnemyShootNode(m_parent);
	m_child_Node[1] = new CEnemyReloadNode(m_parent);
}

RESULT CEnemySelector::Update()
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

CEnemySequence::CEnemySequence(CEnemy* parent)
{
	m_parent = parent;
	m_child_Node[0] = new CEnemySearchNode(m_parent);
	m_child_Node[1] = new CEnemyWalkNode(m_parent);
}

CEnemySearchNode::CEnemySearchNode(CEnemy* parent)
{
	m_parent = parent;
}

RESULT CEnemySearchNode::Update()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	m_parent->SetLockOnEnemy(pPlayer);		//プレイヤーをロックオン

	return RESULT_SUCCEEDED;
}

CEnemyWalkNode::CEnemyWalkNode(CEnemy* parent)
{
	m_parent = parent;
}

RESULT CEnemyWalkNode::Update()
{
	;
	D3DXVECTOR3 Velocity = GetNorm(m_parent->GetPosition(), m_parent->GetLockOnEnemy()->GetPosition());
	D3DXVECTOR3 Position = m_parent->GetPosition() + Velocity / 15;

	m_parent->LookPlayer();
	m_parent->ChangeAnimation((char*)"run");
	m_parent->SetPosition(Position);

	//当たり判定
	D3DXVECTOR3 direction = m_parent->GetPosition() - m_parent->GetLockOnEnemy()->GetPosition();
	float length = D3DXVec3Length(&direction);
	if (length < 30.0f) return RESULT_SUCCEEDED;

	return RESULT_PROGRESS;
}

CEnemyShootNode::CEnemyShootNode(CEnemy* parent)
{
	m_parent = parent;
}

RESULT CEnemyShootNode::Update()
{
	//当たり判定
	D3DXVECTOR3 direction = m_parent->GetPosition() - m_parent->GetLockOnEnemy()->GetPosition();
	float length = D3DXVec3Length(&direction);
	m_parent->LookPlayer();

	if (length > 60.0f) return RESULT_FAILED;					//ロックオンしていたキャラが範囲外に逃げたら
	if (m_parent->Shoot() == false) return RESULT_FAILED;		//弾切れだったら

	return RESULT_PROGRESS;
}

CEnemyReloadNode::CEnemyReloadNode(CEnemy* parent)
{
	m_parent = parent;
}

RESULT CEnemyReloadNode::Update()
{
	if (m_parent->isOverReload() == true) return RESULT_SUCCEEDED;

	m_parent->Reload();

	return RESULT_PROGRESS;
}