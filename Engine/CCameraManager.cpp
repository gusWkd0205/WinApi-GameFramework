#include "pch.h"
#include "CCameraManager.h"

CCameraManager::CCameraManager()
{
	lookAt			= Vec2(0, 0);
	targetPos		= Vec2(0, 0);
	targetObj		= nullptr;
	timeToTarget	= 0;

	fadeImage		= nullptr;
	targetBright	= 1;
	curBright		= 1;
	timeToBright	= 0;
}

CCameraManager::~CCameraManager()
{
}

void CCameraManager::Init()
{
	fadeImage = new CImage();
	fadeImage->Create((UINT)SINGLE(CEngine)->GetWinSize().x, (UINT)SINGLE(CEngine)->GetWinSize().y);
	PatBlt(fadeImage->GetImageDC(), 0, 0, fadeImage->GetBmpWidth(), fadeImage->GetBmpHeight(), BLACKNESS);
}

void CCameraManager::Update()
{
	// ������ ���ӿ�����Ʈ�� ���� ���
	if (nullptr != targetObj)
	{
		if (targetObj->IsReservedDelete())
		{
			// ������ ���ӿ�����Ʈ�� ���������� ��� ���� ����
			targetObj = nullptr;
		}
		else
		{
			// ������ ���ӿ�����Ʈ�� ���� ��� ���ӿ�����Ʈ�� ��ġ�� ��ǥ��ġ�� ����
			targetPos = targetObj->GetPos();
		}
	}

	MoveToTarget();
	BrightToTarget();
}

void CCameraManager::Render()
{
	if (curBright >= 1)
		return;

	RENDER->BlendImage(
		fadeImage,
		0, 0,
		SINGLE(CEngine)->GetWinSize().x,
		SINGLE(CEngine)->GetWinSize().y,
		0, 0,
		(float)(fadeImage->GetBmpWidth()),
		(float)(fadeImage->GetBmpHeight()),
		(1 - curBright)
	);
}

void CCameraManager::Release()
{
	delete fadeImage;
}

Vec2 CCameraManager::WorldToScreenPoint(Vec2 worldPoint)
{
	Vec2 center = SINGLE(CEngine)->GetWinSize() * 0.5f;
	return worldPoint - (lookAt - center);
}

Vec2 CCameraManager::ScreenToWorldPoint(Vec2 screenPoint)
{
	Vec2 center = SINGLE(CEngine)->GetWinSize() * 0.5f;
	return screenPoint + (lookAt - center);
}

void CCameraManager::Scroll(Vec2 dir, float velocity)
{
	// ��ũ���� ���� ũ�Ⱑ ���� ��� �������� ����
	if (dir.Magnitude() == 0)
		return;

	// ��ũ���� ��ǥ ��ġ�� ������ġ���� ��ũ�� �������� ������ ��ġ
	targetPos = lookAt;
	targetPos += dir.Normalized() * velocity * DT;
	timeToTarget = 0;	// ��ũ���� �ð����� ���� ���� �ﰢ �̵�
}

void CCameraManager::FadeIn(float duration)
{
	targetBright = 1;
	timeToBright = duration;
}

void CCameraManager::FadeOut(float duration)
{
	targetBright = 0;
	timeToBright = duration;
}

void CCameraManager::SetTargetPos(const Vec2& targetPos, float timeToTarget)
{
	this->targetPos = targetPos;
	this->timeToTarget = timeToTarget;
}

void CCameraManager::SetTargetObj(CGameObject* targetObj)
{
	this->targetObj = targetObj;
}

void CCameraManager::MoveToTarget()
{
	timeToTarget -= DT;

	if (timeToTarget <= 0)
	{
		// ��ǥ��ġ���� ���� �ð��� ���� ��� �������� ������ġ ����
		lookAt = targetPos;
	}
	else
	{
		// ��ǥ��ġ���� ���� �ð��� ���� ���
		// ���������� �����ð���ŭ�� �ӵ��� �̵�
		// �̵��Ÿ� = �ӷ� * �ð�
		// �ӷ� = (������ - �����) / �ҿ�ð�
		// �ð� = �����Ӵ����ð�
		lookAt += (targetPos - lookAt) / timeToTarget * DT;
	}
}

void CCameraManager::BrightToTarget()
{
	timeToBright -= DT;

	if (timeToBright <= 0)
	{
		// ��ǥ��ġ���� ���� �ð��� ���� ��� �������� ������ġ ����
		curBright = targetBright;
	}
	else
	{
		// ��ǥ��ġ���� ���� �ð��� ���� ���
		// ���������� �����ð���ŭ�� �ӵ��� �̵�
		// �̵��Ÿ� = �ӷ� * �ð�
		// �ӷ� = (������ - �����) / �ҿ�ð�
		// �ð� = �����Ӵ����ð�
		curBright += (targetBright - curBright) / timeToBright * DT;
		if		(curBright > 1) curBright = 1;
		else if (curBright < 0) curBright = 0;
	}
}
