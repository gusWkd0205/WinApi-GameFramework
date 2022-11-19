#pragma once
class CInputManager : public SingleTon<CInputManager>
{
	friend SingleTon<CInputManager>;
private:
	CInputManager();
	virtual ~CInputManager();

	static const UINT VKEY_SIZE = 0xFF;	// VK�� �ִ� ����

public:
	void		Init();
	void		Update();
	void		Release();

	bool		GetButtonStay(const int key);		// Ű�� ������ �ִ� ��
	bool		GetButtonUp(const int key);		// Ű�� �ö� ����
	bool		GetButtonDown(const int key);	// Ű�� ������ ����
	Vec2		GetMousePos();					// ���� ���콺 ��ġ

private:
	HWND					hWnd;

	array<bool, VKEY_SIZE>	prevKeys;		// ���� Ű�� �Է»���
	array<bool, VKEY_SIZE>	curKeys;		// ���� Ű�� �Է»���
	POINT					mousePos;		// ���� ���콺 ��ġ
};

#define BUTTONSTAY(key)			CInputManager::GetInstance()->GetButtonStay(key)
#define BUTTONUP(key)			CInputManager::GetInstance()->GetButtonUp(key)	
#define BUTTONDOWN(key)			CInputManager::GetInstance()->GetButtonDown(key)
#define MOUSEPOS				CInputManager::GetInstance()->GetMousePos()