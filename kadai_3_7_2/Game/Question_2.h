#pragma once

#include "QuestionBase.h"

class Star;

class Question_2 : public  QuestionBase
{
public:
	Question_2();
	~Question_2();
	EnTestResult OnTestProgress() override;
	CVector3 GetUnityChanMoveDirection();
private:
	const wchar_t* GetTitleText() const override
	{
		return L"ミッション ２ \nユニティちゃんをX軸方向に進めろ！！！";
	}
	const wchar_t* GetFailedText() const override
	{
		return m_failedMessage.c_str();
	}
	std::wstring m_failedMessage;		//テストに失敗したときのメッセージ。
	Star* m_star = nullptr;
};

