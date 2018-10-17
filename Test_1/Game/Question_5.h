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
		return L"�~�b�V���� �T \n���j�e�B������X���̃}�C�i�X�����ɐi�߂�I�I�I";
	}
	Star* m_star = nullptr;
};
