#include "pch.h"
#include "CRenderManager.h"

CRenderManager::CRenderManager()
{
	hWnd	= 0;
	hDC		= 0;
	hMemDC	= 0;
	hBMP	= 0;
	winSize	= Vec2(0.f, 0.f);

	hCurPen = 0;
	penType = PenType::Solid;
	penWidth = 1;
	penColor = RGB(0, 0, 0);

	hCurBrush = 0;
	brushType = BrushType::Solid;
	brushColor = RGB(255, 255, 255);

	hFont = 0;
	textSize = 10;
	textColor = RGB(0, 0, 0);
	textAlign = TextAlign::Center;
	textBackMode = TextBackMode::Null;
	textBackColor = RGB(255, 255, 255);
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

	// �⺻ �� & �귯�� ����
	SetPen();
	SetBrush();
	SetText();
	SetTextBackMode();
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

	// ����ߴ� �� & �귯�� ����
	DeleteObject(hCurPen);
	DeleteObject(hCurBrush);

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
	// WinGDI ����
	// 1. ������� ����귯�ø� ����
	// 2. �׸��� �۾� ����
	// 3. ������� �����귯�÷� ����
	// Why? �ٸ� �������� ����ϴ� ��� ������ ��츦 ���

	HPEN prevPen = static_cast<HPEN>(SelectObject(hMemDC, hCurPen));
	HBRUSH prevBrush = static_cast<HBRUSH>(SelectObject(hMemDC, hCurBrush));

	MoveToEx(hMemDC, (int)startX, (int)startY, NULL);
	LineTo(hMemDC, (int)endX, (int)endY);

	SelectObject(hMemDC, prevPen);
	SelectObject(hMemDC, prevBrush);
}

void CRenderManager::Rect(float startX, float startY, float endX, float endY)
{
	HPEN prevPen = static_cast<HPEN>(SelectObject(hMemDC, hCurPen));
	HBRUSH prevBrush = static_cast<HBRUSH>(SelectObject(hMemDC, hCurBrush));

	Rectangle(hMemDC, (int)startX, (int)startY, (int)endX, (int)endY);

	SelectObject(hMemDC, prevPen);
	SelectObject(hMemDC, prevBrush);
}

void CRenderManager::Circle(float x, float y, float radius)
{
	HPEN prevPen = static_cast<HPEN>(SelectObject(hMemDC, hCurPen));
	HBRUSH prevBrush = static_cast<HBRUSH>(SelectObject(hMemDC, hCurBrush));

	::Ellipse(hMemDC, (int)(x - radius), (int)(y - radius), (int)(x + radius), (int)(y + radius));

	SelectObject(hMemDC, prevPen);
	SelectObject(hMemDC, prevBrush);
}

void CRenderManager::Ellipse(float startX, float startY, float endX, float endY)
{
	HPEN prevPen = static_cast<HPEN>(SelectObject(hMemDC, hCurPen));
	HBRUSH prevBrush = static_cast<HBRUSH>(SelectObject(hMemDC, hCurBrush));

	::Ellipse(hMemDC, (int)startX, (int)startY, (int)endX, (int)endY);

	SelectObject(hMemDC, prevPen);
	SelectObject(hMemDC, prevBrush);
}

void CRenderManager::Text(float x, float y, wstring str)
{
	TextOut(hMemDC, (int)x, (int)y, str.c_str(), (int)str.size());
}

void CRenderManager::BitImage(CImage* pImg, float startX, float startY, float endX, float endY)
{
	BitBlt(hMemDC, (int)startX, (int)startY, (int)endX, (int)endY, pImg->GetImageDC(), 0, 0, SRCCOPY);
}

void CRenderManager::StrectchImage(CImage* pImg, float startX, float startY, float endX, float endY)
{
	StretchBlt(hMemDC, (int)startX, (int)startY, (int)(endX - startX), (int)(endY - startY),
		pImg->GetImageDC(), 0, 0, pImg->GetBmpWidth(), pImg->GetBmpHeight(), SRCCOPY);
}

void CRenderManager::TransparentImage(CImage* pImg, float startX, float startY, float endX, float endY, COLORREF transparent)
{
	TransparentBlt(hMemDC, (int)startX, (int)startY, (int)(endX - startX), (int)(endY - startY),
		pImg->GetImageDC(), 0, 0, pImg->GetBmpWidth(), pImg->GetBmpHeight(), transparent);
}

