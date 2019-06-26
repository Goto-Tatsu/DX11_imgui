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
	/* 頂点ばっふぁ〜生成 */
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
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	/* 頂点ばっふぁ〜生成おわり */

	// テクスチャよみこみ
	m_Texture = new CTexture();
	m_Texture->Load("asset/number.tga");

}

void CField::Init(const char * TexName)
{
	g_Rotation = 0.0f;
	g_Scale = 1.0;

	/* 頂点ばっふぁ〜生成 */
	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(-5.0f, 0.0f, 5.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(5.0f, 0.0f, 5.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-5.0f, 0.0f, -5.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(5.0f, 0.0f, -5.0f);
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
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	/* 頂点ばっふぁ〜生成おわり */

	// テクスチャよみこみ
	m_Texture = new CTexture();
	m_Texture->Load(TexName);

}

void CField::Init(const float PosX, const float PosY, const float PosZ, const float ScaleX, const float ScaleY, const float ScaleZ, const char * TexName)
{
	/* 頂点ばっふぁ〜生成 */
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
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	/* 頂点ばっふぁ〜生成おわり */

	// テクスチャよみこみ
	m_Texture = new CTexture();
	m_Texture->Load(TexName);
}


void CField::Uninit()
{
	m_VertexBuffer->Release();	// ちょうてんばっふぁばいばい
	m_Texture->Unload();		// よんだてくすちゃばいばい
	delete m_Texture;			// いれものばいばい
}


void CField::Update()
{
	g_Rotation += 0.1f;
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
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);		// 頂点バッファ設定
	CRenderer::SetTexture(m_Texture);

	// SetWorldViewProjection2Dの代わり
	XMMATRIX world;
	world = XMMatrixScaling(1.0f, 1.0f, 1.0f);					// 拡大縮小
	world *= XMMatrixRotationRollPitchYaw(0.0f, g_Rotation, 0.0f);	// 回転(ラジアン角度)
	world *= XMMatrixTranslation(0.0f, 0.0f, 0.0f);				// 移動
	CRenderer::SetWorldMatrix(&world);							

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	// トポロジー(どうやって配置するか)設定
	CRenderer::GetDeviceContext()->Draw(4, 0);
}


void CField::Draw(const float ScaleX, const float ScaleY, const float ScaleZ, const float RotX, const float RotY, const float RotZ, const float MoveX, const float MoveY, const float MoveZ)
{
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);		// 頂点バッファ設定
	CRenderer::SetTexture(m_Texture);

	// SetWorldViewProjection2Dの代わり
	XMMATRIX world;
	world = XMMatrixScaling(1.0f * ScaleX, 1.0f * ScaleY, 1.0f * ScaleZ);					// 拡大縮小
	world *= XMMatrixRotationRollPitchYaw(RotX, RotY + g_Rotation, RotZ);	// 回転(ラジアン角度)
	world *= XMMatrixTranslation(MoveX, MoveY, MoveZ);				// 移動
	CRenderer::SetWorldMatrix(&world);

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	// トポロジー(どうやって配置するか)設定
	CRenderer::GetDeviceContext()->Draw(4, 0);
}


