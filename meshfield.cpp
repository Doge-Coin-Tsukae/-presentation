
#include "main.h"
#include "renderer.h"
#include "meshfield.h"

#define LAND 30

float g_FieldHeight[FIELDX][FIELDY] =
{
	{ 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,},
	{ 2.0f, 2.0f, 2.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,},
	{-1.0f,-1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,},
	{-3.0f,-3.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 0.0f, 0.0f, 0.0f,},
	{-5.0f,-5.0f,-3.0f,-3.0f,-3.0f,-3.0f,-3.0f,-3.0f,-3.0f,-3.0f,-3.0f,-3.0f,-3.0f,-3.0f,-1.0f,-1.0f,-1.0f, 2.0f, 2.0f, 2.0f, 0.0f,},
	{-3.0f,-3.0f,-5.0f,-5.0f,-5.0f,-5.0f,-5.0f,-5.0f,-5.0f,-5.0f,-5.0f,-5.0f,-5.0f,-5.0f,-3.0f,-3.0f,-3.0f,-1.0f,-1.0f,-1.0f, 2.0f,},
	{-1.0f,-1.0f,-3.0f,-3.0f,-3.0f,-3.0f,-3.0f,-3.0f,-3.0f,-3.0f,-3.0f,-3.0f,-3.0f,-3.0f,-5.0f,-5.0f,-5.0f,-3.0f,-3.0f,-3.0f,-1.0f,},
	{2.0f,  1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-3.0f,-3.0f,-3.0f,-5.0f,-5.0f,-5.0f,-3.0f,},
	{0.0f,  2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f,-1.0f,-1.0f,-1.0f,-3.0f,-3.0f,-3.0f,-5.0f,},
	{0.0f,  0.0f, 2.0f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 2.0f, 2.0f, 2.0f,-1.0f,-1.0f,-1.0f,-3.0f,},
	{0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f,-1.0f,},
	{0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 2.0f,},
	{0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,},
	{0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,},
	{0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,},
	{0.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,},
	{0.0f,  1.0f, 3.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,},
	{0.0f,  1.0f, 10.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,},
	{0.0f,  1.0f, 10.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,},
	{0.0f,  1.0f, 3.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,},
	{0.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,},
};

void CMeshField::Init()
{
	// 頂点座標の設定 (<= FIELDX-1)
	for (int x = 0; x < FIELDX; x++)
	{
		for (int z = 0; z < FIELDY; z++)
		{
			float y = g_FieldHeight[z][x];
			//数式で設定
			/*float px, pz;
			px = (x - 10) * 5.0f;
			pz = (z - 10) * -5.0f;

			float y = sinf(x*px) *sinf(z*pz)* 5.0f;*/

			// 座標の設定
			m_Vertex[x][z].Position = D3DXVECTOR3((x-10)*5.0f, 0,(z-10)*-5.0f);
			// 法線の設定
			m_Vertex[x][z].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			// 頂点カラーの設定
			m_Vertex[x][z].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			// テクスチャ座標の設定
			m_Vertex[x][z].TexCoord = D3DXVECTOR2(x*0.5f, z*0.5f);
		}
	}
	int seed = 1;
	srand(seed);	//乱数リセット

	m_Vertex[0][0].Position.y = rand()% LAND;
	m_Vertex[FIELDX - 1][0].Position.y = rand() % LAND;
	m_Vertex[0][FIELDY - 1].Position.y = rand() % LAND;
	m_Vertex[FIELDX - 1][FIELDY - 1].Position.y = rand() % LAND;


	TyutenHenni(FIELDX /2 -1 ,FIELDY /2 -1);	//中点変位法

	//法線ベクトル算出
	for (int x = 1; x <= 19; x++)
	{
		for (int z = 1; z <= 19; z++)
		{
			D3DXVECTOR3 vx, vz, vn;

			vx = m_Vertex[x + 1][z].Position - m_Vertex[x - 1][z].Position;
			vz = m_Vertex[x][z - 1].Position - m_Vertex[x][z + 1].Position;

			D3DXVec3Cross(&vn,&vz,&vx);	//外積(掛ける順番に気を付ける)
			D3DXVec3Normalize(&vn, &vn);//正規化(長さ1にする)
			m_Vertex[x][z].Normal = vn;
		}
	}

	//頂点バッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * FIELDX*FIELDY;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = m_Vertex;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}

	// インデックスバッファ生成
	{
		unsigned int index[(22 * 2) * 20 - 2];		//インデックスの数と同じ

		int i = 0;
		for (int x = 0; x < FIELDX-1; x++)
		{
			for (int z = 0; z < FIELDY; z++)
			{
				index[i] = x * FIELDX + z;
				i++;
				index[i] = (x + 1) * FIELDY + z;
				i++;
			}

			if (x == 19)
				break;
			index[i] = (x + 1) * 21 + 20;
			i++;
			index[i] = (x + 1) * 21;
			i++;

		}
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * (22*2) * 20 -2;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	}

	//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"asset/texture//moss_light.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);

	//テクスチャが張ってないとき、エラーを検知する
	assert(m_Texture);

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void CMeshField::Uninit()
{
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_Texture->Release();
}

void CMeshField::Update()
{

}

void CMeshField::Draw()
{
	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	//拡大縮小のマトリクス
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//ヨーピッチロールのマトリクス
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	//位置マトリクス
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot*trans;
	CRenderer::SetWorldMatrix(&world);

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//インデックスバッファ設定
	CRenderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer,DXGI_FORMAT_R32_UINT,0);

	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	CRenderer::SetMaterial(material);

	//テクスチャ設定
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//プリミティブトポロジ設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	CRenderer::GetDeviceContext()->DrawIndexed((22 * 2) * 20 - 2, 0, 0);
}