void CRenderManager::FrameImage(CImage* pImg, float dstStartX, float dstStartY, float dstEndX, float dstEndY, float srcStartX, float srcStartY, float srcEndX, float srcEndY, COLORREF transparent)
{
	TransparentBlt(hMemDC, (int)dstStartX, (int)dstStartY, (int)(dstEndX - dstStartX), (int)(dstEndY - dstStartY),
		pImg->GetImageDC(), (int)srcStartX, (int)srcStartY, (int)(srcEndX - srcStartX), (int)(srcEndY - srcStartY), transparent);
}

void CRenderManager::BlendImage(CImage* pImg, float dstStartX, float dstStartY, float dstEndX, float dstEndY, float srcStartX, float srcStartY, float srcEndX, float srcEndY, float ratio)
{
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = (BYTE)(ratio * 255);

	AlphaBlend(hMemDC, (int)dstStartX, (int)dstStartY, (int)(dstEndX - dstStartX), (int)(dstEndY - dstStartY),
		pImg->GetImageDC(), (int)srcStartX, (int)srcStartY, (int)(srcEndX - srcStartX), (int)(srcEndY - srcStartY), bf);
}

void CRenderManager::SetPen(PenType type, COLORREF color, int width)
{
	// �����ϴ� ���� ���� ��� ������ ��� ���� ������ ����
	if (penType == type && penWidth == width && penColor == color)
		return;

	penType = type;
	penWidth = width;
	penColor = color;

	// ���� ���� ����
	DeleteObject(hCurPen);

	// �� Ÿ�Կ� ���� �� ��Ÿ���� �ٸ��� ����
	switch (type)
	{
	case PenType::Solid:
		hCurPen = CreatePen(PS_SOLID, width, color);
		break;
	case PenType::Dot:
		hCurPen = CreatePen(PS_DOT, width, color);
		break;
	case PenType::Dash:
		hCurPen = CreatePen(PS_DASH, width, color);
		break;
	case PenType::Null:
		hCurPen = CreatePen(PS_NULL, width, color);
		break;
	default:
		hCurPen = CreatePen(PS_SOLID, width, color);
		break;
	}
}

void CRenderManager::SetBrush(BrushType type, COLORREF color)
{
	// �����ϴ� �귯�ð� ���� �귯�ÿ� ������ ��� ���� ������ ����
	if (brushType == type && brushColor == color)
		return;

	brushType = type;
	brushColor = color;

	// ���� �귯�ø� ����
	DeleteObject(hCurBrush);

	// �귯�� Ÿ�Կ� ���� �귯�� ��Ÿ���� �ٸ��� ����
	switch (type)
	{
	case BrushType::Solid:
		hCurBrush = CreateSolidBrush(color);
		break;
	case BrushType::Null:
		// Null �귯�ø� ���� ����� ����
		// ��ǻ�ʹ� ����ǥ���� �Ұ��� -> Ư��ó�� �ʿ�
		hCurBrush = static_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
		break;
	default:
		hCurBrush = CreateSolidBrush(color);
		break;
	}
}

void CRenderManager::SetText(int size, COLORREF color, TextAlign align)
{
	// �����ϴ� �ؽ�Ʈ�� ���� �ؽ�Ʈ�� ������ ��� ���� ������ ����
	if (textSize == size && textColor == color && textAlign == align)
		return;

	textSize = size;
	textColor = color;
	textAlign = align;

	DeleteObject(hFont);
	hFont = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("����"));
	SelectObject(hMemDC, hFont);

	SetTextColor(hMemDC, color);

	switch (align)
	{
	case TextAlign::Top:
		SetTextAlign(hMemDC, TA_TOP);
		break;
	case TextAlign::Bottom:
		SetTextAlign(hMemDC, TA_BOTTOM);
		break;
	case TextAlign::Left:
		SetTextAlign(hMemDC, TA_LEFT);
		break;
	case TextAlign::Right:
		SetTextAlign(hMemDC, TA_RIGHT);
		break;
	case TextAlign::Center:
		SetTextAlign(hMemDC, TA_CENTER);
		break;
	default:
		SetTextAlign(hMemDC, TA_TOP);
		break;
	}

}

void CRenderManager::SetTextBackMode(TextBackMode mode, COLORREF backColor)
{
	// �����ϴ� �ؽ�Ʈ ����� ���� �ؽ�Ʈ�� ������ ��� ���� ������ ����
	if (textBackMode == mode && textBackColor == backColor)
		return;

	switch (mode)
	{
	case TextBackMode::Null:
		SetBkMode(hMemDC, TRANSPARENT);
		break;
	case TextBackMode::Solid:
		SetBkMode(hMemDC, OPAQUE);
		break;
	default:
		SetBkMode(hMemDC, TRANSPARENT);
		break;
	}
}
