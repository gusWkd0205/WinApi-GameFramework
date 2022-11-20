#include "pch.h"
#include "CUI.h"

CUI::CUI()
{
	name		= TEXT("");
	pos			= Vec2(0, 0);
	worldPos	= Vec2(0, 0);
	renderPos	= Vec2(0, 0);
	scale		= Vec2(0, 0);
	screenFixed	= true;
	show		= true;
}

CUI::~CUI()
{
}

void CUI::ComponentInit()
{
	Composite::ComponentInit();
}

void CUI::ComponentOnEnable()
{
	Composite::ComponentOnEnable();
}

void CUI::ComponentUpdate()
{
	if (IsReservedDelete())
		return;

	// �θ� ���ӿ�����Ʈ�� �ִ� ���, ��ġ�� �θ� ���������� �����ġ
	if (GetOwner() != nullptr)
		worldPos = GetOwner()->GetWorldPos() + pos;
	// �θ� ���ӿ�����Ʈ�� ���� ���, ��ġ�� ���带 ���������� ������ġ
	else
		worldPos = pos;

	if (IsScreenFixed())
		renderPos = worldPos;
	else
		renderPos = SINGLE(CCameraManager)->WorldToScreenPoint(worldPos);

	Composite::ComponentUpdate();
}

void CUI::ComponentRender()
{
	if (IsReservedDelete() || !IsShow())
		return;

	Composite::ComponentRender();
}

void CUI::ComponentOnDisable()
{
	Composite::ComponentOnDisable();
}

void CUI::ComponentRelease()
{
	Composite::ComponentRelease();
}
