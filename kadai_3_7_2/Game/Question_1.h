#pragma once

#include "QuestionBase.h"

class Star;

class Question_1 final : public QuestionBase {
public:
	Question_1();
	~Question_1();
	EnTestResult OnTestProgress() override;
	CVector3 GetUnityChanMoveDirection();
private:
	const wchar_t* GetTitleText() const override
	{
		return L"�~�b�V���� �P \n���j�e�B������Z�������ɐi�߂�I�I�I";
	}
	const wchar_t* GetFailedText() const override
	{
		return m_failedMessage.c_str();
	}
	std::wstring m_failedMessage;		//�e�X�g�Ɏ��s�����Ƃ��̃��b�Z�[�W�B
	Star* m_star = nullptr;
};