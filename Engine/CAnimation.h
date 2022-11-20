#pragma once
#include "CResource.h"

class CAnimator;
class CImage;

struct AniFrame
{
	Vec2	pos;
	Vec2	scale;
	float	time;
};

class CAnimation : public CResource
{
	friend CAnimator;
public:
	CAnimation();
	virtual ~CAnimation();

public:
	const static UINT	FRAME_SIZE = 128;

	// void				Load(const wstring& path);	�ִϸ��̼��� �ܺ� ���ҽ��� ���� �ҷ����� ���� �ִϸ��̼� ���� ����
	void				Create(CImage* image, float stepTime, UINT count, bool repeat,
							Vec2 pos, Vec2 scale, Vec2 step);	// ���� �������� ������ ����

private:
	CImage*				image;		// �ִϸ��̼� �̹���
	vector<AniFrame>	frames;		// �ִϸ��̼� �����ӵ�
	bool				repeat;		// �ִϸ��̼� �ݺ�����
};

