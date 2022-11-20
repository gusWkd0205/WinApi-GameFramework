#include "pch.h"
#include "CAnimator.h"

CAnimator::CAnimator()
{
	curAnimation	= nullptr;
	playing			= false;
	ratio			= 1;
	curFrame		= 0;
	curTime			= 0;
}

CAnimator::~CAnimator()
{
}

void CAnimator::AddAnimation(const wstring& aniName, CAnimation* animation)
{
	CAnimation* ani = FindAnimation(aniName);
	assert(nullptr == ani && "Animation already exist");

	animation->SetKey(aniName);
	animation->SetPath(TEXT(""));
	animationMap.insert(make_pair(aniName, animation));
}

void CAnimator::RemoveAnimation(const wstring& aniName)
{
	CAnimation* ani = FindAnimation(aniName);

	if (nullptr != ani)
	{
		animationMap.erase(aniName);
		delete ani;
	}
}

CAnimation* CAnimator::FindAnimation(const wstring& aniName)
{
	auto iter = animationMap.find(aniName);
	if (iter == animationMap.end())
		return nullptr;
	else
		return iter->second;
}

void CAnimator::CreateAnimation(const wstring& aniName, CImage* image, float stepTime, UINT count, bool repeat, Vec2 pos, Vec2 scale, Vec2 step)
{
	CAnimation* ani = new CAnimation();
	ani->Create(image, stepTime, count, repeat, pos, scale, step);
	AddAnimation(aniName, ani);
}

void CAnimator::Play(const wstring& aniName, bool reset)
{
	// ���� �ִϸ��̼��� �÷����ϰ��� �ϴ� �ִϸ��̼��̸�
	// reset �ƴ� ��� ���� �ִϸ��̼��� �������� ����
	// reset : ���� �ִϸ��̼��� ó������ ���
	// (ex. ���� ���ó�� ���������� ó������ ����ؾ��ϴ� �ִϸ��̼�)
	if (playing && aniName == curAnimation->GetKey() && !reset)
		return;

	CAnimation* animation = FindAnimation(aniName);
	assert(nullptr != animation && "Animation no exist");

	// reset �� ��� ó������ ���
	if (reset || curAnimation != animation)
	{
		curFrame = 0;
		curTime = 0;
	}
	curAnimation = animation;
}

void CAnimator::Stop()
{
	playing = false;
}

void CAnimator::ComponentInit()
{
}

void CAnimator::ComponentOnEnable()
{
	Component::ComponentOnEnable();
}

void CAnimator::ComponentUpdate()
{
	// ���� �÷������� �������� �����ð�
	curTime += DT;

	// �����ð��� ���� �÷������� �������� ���ӽð����� Ŀ���� ���
	// -> ���� �������� ������� �ϴ� ���
	if (curAnimation->frames[curFrame].time < curTime)
	{
		curFrame++;	// ���� �÷������� �������� �ε����� �ϳ� ����
		curTime = 0;	// ���� �÷������� �������� �����ð� �ʱ�ȭ

		// ���� �÷������� �������� ������ �������̾��� ���
		if (curFrame == curAnimation->frames.size())
		{
			// �ݺ� �ִϸ��̼��̶�� ó������, �ƴ϶�� �������� �ٽ� ���
			if (curAnimation->repeat)	curFrame = 0;
			else						curFrame--;
		}
	}
}

void CAnimator::ComponentRender()
{
	Vec2 pos = GetOwner()->GetWorldPos();				// �ִϸ��̼��� �׷��� ��ġ Ȯ��
	AniFrame frame = curAnimation->frames[curFrame];	// �ִϸ��̼��� �׷��� ������ Ȯ��

	// ������ �̹��� �׸���
	RENDER->FrameImage(
		curAnimation->image,
		pos.x - frame.scale.x * 0.5f * ratio,
		pos.y - frame.scale.y * 0.5f * ratio,
		pos.x + frame.scale.x * 0.5f * ratio,
		pos.y + frame.scale.y * 0.5f * ratio,
		frame.pos.x,
		frame.pos.y,
		frame.pos.x + frame.scale.x,
		frame.pos.y + frame.scale.y
	);
}

void CAnimator::ComponentOnDisable()
{
	Component::ComponentOnDisable();
}

void CAnimator::ComponentRelease()
{
	for (pair<wstring, CAnimation*> animation : animationMap)
	{
		delete animation.second;
	}
	animationMap.clear();
}
