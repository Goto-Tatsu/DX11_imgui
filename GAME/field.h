#ifndef FIELD_H_
#define FIELD_H_

#define FIELD_X		(3)	// フィールドの横メッシュ数
#define FIELD_Z		(3)	// フィールドの縦メッシュ数
#define FIELD_SIZE	(1)


class CField:public CGameObject	// CGameObjectから継承
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

	void MuraseField();
	void MuraseFieldDraw();

	int m_xCnt = 0;
	int m_zCnt = 0;
	int vertexCnt;
	int returnCnt;

	VERTEX_3D m_Vertex[25];	// MuraseField用の配列要素

	ID3D11Buffer* m_pVertexBuffer = NULL;
	ID3D11Buffer* m_pIndexBuffer = NULL;

private:

	CTexture* m_Texture = NULL;
};

void Vertex_Index_Config();
void Vertex_Index_Config(float size, int field_x, int field_z);


#endif // !FIELD_H_
