//---------------------------------
//
//画面右のボックスの管理
//
//---------------------------------

#include "main.h"
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "Vector.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "input.h"
#include "scene.h"
#include "polygon.h"
#include "chip.h"
#include "model.h"
#include "animationmodel.h"
#include "human.h"
#include "carsor.h"
#include "colider.h"
#include "camera.h"
#include "bunker.h"
#include "sight.h"
#include "player.h"
#include "enemy.h"
#include "friend.h"
#include "base.h"
#include "deadtree.h"
#include "tree.h"
#include "spownpoint.h"

#include "selectpointer.h"
#include "modechip.h"
#include "saveloadchip.h"
#include "triangle.h"
#include "selectitem.h"

#define ITEMCHIPX 2
#define ITEMCHIPY 4


enum BOTTONMODE
{
	SET,		//設置
	EDIT,		//編集
};

void CSelectItem::Init()
{
	const char* texturename[2] = //ファイルネーム
	{
		"asset/texture/selectitem/button-mode-set.png",
		"asset/texture/selectitem/button-mode-edit.png",
	};

	m_Position = D3DXVECTOR3(800.0f, 40.0f, 0.0f);

	m_under = new CPolygon;
	m_under->SetSize(300.0f, 150.0f);
	m_under->SetTexture((char*)"asset/texture/selectitem/under2.png");
	m_under->Init(m_Position);

	m_pointer = new CSelectpointer;
	m_pointer->Init();
	m_pointer->SetPosition(m_Position = D3DXVECTOR3(m_Position.x + 3.0f, m_Position.y + 28.0f, 0.0f));

	//縦方向
	for (int h = 0; h < ITEMCHIPY; h++)
	{
		//横方向
		for (int w = 0; w < ITEMCHIPX; w++)
		{
			m_chip[h][w] = new CChip;
			m_chip[h][w]->Init();
			m_chip[h][w]->SetPosition(D3DXVECTOR3(m_Position.x - 2 + 75 * w, m_Position.y - 2 + 69 * h, 0.0f));
			m_chip[h][w]->SetPolygon((char*)"asset/texture/selectitem/chip2.png",
				D3DXVECTOR2(73.0f, 68.0f),
				D3DXVECTOR2(0.5f*w, 0.25f*h), D3DXVECTOR2(0.5f + (0.5f * w), 0.25 + (0.25*h)));

			m_chip[h][w]->Setid((h * 2) + w);
		}
	}

	//モードチップの数分ループ
	for (int h = 0; h < 2; h++)
	{
		m_modechip[h] = new CMODECHIP;
		m_modechip[h]->Init();
		m_modechip[h]->SetPosition(D3DXVECTOR3(m_Position.x - 2 + 78 * h, m_Position.y - 53, 0.0f));
		m_modechip[h]->SetPolygon((char*)texturename[h],
			D3DXVECTOR2(70.0f, 25.0f));
		m_modechip[h]->Setid(h);
	}
	m_modechip[1]->SetMode();		//配置モードにする
	NowMode = SET;

	m_carsor = new CCARSOR;
	m_carsor->Init();

	m_SaveLoadChip = new CSaveLoadChip;
	m_SaveLoadChip->SetPosition(m_Position);
	m_SaveLoadChip->Init();

	m_Triangle = new CTriangle;
	m_Triangle->Init();

	min = D3DXVECTOR2(0, 0);
	max = D3DXVECTOR2(150.0f, 300.0f);
	click = false;
	isEnemy = false;
}