float CMeshField::GetHeight(D3DXVECTOR3 Position)
{
	int x, z;

	//ブロック番号算出
	x = Position.x / 5.0f + 10.0f;
	z = Position.z / -5.0f + 10.0f;

	D3DXVECTOR3 pos0, pos1, pos2, pos3;

	pos0 = m_Vertex[x][z].Position;
	pos1 = m_Vertex[x + 1][z].Position;
	pos2 = m_Vertex[x][z + 1].Position;
	pos3 = m_Vertex[x + 1][z + 1].Position;

	D3DXVECTOR3 v12, v1p, c;

	v12 = pos2 - pos1;
	v1p = Position - pos1;

	D3DXVec3Cross(&c, &v12, &v1p);

	float py;
	D3DXVECTOR3 n;

	if (c.y > 0.0f)
	{
		//左上ポリゴン
		D3DXVECTOR3 v10;
		v10 = pos0 - pos1;
		D3DXVec3Cross(&n, &v10, &v12);
	}
	else
	{
		//右下ポリゴン
		D3DXVECTOR3 v13;
		v13 = pos3 - pos1;
		D3DXVec3Cross(&n, &v12, &v13);
	}

	//高さ取得
	py = -((Position.x - pos1.x) * n.x + (Position.z - pos1.z)*n.z) / n.y + pos1.y;

	return py;
}

void CMeshField::TyutenHenni(int centerx ,int centery)
{
	if (centerx >= FIELDX)return;
	if (centery >= FIELDY)return;
	if(m_Vertex[centerx][centery].Position.y != 0.0f) return;	//その点が変更済みの場合
	float pos[4];		//四隅

	int sx, sy;
	sx = centerx;
	sy = centery;

	if (FIELDX < sx)
	{
		sx -= FIELDX;
	}
	if (FIELDY < sy)
	{
		sy -= FIELDY;
	}

	//pos[0] = m_Vertex[centerx - sx][centery - sy].Position.y;
	//pos[1] = m_Vertex[centerx + sx][centery - sy].Position.y;
	//pos[2] = m_Vertex[centerx - sx][centery + sy].Position.y;
	//pos[3] = m_Vertex[centerx + sx][centery + sy].Position.y;



	/*int ry = (pos[0] + pos[1] + pos[3] + pos[4]) / 4;
	ry += rand() % LAND;*/
	int ry = rand() % LAND;
	m_Vertex[centerx][centery].Position.y = ry;

	//再帰呼び出し
	TyutenHenni(centerx -sx/2, centery -sy/ 2);
	TyutenHenni(centerx + (sx / 2), centery -sy/ 2);
	TyutenHenni(centerx -sx/ 2, centery + (sy/ 2));
	TyutenHenni(centerx + (sx / 2), centery + (sy / 2));

}