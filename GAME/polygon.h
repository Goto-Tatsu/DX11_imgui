#ifndef POLYGON_H_
#define POLYGON_H_



class CPolygon : public CGameObject	// CGameObjectÇ©ÇÁåpè≥
{
public:
	void Init();
	void IndexInit();
	void Init(const char* TexName);
	void Init(const float PosX, const float PosY, const short ScaleX, const short ScaleY, const char* TexName);
	void Uninit();
	void Update();
	void Draw();

private:
	ID3D11Buffer* m_pVertexBuffer = NULL;	
	ID3D11Buffer* m_pIndexBuffer = NULL;
	CTexture* m_Texture = NULL;	

	
};

#endif // !POLYGON_H_