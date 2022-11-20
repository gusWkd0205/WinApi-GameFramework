#pragma once

class CImage;

enum class PenType { Solid, Dot, Dash, Null };
enum class BrushType { Solid, Null };
enum class TextAlign { Top, Bottom, Left, Right, Center };
enum class TextBackMode { Solid, Null };

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

	void		BitImage(CImage* pImg, float startX, float startY, float endX, float endY);			// �̹��� �׸���
	void		StrectchImage(CImage* pImg, float startX, float startY, float endX, float endY);	// ũ�⺯���̹��� �׸���
	void		TransparentImage(CImage* pImg, float startX, float startY, float endX, float endY,	// �����̹��� �׸���
								COLORREF transparent = RGB(255, 0, 255));
	void		FrameImage(CImage* pImg,
					float dstStartX, float dstStartY, float dstEndX, float dstEndY,
					float srcStartX, float srcStartY, float srcEndX, float srcEndY,
					COLORREF transparent = RGB(255, 0, 255));		// �̹��� �Ϻκ� �׸���

	void		SetPen(PenType type = PenType::Solid, COLORREF color = RGB(0, 0, 0), int width = 1);
	void		SetBrush(BrushType type = BrushType::Solid, COLORREF color = RGB(255, 255, 255));
	void		SetText(int size = 10, COLORREF color = RGB(0, 0, 0), TextAlign align = TextAlign::Center);
	void		SetTextBackMode(TextBackMode mode = TextBackMode::Null, COLORREF color = RGB(255, 255, 255));

	HDC			GetMemDC() { return hMemDC; }

private:
	HWND			hWnd;			// ������ �ڵ�
	HDC				hDC;			// ����Ʈ����(��� ����ȭ��)�� �׸� dc
	HDC				hMemDC;			// �����(�׸����� ����ȭ��)�� �׸� dc
	HBITMAP			hBMP;			// ����ۿ� ��Ʈ��(�̹���)
	Vec2			winSize;		// ������ ������

	// ��
	HPEN			hCurPen;
	PenType			penType;
	int				penWidth;
	COLORREF		penColor;

	// �귯��
	HBRUSH			hCurBrush;
	BrushType		brushType;
	COLORREF		brushColor;

	// �ؽ�Ʈ
	HFONT			hFont;
	int				textSize;
	COLORREF		textColor;
	TextAlign		textAlign;
	TextBackMode	textBackMode;
	COLORREF		textBackColor;
};

#define RENDER		CRenderManager::GetInstance()
#define MAINDC		CRenderManager::GetInstance()->GetMemDC()