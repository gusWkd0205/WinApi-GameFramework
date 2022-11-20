#pragma once
class CCameraManager : public SingleTon<CCameraManager>
{
	friend SingleTon<CCameraManager>;
private:
	CCameraManager();
	virtual ~CCameraManager();

public:
	void				Init();
	void				Update();
	void				Release();

	Vec2				WorldToScreenPoint(Vec2 worldPoint);	// ������ġ->ȭ����ġ
	Vec2				ScreenToWorldPoint(Vec2 screenPoint);	// ȭ����ġ->������ġ

	const Vec2&			GetLookAt()						{ return lookAt; }
	const CGameObject*	GetTarget()						{ return target; }

	void				SetLookAt(const Vec2& lookAt)	{ this->lookAt = lookAt; }
	void				SetTarget(CGameObject* target)	{ this->target = target; }

private:
	// ��ǥ ������Ʈ�� ������ ��� ��ǥ ��ġ�� ��ǥ ������Ʈ�� ��ġ�� ������
	Vec2				lookAt;		// ī�޶� �����ִ� ��ġ
	CGameObject*		target;		// ī�޶��� ��ǥ ������Ʈ
};

#define CAMERA	CCameraManager::GetInstance()