#ifndef FIELD_H_
#define FIELD_H_


class CField:public CGameObject	// CGameObjectÇ©ÇÁåpè≥
{
public:
	void Init(void);
	void Init(const char* TexName);
	void Init(const float PosX, const float PosY, const float PosZ, const float ScaleX, const float ScaleY, const float ScaleZ, const char * TexName);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Draw(const float ScaleX, const float ScaleY, const float ScaleZ, const float RotX, const float RotY, const float RotZ, const float MoveX, const float MoveY, const float MoveZ);
	void ScalePlus();
	void ScaleMinus();

private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	CTexture* m_Texture = NULL;
};


#endif // !FIELD_H_
