#pragma once

// ���ҽ� : ���ӿ� �ʿ��� �ڵ� ���� �ڿ�
// ex) �̹���, ����, �ִϸ��̼�, ��
class CResource
{
public:
	CResource();
	virtual ~CResource();

public:
	const		wstring& GetKey()				{ return key; }
	const		wstring& GetPath()				{ return path; }

	void		SetKey(const wstring& key)		{ this->key = key; }
	void		SetPath(const wstring& path)	{ this->path = path; }

protected:
	wstring		key;							// ���ҽ��� Ž���� Ű
	wstring		path;							// ���ҽ��� ���
};
