//---------------------------------
//
//��ʉE�̃{�b�N�X�̊Ǘ�
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
	SET,		//�ݒu
	EDIT,		//�ҏW
};

void CSelectItem::Init()
{
	const char* texturename[2] = //�t�@�C���l�[��
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

	//�c����
	for (int h = 0; h < ITEMCHIPY; h++)
	{
		//������
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

	//���[�h�`�b�v�̐������[�v
	for (int h = 0; h < 2; h++)
	{
		m_modechip[h] = new CMODECHIP;
		m_modechip[h]->Init();
		m_modechip[h]->SetPosition(D3DXVECTOR3(m_Position.x - 2 + 78 * h, m_Position.y - 53, 0.0f));
		m_modechip[h]->SetPolygon((char*)texturename[h],
			D3DXVECTOR2(70.0f, 25.0f));
		m_modechip[h]->Setid(h);
	}
	m_modechip[1]->SetMode();		//�z�u���[�h�ɂ���
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

	//�c����
	for (int h = 0; h < ITEMCHIPY; h++)
	{
		//������
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
	//�c����
	for (int h = 0; h < ITEMCHIPY; h++)
	{
		//������
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
		m_Triangle->SetPosition(Tpos);//���݃N���b�N���Ă���Q�[���I�u�W�F�N�g�ɋt�O�p�`�̃I�u�W�F�N�g���o��
	}
	UpdateControll();

}

void CSelectItem::Draw()
{
	m_Triangle->Draw();

	m_under->Draw();
	m_pointer->Draw();

	//�c����
	for (int h = 0; h < ITEMCHIPY; h++)
	{
		//������
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

	//�z�u���[�h�̎��ɔz�u����
	if (NowMode == SET)
	{
		//IMGUI
		ImGuiSetMode();

	}

	//�ҏW���[�h�̎��ɔz�u����
	if (NowMode == EDIT)
	{

		//IMGUI

		ImGui::SetNextWindowSize(ImVec2(220, 200));
		ImGui::Begin("EDIT_MODE");

		if (m_EditGameObject != nullptr)
		{
			m_EditGameObject->SetImGui();		//���݃N���b�N���Ă���Q�[���I�u�W�F�N�g�̕ҏW��ʂ��o��
		}
		ImGui::End();
	}
}

void CSelectItem::UpdateControll()
{
	//�J����������
	if (CInput::GetKeyTrigger(VK_UP))	 m_pointer->move_up();
	if (CInput::GetKeyTrigger(VK_DOWN))  m_pointer->move_down();
	if (CInput::GetKeyTrigger(VK_LEFT))  m_pointer->move_left();
	if (CInput::GetKeyTrigger(VK_RIGHT)) m_pointer->move_right();

	//���N���b�N�������̓���
	if (CInput::GetKeyTrigger(VK_LBUTTON))
	{
		//�A�C�e���{�b�N�X���N���b�N���ĂȂ������烏�[���h�ɃI�u�W�F�N�g�z�u
		if (ClickItemBox() == false && ClikEditBox() == false && m_SaveLoadChip->ClickSaveLoad() ==false)
		{
			//�ݒu���[�h�̂Ƃ��̓��[���h�ɃI�u�W�F�N�g�z�u
			if (NowMode == SET)
				WorldObject();

			//�ҏW���[�h�̂Ƃ��̓I�u�W�F�N�g���N���b�N���ꂽ�炻�̃I�u�W�F�N�g�̕ҏW��ʕ\��
			if (NowMode == EDIT)
			{
				ClickColider();
			}
		}

		click = false;
	}
	//�������ςȂ��ɂ����Ƃ��A�I�u�W�F�N�g�����Ă���悤�ɂ���
	if (CInput::GetKeyPress(VK_LBUTTON))
	{
		if (!m_EditGameObject) return;
		if(click == false)
		{
			if (m_carsor->Collision(m_EditGameObject) == false) return;
			click = true;
		}
		
		//�V�t�g�L�[�������Ă����烂�f���̊p�x��������
		if (CInput::GetKeyPress(VK_SHIFT))
		{
			D3DXVECTOR3 editrot = m_EditGameObject->GetRotation();

			D3DXVECTOR3 editobjectforwardpos = m_EditGameObject->GetPosition();

			editobjectforwardpos.x = editobjectforwardpos.x - 5.0f * cos(m_EditGameObject->GetRotation().y) * cos(m_EditGameObject->GetRotation().x *1.1f);	//���W
			editobjectforwardpos.y = (editobjectforwardpos.y + 1.0f) - 8.0f * sin(m_EditGameObject->GetRotation().x);
			editobjectforwardpos.z = editobjectforwardpos.z - 5.0f * -sin(m_EditGameObject->GetRotation().y) * cos(m_EditGameObject->GetRotation().x);	//���W


			D3DXVECTOR3 Velocity = GetNorm(m_carsor->GetPosition(), m_EditGameObject->GetPosition());
			D3DXVECTOR3 Velocity2 = GetNorm(m_EditGameObject->GetPosition(), editobjectforwardpos);

			editrot.y += (Velocity.x * Velocity2.x + Velocity.z * Velocity2.z) / (sqrt((Velocity.x * Velocity.x) + (Velocity.z * Velocity.z)) * sqrt((Velocity2.x * Velocity2.x) + (Velocity2.z * Velocity2.z)));
			m_EditGameObject->SetRotation(editrot);

		}
		else
		{
			//�J�[�\���ɃQ�[���I�u�W�F�N�g���z���t����
			D3DXVECTOR3 cpos = m_carsor->GetPosition();
			m_EditGameObject->SetPosition(cpos);
		}
	}

	//�E�N���b�N�����Ƃ��J���������Ă���悤�ɂ���
	if (CInput::GetKeyPress(VK_RBUTTON))
	{
		CCamera* camera = CManager::GetScene()->GetGameObject<CCamera>(0);
		camera->CameraMouseMove();
	}

	//�z�C�[������������J�������邮�邷��
	if(CInput::GetKeyPress(VK_MBUTTON))
	{
		CCamera* camera = CManager::GetScene()->GetGameObject<CCamera>(0);
		camera->CameraMouseRotate();
	}

	//�f���[�g�L�[�őI�����Ă���I�u�W�F�N�g�폜
	if (CInput::GetKeyTrigger(VK_DELETE))
	{
		if (!m_EditGameObject) return;
		m_EditGameObject->SetDestroy();
	}

	//1�L�[�Ŕz�u���[�h
	if (CInput::GetKeyTrigger('1'))
	{
		if (m_modechip[0]->GetSelectMode() == false)
		{
			m_modechip[0]->SetMode();
			m_modechip[1]->SetMode();
			NowMode = 0;	//���[�h�Z�b�g
		}
	}
	//2�L�[�ŕҏW���[�h
	if (CInput::GetKeyTrigger('2'))
	{
		if (m_modechip[1]->GetSelectMode() == false)
		{
			m_modechip[1]->SetMode();
			m_modechip[0]->SetMode();
			NowMode = 1;	//���[�h�Z�b�g
		}
	}

	//�}�E�X�z�C�[��
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
	GetCursorPos(&pos);		//���݂̃J�[�\���̃|�W�V�����擾
	ScreenToClient(GetWindow(), &pos);

	for (int i = 0; i < 2; i++)
	{
		//�{�^�����N���b�N����Ă���
		if (m_modechip[i]->Colision(pos) == true && NowMode != i)
		{
			m_modechip[i]->SetMode();
			m_modechip[1 - i]->SetMode();

			NowMode = i;	//���[�h�Z�b�g

			m_EditGameObject = nullptr;	//�ҏW���[�h�ŃI�u�W�F�N�g�폜���ă��[�h�ύX����ƃN���b�V������̂�

			return true;
		}
	}

	return false;
}

bool CSelectItem::ClickItemBox()
{
	POINT pos;
	GetCursorPos(&pos);		//���݂̃J�[�\���̃|�W�V�����擾
	ScreenToClient(GetWindow(), &pos);

	//�J�[�\�����{�b�N�X�͈̔͊O�������烋�[�v������
	if (pos.x < m_Position.x + min.x)return false;
	if (pos.x > m_Position.x + max.x)return false;
	if (pos.y < m_Position.y + min.y)return false;
	if (pos.y > m_Position.y + max.y)return false;

	m_EditGameObject = nullptr;	//�ҏW���[�h�ŃI�u�W�F�N�g�폜���ăA�C�e���{�b�N�X���N���b�N����ƃN���b�V������̂�

	//�`�b�v�̓����蔻��
		//�c����
	for (int h = 0; h < ITEMCHIPY; h++)
	{
		//������
		for (int w = 0; w < ITEMCHIPX; w++)
		{
			if (m_chip[h][w]->Colision(pos) == true)
			{
				m_pointer->SetPos(D3DXVECTOR2((float)w, (float)h));	//�|�C���^�[�̈ʒu���J�[�\�����������Ƃ����
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
				m_EditGameObject = gameobject;	//m_EditGameObject�ɃN���b�N���ꂽ�I�u�W�F�N�g�̃|�C���^�N���X������
				return;
			}
		}
	}
}

void CSelectItem::WorldObject()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	//�I�u�W�F�N�g�̐ݒu�������Ȃ�
	//�I�������I�u�W�F�N�g�Ŕz�u�I�u�W�F�N�g�ύX
	switch (m_chip[(int)m_pointer->GetPos().y][(int)m_pointer->GetPos().x]->GetId())
	{
	case 0:
		//������(�v���C���[�͈�l�������݂��Ȃ�)
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

	//���ʂ��镨

	ImGui::SliderFloat("rotation", &m_Rotation.y, 0, 10);
	ImGui::SliderFloat("scale", &m_Scale.x, 0, 10);

	switch (m_chip[(int)m_pointer->GetPos().y][(int)m_pointer->GetPos().x]->GetId())
	{
	case 0:		//�v���C���[
		//���f���ύX�������ł����Ȃ�����
		break;
	case 1:		//�G
		ImGui::Checkbox("Enemy", &isEnemy);
		break;
	case 2:		//���_
		//����̉~�̑傫����ύX������
		break;
	case 3:		//�͂��
		//�����z�u���s������
		//�~��\�����Ă��͈͓̔��ŗ����z�u���s������
		break;
	case 4:		//��
		//�����z�u���s������
		//�~��\�����Ă��͈͓̔��ŗ����z�u���s������
		break;
	case 5:		//����
		//���f���ύX�������Ȃ�����
		break;
	case 6:		//�X�|�[���|�C���g
		//�X�|�[�������ύX���s������
		break;
	default:	//����ȊO
		break;
	}

	
	ImGui::End();
}