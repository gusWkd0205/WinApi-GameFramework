#include "pch.h"
#include "CPathManager.h"

CPathManager::CPathManager()
{
}

CPathManager::~CPathManager()
{
}

void CPathManager::Init()
{
	WCHAR pathArray[255] = {};				// ��θ� �ޱ� ���� ���ڿ�
	GetCurrentDirectory(255, pathArray);	// ���� ��θ� Ȯ��
	path = wstring(pathArray);				// ���ڿ��� wstring���� ��ȯ

	Logger::Debug(TEXT("���� ���"));
	Logger::Debug(path);
}

void CPathManager::Release()
{
}

const wstring& CPathManager::GetPath()
{
	return path;
}
