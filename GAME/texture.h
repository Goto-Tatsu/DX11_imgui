#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <stdio.h>
#include "main.h"
#include "renderer.h"

#define TEXTURE_FILENAME_MAX	(64)

typedef struct {
	const char filename[TEXTURE_FILENAME_MAX];
	int tex_width;
	int tex_height;
	int tex_pattern_X;		// X方向のパターン数
	int tex_pattern_Y;		// Y方向のパターン数
	int tex_pattern_Max;	// 全パターン数
	int frameCnt;			// UVの描画速度
}TEXTURE_FILE_DATA;

// データベースの作成
static const TEXTURE_FILE_DATA TEXTURE_LIST[] = {
	{"asset/number.tga", 512, 512, 5, 3, 13},
	{"asset/field004.tga", 128, 128, 1, 1, 1},
	{"asset/primals.tga", 355, 352, 1, 1, 1},
};

enum {
	TEX_NUMBER,
	TEX_FILED004,
	TEX_PRIMALS,


	TEX_MAX
};

class CTexture
{

public:
	enum TexNum {
		TEXTURE_PLASTICSIS,
		TEXTURE_PRIMALS,

		TEXTURE_MAX
	};

	void Load(const char *FileName);
	void Unload();

	ID3D11ShaderResourceView* GetShaderResourceView() { return m_ShaderResourceView; }



private:

	ID3D11Texture2D*			m_Texture;
	ID3D11ShaderResourceView*	m_ShaderResourceView;

	static int GetTextureMax();
};

#endif // !TEXTURE_H_
