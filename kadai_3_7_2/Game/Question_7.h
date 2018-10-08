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
		return L"�~�b�V���� �V \n���j�e�B������Z�������ɐi�߂�I�I�I";
	}
	const wchar_t* GetFailedText() const override
	{
		return m_failedMessage.c_str();
	}
	std::wstring m_failedMessage;		//�e�X�g�Ɏ��s�����Ƃ��̃��b�Z�[�W�B
	Star* m_star = nullptr;
};

