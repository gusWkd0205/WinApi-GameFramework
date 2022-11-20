#include "pch.h"
#include "CCameraManager.h"

CCameraManager::CCameraManager()
{
	lookAt	= Vec2(0, 0);
	target	= nullptr;
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
	if (nullptr != target)
	{
		if (target->IsReservedDelete())
		{
			// ������ ���ӿ�����Ʈ�� ���������� ��� ���� ����
			target = nullptr;
		}
		else
		{
			// ������ ���ӿ�����Ʈ�� ���� ��� ���ӿ�����Ʈ�� ��ġ�� ��ǥ��ġ�� ����
			lookAt = target->GetPos();
		}
	}
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
