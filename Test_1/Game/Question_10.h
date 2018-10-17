#pragma once
#include "QuestionBase.h"

class Star;

class Question_10 : public QuestionBase
{
public:
	Question_10();
	~Question_10();
	EnTestResult OnTestProgress() override;
	float GetUnityToStarLength(CVector3 starPos, CVector3 unityPos);
	const wchar_t* GetTitleText() const override
	{
		return L"ミッション １０\nユニティちゃんとスターの距離を計算しろ！！！";
	}

	Star* m_star = nullptr;
	float m_distUnityToStar = 0.0f;
};

