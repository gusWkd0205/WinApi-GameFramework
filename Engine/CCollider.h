#pragma once

class CCollisionManager;

class CCollider : public Component<CGameObject>, public IRender
{
	friend CCollisionManager;
public:
	CCollider();
	virtual ~CCollider();

public:
	UINT			GetLayer()						{ return layer; }
	const Vec2&		GetPos()						{ return pos; }
	const Vec2&		GetOffset()						{ return offset; }
	const Vec2&		GetScale()						{ return scale; }

	void			SetLayer(UINT layer)			{ this->layer = layer; }
	void			SetPos(const Vec2& pos)			{ this->pos = pos; }
	void			SetOffset(const Vec2& offset)	{ this->offset = offset; }
	void			SetScale(const Vec2 scale)		{ this->scale = scale; }

private:
	virtual	bool	IsCollision(CCollider* other);

	void			Render()						override;

	void			ComponentInit()					override;
	void			ComponentOnEnable()				override;
	void			ComponentUpdate()				override;
	void			ComponentRender()				override;
	void			ComponentOnDisable()			override;
	void			ComponentRelease()				override;

	UINT			layer;							// �浹ü�� ���̾�
	Vec2			pos;
	Vec2			offset;							// �浹ü�� ������
	Vec2			scale;

private:
	// �浹���� �Լ�
	void			OnCollisionStay(CCollider* other);		// �浹 ��
};
