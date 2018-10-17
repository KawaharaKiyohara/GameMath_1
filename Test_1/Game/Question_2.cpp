#include "stdafx.h"
#include "Question_2.h"
#include "Star.h"
#include "Player.h"

Question_2::Question_2()
{
	m_star = NewGO<Star>(0);
	m_star->m_position = { 0.0f, 40.0f, -500.0f };
}
Question_2::~Question_2()
{
	DeleteGO(m_star);
}
QuestionBase::EnTestResult Question_2::OnTestProgress()
{
	CVector3 moveDirection = GetUnityChanMoveDirection();
	m_player->m_moveSpeed = moveDirection * 5.0f;

	if (moveDirection.Length() > 1.02f) {
		//テスト失敗。
		//ベクトルの大きさが１より大きいぞ。
		m_failedMessage = L"ベクトルの大きさが１より大きい！";
		return enTestResult_Failed;
	}
	if (moveDirection.Length() < 0.98f) {
		//テスト失敗。
		//ベクトルの大きさが１より小さいぞ。
		m_failedMessage = L"ベクトルの大きさが１より小さい！";
		return enTestResult_Failed;
	}
	if (fabsf(moveDirection.Dot(CVector3::AxisZ) + 1.0f) > FLT_EPSILON) {
		//テスト失敗。
		//ベクトルの向きが違う。
		m_failedMessage = L"ベクトルの向きが違う！";
		return enTestResult_Failed;
	}
	//テスト成功判定。
	if (m_star != nullptr) {
		CVector3 diff = m_star->m_position - m_player->m_position;
		if (diff.Length() < 50.0f) {
			//テスト成功。
			m_star->Get();
			//取ったら内部で勝手に死ぬのでnullを指定する。
			m_star = nullptr;
			return enTestResult_Success;
		}
	}
	//テスト実行中。
	return enTestResult_Progress;
}

