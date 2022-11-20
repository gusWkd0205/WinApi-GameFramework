#pragma once

//========================================
//##		������ ���� FlyWeight		##
//========================================
/*
	�Ѱ��� ���� �����͸� �ٸ� ��ü�鿡�� �����ϰ� ����� �޸� ��뷮�� ����
	���� �����͸� �����Ͽ� ����ϱ⿡ �ҷ����� �ð��� ����
*/

class CImage;
class CSound;

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

	// �ִϸ��̼� ���� �ʿ�
	//CAnimation*		AnimationFind(const wstring& key);
	//CAnimation*		AnimationLoad(const wstring& key, const wstring file);

	CSound*			SoundFind(const wstring& key);
	CSound*			SoundLoad(const wstring& key, const wstring& file);

	const wstring&	GetResourceFolder()							{ return resourceFolder; }
	void			SetResourceFolder(const wstring& folder)	{ this->resourceFolder = folder; }

private:
	unordered_map<wstring, CImage*>	images;
	unordered_map<wstring, CSound*>	sounds;

	wstring resourceFolder;
};

#define LOADIMAGE(key, file)	CResourceManager::GetInstance()->ImageLoad(key, file)
#define LOADSOUND(key, file)	CResourceManager::GetInstance()->SoundLoad(key, file)