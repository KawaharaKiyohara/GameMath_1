#pragma once

#include "QuestionBase.h"

class Star;

class Question_6 final : public QuestionBase
{
public:
	Question_6();
	~Question_6();
	EnTestResult OnTestProgress() override;
	CVector3 GetUnityChanMoveSpeed(CVector3 starPos, CVector3 playerPos);
	const wchar_t* GetTitleText() const override
	{
		return L"ミッション ６ \nユニティちゃんをスターの方向に進めろ！！！";
	}
	Star* m_star = nullptr;
	CVector3 m_toStarDir;				//星に向かって伸びるベクトル。
};

