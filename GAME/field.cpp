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

int g_gridsize_x;
int g_gridsize_z;
int g_gridnumber_x;
int g_gridnumber_z;
static int g_indexnumber;
static int g_vertexnumber;

static float g_FieldHeight[5][5] =
{
 {1.0f,2.0f,0.0f,-1.0f,0.0f},
 {0.5f,1.0f,0.0f,-0.5f,0.0f},
 {2.0f,0.5f,0.0f,-2.0f,0.0f},
 {0.5f,2.0f,0.0f,-2.0f,0.0f},
 {2.0f,4.0f,0.0f,-5.0f,0.0f},
};


void CField::Init(const char * TexName)
{
	// 頂点バッファとIndexバッファの設定
	int vertexCnt = 0;
	int indexCnt = 0;
	int u = 0;
	int v = 1;

	g_gridsize_x = 5;
	g_gridsize_z = 5;
	g_gridnumber_x = 5;
	g_gridnumber_z = 5;

	g_indexnumber = (2 + (g_gridnumber_x * 2 * g_gridnumber_z) + (g_gridnumber_z - 1) * 4);
	g_vertexnumber = (g_gridnumber_x + 1) * (g_gridnumber_z + 1);

	// テクスチャよみこみ
	m_Texture = new CTexture();
	m_Texture->Load(TexName);

	/* 頂点ばっふぁ～設定 */
	VERTEX_3D* pVertex = new VERTEX_3D[g_vertexnumber];
	unsigned short* index = new unsigned short [g_indexnumber];

	// 頂点座標設定
	for (int cntZ = 0; cntZ < g_gridnumber_z + 1; cntZ++)
	{
		for (int cntX = 0; cntX < g_gridnumber_x + 1; cntX++)
		{
			vertexCnt = cntX + cntZ * (g_gridnumber_x + 1);
			pVertex[vertexCnt].Position	= XMFLOAT3((cntX * g_gridsize_x) - (g_gridsize_x * g_gridnumber_x / 2), g_FieldHeight[cntX][cntZ], (cntZ * g_gridsize_z) - (g_gridsize_z * g_gridnumber_z / 2));
			pVertex[vertexCnt].Normal		= XMFLOAT3(0.0f, 1.0f, 0.0f);		// 法線ベクトルの方向を決める
			pVertex[vertexCnt].Diffuse		= XMFLOAT4(1, 1, 1, 1);		// RGBA
			pVertex[vertexCnt].TexCoord	= XMFLOAT2(cntX, cntZ);
		}
	}

	// 法線ベクトルのせってい
	XMFLOAT3 va, vb, n;

	for (int cntZ = 1; cntZ < 4; cntZ++)
	{
		for (int cntX = 1; cntX < 4; cntX++)
		{
			va.x = m_Vertex[(cntZ - 1) * 5 + cntX].Position.x - m_Vertex[(cntZ + 1) * 5 + cntX].Position.x;
			va.y = m_Vertex[(cntZ - 1) * 5 + cntX].Position.y - m_Vertex[(cntZ + 1) * 5 + cntX].Position.y;
			va.z = m_Vertex[(cntZ - 1) * 5 + cntX].Position.z - m_Vertex[(cntZ + 1) * 5 + cntX].Position.z;

			vb.x = m_Vertex[(cntX + 1) * 5 + cntZ].Position.x - m_Vertex[(cntX - 1) * 5 + cntZ].Position.x;
			vb.y = m_Vertex[(cntX + 1) * 5 + cntZ].Position.y - m_Vertex[(cntX - 1) * 5 + cntZ].Position.y;
			vb.z = m_Vertex[(cntX + 1) * 5 + cntZ].Position.z - m_Vertex[(cntX - 1) * 5 + cntZ].Position.z;

			n.x = va.y * va.z - va.z * vb.y;
			n.y = va.z * va.x - va.x * vb.z;
			n.z = va.x * va.y - va.y * vb.x;
		}
	}

	// 頂点Index設定
	for (int cntz = 0; cntz < g_gridnumber_z; cntz++)
	{
		for (int cntx = 0; cntx <= g_gridnumber_x; cntx++)
		{
			index[indexCnt++] = cntx + cntz + (g_gridnumber_x * cntz);
			index[indexCnt++] = cntx + cntz + (g_gridnumber_x * (cntz + 1)) + 1;
		}

		if (g_indexnumber != indexCnt)
		{
			index[indexCnt++] = (g_gridnumber_x * (2 + cntz) + 1 + cntz);
			index[indexCnt++] = (g_gridnumber_x * (1 + cntz) + 1 + cntz);
		}
	}

	// 頂点バッファの生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * g_vertexnumber;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pVertex;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_pVertexBuffer);
	}

	// Indexバッファの生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned short) * g_indexnumber;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_pIndexBuffer);
	}

	delete[] index;
	delete[] pVertex;
	/* 頂点ばっふぁ～生成おわり */

}

