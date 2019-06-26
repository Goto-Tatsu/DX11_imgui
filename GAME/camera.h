#ifndef CAMERA_H_
#define CAMERA_H_


class CCamera : public CGameObject	// CGameObject����p��
{
private:

	XMFLOAT3					m_Position;
	XMFLOAT3					m_Rotation;

	RECT m_Viewport;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();


};

#endif // !CAMERA_H_