#pragma
#include "Objects/Functional/CollisionObject.h"

//ToDo : Jump와 Controlloer 컴포넌트 구현 (컴포넌트에서 키를 누르면 owner에게 신호 전달하는 형태)
class PlayerCircle : public CollisionObject
{
public:
	PlayerCircle(Vector2 position, Vector2 scale, Color color = RED, UINT segments = 50);
	~PlayerCircle() override = default;

	void Update() override;
	void Render() override;

	void onCollision(shared_ptr<Collider> target) override; //충돌했을 때의 행동

	void DoJump(float amount);

private:

	bool immuteEnd_Dirty = false; //플레이어의 무적 상태 종료 이벤트를 종료 직후 1회만 실행하기 위한 변수값
	Color damegeColor = RED; //데미지를 받았을시 바뀔 색상
	//Component Precache
private:
	shared_ptr<class Material> material;
	shared_ptr<class MeshRenderer> meshRenderer;
	shared_ptr<class CircleCollider> circleCollider;
	shared_ptr<class BoxCollider> boxCollider;
	shared_ptr<class Jump> jump;
	shared_ptr<class Health> health;

};