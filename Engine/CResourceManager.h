#pragma once

//========================================
//##		������ ���� FlyWeight		##
//========================================
/*
	�Ѱ��� ���� �����͸� �ٸ� ��ü�鿡�� �����ϰ� ����� �޸� ��뷮�� ����
	���� �����͸� �����Ͽ� ����ϱ⿡ �ҷ����� �ð��� ����
*/

class CResourceManager : public SingleTon<CResourceManager>
{
	friend SingleTon<CResourceManager>;
private:
	CResourceManager();
	virtual ~CResourceManager();

public:
	void			Init();
	void			Release();

	CImage*			ImageFind(const wstring& key);
	CImage*			ImageLoad(const wstring& key, const wstring& file);

	const wstring&	GetResourceFolder()							{ return resourceFolder; }
	void			SetResourceFolder(const wstring& folder)	{ this->resourceFolder = folder; }

private:
	unordered_map<wstring, CImage*>	images;

	wstring resourceFolder;
};

#define LOADIMAGE(key, file)	CResourceManager::GetInstance()->ImageLoad(key, file)