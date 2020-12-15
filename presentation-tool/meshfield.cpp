
#include "main.h"
#include "renderer.h"
#include "meshfield.h"

#define LAND 100		//�l���̋N���̍���
#define SEED 0			//�V�[�h�l�̏����l

#define RANDHIGHT  4.0f		//�_�C�A�����h�X�N�G�A�̋N���̌덷

void CMeshField::Init()
{
	// ���_���W�̐ݒ� (<= FIELDX-1)
	for (int x = 0; x < FIELDX; x++)
	{
		for (int z = 0; z < FIELDY; z++)
		{
			// ���W�̐ݒ�
			m_Vertex[x][z].Position = D3DXVECTOR3((x-10)*5.0f, 0,(z-10)*-5.0f);
			// �@���̐ݒ�
			m_Vertex[x][z].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			// ���_�J���[�̐ݒ�
			m_Vertex[x][z].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			// �e�N�X�`�����W�̐ݒ�
			m_Vertex[x][z].TexCoord = D3DXVECTOR2(x*0.5f, z*0.5f);
		}
	}
	seed = SEED;
	oldseed = seed;
	srand(seed);	//�������Z�b�g

	Automaticallygenerated();

	//�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"asset/texture//moss_light.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);

	//�e�N�X�`���������ĂȂ��Ƃ��A�G���[�����m����
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
	UpdateSeed();
}

void CMeshField::UpdateSeed()
{
	if (seed == oldseed) return;	//�V�[�h�l�ύX����ĂȂ���ΏI��
	srand(seed);	//�������Z�b�g
	Automaticallygenerated();
	oldseed = seed;
}
void CMeshField::Automaticallygenerated()
{
	//�l������
	m_Vertex[0][0].Position.y = rand() % LAND;
	m_Vertex[FIELDX - 1][0].Position.y = rand() % LAND;
	m_Vertex[0][FIELDY - 1].Position.y = rand() % LAND;
	m_Vertex[FIELDX - 1][FIELDY - 1].Position.y = rand() % LAND;


	//�ʂ�(m_vertex.position�ł��ƃG���[���o�邩��)
	float pos[FIELDX][FIELDY];
	for (int x = 0; x < FIELDX; x++)
	{
		for (int z = 0; z < FIELDY; z++)
		{
			pos[x][z] = m_Vertex[x][z].Position.y;
		}
	}

	//�_�C�A�����h�X�N�G�A(���W,2��n��+1)
	CDiamondSquare *DiamondSquare = new CDiamondSquare();
	DiamondSquare->diamondSquare(pos, 129);
	delete DiamondSquare;
	//�ʂ�(���W��߂�)
	for (int x = 0; x < FIELDX; x++)
	{
		for (int z = 0; z < FIELDY; z++)
		{
			m_Vertex[x][z].Position.y = pos[x][z];
		}
	}

	//�@���x�N�g���Z�o
	for (int x = 1; x < FIELDX - 1; x++)
	{
		for (int z = 1; z < FIELDY - 1; z++)
		{
			D3DXVECTOR3 vx, vz, vn;

			vx = m_Vertex[x + 1][z].Position - m_Vertex[x - 1][z].Position;
			vz = m_Vertex[x][z - 1].Position - m_Vertex[x][z + 1].Position;

			D3DXVec3Cross(&vn, &vz, &vx);	//�O��(�|���鏇�ԂɋC��t����)
			D3DXVec3Normalize(&vn, &vn);//���K��(����1�ɂ���)
			m_Vertex[x][z].Normal = vn;
		}
	}

	//���_�o�b�t�@����
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

	// �C���f�b�N�X�o�b�t�@����
	{
		unsigned int index[(FIELDX * 2) * FIELDY - 2];		//�C���f�b�N�X�̐��Ɠ���

		int i = 0;
		for (int x = 0; x < FIELDX - 1; x++)
		{
			for (int z = 0; z < FIELDY; z++)
			{
				index[i] = x * FIELDX + z;
				i++;
				index[i] = (x + 1) * FIELDY + z;
				i++;
			}

			if (x == FIELDX - 1)
				break;
			index[i] = (x + 1) * FIELDX + (FIELDX - 1);
			i++;
			index[i] = (x + 1) * FIELDX;
			i++;

		}
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * (FIELDX * 2) * FIELDY - 2;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	}
}

