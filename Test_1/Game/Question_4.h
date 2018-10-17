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
		return L"�~�b�V���� �S \n���j�e�B������X���̃v���X�����ɐi�߂�I�I�I";
	}
	Star* m_star = nullptr;
};

