#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "sound.h"
#include "input.h"
#include "gamemaneger.h"
#include "Game.h"
#include "Title.h"
#include "fade.h"

CScene* CManager::m_Scene = NULL;

void CManager::Init()
{
	ShowCursor(FALSE);	//�J�[�\��������

	CRenderer::Init();
	CInput::Init();
	CFADE::Init();
	InitSound(GetWindow());

	SetScene<CTitle>();
}

void CManager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;
	
	UninitSound();
	CFADE::Uninit();
	CInput::Uninit();
	CRenderer::Uninit();
}

void CManager::Update()
{
	CInput::Update();
	CFADE::Update();
	m_Scene->Update();
}

void CManager::Draw()
{

	LIGHT light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 0.5f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//-----------���C�g���J�����Ƃ݂Ȃ����s����쐬
	D3DXVECTOR3 pEye(350.0f, 10.0f, -200.0f), pAt(0.0f, 0.0f, 0.0f), pUp(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&light.ViewMatrix, &pEye,
		&pAt, &pUp);
	//-----------���C�g�p�̃v���W�F�N�V�����s����쐬
	D3DXMatrixPerspectiveFovLH(&light.ProjectionMatrix, 1.0f,
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, 5.0f, 30.0f);
	CRenderer::SetLight(light);
	CRenderer::BeginDepth();//�ǉ�-�V���h�E�o�b�t�@��[�x�o�b�t�@�֐ݒ蓙
	CRenderer::SetViewMatrix(&light.ViewMatrix);//�ǉ�-�J�����փ��C�g�p�s��Z�b�g
	CRenderer::SetProjectionMatrix(&light.ProjectionMatrix);//�ǉ�-�v���W�F�N�V�����փ��C�g�p�s����Z�b

	m_Scene->ShadowDraw();

	CRenderer::Begin();

	//�J����->3D�|���S��->2D�|���S���̏��Ԃŕ`�悷��
	m_Scene->Draw();

	CFADE::Draw();

	CRenderer::End();
}
