#pragma once
#include "QuestionBase.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"

class Question_11 : public QuestionBase
{
public:
	Question_11();
	~Question_11();
	EnTestResult OnTestProgress() override;
	void UpdateUnityChanPosition(CVector3& unityPos, CVector3 moveSpeed);
	const wchar_t* GetTitleText() const override
	{
		return L"ミッション １１\nユニティちゃんを嵐で吹き飛ばせ！！！";
	}
	bool IsContactStorm() const;
	prefab::CEffect* m_effect = nullptr;
	CPhysicsGhostObject m_windowGhostObject;	//ゴーストオブジェクト。
	int m_timer = 0;
	bool m_isStormEmit = false;
	bool m_isTestStart = false;
	bool m_isTestSuccess = true;
};

