#pragma once

#include "QuestionBase.h"

class Star;

class Question_9 final : public QuestionBase
{
public:
	Question_9();
	~Question_9();
	EnTestResult OnTestProgress() override;
	CVector3 GetUnityChanNextPosition(CVector3 starPos, CVector3 playerPos);
	const wchar_t* GetTitleText() const override
	{
		return L"�~�b�V���� �X \n���j�e�B�������X�^�[�̕����ɐi�߂�I�I�I";
	}
	Star* m_star = nullptr;
	CVector3 m_toStarDir;				//���Ɍ������ĐL�т�x�N�g���B
};

