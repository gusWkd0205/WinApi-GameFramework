#include "pch.h"
#include "CRenderManager.h"

CRenderManager::CRenderManager()
{
	hWnd	= 0;
	hDC		= 0;
	hMemDC	= 0;
	hBMP	= 0;
	winSize	= Vec2(0.f, 0.f);
}

CRenderManager::~CRenderManager()
{
}

void CRenderManager::Init()
{
	hWnd	= SINGLE(CEngine)->GetHWnd();
	winSize = SINGLE(CEngine)->GetWinSize();
	hDC		= GetDC(SINGLE(CEngine)->GetHWnd());

	// <���� ���۸�>
	// ���� ����ȭ�鿡 ���� �׸���� �׸��� ������ �����Ǿ�
	// ��¦�Ÿ��� ��ũ ���� �߻�
	// ����ۿ� �׸��� �۾��� �����ϰ� ��� �׷��� ���
	// ���Ʈ���ۿ� ������� �������ִ� ������� ��ũ ������ �ذ�

	// ���� ���۸��� �޸� DC�� ��Ʈ�� ����
	hMemDC = CreateCompatibleDC(hDC);
	hBMP = CreateCompatibleBitmap(hDC, (int)winSize.x, (int)winSize.y);

	HBITMAP hOldBitmap = static_cast<HBITMAP>(SelectObject(hMemDC, hBMP));
	DeleteObject(hOldBitmap);
}

void CRenderManager::BeginDraw()
{
	// ����۸� ��� ������� �ʱ�ȭ
	PatBlt(hMemDC, 0, 0, (int)winSize.x, (int)winSize.y, WHITENESS);
}

void CRenderManager::EndDraw()
{
	// ����۸� ����Ʈ���۷� ����
	BitBlt(hDC, 0, 0, (int)winSize.x, (int)winSize.y, hMemDC, 0, 0, SRCCOPY);
}

void CRenderManager::Release()
{
	// ����ߴ� ����Ʈ���ۿ� ����� ����
	DeleteObject(hMemDC);
	DeleteObject(hBMP);
	ReleaseDC(hWnd, hDC);

	hDC = 0;
	hMemDC = 0;
	hBMP = 0;
}

void CRenderManager::Pixel(float x, float y, COLORREF color)
{
	SetPixel(hMemDC, (int)x, (int)y, color);
}

void CRenderManager::Line(float startX, float startY, float endX, float endY)
{
	MoveToEx(hMemDC, (int)startX, (int)startY, NULL);
	LineTo(hMemDC, (int)endX, (int)endY);
}

void CRenderManager::Rect(float startX, float startY, float endX, float endY)
{
	Rectangle(hMemDC, (int)startX, (int)startY, (int)endX, (int)endY);
}

void CRenderManager::Circle(float x, float y, float radius)
{
	::Ellipse(hMemDC, (int)(x - radius), (int)(y - radius), (int)(x + radius), (int)(y + radius));
}

void CRenderManager::Ellipse(float startX, float startY, float endX, float endY)
{
	::Ellipse(hMemDC, (int)startX, (int)startY, (int)endX, (int)endY);
}

void CRenderManager::Text(float x, float y, wstring str)
{
	TextOut(hMemDC, (int)x, (int)y, str.c_str(), (int)str.size());
}