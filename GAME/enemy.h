#ifndef ENEMY_H_
#define ENEMY_H_

class CEnemy : public CGameObject
{
private:
	CModel* m_pModel;

public:
	void Init();
	void Init(const char* pFilename, float posX, float posY, float posZ);
	void Uninit();
	void Update();
	void Draw();

	XMFLOAT3 GetPosition();
};

#endif // !ENEMY_H_