void CField::Init(const float PosX, const float PosY, const float PosZ, const float ScaleX, const float ScaleY, const float ScaleZ, const char * TexName)
{
	/* 頂点ばっふぁ～生成 */
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

	// ばっふぁにもってく
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// 頂点バッファ
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_pVertexBuffer);
	/* 頂点ばっふぁ～生成おわり */

	// テクスチャよみこみ
	m_Texture = new CTexture();
	m_Texture->Load(TexName);
}


void CField::Uninit()
{
	m_pVertexBuffer->Release();	// ちょうてんばっふぁばいばい
	m_pIndexBuffer->Release();
	m_Texture->Unload();		// よんだてくすちゃばいばい
	delete m_Texture;			// いれものばいばい
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
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);		// 頂点バッファ設定
	CRenderer::GetDeviceContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, offset);
	CRenderer::SetTexture(m_Texture);

	// SetWorldViewProjection2Dの代わり
	XMMATRIX world;
	world = XMMatrixScaling(1.0f, 1.0f, 1.0f);					// 拡大縮小
	world *= XMMatrixRotationRollPitchYaw(0.0f, g_Rotation, 0.0f);	// 回転(ラジアン角度)
	world *= XMMatrixTranslation(0.0f, 0.0f, 0.0f);				// 移動
	CRenderer::SetWorldMatrix(&world);							

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	// トポロジー(どうやって配置するか)設定
	CRenderer::GetDeviceContext()->DrawIndexed(g_indexnumber, 0, 0);
}

void Vertex_Index_Config()
{
	CField* pField;
	pField = new CField();

	pField->m_xCnt = FIELD_X;		//横の分割数
	pField->m_zCnt = FIELD_Z;		//縦の分割数
	pField->vertexCnt = (FIELD_X + 1) * (FIELD_Z + 1);	//頂点の数
	pField->returnCnt = FIELD_Z - 1;					//折り返しの回数

	g_Rotation = 0.0f;
	g_Scale = 1.0;

	/* 頂点ばっふぁ～生成 */
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

	// ばっふぁにもってく
	// 頂点バッファの生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * (FIELD_X + 1) * (FIELD_Z + 1);
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// 頂点バッファ
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
			//w * j * 2 = 前回までの折り返しを除くインデックス数
			//(j - 1) * 2　= 前回までの折り返し分のインデックス数
			pIndex[(w * j * 2) + ((j - 1) * 2)] = (j + 1) * w - 1;	//右辺　ｊ * w = ここまでの頂点データ
			pIndex[(w * j * 2) + ((j - 1) * 2) + 1] = j * w;
		}

		for (int i = 0; i < w; i++)
		{
			pIndex[(w * j * 2) + (i * 2) + (j * 2)] = (j * w) + i;	//w * j * 2 = 前回までの折り返しを除くインデックス数
			//j * 2　＝　前回までの折り返し分のインデックス数
			pIndex[(w * j * 2) + (i * 2 + 1) + (j * 2)] = (j * w) + i + w;
		}
	}

	// Indexバッファの生成
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
	/* 頂点ばっふぁ～生成おわり */

}
//void Vertex_Index_Config(float size, int field_x, int field_z)
//{
//	CField* pField;
//	pField = new CField();
//
//	pField->m_xCnt = FIELD_X;		//横の分割数
//	pField->m_zCnt = FIELD_Z;		//縦の分割数
//	pField->vertexCnt = (FIELD_X + 1) * (FIELD_Z + 1);	//頂点の数
//	pField->returnCnt = FIELD_Z - 1;					//折り返しの回数
//
//
//	// インデックスの
//	WORD IndexList[]{
//		0, 1, 2,
//		2, 3, 1,
//	};
//
//	g_Rotation = 0.0f;
//	g_Scale = 1.0;
//
//	/* 頂点ばっふぁ～生成 */
//	VERTEX_3D* pVertex;
//	pVertex = new VERTEX_3D[pField->vertexCnt];
//
//	for (int j = 0; j <= FIELD_Z; j++) {
//		for (int i = 0; i <= FIELD_X; i++) {
//			pVertex[i + (FIELD_X + 1) * j].Position = XMFLOAT3(-(FIELD_X * FIELD_SIZE) / 2 + FIELD_SIZE * i, 0.0f, -(FIELD_Z * FIELD_SIZE) / 2 + FIELD_SIZE * j);
//		}
//	}
//
//	for (int i = 0; i < pField->vertexCnt; i++) {
//		pVertex[i].Diffuse = XMFLOAT4(128, 128, 255, 255);
//		pVertex[i].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
//	}
//
//	// ばっふぁにもってく
//	// 頂点バッファの生成
//	{
//		D3D11_BUFFER_DESC bd;
//		ZeroMemory(&bd, sizeof(bd));
//		bd.Usage = D3D11_USAGE_DEFAULT;
//		bd.ByteWidth = sizeof(VERTEX_3D) * pField->vertexCnt;
//		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// 頂点バッファ
//		bd.CPUAccessFlags = 0;
//
//		D3D11_SUBRESOURCE_DATA sd;
//		ZeroMemory(&sd, sizeof(sd));
//		sd.pSysMem = pVertex;
//		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &pField->m_pVertexBuffer);
//	}
//
//
//	WORD* pIndex = new WORD[((FIELD_X + 1) * 2 + 2) * FIELD_Z - 2];
//	int w = FIELD_X + 1;
//	for (int j = 0; j < FIELD_Z; j++)
//	{
//		if (j != 0)
//		{
//			//w * j * 2 = 前回までの折り返しを除くインデックス数
//			//(j - 1) * 2　= 前回までの折り返し分のインデックス数
//			pIndex[(w * j * 2) + ((j - 1) * 2)] = (j + 1) * w - 1;	//右辺　ｊ * w = ここまでの頂点データ
//			pIndex[(w * j * 2) + ((j - 1) * 2) + 1] = j * w;
//		}
//
//		for (int i = 0; i < w; i++)
//		{
//			pIndex[(w * j * 2) + (i * 2) + (j * 2)] = (j * w) + i;	//w * j * 2 = 前回までの折り返しを除くインデックス数
//			//j * 2　＝　前回までの折り返し分のインデックス数
//			pIndex[(w * j * 2) + (i * 2 + 1) + (j * 2)] = (j * w) + i + w;
//		}
//	}
//
//	// Indexバッファの生成
//	{
//		D3D11_BUFFER_DESC bd;
//		ZeroMemory(&bd, sizeof(bd));
//		bd.Usage = D3D11_USAGE_DEFAULT;
//		bd.ByteWidth = sizeof(WORD) * ((FIELD_X + 1) * 2 + 2) * FIELD_Z - 2;
//		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
//		bd.CPUAccessFlags = 0;
//
//		D3D11_SUBRESOURCE_DATA sd;
//		ZeroMemory(&sd, sizeof(sd));
//		sd.pSysMem = IndexList;
//
//		if (FAILED(CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &pField->m_pIndexBuffer)))
//			return;
//	}
//
//	delete[]pIndex;
//	/* 頂点ばっふぁ～生成おわり */
//
//}

