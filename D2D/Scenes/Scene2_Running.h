#pragma once
#include "Scene.h"

class Scene2 : public Scene
{
public:
	void Init() override;
	void Destroy() override;

	void Update() override;
	void Render() override;

	void Player_Dameged(); //플레이어가 데미지를 입음
	void Player_Dead(); //플레이어가 체력이 0이 되어 사망함
	void Player_Fever();
	void addScore(int amount) { score += amount; }
private:
	shared_ptr<class PlayerCircle> playerCircle;
	shared_ptr<class CircleCollider> playerCircleCollider;
	shared_ptr<class Jump> playerCircleJump;

	shared_ptr<class ColorRect> floor;
	shared_ptr<class BoxCollider> floorCollider;

	shared_ptr<class ObjectContainer> objects;
	vector<shared_ptr<BoxCollider>, shared_ptr<Transform>> boxObstacles;
	vector<shared_ptr<CircleCollider>, shared_ptr<Transform>> circleObstacles;
	vector <shared_ptr<CircleCollider>, shared_ptr<Transform>> coins;

	pair<float, float> spawn_range = (300.f, 1000.f); //물체들의 x좌표 랜덤스폰 지점 (화면 중앙 기준)
	float scrollSpeed = -450.f;
	float curScrollSpeed = scrollSpeed;
	unsigned int score = 0; //점수
	float score_addTime = 0.1f; //몇초 마다 점수가 추가될건지
};