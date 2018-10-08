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
		return L"ミッション ４ \nユニティちゃんをZ軸方向に進めろ！！！";
	}
	const wchar_t* GetFailedText() const override
	{
		return m_failedMessage.c_str();
	}
	std::wstring m_failedMessage;		//テストに失敗したときのメッセージ。
	Star* m_star = nullptr;
};

