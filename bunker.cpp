#include "main.h"
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "model.h"
#include "camera.h"
#include "meshfield.h"
#include "colider.h"
#include "bunker.h"

class CModel* CBUNKER::m_Model;

void CBUNKER::Load()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\bunker.obj");
}

void CBUNKER::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void CBUNKER::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_Colider.Init(m_Position + D3DXVECTOR3(-10.0f, 0.0f, -8.0f), m_Position+ D3DXVECTOR3(10.0f, 2.0f, 8.0f), m_Position);

	CRenderer::CreateVertexShader(&m_VertexShader[0], &m_VertexLayout,"vertexShader.cso");

	//ピクセルシェーダーファイルのロード＆オブジェクト作成
	CRenderer::CreatePixelShader(&m_PixelShader[0],"pixelShader.cso");

	CRenderer::CreateVertexShader(&m_VertexShader[1], &m_VertexLayout, "vertexShader.cso");

	//ピクセルシェーダーファイルのロード＆オブジェクト作成
	CRenderer::CreatePixelShader(&m_PixelShader[1], "pixelShader.cso");
}

void CBUNKER::Uninit()
{
}
void CBUNKER::Update()
{
	m_Colider.update(m_Position);

	//メッシュフィールド高さ取得
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);

}
void CBUNKER::Draw()
{
	CScene* scene = CManager::GetScene();
	CCamera* camera = scene->GetGameObject <CCamera>(0);

	if (!camera->CheckView(m_Position))
		return;

	//インプットレイアウトのセット(DirectXへ頂点の構造を教える)
	CRenderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	//バーテックスシェーダーオブジェクトのセット
	CRenderer::GetDeviceContext()->VSSetShader(m_VertexShader[0], NULL, 0);
	//ピクセルシェーダーオブジェクトのセット
	CRenderer::GetDeviceContext()->PSSetShader(m_PixelShader[0], NULL, 0);

	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans, shadow, modelshadow;
	//拡大縮小のマトリクス
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//ヨーピッチロールのマトリクス
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	//位置マトリクス
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	CRenderer::SetWorldMatrix(&world);

	ID3D11ShaderResourceView* shadowDepthTexture = CRenderer::GetShadowDepthTexture();//-追加
	CRenderer::GetDeviceContext()->PSSetShaderResources(1, 1, &shadowDepthTexture);//-追加

	m_Model->Draw();

	//インプットレイアウトのセット(DirectXへ頂点の構造を教える)
	CRenderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	//バーテックスシェーダーオブジェクトのセット
	CRenderer::GetDeviceContext()->VSSetShader(m_VertexShader[1], NULL, 0);
	//ピクセルシェーダーオブジェクトのセット
	CRenderer::GetDeviceContext()->PSSetShader(m_PixelShader[1], NULL, 0);

}

void CBUNKER::Load(FILE*fp, int line)
{
	for (int i = 0; i < line * 3; i++)
	{
		fscanf(fp, "");
	}

	fscanf(fp, "%f%f%f", &m_Position.x, &m_Position.y, &m_Position.z);
	fscanf(fp, "%f%f%f", &m_Rotation.x, &m_Rotation.y, &m_Rotation.z);
	fscanf(fp, "%f%f%f", &m_Scale.x, &m_Scale.y, &m_Scale.z);
}