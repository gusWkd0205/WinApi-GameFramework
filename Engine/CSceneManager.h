#pragma once

// ���漱�� : Ŭ������ �̸������� ����
class CScene;

class CSceneManager : public SingleTon<CSceneManager>
{
	friend SingleTon<CSceneManager>;
private:
	CSceneManager();
	virtual ~CSceneManager();

public:
	void		Init();
	void		Update();
	void		Render();
	void		Release();

	CScene*		FindScene(int key);					// �� Ž��
	void		AddScene(int key, CScene* scene);	// �� �߰�
	void		RemoveScene(int key);				// �� ����
	void		ChangeScene(int key);				// �� ��ȯ
	void		SetStartScene(int key);				// ���� �� ����

	CScene*		GetCurScene();						// ���� �� ��ȯ

private:
	map<int, CScene*>		mapScene;				// ���Ӿ����� �����ϴ� �ڷᱸ��
	CScene*					curScene;				// ���� ���Ӿ�
};

