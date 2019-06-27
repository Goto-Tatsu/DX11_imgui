#ifndef PLAYER_H_
#define PLAYER_H_

class CScene;

class CPlayer:public CGameObject
{

private:
	XMFLOAT3 m_Position;
	XMFLOAT3 m_Rotation;
	XMFLOAT3 m_Scale;

	CModel* m_pModel;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	float GetPositionX(void) { return m_Position.x; };
};

#endif // !PLAYER_H_
