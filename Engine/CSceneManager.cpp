#include "pch.h"
#include "CSceneManager.h"

CSceneManager::CSceneManager()
{
	curScene = nullptr;
}

CSceneManager::~CSceneManager()
{
}

void CSceneManager::Init()
{
}

void CSceneManager::Update()
{
	curScene->Update();
}

void CSceneManager::Render()
{
	curScene->Render();
}

void CSceneManager::Release()
{
	// ���Ӿ� �ڷᱸ���� ��ȸ�ϸ� �����Ҵ�� ���� ����
	for (pair<int, CScene*> scene : mapScene)
	{
		scene.second->Release();
		delete scene.second;
	}
	mapScene.clear();
}

CScene* CSceneManager::FindScene(int key)
{
	auto iter = mapScene.find(key);
	if (iter == mapScene.end())
		return nullptr;
	else
		return iter->second;
}

void CSceneManager::AddScene(int key, CScene* scene)
{
	// ���� Ű���� ���� �̹� ���� ���
	CScene* findScene = FindScene(key);
	assert(nullptr != scene && "Scene already exist");

	scene->Init();
	mapScene.insert(make_pair(key, scene));
}

void CSceneManager::RemoveScene(int key)
{
	CScene* findScene = FindScene(key);
	if (nullptr == findScene) return;

	mapScene.erase(key);
	findScene->Release();
	delete findScene;
}

void CSceneManager::ChangeScene(int key)
{
	CScene* scene = FindScene(key);
	assert(nullptr != scene && "Scene do not exist");

	// ���� ���� Exit, ���� ���� Enter
	curScene->Exit();
	curScene = scene;
	curScene->Enter();
}

void CSceneManager::SetStartScene(int key)
{
	CScene* scene = FindScene(key);
	assert(nullptr != scene && "Scene do not exist");

	curScene = scene;
	curScene->Enter();
}

CScene* CSceneManager::GetCurScene()
{
	return curScene;
}

