#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

class CGameObject 
{
private:
	bool m_Destroy = false;

protected:
	XMFLOAT3 m_Position;
	XMFLOAT3 m_Rotation;
	XMFLOAT3 m_Scale;

public:
	CGameObject() {};
	virtual ~CGameObject() {};	
	virtual void Init() {};
	virtual void Uninit() {};
	virtual void Update() {};
	virtual void Draw() {};

	void SetPosition(XMFLOAT3 position) {
		m_Position = position;
	};

	void SetDestroy(void) { m_Destroy = true; }

	bool Destroy(void) {
		if (m_Destroy) {
			Uninit();
			delete this;
			return true;
		}
		else {
			return false;
		}
	}
};

#endif // !GAMEOBJECT_H_
