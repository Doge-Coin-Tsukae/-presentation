#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "light.h"
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
	CRenderer::Begin();


	//�J����->3D�|���S��->2D�|���S���̏��Ԃŕ`�悷��
	m_Scene->Draw();

	CFADE::Draw();

	CRenderer::End();
}
