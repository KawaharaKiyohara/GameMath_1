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
		return L"�~�b�V���� �P \n���j�e�B������Z���̃v���X�����ɐi�߂�I�I�I";
	}
	Star* m_star = nullptr;
};