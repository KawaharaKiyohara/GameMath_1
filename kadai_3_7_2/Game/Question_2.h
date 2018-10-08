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
		return L"�~�b�V���� �Q \n���j�e�B������X�������ɐi�߂�I�I�I";
	}
	const wchar_t* GetFailedText() const override
	{
		return m_failedMessage.c_str();
	}
	std::wstring m_failedMessage;		//�e�X�g�Ɏ��s�����Ƃ��̃��b�Z�[�W�B
	Star* m_star = nullptr;
};

