#pragma once
class CSceneManager;
class CEventManager;
class CGameObject;
class CUI;

class CScene
{
	friend CEventManager;
	friend CSceneManager;
public:
	CScene();
	virtual ~CScene();

public:
	void				AddGameObject(CGameObject* obj);
	void				DeleteGameObject(CGameObject* obj);
	void				DeleteAllObject();

	void				AddRenderer(IRender* renderer);

	void				AddUI(CUI* ui);
	void				DeleteUI(CUI* ui);
	void				DeleteAllUI();

private:
	// ���������Լ� :
	// �Լ��� �߻�ȭ�Ͽ� ��üȭ���� ���� ��� �ν��Ͻ� ������ ����
	// ���� ��ӹ޾� ���������Լ����� ��üȭ���� ���� �ϼ���Ŵ
	virtual void		Init()		= 0;	// �ʱ�ȭ
	virtual void		Enter()		= 0;	// ����
	virtual void		Update()	= 0;	// ���ӷ��� ����
	virtual void		Render()	= 0;	// ����ǥ�� ����
	virtual void		Exit()		= 0;	// Ż��
	virtual void		Release()	= 0;	// ������

	// �� �θ� ���� �Լ��� :
	// ���� �ִ� ��� ���ӿ�����Ʈ���� ����
	void				SceneInit();		
	void				SceneEnter();		
	void				SceneUpdate();		
	void				SceneRender();		
	void				SceneExit();		
	void				SceneRelease();		

private:
	list<CGameObject*>						objList;
	list<CUI*>								uiList;
	bool									active;
	priority_queue<pair<float, IRender*>>	renderPQueue;
};

