#ifndef CAMERA_H_
#define CAMERA_H_

class CPlayer;

class CCamera : public CGameObject	// CGameObjectから継承
{
private:

	RECT						m_Viewport;	// 
	float						m_fCameraAngle;// カメラアングル

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	XMFLOAT3					m_Position;	// カメラの位置(座標)
	XMFLOAT3					m_Rotation;	// カメラの回転要素
	XMFLOAT3					m_Target;	// 注視点

};

#endif // !CAMERA_H_