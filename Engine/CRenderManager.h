#pragma once
class CRenderManager : public SingleTon<CRenderManager>
{
	friend SingleTon<CRenderManager>;
private:
	CRenderManager();
	virtual ~CRenderManager();

public:
	void		Init();
	void		BeginDraw();
	void		EndDraw();
	void		Release();

	void		Pixel(float x, float y, COLORREF color);						// �ȼ� �׸���
	void		Line(float startX, float startY, float endX, float endY);		// �� �׸���
	void		Rect(float startX, float startY, float endX, float endY);		// �簢�� �׸���
	void		Circle(float x, float y, float radius);							// �� �׸���
	void		Ellipse(float startX, float startY, float endX, float endY);	// Ÿ�� �׸���
	void		Text(float x, float y, wstring str);							// �ؽ�Ʈ �׸���

private:
	HWND		hWnd;			// ������ �ڵ�
	HDC			hDC;			// ����Ʈ����(��� ����ȭ��)�� �׸� dc
	HDC			hMemDC;			// �����(�׸����� ����ȭ��)�� �׸� dc
	HBITMAP		hBMP;			// ����ۿ� ��Ʈ��(�̹���)
	Vec2		winSize;		// ������ ������
};

#define RENDER		CRenderManager::GetInstance()