#pragma once

#include "QuestionBase.h"

class Star;

class Question_8 final : public QuestionBase
{
public:
	Question_8();
	~Question_8();
	EnTestResult OnTestProgress() override;
	CVector3 GetUnityChanNextPosition( CVector3 playerPos );
private:
	const wchar_t* GetTitleText() const override
	{
		return L"ミッション ８ \nユニティちゃんをX軸のマイナス方向に進めろ！！！"; 
	}
	Star* m_star = nullptr;
};

