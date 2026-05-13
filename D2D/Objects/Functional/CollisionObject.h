#pragma once
#include "Objects/Object.h"
#include "Components/Collision/Collider.h"

class CollisionObject : public Object
{
public:
	CollisionObject(Vector2 position, Vector2 scale = { 1, 1 }, float rotation = 0.0f);
	~CollisionObject() override = default;

	void Update();

	void AddTarget(const string& name, shared_ptr<Collider> target); //부딛힐 대상 추가

	void RemoveTarget(const string& name); //부딛힐 대상 제거

	void ClearTargets() { targets.clear(); targetTransforms.clear(); } //부딛힐 대상 리스트 초기화

	virtual void onCollision(shared_ptr<Collider> target, shared_ptr<Transform> targetTransform) = 0; //target과 충돌했을 때의 실행할 함수 콜백.

	float calculationDistance = 500.f; //충돌 계산을 시작할 거리. 이보다 멀리 있는 대상과는 충돌 계산을 하지 않음. 단위는 픽셀
protected:
	unordered_map<string, shared_ptr<Collider>> targets; //부딛힐 대상들 (플레이어 등등..) 각자 이름을 가지게 하여 오브젝트를 특정 하거나 중복을 방지, 구분할 수 있도록 함

	unordered_map<string, shared_ptr<Transform>> targetTransforms; /*
	부딛힐 대상들의 Transform 컴포넌트.
	충돌 계산 시작 거리를 계산하기 위해 필요.Collider 컴포넌트와 별도로 보관하여 
	충돌 계산 시작 거리 계산 시 대상의 위치를 매번 
	GetOwnder()->GetTransform()->GetPosition()으로 찾아서 가져오는 것을 방지하여 성능 향상을 의도함
	*/

	//Component Precache
	shared_ptr<class Collider> collider = nullptr;
	//CollisionObject를 상속받는 객체들은 Collider 컴포넌트를 반드시 가지고 있지만 
	//다형성을 고려해 선언만 하고 실제 Collider 컴포넌트는 CollisionObject를 상속받는 클래스에서 precache하도록 함
	shared_ptr<Transform> transform = nullptr; //충돌 계산을 위해 CollisionObject의 Transform 컴포넌트 precache
};