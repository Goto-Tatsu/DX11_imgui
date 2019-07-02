#ifndef CAMERA_H_
#define CAMERA_H_

class CPlayer;

class CCamera : public CGameObject	// CGameObject����p��
{
private:

	RECT						m_Viewport;	// 
	float						m_fCameraAngle;// �J�����A���O��

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	XMFLOAT3					m_Position;	// �J�����̈ʒu(���W)
	XMFLOAT3					m_Rotation;	// �J�����̉�]�v�f
	XMFLOAT3					m_Target;	// �����_

};

#endif // !CAMERA_H_