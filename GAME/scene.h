#ifndef SCENE_H_
#define SCENE_H_

#include <typeinfo>	// typidを使用するため
#include <vector>	// vectorを使用するため

#define ENEMY_MAX	(5)

enum LAYER
{
	LAYER_CAMERA,	// カメラレイヤー
	LAYER_BG,		// 背景(BackGround)レイヤー
	LAYER_3DMODELS,	// 3Dモデルレイヤー
	LAYER_EFFECTS,	// Effectsレイヤー
	LAYER_2DPOLYGONS,	// 2Dポリゴンレイヤー

	LAYER_MAX
};

class CScene {
protected:
	std::list<CGameObject*> m_GameObject[LAYER_MAX];

public:
	// コンストラクタ
	CScene() {};

	// デストラクタ
	virtual ~CScene() {};

	// 配列用の管理テンプレート
	template<typename ClassName>ClassName* AddGameObject(int Layer) {
		ClassName* object = new ClassName();
		object->Init();
		m_GameObject[Layer].push_back(object);
		return object;
	}

	// Textureのファイルパス付テンプレート
	template<typename ClassName, typename TexName> ClassName* AddGameObject(TexName* TexName, int Layer) {
		ClassName* object = new ClassName();
		object->Init(TexName);
		m_GameObject[Layer].push_back(object);
		return object;
	}

	// Modelのファイルパスと、Position設定付きテンプレート
	template<typename ClassName, typename ModelName, typename posX, typename posY, typename posZ > ClassName* AddGameObject(ModelName* ModelName, int Layer) {
		ClassName* object = new ClassName();
		object->Init(ModelName, posX, posY, posZ);
		m_GameObject[Layer].push_back(object);
		return object;
	}

	// typeidを使用、調査テンプレート①
	template<typename ClassName>ClassName* GetGameObject(int Layer) {
		for (CGameObject* object : m_GameObject[Layer]) {
			if (typeid(*object) == typeid(ClassName)) {
				return (ClassName*)object;
			}
		}
	}

	// ①の複数化ver
	template<typename ClassName>std::vector<ClassName*> GetGameObjects(int Layer) {
		std::vector<ClassName*> objects;
		for (CGameObject* object : m_GameObject[Layer]) {
			if (typeid(*object) == typeid(ClassName)) {
				objects.push_back((ClassName*)object);
			}
		}
		return objects;
	}


	/////////////////////
	// 初期化処理
	/////////////////////
	virtual void Init() {
		// レイヤー管理
		AddGameObject<CCamera>(LAYER_CAMERA);
		AddGameObject<CField>("asset/primals.tga", LAYER_3DMODELS);
		AddGameObject<CPlayer>(LAYER_3DMODELS);
		for (int i = 0; i < ENEMY_MAX; i++) {
			AddGameObject<CEnemy>(LAYER_3DMODELS);
		}
		AddGameObject<CPolygon>("asset/number.tga", LAYER_2DPOLYGONS);

	}

	/////////////////////
	// 終了処理
	/////////////////////
	virtual void Uninit() {
		for (int i = 0; i < LAYER_MAX; i++) {
			for (CGameObject* object : m_GameObject[i])
			{
				// 中身の破棄
				object->Uninit();
				delete object;
			}

			// 入れ物の破棄
			m_GameObject[i].clear();
		}
	}

	/////////////////////
	// 更新処理
	/////////////////////
	virtual void Update() {
		for (int i = 0; i < LAYER_MAX; i++) {
			for (CGameObject* object : m_GameObject[i])
			{
				object->Update();
			}

			m_GameObject[i].remove_if([](CGameObject* object) { return object->Destroy(); });
		}
	}

	/////////////////////
	// 描画処理
	/////////////////////
	virtual void Draw() {
		// 配列管理用for構文
		for (int i = 0; i < LAYER_MAX; i++) {
			for (CGameObject* object : m_GameObject[i]) {
				object->Draw();
			}
		}
	}

	/////////////////////
	// 破壊処理
	/////////////////////
	void DestroyGameObject(CGameObject* GameObject) {
		GameObject->SetDestroy();
	}


};

#endif // !SCENE_H_