void CSelectItem::Uninit()
{
	m_SaveLoadChip->Uninit();
	delete m_SaveLoadChip;

	m_carsor->Uninit();
	delete m_carsor;

	for (int h = 0; h < 2; h++)
	{
		m_modechip[h]->Uninit();
		delete m_modechip[h];
	}

	//縦方向
	for (int h = 0; h < ITEMCHIPY; h++)
	{
		//横方向
		for (int w = 0; w < ITEMCHIPX; w++)
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
	for (int h = 0; h < ITEMCHIPY; h++)
	{
		//横方向
		for (int w = 0; w < ITEMCHIPX; w++)
		{
			m_chip[h][w]->Update();
		}
	}

	for (int h = 0; h < 2; h++)
	{
		m_modechip[h]->Update();

	}

	m_carsor->Update();
	m_SaveLoadChip->Update();
	m_Triangle->Update();

	if (m_EditGameObject != nullptr)
	{
		D3DXVECTOR3 Tpos(m_EditGameObject->GetPosition().x, m_EditGameObject->GetPosition().y + 3.5f, m_EditGameObject->GetPosition().z);
		m_Triangle->SetPosition(Tpos);//現在クリックしているゲームオブジェクトに逆三角形のオブジェクトを出す
	}
	UpdateControll();

}

void CSelectItem::Draw()
{
	m_Triangle->Draw();

	m_under->Draw();
	m_pointer->Draw();

	//縦方向
	for (int h = 0; h < ITEMCHIPY; h++)
	{
		//横方向
		for (int w = 0; w < ITEMCHIPX; w++)
		{
			m_chip[h][w]->Draw();
		}
	}

	for (int i = 0; i < 2; i++)
	{
		m_modechip[i]->Draw();
	}

	m_carsor->Draw();

	m_SaveLoadChip->Draw();

	//配置モードの時に配置する
	if (NowMode == SET)
	{
		//IMGUI
		ImGuiSetMode();

	}

	//編集モードの時に配置する
	if (NowMode == EDIT)
	{

		//IMGUI

		ImGui::SetNextWindowSize(ImVec2(220, 200));
		ImGui::Begin("EDIT_MODE");

		if (m_EditGameObject != nullptr)
		{
			m_EditGameObject->SetImGui();		//現在クリックしているゲームオブジェクトの編集画面を出す
		}
		ImGui::End();
	}
}

void CSelectItem::UpdateControll()
{
	//カメラ動かす
	if (CInput::GetKeyTrigger(VK_UP))	 m_pointer->move_up();
	if (CInput::GetKeyTrigger(VK_DOWN))  m_pointer->move_down();
	if (CInput::GetKeyTrigger(VK_LEFT))  m_pointer->move_left();
	if (CInput::GetKeyTrigger(VK_RIGHT)) m_pointer->move_right();

	//左クリックした時の動き
	if (CInput::GetKeyTrigger(VK_LBUTTON))
	{
		//アイテムボックスをクリックしてなかったらワールドにオブジェクト配置
		if (ClickItemBox() == false && ClikEditBox() == false && m_SaveLoadChip->ClickSaveLoad() ==false)
		{
			//設置モードのときはワールドにオブジェクト配置
			if (NowMode == SET)
				WorldObject();

			//編集モードのときはオブジェクトがクリックされたらそのオブジェクトの編集画面表示
			if (NowMode == EDIT)
			{
				ClickColider();
			}
		}

		click = false;
	}
	//押しっぱなしにしたとき、オブジェクトをついてくるようにする
	if (CInput::GetKeyPress(VK_LBUTTON))
	{
		if (!m_EditGameObject) return;
		if(click == false)
		{
			if (m_carsor->Collision(m_EditGameObject) == false) return;
			click = true;
		}
		
		//シフトキーを押していたらモデルの角度をいじる
		if (CInput::GetKeyPress(VK_SHIFT))
		{
			D3DXVECTOR3 editrot = m_EditGameObject->GetRotation();

			D3DXVECTOR3 editobjectforwardpos = m_EditGameObject->GetPosition();

			editobjectforwardpos.x = editobjectforwardpos.x - 5.0f * cos(m_EditGameObject->GetRotation().y) * cos(m_EditGameObject->GetRotation().x *1.1f);	//座標
			editobjectforwardpos.y = (editobjectforwardpos.y + 1.0f) - 8.0f * sin(m_EditGameObject->GetRotation().x);
			editobjectforwardpos.z = editobjectforwardpos.z - 5.0f * -sin(m_EditGameObject->GetRotation().y) * cos(m_EditGameObject->GetRotation().x);	//座標


			D3DXVECTOR3 Velocity = GetNorm(m_carsor->GetPosition(), m_EditGameObject->GetPosition());
			D3DXVECTOR3 Velocity2 = GetNorm(m_EditGameObject->GetPosition(), editobjectforwardpos);

			editrot.y += (Velocity.x * Velocity2.x + Velocity.z * Velocity2.z) / (sqrt((Velocity.x * Velocity.x) + (Velocity.z * Velocity.z)) * sqrt((Velocity2.x * Velocity2.x) + (Velocity2.z * Velocity2.z)));
			m_EditGameObject->SetRotation(editrot);

		}
		else
		{
			//カーソルにゲームオブジェクトを吸い付ける
			D3DXVECTOR3 cpos = m_carsor->GetPosition();
			m_EditGameObject->SetPosition(cpos);
		}
	}

	//右クリックしたときカメラもついてくるようにする
	if (CInput::GetKeyPress(VK_RBUTTON))
	{
		CCamera* camera = CManager::GetScene()->GetGameObject<CCamera>(0);
		camera->CameraMouseMove();
	}

	//ホイールを押したらカメラぐるぐるする
	if(CInput::GetKeyPress(VK_MBUTTON))
	{
		CCamera* camera = CManager::GetScene()->GetGameObject<CCamera>(0);
		camera->CameraMouseRotate();
	}

	//デリートキーで選択しているオブジェクト削除
	if (CInput::GetKeyTrigger(VK_DELETE))
	{
		if (!m_EditGameObject) return;
		m_EditGameObject->SetDestroy();
	}

	//1キーで配置モード
	if (CInput::GetKeyTrigger('1'))
	{
		if (m_modechip[0]->GetSelectMode() == false)
		{
			m_modechip[0]->SetMode();
			m_modechip[1]->SetMode();
			NowMode = 0;	//モードセット
		}
	}
	//2キーで編集モード
	if (CInput::GetKeyTrigger('2'))
	{
		if (m_modechip[1]->GetSelectMode() == false)
		{
			m_modechip[1]->SetMode();
			m_modechip[0]->SetMode();
			NowMode = 1;	//モードセット
		}
	}

	//マウスホイール
	if (GetMouseWheel() > 0)
	{
		CCamera* camera = CManager::GetScene()->GetGameObject<CCamera>(0);
		camera->ZoomCamera();
	}
	if (GetMouseWheel() < 0)
	{
		CCamera* camera = CManager::GetScene()->GetGameObject<CCamera>(0);
		camera->ZoomOutCamera();
	}
}

bool CSelectItem::ClikEditBox()
{
	POINT pos;
	GetCursorPos(&pos);		//現在のカーソルのポジション取得
	ScreenToClient(GetWindow(), &pos);

	for (int i = 0; i < 2; i++)
	{
		//ボタンがクリックされていた
		if (m_modechip[i]->Colision(pos) == true && NowMode != i)
		{
			m_modechip[i]->SetMode();
			m_modechip[1 - i]->SetMode();

			NowMode = i;	//モードセット

			m_EditGameObject = nullptr;	//編集モードでオブジェクト削除してモード変更するとクラッシュするので

			return true;
		}
	}

	return false;
}

bool CSelectItem::ClickItemBox()
{
	POINT pos;
	GetCursorPos(&pos);		//現在のカーソルのポジション取得
	ScreenToClient(GetWindow(), &pos);

	//カーソルがボックスの範囲外だったらループ抜ける
	if (pos.x < m_Position.x + min.x)return false;
	if (pos.x > m_Position.x + max.x)return false;
	if (pos.y < m_Position.y + min.y)return false;
	if (pos.y > m_Position.y + max.y)return false;

	m_EditGameObject = nullptr;	//編集モードでオブジェクト削除してアイテムボックスをクリックするとクラッシュするので

	//チップの当たり判定
		//縦方向
	for (int h = 0; h < ITEMCHIPY; h++)
	{
		//横方向
		for (int w = 0; w < ITEMCHIPX; w++)
		{
			if (m_chip[h][w]->Colision(pos) == true)
			{
				m_pointer->SetPos(D3DXVECTOR2((float)w, (float)h));	//ポインターの位置をカーソルがさしたところに
				return true;
			}
		}
	}

	return false;
}

void CSelectItem::ClickColider()
{
	CScene* scene = CManager::GetScene();

	std::vector<CGameObject*> gameobjectlist = scene->GetALLGameObjects<CGameObject>(1);
	CCARSOR *cursor = scene->GetGameObject<CCARSOR>(1);
	for (CGameObject* gameobject : gameobjectlist)
	{
		if (gameobject->GetPosition() != cursor->GetPosition())
		{
			if (cursor->Collision(gameobject) == true)
			{
				m_EditGameObject = gameobject;	//m_EditGameObjectにクリックされたオブジェクトのポインタクラスを入れる
				return;
			}
		}
	}
}

void CSelectItem::WorldObject()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	//オブジェクトの設置をおこなう
	//選択したオブジェクトで配置オブジェクト変更
	switch (m_chip[(int)m_pointer->GetPos().y][(int)m_pointer->GetPos().x]->GetId())
	{
	case 0:
		//個数制限(プレイヤーは一人しか存在しない)
		if (pPlayer)pPlayer->SetDestroy();
		scene->AddGameObject<CPlayer>(1)->SetPosition(m_carsor->GetPosition());
		break;
	case 1:
		if(isEnemy == true) 
			scene->AddGameObject<CEnemy>(1)->SetPosition(m_carsor->GetPosition());
		else
			scene->AddGameObject<CFriend>(1)->SetPosition(m_carsor->GetPosition());
		break;
	case 2:
		scene->AddGameObject<CBase>(1)->SetPosition(m_carsor->GetPosition());
		break;
	case 3:
		scene->AddGameObject<CDEADTREE>(1)->SetPosition(m_carsor->GetPosition());
		break;
	case 4:
		scene->AddGameObject<CTREE>(1)->SetPosition(m_carsor->GetPosition());
		break;
	case 5:
		scene->AddGameObject<CBUNKER>(1)->SetPosition(m_carsor->GetPosition());
		break;
	case 6:
		scene->AddGameObject<CSpownPoint>(1)->SetPosition(m_carsor->GetPosition());
	default:
		break;
	}

}

void CSelectItem::ImGuiSetMode()
{
	ImGui::SetNextWindowSize(ImVec2(220, 200));
	ImGui::Begin("SET_MODE");

	//共通する物

	ImGui::SliderFloat("rotation", &m_Rotation.y, 0, 10);
	ImGui::SliderFloat("scale", &m_Scale.x, 0, 10);

	switch (m_chip[(int)m_pointer->GetPos().y][(int)m_pointer->GetPos().x]->GetId())
	{
	case 0:		//プレイヤー
		//モデル変更をここでおこないたい
		break;
	case 1:		//敵
		ImGui::Checkbox("Enemy", &isEnemy);
		break;
	case 2:		//拠点
		//判定の円の大きさを変更したい
		break;
	case 3:		//枯れ木
		//複数配置を行いたい
		//円を表示してその範囲内で乱数配置を行いたい
		break;
	case 4:		//木
		//複数配置を行いたい
		//円を表示してその範囲内で乱数配置を行いたい
		break;
	case 5:		//建物
		//モデル変更をおこないたい
		break;
	case 6:		//スポーンポイント
		//スポーン条件変更を行いたい
		break;
	default:	//それ以外
		break;
	}

	
	ImGui::End();
}