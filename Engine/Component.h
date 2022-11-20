#pragma once

// ���������� ������Ʈ :
// ���� ���� ��ü��� ������ ���� ��ü�� ���� ��ü��
// Ŭ���̾�Ʈ���� ���� ���� �ٷ�� ���ִ� ����
// ��ü-�κ��� ���踦 ���� ��ü�� ������ ���踦 ������ �� ����
// Ʈ���� ������ ������ ��
// 
// �������α׷��� ������Ʈ : 
// ���α׷��ֿ� �־� ��� ������ ������ ������ ������ ���
// ������Ʈ �������� �θ� ���Ե� ��� ���������� �����ϴ� �ڽ� ���� ���
// ����� ��� ��� ����ϴ� �ڽĿ��� �ݵ�� ����� ���Ե�����
// ������Ʈ�� ��� �ʿ��� ��ü���� ���������� ���� �� ����

template <typename T>
class Component
{
public:
	Component() {}
	virtual ~Component() {}

public:
	virtual void	ComponentInit()			= 0;
	virtual void	ComponentOnEnable()		{ active = true; }
	virtual void	ComponentUpdate()		= 0;
	virtual void	ComponentRender()		= 0;
	virtual void	ComponentOnDisable()	{ active = false; }
	virtual void	ComponentRelease()		= 0;

public:
	T*				GetOwner()				{ return owner; }
	bool			IsActive()				{ return active; }

protected:
	void			SetOwner(T* owner)		{ this->owner = owner; }
	void			SetActive(bool active)	{ this->active = active; }

protected:
	T*				owner					= nullptr;
	bool			active					= false;
};

template <typename T>
class Composite abstract : public Component<T>
{
public:
	Composite() {}
	virtual ~Composite() {}

public:
	void ComponentInit() override
	{
	}

	void ComponentOnEnable() override
	{
		this->active = true;
		for (Component<T>* component : childList)
		{
			component->ComponentOnEnable();
		}
	}

	void ComponentUpdate() override
	{
		for (Component<T>* component : childList)
		{
			component->ComponentUpdate();
		}
	}

	void ComponentRender() override
	{
		for (Component<T>* component : childList)
		{
			component->ComponentRender();
		}
	}

	void ComponentOnDisable() override
	{
		for (Component<T>* component : childList)
		{
			component->ComponentOnDisable();
		}
		this->active = false;
	}

	void ComponentRelease() override
	{
		for (Component<T>* component : childList)
		{
			component->ComponentRelease();
			delete component;
		}
		childList.clear();
	}

protected:
	void AddChild(Component<T>* component)
	{
		childList.push_back(component);
		component->SetOwner((T*)this);
		component->ComponentInit();
		if (this->IsActive()) component->ComponentOnEnable();
	}

	void RemoveChild(Component<T>* component)
	{
		if (this->IsActive()) component->ComponentOnDisable();
		component->ComponentRelease();
		component->SetOwner(nullptr);
		childList.remove(component);
		delete component;
	}

protected:
	list<Component<T>*> childList;
};