void CMeshField::Draw()
{

	//�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	//�g��k���̃}�g���N�X
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//���[�s�b�`���[���̃}�g���N�X
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	//�ʒu�}�g���N�X
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot*trans;
	CRenderer::SetWorldMatrix(&world);

	//���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//�C���f�b�N�X�o�b�t�@�ݒ�
	CRenderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer,DXGI_FORMAT_R32_UINT,0);

	//�}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	CRenderer::SetMaterial(material);

	//�e�N�X�`���ݒ�
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//�v���~�e�B�u�g�|���W�ݒ�
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�|���S���`��
	CRenderer::GetDeviceContext()->DrawIndexed((FIELDX * 2) * FIELDY - 2, 0, 0);

	//IMGUI

	ImGui::SetNextWindowSize(ImVec2(320, 100));
	ImGui::Begin("FIELD");
	SetImGui();		//���݃N���b�N���Ă���Q�[���I�u�W�F�N�g�̕ҏW��ʂ��o��
	ImGui::End();

}

void CMeshField::SetImGui()
{
	ImGui::SliderInt("seed", &seed, 0, 1000);
}

void CMeshField::Save(FILE* fp)
{
	fputs("bigin\n", fp);
	fprintf(fp, "%d\n", seed);
	fputs("end\n", fp);
	fputs("\n", fp);
}

float CMeshField::GetHeight(D3DXVECTOR3 Position)
{
	int x, z;

	//�u���b�N�ԍ��Z�o
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
		//����|���S��
		D3DXVECTOR3 v10;
		v10 = pos0 - pos1;
		D3DXVec3Cross(&n, &v10, &v12);
	}
	else
	{
		//�E���|���S��
		D3DXVECTOR3 v13;
		v13 = pos3 - pos1;
		D3DXVec3Cross(&n, &v12, &v13);
	}

	//�����擾
	py = -((Position.x - pos1.x) * n.x + (Position.z - pos1.z)*n.z) / n.y + pos1.y;

	return py;
}



void CDiamondSquare::squareStep(float Array[FIELDX][FIELDY], int x, int z, int reach)
{
	int count = 0;
	float avg = 0.0f;
	if (x - reach >= 0 && z - reach >= 0)
	{
		avg += Array[x - reach][z - reach];
		count++;
	}
	if (x - reach >= 0 && z + reach < FIELDY)
	{
		avg += Array[x - reach][z + reach];
		count++;
	}
	if (x + reach < FIELDX && z - reach >= 0)
	{
		avg += Array[x + reach][z - reach];
		count++;
	}
	if (x + reach < FIELDX && z + reach < FIELDY)
	{
		avg += Array[x + reach][z + reach];
		count++;
	}
	avg += random(reach);
	avg /= count;
	Array[x][z] = round(avg);
}

void CDiamondSquare::diamondStep(float Array[FIELDX][FIELDY], int x, int z, int reach)
{
	int count = 0;
	float avg = 0.0f;
	if (x - reach >= 0)
	{
		avg += Array[x - reach][z];
		count++;
	}
	if (x + reach < FIELDX)
	{
		avg += Array[x + reach][z];
		count++;
	}
	if (z - reach >= 0)
	{
		avg += Array[x][z - reach];
		count++;
	}
	if (z + reach < FIELDY)
	{
		avg += Array[x][z + reach];
		count++;
	}
	avg += random(reach);
	avg /= count;
	Array[x][z] = avg;
}

float CDiamondSquare::random(int range)
{
	return (rand() % (range * 4)) - range;
}

void CDiamondSquare::diamondSquare(float Array[FIELDX][FIELDY], int size)
{
	int half = size / 2;
	if (half < 1)
		return;
	//square steps
	for (int z = half; z < FIELDY; z += size)
		for (int x = half; x < FIELDX; x += size)
			squareStep(Array, x % FIELDX, z % FIELDY, half);
	// diamond steps
	int col = 0;
	for (int x = 0; x < FIELDX; x += half)
	{
		col++;
		//If this is an odd column.
		if (col % 2 == 1)
			for (int z = half; z < FIELDY; z += size)
				diamondStep(Array, x % FIELDX, z % FIELDY, half);
		else
			for (int z = 0; z < FIELDY; z += size)
				diamondStep(Array, x % FIELDX, z % FIELDY, half);
	}
	diamondSquare(Array, size / 2);
}