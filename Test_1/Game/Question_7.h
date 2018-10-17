#pragma once

#include "QuestionBase.h"

class Star;

class Question_7 final : public QuestionBase
{
public:
	Question_7();
	~Question_7();
	EnTestResult OnTestProgress() override;
	CVector3 GetUnityChanNextPosition( CVector3 playerPos );
private:
	const wchar_t* GetTitleText() const override
	{
		return L"ミッション ７ \nユニティちゃんをZ軸のプラス方向に進めろ！！！";
	}
	Star* m_star = nullptr;
};

