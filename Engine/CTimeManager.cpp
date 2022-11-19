#include "pch.h"
#include "CTimeManager.h"

CTimeManager::CTimeManager()
{
	fps = 1;
	dt = 1;
	updateCount = 0;
	updateOneSecond = 0;

	prevTime = {};
	curTime = {};
}

CTimeManager::~CTimeManager()
{
}

void CTimeManager::Init()
{
	prevTime = chrono::high_resolution_clock::now();
	curTime = chrono::high_resolution_clock::now();
}

void CTimeManager::Update()
{
	// ���������ӿ��� ���������ӱ��� �ɸ� �ð��� ����
	// �����ð� = ���������ӽð� - ���������ӽð�
	curTime = chrono::high_resolution_clock::now();
	chrono::duration<float> elapsed = curTime - prevTime;

	dt = elapsed.count();
	if (dt > 0.1f) dt = 0.1f;
	prevTime = curTime;

	// 1�ʰ� �ɸ������� �ݺ��� Ƚ���� �ʴ������Ӽ�
	updateCount++;
	updateOneSecond += dt;
	if (updateOneSecond >= 1.0)
	{
		fps = updateCount;
		updateOneSecond = 0;
		updateCount = 0;
	}
}

void CTimeManager::Release()
{
}

UINT CTimeManager::GetFPS()
{
	return fps;
}

float CTimeManager::GetDT()
{
	return dt;
}
