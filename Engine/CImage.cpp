#include "pch.h"
#include "CImage.h"

CImage::CImage()
{
	hDC = 0;
	hBmp = 0;
	bmpInfo = {};
}

CImage::~CImage()
{
	DeleteDC(hDC);
	DeleteObject(hBmp);
}

void CImage::Load(const wstring path)
{
	hBmp = (HBITMAP)LoadImage(
		nullptr,								// hInstance. nullptr�� �ص� ��.
		path.c_str(),							// ���� ��θ� C style ���ڿ��� ��ȯ
		IMAGE_BITMAP,							// �̹��� Ÿ��, ��Ʈ�� �̹����� ����
		0, 0,									// �̹����� X, Y ũ��, 0�� �ָ� �̹��� ũ��� ����
		LR_CREATEDIBSECTION | LR_LOADFROMFILE	// �̹��� �ε� Ÿ��.
	);

	assert(hBmp && "Image Load Failed");		// �̹����� ���ٸ� assert�� ���� ����

	hDC = CreateCompatibleDC(MAINDC);			// ��Ʈ���̹����� ������ DC ����
	SelectObject(hDC, hBmp);					// ��Ʈ���̹����� DC ����
	GetObject(hBmp, sizeof(BITMAP), &bmpInfo);	// ��Ʈ���̹��� ���� ����
}

void CImage::Create(UINT sizeX, UINT sizeY)
{
	hBmp = CreateCompatibleBitmap(MAINDC, sizeX, sizeY);
	hDC = CreateCompatibleDC(MAINDC);

	HBITMAP hOldBmp = (HBITMAP)SelectObject(hDC, hBmp);
	DeleteObject(hOldBmp);

	GetObject(hBmp, sizeof(BITMAP), &bmpInfo);
}
