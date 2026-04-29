#include "stdafx.h"
#include "FollowObject.h"
#include "Components/Transform.h"

FollowObject::FollowObject(int followPosition, int followScale, bool followRotation, float delayTime, const string& name)
	: Component(name), followPosition(followPosition), followScale(followScale), followRotation(followRotation), followDelayTime(delayTime)
{
	if (this->GetOwner()->GetTransform() != nullptr)
		ownerTransform = this->GetOwner()->GetTransform();
}

void FollowObject::doFollowWith(shared_ptr<Transform> target)
{
	if (target != nullptr)
	{
		followingObject = target;
	}
}


void FollowObject::Update()
{
	if (ownerTransform != nullptr && followingObject != nullptr)
	{
		if (followPosition != 0x00)
		{
			switch (followPosition)
			{
			case(0x10):
			{
				ownerTransform->SetPosition(
					Vector2(followingObject->GetPosition().x, ownerTransform->GetPosition().y));
				break;
			}
			case(0x01):
			{
				ownerTransform->SetPosition(
					Vector2(ownerTransform->GetPosition().x, followingObject->GetPosition().y));
				break;
			}
			case(0x11):
			{
				ownerTransform->SetPosition(followingObject->GetPosition());
			break;
			}
			}
		}
		if (followScale != 0x00)
		{
			switch (followScale)
			{
			case(0x10):
			{
				ownerTransform->SetScale(
					Vector2(followingObject->GetScale().x, ownerTransform->GetScale().y));
				break;
			}
			case(0x01):
			{
				ownerTransform->SetScale(
					Vector2(ownerTransform->GetScale().x, followingObject->GetScale().y));
				break;
			}
			case(0x11):
			{
				ownerTransform->SetScale(followingObject->GetScale());
				break;
			}
			}
		}
		if (followRotation)
			ownerTransform->SetRotationRadian(followingObject->GetRotationRadian());
	}
}