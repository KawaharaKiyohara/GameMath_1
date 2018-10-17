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
		return L"�~�b�V���� �V \n���j�e�B������Z���̃v���X�����ɐi�߂�I�I�I";
	}
	Star* m_star = nullptr;
};

