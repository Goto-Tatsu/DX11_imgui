/*==============================================================================


														 Author : Tatsuki Goto
														 Date   : 2019/06/04
--------------------------------------------------------------------------------
==============================================================================*/

#include "main.h"
#include "gameobject.h"
#include "texture.h"
#include "field.h"


float g_Rotation;
float g_Scale;



void CField::Init()
{
	/* ���_�΂��ӂ��`���� */
	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(300.0f, 300.0f, 10.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(300.0f, 300.0f, 10.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(300.0f, 300.0f, 2.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(300.0f, 300.0f, 2.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	// �΂��ӂ��ɂ����Ă�
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// ���_�o�b�t�@
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_pVertexBuffer);
	/* ���_�΂��ӂ��`��������� */

	// �e�N�X�`����݂���
	m_Texture = new CTexture();
	m_Texture->Load("asset/number.tga");

}

void CField::Init(const char * TexName)
{
	// ���_�o�b�t�@��Index�o�b�t�@�̐ݒ�
	m_xCnt = FIELD_X;		//���̕�����
	m_zCnt = FIELD_Z;		//�c�̕�����
	vertexCnt = (FIELD_X + 1) * (FIELD_Z + 1);	//���_�̐�
	returnCnt = FIELD_Z - 1;					//�܂�Ԃ��̉�

	// �e�N�X�`����݂���
	m_Texture = new CTexture();
	m_Texture->Load(TexName);

	/* ���_�΂��ӂ��`���� */
	VERTEX_3D* pVertex;
	pVertex = new VERTEX_3D[vertexCnt];
	for (int j = 0; j <= FIELD_Z; j++) {
		for (int i = 0; i <= FIELD_X; i++) {
			pVertex[i + (FIELD_X + 1) * j].Position = XMFLOAT3(-(FIELD_X * FIELD_SIZE) / 2 + FIELD_SIZE * i, 0.0f, -(FIELD_Z * FIELD_SIZE) / 2 + FIELD_SIZE * j);
			pVertex[i + (FIELD_X + 1) * j].TexCoord = XMFLOAT2(pVertex[i + (FIELD_X + 1) * j].Position.x / m_xCnt, pVertex[i + (FIELD_X + 1) * j].Position.z / m_zCnt);
		}
	}
	for (int i = 0; i < vertexCnt; i++) {
		pVertex[i].Diffuse = XMFLOAT4(128, 128, 255, 150);
		pVertex[i].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	}

	// �΂��ӂ��ɂ����Ă�
	// ���_�o�b�t�@�̐���
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * (FIELD_X + 1) * (FIELD_Z + 1);
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// ���_�o�b�t�@
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pVertex;
		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_pVertexBuffer);
	}


	WORD* pIndex = new WORD[((FIELD_X + 1) * 2 + 2) * FIELD_Z - 2];
	int w = FIELD_X + 1;
	for (int j = 0; j < FIELD_Z; j++)
	{
		if (j != 0)
		{
			//w * j * 2 = �O��܂ł̐܂�Ԃ��������C���f�b�N�X��
			//(j - 1) * 2�@= �O��܂ł̐܂�Ԃ����̃C���f�b�N�X��
			pIndex[(w * j * 2) + ((j - 1) * 2)] = (j + 1) * w - 1;	//�E�Ӂ@�� * w = �����܂ł̒��_�f�[�^
			pIndex[(w * j * 2) + ((j - 1) * 2) + 1] = j * w;
		}

		for (int i = 0; i < w; i++)
		{
			pIndex[(w * j * 2) + (i * 2) + (j * 2)] = (j * w) + i;	//w * j * 2 = �O��܂ł̐܂�Ԃ��������C���f�b�N�X��
			//j * 2�@���@�O��܂ł̐܂�Ԃ����̃C���f�b�N�X��
			pIndex[(w * j * 2) + (i * 2 + 1) + (j * 2)] = (j * w) + i + w;
		}
	}

	// Index�o�b�t�@�̐���
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(WORD) * ((FIELD_X + 1) * 2 + 2) * FIELD_Z - 2;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pIndex;

		if (FAILED(CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_pIndexBuffer)))
			return;
	}

	delete[]pIndex;
	/* ���_�΂��ӂ��`��������� */

}

