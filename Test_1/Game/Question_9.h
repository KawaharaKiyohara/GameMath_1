#pragma once

#include "QuestionBase.h"

class Star;

class Question_9 final : public QuestionBase
{
public:
	Question_9();
	~Question_9();
	EnTestResult OnTestProgress() override;
	CVector3 GetUnityChanNextPosition(CVector3 starPos, CVector3 playerPos);
	const wchar_t* GetTitleText() const override
	{
		return L"ミッション ９ \nユニティちゃんをスターの方向に進めろ！！！";
	}
	Star* m_star = nullptr;
	CVector3 m_toStarDir;				//星に向かって伸びるベクトル。
};

