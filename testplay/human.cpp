//****************************************
//����NPC
//****************************************

////#include "main.h"
////#include "renderer.h"
////#include "scene.h"
////#include "manager.h"
////#include "sound.h"
////#include "model.h"
////#include "camera.h"
////#include "Vector.h"
////#include "model.h"
////#include "animationmodel.h"
////#include "sight.h"
////#include "weapon.h"
////#include "rifle.h"
////#include "colider.h"
////#include "meshfield.h"
//#include "human.h"
//
//
////class CAnimationModel* Human::m_Animodel;
//
//#define		ANIMEBLENDSPEED	0.1f
//
//typedef struct
//{
//	char* pFilename;	// �t�@�C����
//} ANIMENAME4;
//
//ANIMENAME4 g_aParam2[5] =
//{
//	{(char*)"idle"},				// �ҋ@
//	{(char*)"ready"},				// �\����
//	{(char*)"run"},				// ����
//	{(char*)"fire"},				//����
//	{(char*)"Death"},
//};
//
//void Human::Load()
//{
//	//m_Animodel = new CAnimationModel();
//	//m_Animodel->Load("asset\\model\\player\\chara.fbx");					//���f���̃��[�h(�{�[���t��)
//	//m_Animodel->LoadAnimation("asset\\model\\player\\idle.fbx", g_aParam2[0].pFilename);		//�A�j���[�V����
//	//m_Animodel->LoadAnimation("asset\\model\\player\\ready.fbx", g_aParam2[1].pFilename);		//�A�j���[�V����
//	//m_Animodel->LoadAnimation("asset\\model\\player\\run.fbx", g_aParam2[2].pFilename);		//�A�j���[�V����
//	//m_Animodel->LoadAnimation("asset\\model\\player\\fire.fbx", g_aParam2[3].pFilename);
//	//m_Animodel->LoadAnimation("asset\\model\\player\\Death.fbx", g_aParam2[4].pFilename);
//}
//
//void Human::Unload()
//{
//	//m_Animodel->Unload();
//	//delete m_Animodel;
//}
//
//void Human::Init()
//{
//	//m_Sight = new CSIGHT();
//	//m_Sight->Init();
//	//m_Sight->Setparent(this);		//�Ə��̐e��������
//
//	//m_Weapon = new Crifle();
//	//m_Weapon->Init();
//	//m_Weapon->Setparent(this);		//����̐e��������
//
//	//m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	//m_ModelRot = D3DXVECTOR3(1.6f, 0.0f, 0.0f);
//	//m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	//m_Scale = D3DXVECTOR3(1.3f, 1.3f, 1.3f);
//	//m_TeamNumber = TEAM_FRIENDRY;		//�`�[���ݒ�
//
//	////�A�j���[�V����
//	//m_NowAnimationChara = g_aParam2[0].pFilename;
//	//m_OldAnimationChara = g_aParam2[1].pFilename;
//	//m_Frame = 0;
//	//rate = 0;
//}
//
//void Human::Uninit()
//{
//	//m_Weapon->Uninit();
//	//delete m_Weapon;
//
//	//m_Sight->Uninit();
//	//delete m_Sight;
//}
//
//void Human::Update()
//{
//	//rate = std::min(rate, 1.0f);
//	//rate = std::max(rate, 0.0f);
//
//	////�w���p�[�֐�
//	//Update_AI();
//	////�v���C���[�ɓ����Ă���N���X�̍X�V����
//	//m_Sight->Update();
//	//m_Weapon->Update();
//
//	//rate += ANIMEBLENDSPEED;
//	//m_Frame += 0.3f;
//
//	////���񂾎��̏���
//	//if (m_Death == true)
//	//{
//	//	m_OldAnimationChara = (char*)"Death";
//	//	m_NowAnimationChara = (char*)"Death";
//
//	//	m_Frame += 0.7f;
//	//	if (m_Frame > 177)	//���̃t���[�����ɒB�����烏�[���h����폜
//	//		SetDestroy();
//	//}
//
//	////���b�V���t�B�[���h�����擾
//	//CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
//	//m_Position.y = meshField->GetHeight(m_Position);
//}
//
//void Human::Draw()
//{
//	//CScene* scene = CManager::GetScene();
//	//CCamera* camera = scene->GetGameObject <CCamera>(0);
//
//	////��ʊO�ɂ���l�͕`�悵�Ȃ�
//	//if (!camera->CheckView(m_Position))
//	//	return;
//
//	////�����N���X����
//	////m_Weapon->Draw();
//	//m_Sight->Draw();
//
//	////�}�g���N�X�ݒ�
//	//D3DXMATRIX world, scale, rot, trans;
//	////�g��k���̃}�g���N�X
//	//D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
//	////���[�s�b�`���[���̃}�g���N�X
//	//D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x + m_ModelRot.x, -m_Rotation.z - m_ModelRot.z, m_Rotation.y + m_ModelRot.y);
//	////�ʒu�}�g���N�X6
//	//D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
//	//world = scale * rot * trans;
//	//CRenderer::SetWorldMatrix(&world);
//
//	//m_Animodel->Update(m_OldAnimationChara, m_NowAnimationChara, m_Frame, rate);
//	//m_Animodel->Draw();
//}
//
//void Human::ChangeAnimation(char* Name)
//{
//	//if (m_NowAnimationChara == Name)return;	//���̃A�j���[�V�����Ǝ��̃A�j���[�V�������ꏏ�Ȃ�
//	//m_OldAnimationChara = m_NowAnimationChara;		//�V�����A�j���[�V�����f�[�^���Â��A�j���[�V�����f�[�^�ɂ���
//	//m_NowAnimationChara = Name;						//�V�����A�j���[�V�����f�[�^������
//	//rate = 0.0f;									//�u�����h�l�����Z�b�g
//}
//
//void Human::Death()
//{
//	//if (m_Death == true) return;
//	//PlaySound(SOUND_SE_DEATH);
//	//m_Death = true;
//	//m_Frame = 1;
//}