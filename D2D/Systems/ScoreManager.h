#pragma once

class ScoreManager
{
	DECLARE_SINGLETON(ScoreManager)

public:
	bool enabled = true; //Update함수 실행여부

	void Update();

	bool SetAddPerTime(const float& value) { addTime = value; }; //일정 시간이 지날때 마다 점수를 얼마나 추가할지에 대한 여부 (0 = 비활성화)

	int GetScore() const { return curScore; } //현재 score 값

	int AddScore(const float& value) { curScore += value; return curScore; }

private:
	unsigned int curScore = 0; //현재 점수
	float autoScoreAddingTime = 0.1f; //몇초 마다 점수가 추가될건지
	float autoScoreAddingCurTime = 0.f; //점수가 추가되고 경과한 시간
	float addScorePerTime
};