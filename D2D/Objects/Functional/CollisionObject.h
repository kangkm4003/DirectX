#pragma once
#include "Objects/Object.h"

class CollisionObject : public Object
{
public:
	CollisionObject(Vector2 position, Vector2 scale = { 1, 1 }, float rotation = 0.0f);
	~CollisionObject() override = default;

	void Update();

	void AddTarget(const string& name, shared_ptr<Collider> target); //부딛힐 대상 추가
	void RemoveTarget(const string& name); //부딛힐 대상 제거
	void ClearTargets() { targets.clear(); } //부딛힐 대상 리스트 초기화

	virtual void onCollision(shared_ptr<Collider> target) = 0; //충돌했을 때의 행동, 충돌 대상이 매개변수로 들어옴, 충돌 대상이 여러개일 수 있으므로 리스트로 받는 것도 고려해볼 수 있음

protected:
	unordered_map<string, shared_ptr<Collider>> targets; //부딛힐 대상들 (플레이어 등등..) 각자 이름을 가지게 하여 오브젝트를 특정 하거나 중복을 방지, 구분할 수 있도록 함

	//Component Precache
	shared_ptr<class Collider> collider;
	shared_ptr<class Transform> transform;
};