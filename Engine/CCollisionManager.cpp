#include "pch.h"
#include "CCollisionManager.h"

CCollisionManager::CCollisionManager()
{
	ResetCheck();
}

CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::Init()
{
}

void CCollisionManager::Update()
{
	for (UINT left = 0; left < MAXLAYER; left++)
	{
		for (UINT right = left; right < MAXLAYER; right++)
		{
			if (layerMask[left][right])
			{
				CollisionUpdate(left, right);
			}
		}
	}
}

void CCollisionManager::Release()
{
}

void CCollisionManager::AddCollider(CCollider* collider)
{
	colliderList[collider->GetLayer()].push_back(collider);
}

void CCollisionManager::RemoveCollider(CCollider* collider)
{
	colliderList[collider->GetLayer()].remove(collider);
}

void CCollisionManager::CheckLayer(UINT left, UINT right)
{
	layerMask[left][right] = true;
	layerMask[right][left] = true;
}

void CCollisionManager::UnCheckLayer(UINT left, UINT right)
{
	layerMask[left][right] = false;
	layerMask[right][left] = false;
}

void CCollisionManager::ResetCheck()
{
	for (UINT i = 0; i < layerMask.size(); i++)
		layerMask[i].fill(false);
}

void CCollisionManager::CollisionUpdate(UINT left, UINT right)
{
	for (CCollider* leftCollider : colliderList[left])
	{
		for (CCollider* rightCollider : colliderList[right])
		{
			// �ڱ� �ڽŰ��� �浹�� ����
			if (leftCollider == rightCollider)
				continue;

			// �浹ü�� �浹ü�� ID Ȯ��
			UINT64 collisionID = CollisionID(leftCollider->GetID(), rightCollider->GetID());
			// �浹 ������ ������ ���, �浹���� ���� ���¸� �߰�
			if (prevCollision.find(collisionID) == prevCollision.end())
				prevCollision.insert(make_pair(collisionID, false));

			// �浹ó�� Ȯ��
			if (leftCollider->IsCollision(rightCollider))
			{
				// ���� ������ O, ���� ������ O
				if (prevCollision[collisionID])
				{
					leftCollider->OnCollisionStay(rightCollider);
					rightCollider->OnCollisionStay(leftCollider);
				}
				// ���� ������ X, ���� ������ O
				else
				{
					leftCollider->OnCollisionEnter(rightCollider);
					rightCollider->OnCollisionEnter(leftCollider);
				}
				prevCollision[collisionID] = true;
			}
			else
			{
				// ���� ������ O, ���� ������ X
				if (prevCollision[collisionID])
				{
					leftCollider->OnCollisionExit(rightCollider);
					rightCollider->OnCollisionExit(leftCollider);
				}
				// ���� ������ X, ���� ������ X
				else
				{
					// �ƹ��͵� ���� ����
				}
				prevCollision[collisionID] = false;
			}
		}
	}
}

UINT64 CCollisionManager::CollisionID(UINT leftID, UINT rightID)
{
	UINT64 result = 0;
	if (leftID < rightID)
	{
		result |= (UINT64)leftID << 32;
		result |= rightID;
		return result;
	}
	else
	{
		result |= (UINT64)rightID << 32;
		result |= leftID;
		return result;
	}
}
