#include "pch.h"
#include "CGame.h"

#include "Resource.h"

const Vec2 CGame::WINSTART	= Vec2(100, 100);
const Vec2 CGame::WINSIZE	= Vec2(1280, 720);

CGame::CGame()
{
	hInst	= 0;
	hWnd	= 0;

	moveDir	= Vec2(0.f, 0.f);
	pos		= Vec2(WINSIZE.x * 0.5f, WINSIZE.y * 0.5f);
	scale	= Vec2(100.f, 100.f);
}

CGame::~CGame()
{
}

void CGame::Init(HINSTANCE hInstance)
{
	// ������ �ʱ�ȭ ����
	const UINT MAX_LOADSTRING = 100;
	WCHAR szTitle[MAX_LOADSTRING];
	WCHAR szWindowClass[MAX_LOADSTRING];
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WINAPI, szWindowClass, MAX_LOADSTRING);

	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

	hWnd = CreateWindow(	// ������ ���� �� �ڵ鰪 ��ȯ
		szWindowClass,		// ������ Ŭ���� �̸�
		szTitle,			// ������ Ÿ��Ʋ �̸�
		WINSTYLE,			// ������ ��Ÿ��
		(int)WINSTART.x,	// ������ ȭ�� X
		(int)WINSTART.y,	// ������ ȭ�� Y
		(int)WINSIZE.x,		// ������ ���� ũ��
		(int)WINSIZE.y,		// ������ ���� ũ��
		nullptr,			// �θ� ������
		nullptr,			// �޴� �ڵ�
		hInstance,			// �ν��Ͻ� ����
		nullptr				// �߰� �Ű�����
	);

	assert(hWnd != nullptr && "Create window failed");

	// ���� ������ ũ��(�׵θ�, �޴����� ũ�⸦ ������ ũ��)�� ���ϱ� ���� AdjustWindowRect ���
	RECT rc = { 0, 0, (LONG)WINSIZE.x, (LONG)WINSIZE.y };

	// ������ ��Ÿ�Ͽ� ���� ȭ�� �������� ũ�⿡ �°� ���´�.
	AdjustWindowRect(&rc, WINSTYLE, FALSE);
	// ������ ����� ����
	SetWindowPos(hWnd, HWND_TOPMOST, (int)WINSTART.x, (int)WINSTART.y, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOMOVE);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	// ���ӿ��� �ʱ�ȭ
	SINGLE(CEngine)->Init(hInst, hWnd, WINSIZE);
	SINGLE(CTimeManager)->Init();
	SINGLE(CRenderManager)->Init();
}

void CGame::Run()
{
	// ������ ���� ����

	Input();
	Update();
	Render();
}

void CGame::Release()
{
	// ������ ������ ����

	// ���ӿ��� ������
	SINGLE(CEngine)->Release();
	SINGLE(CTimeManager)->Release();
	SINGLE(CRenderManager)->Release();
}

void CGame::Input()
{
	// ������ �Է� ����

	// GetAsyncKeyState : Ű������ Ű �Է»��� Ȯ��
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		moveDir.x = -1;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		moveDir.x = +1;
	}
	else
	{
		moveDir.x = 0;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		moveDir.y = -1;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		moveDir.y = +1;
	}
	else
	{
		moveDir.y = 0;
	}
}

void CGame::Update()
{
	// ������ ó�� ����

	SINGLE(CTimeManager)->Update();

	pos += moveDir * 100 * DT;
}

void CGame::Render()
{
	SINGLE(CRenderManager)->BeginDraw();

	// ������ ǥ�� ����

	RENDER->SetPen(PenType::Solid, RGB(255, 0, 0), 1);
	RENDER->SetBrush(BrushType::Solid, RGB(0, 255, 0));
	RENDER->Rect(
		pos.x - scale.x * 0.5f,
		pos.y - scale.y * 0.5f,
		pos.x + scale.x * 0.5f,
		pos.y + scale.y * 0.5f
	);
	RENDER->SetPen();
	RENDER->SetBrush();

	// ������ ���ܿ� ���� FPS ��� (60������ �̻��� ��ǥ�� ����ȭ �ؾ���)
	wstring frame = to_wstring(FPS);
	RENDER->SetText(20, RGB(0, 255, 0), TextAlign::Right);
	RENDER->Text(WINSIZE.x - 30, 10, frame);
	RENDER->SetText();

	SINGLE(CRenderManager)->EndDraw();
}
