#pragma once
#include "QuestionBase.h"

class Star;
class Playerl;

class Question_3 : public QuestionBase
{
public:
	Question_3();
	~Question_3();
	EnTestResult OnTestProgress() override;
	CVector3 GetUnityChanMoveDirection( CVector3 starPos, CVector3 playerPos );
	const wchar_t* GetTitleText() const override
	{
		return L"ミッション ３ \nユニティちゃんをスターの方向に進めろ！！！";
	}
	Star* m_star = nullptr;
	CVector3 m_toStarDir;				//星に向かって伸びるベクトル。

};

