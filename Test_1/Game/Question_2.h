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
		return L"�~�b�V���� �Q \n���j�e�B������Z���̃}�C�i�X�����ɐi�߂�I�I�I";
	}
	Star* m_star = nullptr;
};

