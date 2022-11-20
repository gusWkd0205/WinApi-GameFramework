#include "pch.h"
#include "CCameraManager.h"

CCameraManager::CCameraManager()
{
	lookAt			= Vec2(0, 0);
	targetPos		= Vec2(0, 0);
	targetObj		= nullptr;
	timeToTarget	= 0;
}

CCameraManager::~CCameraManager()
{
}

void CCameraManager::Init()
{
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
}

void CCameraManager::Release()
{
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
