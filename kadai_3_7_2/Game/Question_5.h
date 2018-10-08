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
		return L"�~�b�V���� �T \n���j�e�B������X�������ɐi�߂�I�I�I";
	}
	const wchar_t* GetFailedText() const override
	{
		return m_failedMessage.c_str();
	}
	std::wstring m_failedMessage;		//�e�X�g�Ɏ��s�����Ƃ��̃��b�Z�[�W�B
	Star* m_star = nullptr;
};
