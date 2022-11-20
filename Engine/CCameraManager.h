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

	void				SetTargetPos(const Vec2& targetPos, float timeToTarget = 0);
	void				SetTargetObj(CGameObject* targetObj);

	const Vec2&			GetLookAt()							{ return lookAt; }
	const Vec2&			GetTargetPos()						{ return targetPos; }
	const CGameObject*	GetTargetObj()						{ return targetObj; }

private:
	void				MoveToTarget();

	// ��ǥ ������Ʈ�� ������ ��� ��ǥ ��ġ�� ��ǥ ������Ʈ�� ��ġ�� ������
	Vec2				lookAt;			// ī�޶� �����ִ� ��ġ
	Vec2				targetPos;		// ī�޶��� ��ǥ ��ġ
	CGameObject*		targetObj;		// ī�޶��� ��ǥ ������Ʈ

	float				timeToTarget;	// ��ǥ���� ���� �ð�
};

#define CAMERA	CCameraManager::GetInstance()