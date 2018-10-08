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
		return L"ミッション ８ \nユニティちゃんをX軸方向に進めろ！！！";
	}
	const wchar_t* GetFailedText() const override
	{
		return m_failedMessage.c_str();
	}
	std::wstring m_failedMessage;		//テストに失敗したときのメッセージ。
	Star* m_star = nullptr;
};

