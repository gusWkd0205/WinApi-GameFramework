#include "pch.h"
#include "CEventManager.h"

CEventManager::CEventManager()
{
}

CEventManager::~CEventManager()
{
}

void CEventManager::Init()
{
}

void CEventManager::Update()
{
	ProgressAddGameObject();
	ProgressDeleteObject();
	ProgressAddComponent();
	ProgressChangeScene();
}

void CEventManager::Release()
{
}

void CEventManager::AddGameObject(CScene* scene, CGameObject* obj)
{
	addGameObjectQueue.push(make_pair(scene, obj));
}

void CEventManager::AddChild(CGameObject* parent, Component<CGameObject>* child)
{
	addChildQueue.push(make_pair(parent, child));
}

void CEventManager::DeleteObject(CScene* scene, Component<CGameObject>* obj)
{
	deleteObjectQueue.push(make_pair(scene, obj));
}

void CEventManager::ChangeScene(int sceneType)
{
	changeSceneValue = sceneType;
}

void CEventManager::ProgressAddGameObject()
{
	while (!addGameObjectQueue.empty())
	{
		CScene* scene = addGameObjectQueue.front().first;
		CGameObject* obj = addGameObjectQueue.front().second;
		addGameObjectQueue.pop();
		scene->AddGameObject(obj);
	}
}

void CEventManager::ProgressAddComponent()
{
	while (!addChildQueue.empty())
	{
		CGameObject* parent = addChildQueue.front().first;
		Component<CGameObject>* child = addChildQueue.front().second;
		addChildQueue.pop();
		parent->AddChild(child);
	}
}

void CEventManager::ProgressDeleteObject()
{
	// ���� ���� ǥ�õ� ���ӿ�����Ʈ�� ���� ����
	CScene* curScene = SINGLE(CSceneManager)->GetCurScene();
	list<CGameObject*>& objList = curScene->objList;

	objList.remove_if([&](CGameObject* obj) {
		if (obj->IsReservedDelete())
		{
			if (curScene->active) obj->ComponentOnDisable();
			obj->ComponentRelease();
			obj->SetScene(nullptr);
			delete obj;
			return true;
		}
		else
		{
			obj->DeleteReservedChild();
			return false;
		}
		});

	// ���� ������ ���ӿ�����Ʈ�� �������� ǥ�ø� ����
	while (!deleteObjectQueue.empty())
	{
		Component<CGameObject>* component = deleteObjectQueue.front().second;
		deleteObjectQueue.pop();
		component->SetReservedDelete();
	}
}

void CEventManager::ProgressChangeScene()
{
	// �� ��ȯ �̺�Ʈ�� �ִ� ��� �� ��ȯ ����
	if (changeSceneValue != -1)
	{
		SINGLE(CSceneManager)->ChangeScene(changeSceneValue);
		changeSceneValue = -1;
	}
}
