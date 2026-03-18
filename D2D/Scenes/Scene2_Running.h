#pragma once
#include "Scene.h"

class Scene2 : public Scene
{
public:
	void Init() override;
	void Destroy() override;

	void Update() override;
	void Render() override;

	void Player_Dameged(int damege, float immuteTime); //플레이어가 데미지를 입음
	void Player_Dead(); //플레이어가 체력이 0이 되어 사망함
	void addScore(int amount) { score += amount; }
	void ResetObstacle(shared_ptr<Transform> target);
	void addFeverGauge(float amount) { feverGauge += amount; if (feverGauge > 100) feverGauge = 100; }
	void startFever(float time);

	void Player_ImmuteEnd();
private:
	shared_ptr<class PlayerCircle> playerCircle;
	shared_ptr<class CircleCollider> playerCircleCollider;
	shared_ptr<class BoxCollider> playerBoxCollider;
	shared_ptr<class Jump> playerCircleJump;

	shared_ptr<class ColorRect> floor;
	shared_ptr<BoxCollider> floorCollider;

	shared_ptr<class ObjectContainer> objects;
	vector<pair<shared_ptr<BoxCollider>, shared_ptr<Transform>>> boxObstacles;
	vector<pair<shared_ptr<CircleCollider>, shared_ptr<Transform>>> circleObstacles;
	vector<pair<shared_ptr<CircleCollider>, shared_ptr<Transform>>> coins;

	pair<float, float> spawn_range = { 300.f, 1000.f }; //물체들의 x좌표 랜덤스폰 지점 (화면 중앙 기준)
	float scrollSpeed = -450.f;
	float curScrollSpeed = scrollSpeed;
	unsigned int score = 0; //점수
	float score_AddTime = 0.1f; //몇초 마다 점수가 추가될건지
	float score_curTime = 0.f; //점수가 추가되고 경과한 시간

	float feverTime = 5.f; //피버의 지속시간
	float feverGauge = 100.f; //피버의 게이지 (0~100)
	float feverColorTime = 0.05f;
	float feverColorCurTime = 0.f;
	bool inFever = false;

	bool immuteEnd_Function_Dirty = false;
};