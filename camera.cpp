//=====================================
//
//	�J����
//  written by Y.Okubo
//
//=====================================
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "Vector.h"
#include "model.h"
#include "input.h"

#include "human.h"
#include "animationmodel.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "player.h"
#include"camera.h"

void CCamera::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 3.0f, -150.0f);
	m_Target = D3DXVECTOR3(1.0f, 3.0f, -150.0f);
	m_zoom = false;
}

void CCamera::Uninit()
{

}

void CCamera::Update()
{
	//�v���C���[�擾
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	if (!pPlayer) return;		//�v���C���[��񂪂Ȃ��Ƃ��͏������s��Ȃ�

	Target_Player();		//�v���C���[��ǂ�������
	BackFront_Player();		//�v���C���[�̌��ɉ�荞�ނ悤�ɂ���
	Zoom_Player();			//�Y�[��
}
void CCamera::Target_Player()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	m_Target = pPlayer->GetPosition();		//�����_���v���C���[��
	m_Target.y += 8.0f;						//�J�������������
}
void CCamera::BackFront_Player()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	m_Position.x = m_Target.x + 12.0f *cos(pPlayer->GetRotation().y)*cos(pPlayer->GetRotation().x);	//���W
	m_Position.y = m_Target.y + 12.0f *sin(pPlayer->GetRotation().x);
	m_Position.z = m_Target.z + 12.0f *-sin(pPlayer->GetRotation().y)*cos(pPlayer->GetRotation().x);	//���W
}
void CCamera::Zoom_Player()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	if (m_zoom == true)
	{
		m_Target.y -= 3.0f;
		m_Target.x = m_Target.x + 1.4f *sin(pPlayer->GetRotation().y)*cos(pPlayer->GetRotation().x);	//���W
		m_Target.y = m_Target.y + 1.4f *sin(pPlayer->GetRotation().x);
		m_Target.z = m_Target.z + 1.4f *cos(pPlayer->GetRotation().y)*cos(pPlayer->GetRotation().x);	//���W

		m_Position.x = m_Target.x + 4.0f *cos(pPlayer->GetRotation().y)*cos(pPlayer->GetRotation().x);	//���W
		m_Position.y = m_Target.y + 4.0f *sin(pPlayer->GetRotation().x);
		m_Position.z = m_Target.z + 4.0f *-sin(pPlayer->GetRotation().y)*cos(pPlayer->GetRotation().x);	//���W
	}
	else
	{

	}
}
void CCamera::Draw()
{
	//�r���[�}�g���N�X�ݒ�
	D3DXVECTOR3 Draw= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&viewMatrix,&m_Position,&m_Target,&Draw);

	CRenderer::SetViewMatrix(&viewMatrix);		//Direct9��SetTransform�ɋ߂�

	//�v���W�F�N�V�����}�g���N�X�ݒ�
	D3DXMatrixPerspectiveFovLH(&projectionMatrix,1.0f,(float)SCREEN_WIDTH/SCREEN_HEIGHT,1.0f,1000.0f);

	CRenderer::SetProjectionMatrix(&projectionMatrix);
	CRenderer::SetCameraPosition(m_Position);
}

bool CCamera::CheckView(D3DXVECTOR3 Position)
{
	D3DXMATRIX vp, invvp;

	vp = viewMatrix * projectionMatrix;
	D3DXMatrixInverse(&invvp, NULL, &vp);

	D3DXVECTOR3 vpos[4];
	D3DXVECTOR3 wpos[4];

	vpos[0] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vpos[1] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vpos[2] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vpos[3] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	D3DXVec3TransformCoord(&wpos[0], &vpos[0], &invvp);
	D3DXVec3TransformCoord(&wpos[1], &vpos[1], &invvp);
	D3DXVec3TransformCoord(&wpos[2], &vpos[2], &invvp);
	D3DXVec3TransformCoord(&wpos[3], &vpos[3], &invvp);
	//�������4�_�̍��W�����܂�

	if (GetVector(m_Position, Position) >= 200.0f)return false;

	D3DXVECTOR3 v, v1, v2, n;

	v = Position - m_Position;

	//��
	v1 = wpos[0] - m_Position;
	v2 = wpos[2] - m_Position;
	D3DXVec3Cross(&n, &v1, &v2);

	if (D3DXVec3Dot(&n, &v) < 0.0f)
		return false;

	//�E
	v1 = wpos[1] - m_Position;
	v2 = wpos[3] - m_Position;
	D3DXVec3Cross(&n, &v1, &v2);

	if (D3DXVec3Dot(&n, &v) > 0.0f)
		return false;

	//��
	v1 = wpos[0] - m_Position;
	v2 = wpos[1] - m_Position;
	D3DXVec3Cross(&n, &v1, &v2);

	if (D3DXVec3Dot(&n, &v) > 0.0f)
		return false;

	//��
	v1 = wpos[2] - m_Position;
	v2 = wpos[3] - m_Position;
	D3DXVec3Cross(&n, &v1, &v2);

	if (D3DXVec3Dot(&n, &v) < 0.0f)
		return false;


	return true;

}