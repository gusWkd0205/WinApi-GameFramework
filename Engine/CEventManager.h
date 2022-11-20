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

	void AddGameObject(CScene* scene, CGameObject* obj);			// ���ӿ�����Ʈ �߰� �̺�Ʈ �߰�
	void DeleteGameObject(CScene* scene, CGameObject* obj);			// ���ӿ�����Ʈ ���� �̺�Ʈ �߰�

private:
	void ProgressAddGameObject();									// ���ӿ�����Ʈ �߰� �̺�Ʈ ����
	void ProgressDeleteGameObject();								// ���ӿ�����Ʈ ���� �̺�Ʈ ����

private:
	queue<pair<CScene*, CGameObject*>>	addGameObjectQueue;			// ���ӿ�����Ʈ �߰� �̺�Ʈ ����
	queue<pair<CScene*, CGameObject*>>	deleteGameObjectQueue;		// ���ӿ�����Ʈ ���� �̺�Ʈ ����
};

#define EVENT		CEventManager::GetInstance()

