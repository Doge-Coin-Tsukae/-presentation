#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "light.h"

CLight::CLight()
{
	light.Enable = false;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	CRenderer::SetLight(light);
}
CLight::CLight(D3DXVECTOR4 SDirection, D3DXCOLOR SAmbient, D3DXCOLOR SDiffuse)
{
	light.Enable = false;
	light.Direction = SDirection;
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = SAmbient;
	light.Diffuse = SDiffuse;
	CRenderer::SetLight(light);
}

void CLight::Uninit()
{

}

void CLight::Update()
{

}

void CLight::SetDirection(D3DXVECTOR4 SDirection)
{
	light.Direction = SDirection;
}

void CLight::SetAmbient(D3DXCOLOR SAmbient)
{
	light.Ambient = SAmbient;
}

void CLight::SetDiffuse(D3DXCOLOR SDiffuse)
{
	light.Diffuse = SDiffuse;
}

void CLight::EnableLight()
{
	light.Enable = true;
	CRenderer::SetLight(light);
}

void CLight::DisbleLight()
{
	light.Enable = false;
	CRenderer::SetLight(light);
}