void CField::Init(const float PosX, const float PosY, const float PosZ, const float ScaleX, const float ScaleY, const float ScaleZ, const char * TexName)
{
	/* ���_�΂��ӂ��`���� */
	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(PosX, PosY, PosZ);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(PosX + ScaleX, PosY, PosZ);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(PosX, PosX + ScaleY, PosZ);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(PosX + ScaleX, PosY + ScaleY, PosZ);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	// �΂��ӂ��ɂ����Ă�
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// ���_�o�b�t�@
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_pVertexBuffer);
	/* ���_�΂��ӂ��`��������� */

	// �e�N�X�`����݂���
	m_Texture = new CTexture();
	m_Texture->Load(TexName);
}


void CField::Uninit()
{
	m_pVertexBuffer->Release();	// ���傤�Ă�΂��ӂ��΂��΂�
	m_pIndexBuffer->Release();
	m_Texture->Unload();		// ��񂾂Ă�������΂��΂�
	delete m_Texture;			// ������̂΂��΂�
}


void CField::Update()
{
	g_Rotation += 0.01f;
}

void ScalePlus() {
	g_Scale += 0.1f;
}

void ScaleMinus() {
	g_Scale -= 0.1f;
}


void CField::Draw()
{
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);		// ���_�o�b�t�@�ݒ�
	CRenderer::GetDeviceContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	CRenderer::SetTexture(m_Texture);

	// SetWorldViewProjection2D�̑���
	//XMMATRIX world;
	//world = XMMatrixScaling(1.0f, 1.0f, 1.0f);					// �g��k��
	//world *= XMMatrixRotationRollPitchYaw(0.0f, g_Rotation, 0.0f);	// ��](���W�A���p�x)
	//world *= XMMatrixTranslation(0.0f, 0.0f, 0.0f);				// �ړ�
	//CRenderer::SetWorldMatrix(&world);							

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	// �g�|���W�[(�ǂ�����Ĕz�u���邩)�ݒ�
	CRenderer::GetDeviceContext()->DrawIndexed(((FIELD_X + 1) * 2 + 2) * FIELD_Z - 2, 0, 0);
}

void CField::Draw(const float ScaleX, const float ScaleY, const float ScaleZ, const float RotX, const float RotY, const float RotZ, const float MoveX, const float MoveY, const float MoveZ)
{
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);		// ���_�o�b�t�@�ݒ�
	CRenderer::SetTexture(m_Texture);

	// SetWorldViewProjection2D�̑���
	XMMATRIX world;
	world = XMMatrixScaling(1.0f * ScaleX, 1.0f * ScaleY, 1.0f * ScaleZ);					// �g��k��
	world *= XMMatrixRotationRollPitchYaw(RotX, RotY + g_Rotation, RotZ);	// ��](���W�A���p�x)
	world *= XMMatrixTranslation(MoveX, MoveY, MoveZ);				// �ړ�
	CRenderer::SetWorldMatrix(&world);

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	// �g�|���W�[(�ǂ�����Ĕz�u���邩)�ݒ�
	CRenderer::GetDeviceContext()->Draw(4, 0);
}

