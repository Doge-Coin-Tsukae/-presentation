//=====================================
//
//  武器の基底クラス
//  written by Y.Okubo
//
//=====================================
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "sound.h"
#include "Vector.h"
#include "smoke.h"
#include "model.h"
#include "animationmodel.h"
#include "human.h"
#include "colider.h"
#include "weapon.h"
#include "bullet.h"

#define RELOADTIME 240
#define	ANIMEBLENDSPEED	0.1f

class CAnimationModel* CWEAPON::m_AniModel;

typedef struct
{
	char* pFilename;	// ファイル名
} ANIMENAME;

ANIMENAME g_aParam3[6] =
{
	{(char*)"idle"},				// 待機
	{(char*)"ready"},				// 構える
	{(char*)"run"},				// 走る
	{(char*)"readyrun"},
	{(char*)"fire"},				//発射
	{(char*)"Death"},
};

void CWEAPON::Load()
{
	m_AniModel = new CAnimationModel();
	m_AniModel->Load("asset\\model\\weapon\\rifle.fbx");					//モデルのロード(ボーン付き)
	m_AniModel->LoadAnimation("asset\\model\\weapon\\rifle_idle.fbx", g_aParam3[0].pFilename);
	m_AniModel->LoadAnimation("asset\\model\\weapon\\rifle_idle.fbx", g_aParam3[1].pFilename);
}
void CWEAPON::UnLoad()
{
	m_AniModel->Unload();
	m_AniModel->UnloadAnimation();
	delete m_AniModel;
}
void CWEAPON::Init()
{
	m_Position = D3DXVECTOR3(0, 1, 0);
	m_Rotation = D3DXVECTOR3(0, 0, 0);
	m_Scale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);

	MaxAmmo = 5;
	Ammo = MaxAmmo;
	isReload = false;
	isNextShoot = false;
	ReloadTime = 0;
	NextShootTime = 0;

	//アニメーション
	m_NowAnimationChara = g_aParam3[0].pFilename;
	m_OldAnimationChara = g_aParam3[1].pFilename;
	m_Frame = 0;
	rate = 0;
}
void CWEAPON::Uninit()
{

}
void CWEAPON::Update()
{
	rate = std::min(rate, 1.0f);
	rate = std::max(rate, 0.0f);

	//座標の更新
	m_Position = m_parent->GetPosition();
	m_Position.x = m_Position.x - 1.0f * cos(m_parent->GetRotation().y)*cos(m_parent->GetRotation().x);	//座標
	m_Position.z = m_Position.z - 1.0f *-sin(m_parent->GetRotation().y)*cos(m_parent->GetRotation().x);	//座標
	m_Rotation = m_parent->GetRotation();

	rate += ANIMEBLENDSPEED;
	m_Frame+=0.5f;

	//装填中
	if (isReload == true)
	{
		if (ReloadTime <= 0)
		{
			Ammo = MaxAmmo;
			isReload = false;
			ReloadTime = 0;
		}
		ReloadTime--;
	}

	//次撃てるまでの時間
	if (isNextShoot == true)
	{
		if (NextShootTime <= 0)
		{
			//PlaySound(SOUND_SE_RELOAD);
			isNextShoot = false;
			NextShootTime = 0;
			return;
		}
		NextShootTime--;
	}
}
void CWEAPON::Draw()
{
	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	//拡大縮小のマトリクス
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//ヨーピッチロールのマトリクス
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	//位置マトリクス
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	CRenderer::SetWorldMatrix(&world);

	m_AniModel->Update(m_OldAnimationChara, m_NowAnimationChara, m_Frame, rate);
	m_AniModel->Draw();
}

void CWEAPON::Shoot(D3DXVECTOR3 SPos, TEAM_NUMBER SetTeamNumber)
{
	//弾が0になったとき
	if (Ammo <= 0) 
	{ 
		Reload();		//今回に限りオートリロード
		return; 
	}
	if (isNextShoot == false)
	{
		Ammo -= 1;		//弾の消費
		NextShoot();	//次の弾発射

		D3DXVECTOR3 Pos = m_Position;
		Pos.y += 2.8f;
		CScene* scene = CManager::GetScene();
		scene->AddGameObject<CBullet>(1)->Set(Pos, SPos, SetTeamNumber);	//弾の発射
		scene->AddGameObject<CSMOKE>(3)->SetPosition(m_Position);	//煙
		PlaySound(SOUND_SE_SE001);
	}
}

void CWEAPON::NextShoot()
{
	NextShootTime = MaxNextShootTime;		//次、弾発射できるまでの時間をセット(武器によって変える)
	isNextShoot = true;		//フラグを建てる
}

void CWEAPON::Reload()
{
	if (isReload == true) return;
	Ammo = 0;
	ReloadTime = MaxReloadTime;		//装填が終わる時間をセット(武器によって変える)
	isReload = true;				//フラグを建てる
	PlaySound(SOUND_SE_RELOAD2);	//リロード音
}