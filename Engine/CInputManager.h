#pragma once
class CInputManager : public SingleTon<CInputManager>
{
	friend SingleTon<CInputManager>;
private:
	CInputManager();
	virtual ~CInputManager();

	static const UINT VKEY_SIZE = 0xFF;	// VK�� �ִ� ����

public:
	void					Init();
	void					Update();
	void					Release();

	bool					ButtonStay(const int key);	// Ű�� ������ �ִ� ��
	bool					ButtonUp(const int key);	// Ű�� �ö� ����
	bool					ButtonDown(const int key);	// Ű�� ������ ����
	Vec2					MousePos();					// ���� ���콺 ��ġ

private:
	HWND					hWnd;

	array<bool, VKEY_SIZE>	prevKeys;					// ���� Ű�� �Է»���
	array<bool, VKEY_SIZE>	curKeys;					// ���� Ű�� �Է»���
	POINT					mousePos;					// ���� ���콺 ��ġ
};

#define	INPUT				CInputManager::GetInstance()