void CField::MuraseField()
{
	float offset = 1.0f;
	for (int z = 0; z < 5; z++)
	{
		for (int x = 0; x < 5; x++)
		{
			m_Vertex[z * 5 + z].Position.x = x * 2.0f + offset;
			m_Vertex[z * 5 + z].Position.z = -z * 2.0f + offset;
			m_Vertex[z * 5 + z].Position.y = g_FieldHeight[z][x];
		}
	}

	// 頂点バッファの生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * (FIELD_X + 1) * (FIELD_Z + 1);
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// 頂点バッファ
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = m_Vertex;
		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_pVertexBuffer);
	}


	unsigned short index[25];
	for (int z = 0; z < 5; z++)
	{
		for (int x = 0; x < 5; x++)
		{
			//index[x + z] = m_Vertex->Position[x + z];
		}
	}

	// Indexバッファの生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(WORD) * ((FIELD_X + 1) * 2 + 2) * FIELD_Z - 2;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index;

		if (FAILED(CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_pIndexBuffer)))
			return;
	}

	delete[] index;
	/* 頂点ばっふぁ～生成おわり */
}


void CField::MuraseFieldDraw()
{
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);		// 頂点バッファ設定
	CRenderer::GetDeviceContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);			// indexバッファ設定
	CRenderer::SetTexture(m_Texture);																	// テクスチャ設定

	// SetWorldViewProjection2Dの代わり
	XMMATRIX world;													// マトリクス設定
	world = XMMatrixScaling(1.0f, 1.0f, 1.0f);						// 拡大縮小
	world *= XMMatrixRotationRollPitchYaw(0.0f, g_Rotation, 0.0f);	// 回転(ラジアン角度)
	world *= XMMatrixTranslation(0.0f, 0.0f, 0.0f);					// 移動
	CRenderer::SetWorldMatrix(&world);

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	// トポロジー(どうやって配置するか)設定
	CRenderer::GetDeviceContext()->DrawIndexed(((FIELD_X + 1) * 2 + 2) * FIELD_Z - 2, 0, 0);

}

void OkazakiField()
{
	
}