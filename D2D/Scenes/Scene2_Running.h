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
	shared_ptr<class Collider> playerCollider;
	shared_ptr<class Jump> playerCircleJump;

	shared_ptr<class ColorRect> floor;
	shared_ptr<BoxCollider> floorCollider;

	shared_ptr<class ObjectContainer> objects;
	vector<pair<shared_ptr<BoxCollider>, shared_ptr<Transform>>> boxObstacles;
	vector<pair<shared_ptr<CircleCollider>, shared_ptr<Transform>>> circleObstacles;
	vector<pair<shared_ptr<CircleCollider>, shared_ptr<Transform>>> coins;

	pair<float, float> spawn_range = { 300.f, 1000.f }; //물체들의 x좌표 랜덤스폰 지점 (화면 중앙 기준)
	float defaultScrollSpeed = -450.f; //curScrollSpeed의 초기값
	float curScrollSpeed = defaultScrollSpeed; //현재 스크롤 스피드의 값
	unsigned int score = 0; //점수
	float score_AddTime = 0.1f; //몇초 마다 점수가 추가될건지
	float score_curTime = 0.f; //점수가 추가되고 경과한 시간

	float feverTime = 5.f; //피버의 지속시간
	float feverGauge = 100.f; //피버의 게이지 (0~100)
	float feverColorTime = 0.05f; //피버상태일시 색상이 바뀌는 속도(초)
	float feverColorCurTime = 0.f; //피버상태일때 최근 색상이 바뀌고 경과한 시간
	bool inFever = false; //현재 피버 상태인지에 대한 여부

	bool immuteEnd_Function_Dirty = false; //플레이어의 무적 상태 종료 이벤트를 종료 직후 1회만 실행하기 위한 변수값
};