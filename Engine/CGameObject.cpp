#include "pch.h"
#include "CGameObject.h"

CGameObject::CGameObject()
{
	name	= TEXT("");
	pos		= Vec2(0, 0);
	scale	= Vec2(0, 0);
	zOrder	= 0;
}

CGameObject::~CGameObject()
{
}

void CGameObject::ComponentInit()
{
	Init();
	Composite::ComponentInit();
}

void CGameObject::ComponentOnEnable()
{
	OnEnable();
	Composite::ComponentOnEnable();
}

void CGameObject::ComponentUpdate()
{
	if (IsReservedDelete())
		return;

	// �θ� ���ӿ�����Ʈ�� �ִ� ���, ��ġ�� �θ� ���������� �����ġ
	if (GetOwner() != nullptr)
		worldPos = GetOwner()->GetWorldPos() + pos;
	// �θ� ���ӿ�����Ʈ�� ���� ���, ��ġ�� ���带 ���������� ������ġ
	else
		worldPos = pos;

	renderPos = SINGLE(CCameraManager)->WorldToScreenPoint(worldPos);

	Update();
	Composite::ComponentUpdate();
}

void CGameObject::ComponentRender()
{
	if (IsReservedDelete())
		return;

	GetScene()->AddRenderer(this);
	Composite::ComponentRender();
}

void CGameObject::ComponentOnDisable()
{
	Composite::ComponentOnDisable();
	OnDisable();
}

void CGameObject::ComponentRelease()
{
	Composite::ComponentRelease();
	Release();
}
