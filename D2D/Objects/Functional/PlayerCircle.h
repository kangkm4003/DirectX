#pragma
#include "Objects/Functional/CollisionObject.h"

class PlayerCircle : public CollisionObject
{
public:
	PlayerCircle(Vector2 position, Vector2 scale, Color color = GREEN, UINT segments = 50);
	~PlayerCircle() override = default;

	void Update() override;
	void Render() override;

	void onCollision(shared_ptr<Collider> target, shared_ptr<Transform> targetTransform) override; //충돌했을 때의 행동

	void DoJump(float amount);
	void StartFever();

	void ImmuteEnd();
private:
	bool immuteEnd_Dirty = false; //플레이어의 무적 상태 종료 이벤트를 종료 직후 1회만 실행하기 위한 변수값
	Color damegeColor = RED; //데미지를 받았을시 바뀔 색상
	Color originalColor = GREEN; //색상이 바뀌고 돌아갈때의 색상

	//조작키
	int jumpKey = VK_SPACE; //점프키를 스페이스바로 지정
	int feverKey = VK_LSHIFT; //피버 시작키를 왼쪽 쉬프트로 지정


	float jumpAmount = 800.f;
	float gravity = 2000.f;
	int maxJumpCount = 1; //최대 공중 점프 횟수
	int curJumpCount = 0; //현재 공중 점프 횟수
	bool onAir = true; //현재 공중에 뜬 상태인지

private:
	void DoJump(float amount); //점프
	void Land(); //바닥에 착지함 speed 초기화
	float speed = 0.f; // owner가 매 Update마다 이동할 거리(DELTA 미적용)

	//Component Precache
private:
	shared_ptr<class Material> material;
	shared_ptr<class MeshRenderer> meshRenderer;
	shared_ptr<class CircleCollider> circleCollider;
	shared_ptr<class BoxCollider> boxCollider;
	shared_ptr<class Jump> jump;
	shared_ptr<class Health> health;
	shared_ptr<class Fever> fever;

};