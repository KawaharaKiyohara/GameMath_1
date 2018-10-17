#pragma once

#include "QuestionBase.h"

class Star;

class Question_5 final : public QuestionBase
{
public:
	Question_5();
	~Question_5();
	EnTestResult OnTestProgress() override;
	CVector3 GetUnityChanMoveSpeed();
private:
	const wchar_t* GetTitleText() const override
	{
		return L"ミッション ５ \nユニティちゃんをX軸のマイナス方向に進めろ！！！";
	}
	Star* m_star = nullptr;
};