void Vertex_Index_Config()
{
	CField* pField;
	pField = new CField();

	pField->m_xCnt = FIELD_X;		//���̕�����
	pField->m_zCnt = FIELD_Z;		//�c�̕�����
	pField->vertexCnt = (FIELD_X + 1) * (FIELD_Z + 1);	//���_�̐�
	pField->returnCnt = FIELD_Z - 1;					//�܂�Ԃ��̉�

	g_Rotation = 0.0f;
	g_Scale = 1.0;

	/* ���_�΂��ӂ��`���� */
	VERTEX_3D* pVertex;
	pVertex = new VERTEX_3D[pField->vertexCnt];
	for (int j = 0; j <= FIELD_Z; j++) {
		for (int i = 0; i <= FIELD_X; i++) {
			pVertex[i + (FIELD_X + 1) * j].Position = XMFLOAT3(-(FIELD_X * FIELD_SIZE) / 2 + FIELD_SIZE * i, 0.0f, -(FIELD_Z * FIELD_SIZE) / 2 + FIELD_SIZE * j);
		}
	}
	for (int i = 0; i < pField->vertexCnt; i++) {
		pVertex[i].Diffuse = XMFLOAT4(128, 128, 255, 255);
		pVertex[i].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	}

	// �΂��ӂ��ɂ����Ă�
	// ���_�o�b�t�@�̐���
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * (FIELD_X + 1) * (FIELD_Z + 1);
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// ���_�o�b�t�@
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pVertex;
		//CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_pVertexBuffer);
	}


	WORD* pIndex = new WORD[((FIELD_X + 1) * 2 + 2) * FIELD_Z - 2];
	int w = FIELD_X + 1;
	for (int j = 0; j < FIELD_Z; j++)
	{
		if (j != 0)
		{
			//w * j * 2 = �O��܂ł̐܂�Ԃ��������C���f�b�N�X��
			//(j - 1) * 2�@= �O��܂ł̐܂�Ԃ����̃C���f�b�N�X��
			pIndex[(w * j * 2) + ((j - 1) * 2)] = (j + 1) * w - 1;	//�E�Ӂ@�� * w = �����܂ł̒��_�f�[�^
			pIndex[(w * j * 2) + ((j - 1) * 2) + 1] = j * w;
		}

		for (int i = 0; i < w; i++)
		{
			pIndex[(w * j * 2) + (i * 2) + (j * 2)] = (j * w) + i;	//w * j * 2 = �O��܂ł̐܂�Ԃ��������C���f�b�N�X��
			//j * 2�@���@�O��܂ł̐܂�Ԃ����̃C���f�b�N�X��
			pIndex[(w * j * 2) + (i * 2 + 1) + (j * 2)] = (j * w) + i + w;
		}
	}

	// Index�o�b�t�@�̐���
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(WORD) * ((FIELD_X + 1) * 2 + 2) * FIELD_Z - 2;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pIndex;

		if (FAILED(CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &pField->m_pIndexBuffer)))
			return;
	}

	delete[]pIndex;
	/* ���_�΂��ӂ��`��������� */

}
void Vertex_Index_Config(float size, int field_x, int field_z)
{
	CField* pField;
	pField = new CField();

	pField->m_xCnt = FIELD_X;		//���̕�����
	pField->m_zCnt = FIELD_Z;		//�c�̕�����
	pField->vertexCnt = (FIELD_X + 1) * (FIELD_Z + 1);	//���_�̐�
	pField->returnCnt = FIELD_Z - 1;					//�܂�Ԃ��̉�


	// �C���f�b�N�X��
	WORD IndexList[]{
		0, 1, 2,
		2, 3, 1,
	};

	g_Rotation = 0.0f;
	g_Scale = 1.0;

	/* ���_�΂��ӂ��`���� */
	VERTEX_3D* pVertex;
	pVertex = new VERTEX_3D[pField->vertexCnt];

	for (int j = 0; j <= FIELD_Z; j++) {
		for (int i = 0; i <= FIELD_X; i++) {
			pVertex[i + (FIELD_X + 1) * j].Position = XMFLOAT3(-(FIELD_X * FIELD_SIZE) / 2 + FIELD_SIZE * i, 0.0f, -(FIELD_Z * FIELD_SIZE) / 2 + FIELD_SIZE * j);
		}
	}

	for (int i = 0; i < pField->vertexCnt; i++) {
		pVertex[i].Diffuse = XMFLOAT4(128, 128, 255, 255);
		pVertex[i].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	}

	// �΂��ӂ��ɂ����Ă�
	// ���_�o�b�t�@�̐���
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * pField->vertexCnt;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// ���_�o�b�t�@
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pVertex;
		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &pField->m_pVertexBuffer);
	}


	WORD* pIndex = new WORD[((FIELD_X + 1) * 2 + 2) * FIELD_Z - 2];
	int w = FIELD_X + 1;
	for (int j = 0; j < FIELD_Z; j++)
	{
		if (j != 0)
		{
			//w * j * 2 = �O��܂ł̐܂�Ԃ��������C���f�b�N�X��
			//(j - 1) * 2�@= �O��܂ł̐܂�Ԃ����̃C���f�b�N�X��
			pIndex[(w * j * 2) + ((j - 1) * 2)] = (j + 1) * w - 1;	//�E�Ӂ@�� * w = �����܂ł̒��_�f�[�^
			pIndex[(w * j * 2) + ((j - 1) * 2) + 1] = j * w;
		}

		for (int i = 0; i < w; i++)
		{
			pIndex[(w * j * 2) + (i * 2) + (j * 2)] = (j * w) + i;	//w * j * 2 = �O��܂ł̐܂�Ԃ��������C���f�b�N�X��
			//j * 2�@���@�O��܂ł̐܂�Ԃ����̃C���f�b�N�X��
			pIndex[(w * j * 2) + (i * 2 + 1) + (j * 2)] = (j * w) + i + w;
		}
	}

	// Index�o�b�t�@�̐���
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(WORD) * ((FIELD_X + 1) * 2 + 2) * FIELD_Z - 2;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = IndexList;

		if (FAILED(CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &pField->m_pIndexBuffer)))
			return;
	}

	delete[]pIndex;
	/* ���_�΂��ӂ��`��������� */

}