#pragma once

class CScene;
class CGameObject;

class CEventManager : public SingleTon<CEventManager>
{
	friend SingleTon<CEventManager>;
private:
	CEventManager();
	virtual ~CEventManager();

public:
	void Init();
	void Update();
	void Release();

	void AddGameObject(CScene* scene, CGameObject* obj);							// ���ӿ�����Ʈ �߰� �̺�Ʈ �߰�
	void AddChild(CGameObject* parent, Component<CGameObject>* child);				// ������Ʈ �߰� �̺�Ʈ �߰�
	void DeleteObject(CScene* scene, Component<CGameObject>* obj);					// ������Ʈ ���� �̺�Ʈ �߰�
	void ChangeScene(int sceneType);												// �� ��ȯ �̺�Ʈ �߰�

private:
	void ProgressAddGameObject();													// ���ӿ�����Ʈ �߰� �̺�Ʈ ����
	void ProgressAddComponent();													// ������Ʈ �߰� �̺�Ʈ ����
	void ProgressDeleteObject();													// ������Ʈ ���� �̺�Ʈ ����
	void ProgressChangeScene();														// �� ��ȯ �̺�Ʈ ����

private:
	queue<pair<CScene*, CGameObject*>>					addGameObjectQueue;			// ���ӿ�����Ʈ �߰� �̺�Ʈ ����
	queue<pair<CGameObject*, Component<CGameObject>*>>	addChildQueue;				// ������Ʈ �߰� �̺�Ʈ ����
	queue<pair<CScene*, Component<CGameObject>*>>		deleteObjectQueue;			// ������Ʈ ���� �̺�Ʈ ����
	int													changeSceneValue = -1;		// �� ��ȯ �̺�Ʈ ���� ����
};

#define EVENT		CEventManager::GetInstance()

