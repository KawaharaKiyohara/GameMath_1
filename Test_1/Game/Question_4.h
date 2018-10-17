#pragma once

#include "QuestionBase.h"

class Star;

class Question_4 final : public QuestionBase
{
public:
	Question_4();
	~Question_4();
	EnTestResult OnTestProgress() override;
	CVector3 GetUnityChanMoveSpeed();
private:
	const wchar_t* GetTitleText() const override
	{
		return L"ミッション ４ \nユニティちゃんをX軸のプラス方向に進めろ！！！";
	}
	Star* m_star = nullptr;
};

