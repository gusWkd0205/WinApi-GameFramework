#include "pch.h"
#include "CSoundManager.h"

CSoundManager::CSoundManager()
{
	system = nullptr;
}

CSoundManager::~CSoundManager()
{
}

void CSoundManager::Init()
{
	// ���� �ý��� ����
	FMOD_RESULT result;
	result = System_Create(&system);
	assert(FMOD_OK == result && "Create sound system falied");

	result = system->init(MAXCHANNEL, FMOD_INIT_NORMAL, nullptr);
	assert(FMOD_OK == result && "Init sound system falied");
}

void CSoundManager::Update()
{
	/* IMPORTANT! CALL THIS ONCE PER FRAME! */
	// FMOD �ý����� ���带 �����ϱ� ���� �����Ӹ��� ȣ�� �ʿ�
	FMOD_RESULT result = system->update();
	assert(FMOD_OK == result && "Update sound system falied");
}

void CSoundManager::Release()
{
	if (nullptr != system)
	{
		system->release();
		system->close();
	}
}
