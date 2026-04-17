#pragma once
#include "Scene.h"

class Scene2 : public Scene
{
public:
	void Init() override;
	void Destroy() override;

	void Update() override;
	void Render() override;

	void PlayerDamegedEvent(int damege, float immuteTime); //플레이어가 데미지를 입음
	void PlayerDeadEvent(); //플레이어가 체력이 0이 되어 사망함
	void AddScore(int amount) { score += amount; }
	void ResetObstacle(shared_ptr<Transform> target);
	void AddFeverGaugeEvent(float amount);
	void startFeverEvent();

	void PlayerImmuteEndEvent();
private:
	shared_ptr<class PlayerCircle> playerCircle;
	shared_ptr<class CircleCollider> playerCircleCollider;
	shared_ptr<class BoxCollider> playerBoxCollider;
	shared_ptr<class Collider> playerCollider;
	shared_ptr<class Jump> playerCircleJump;
	shared_ptr<class ObjectContainer>playerAfterImageObjects;

	shared_ptr<class ColorRect> floor;
	shared_ptr<BoxCollider> floorCollider;

	shared_ptr<ObjectContainer> objects;
	vector<pair<shared_ptr<BoxCollider>, shared_ptr<Transform>>> boxObstacles;
	vector<pair<shared_ptr<CircleCollider>, shared_ptr<Transform>>> circleObstacles;
	vector<pair<shared_ptr<CircleCollider>, shared_ptr<Transform>>> coins;

	pair<float, float> spawnRange = { 300.f, 1000.f }; //물체들의 x좌표 랜덤스폰 지점 (화면 중앙 기준)
	float defaultScrollSpeed = -450.f; //curScrollSpeed의 초기값
	float curScrollSpeed = defaultScrollSpeed; //현재 스크롤 스피드의 값
};