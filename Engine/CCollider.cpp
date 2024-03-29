#include "pch.h"
#include "CCollider.h"

UINT CCollider::colliderCount = 0;

CCollider::CCollider()
{
	id		= colliderCount++;
	count	= 0;
	layer	= 0;
	pos		= Vec2(0, 0);
	offset	= Vec2(0, 0);
	scale	= Vec2(0, 0);
	zOrder	= -10;
}

CCollider::~CCollider()
{
}

bool CCollider::IsCollision(CCollider* other)
{
	// �簢 �浹
	if (abs(GetPos().x - other->GetPos().x) < (GetScale().x + other->GetScale().x) * 0.5f &&
		abs(GetPos().y - other->GetPos().y) < (GetScale().y + other->GetScale().y) * 0.5f)
		return true;
	else
		return false;
}

void CCollider::Render()
{
	Vec2 renderPos = CAMERA->WorldToScreenPoint(pos);

	if (count > 0)
		RENDER->SetPen(PenType::Solid, RGB(255, 0, 0));
	else
		RENDER->SetPen(PenType::Solid, RGB(0, 255, 0));
	RENDER->SetBrush(BrushType::Null);

	RENDER->Rect(
		renderPos.x - scale.x * 0.5f,
		renderPos.y - scale.y * 0.5f,
		renderPos.x + scale.x * 0.5f,
		renderPos.y + scale.y * 0.5f);

	RENDER->SetPen();
	RENDER->SetBrush();
}

void CCollider::ComponentInit()
{
}

void CCollider::ComponentOnEnable()
{
	SINGLE(CCollisionManager)->AddCollider(this);
	Component::ComponentOnEnable();
}

void CCollider::ComponentUpdate()
{
	pos = GetOwner()->GetWorldPos() + offset;
}

void CCollider::ComponentRender()
{
	GetScene()->AddRenderer(this);
}

void CCollider::ComponentOnDisable()
{
	Component::ComponentOnDisable();
	SINGLE(CCollisionManager)->RemoveCollider(this);
}

void CCollider::ComponentRelease()
{
}

void CCollider::OnCollisionEnter(CCollider* other)
{
	count++;
	GetOwner()->OnCollisionEnter(other);
}

void CCollider::OnCollisionStay(CCollider* other)
{
	GetOwner()->OnCollisionStay(other);
}

void CCollider::OnCollisionExit(CCollider* other)
{
	count--;
	GetOwner()->OnCollisionExit(other);
}
