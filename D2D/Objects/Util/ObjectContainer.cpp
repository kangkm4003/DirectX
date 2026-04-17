#include "stdafx.h"
#include "ObjectContainer.h"
#include "Components/Transform.h"

ObjectContainer::ObjectContainer(Vector2 position, Vector2 scale, float rotation, int size) //ObjectGroup의 scale필드값은 멤버 오브젝트들의 scale 배율을 의미함 (1 = 기본 크기) [미완]
	: Object("ObjectContainer", position, scale, rotation)
{
	if (size > 0)
		members.reserve(size); //member vector의 크기(담을 오브젝트의 양)
}

void ObjectContainer::Add(shared_ptr<Object> targetObject, Vector2 groupPosition) //오브젝트 그룹에 멤버 추가
{
	if (targetObject == nullptr) //만약 대상이 유효하지 않다면 (객체가 존재하지 않음)
		return;

	targetObject->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + groupPosition);
	members.push_back(move(targetObject));
}

void ObjectContainer::Insert(shared_ptr<Object> targetObject, Vector2 groupPosition, int index) //오브젝트 그룹에 멤버 특정 인덱스에 삽입 (update 순서)
{
	if (targetObject == nullptr) //만약 대상이 유효하지 않다면 (객체가 존재하지 않음)
		return;

	if (index >= 0 || index <= members.size()) //유효한 값을 입력 했을시 (-1 이하 혹은 현재 크기를 넘어선 인덱스가 아님)
	{
		members.insert(members.begin() + index, move(targetObject));
	}
}