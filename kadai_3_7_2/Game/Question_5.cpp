#include "stdafx.h"
#include "Question_5.h"
#include "Player.h"
#include "Star.h"


Question_5::Question_5()
{
	m_star = NewGO<Star>(0);
	m_star->m_position = { 500.0f, 40.0f, 0.0f };
}
Question_5::~Question_5()
{
	DeleteGO(m_star);
}
QuestionBase::EnTestResult Question_5::OnTestProgress()
{
	CVector3 moveSpeed = GetUnityChanMoveSpeed();
	m_player->m_moveSpeed = moveSpeed;
	if (moveSpeed.Length() > 5.02f) {
		//テスト失敗。
		//ベクトルの大きさが１より大きいぞ。
		m_failedMessage = L"ベクトルの大きさが５より大きい！";
		return enTestResult_Failed;
	}
	if (moveSpeed.Length() < 4.98f) {
		//テスト失敗。
		//ベクトルの大きさが１より小さいぞ。
		m_failedMessage = L"ベクトルの大きさが５より小さい！";
		return enTestResult_Failed;
	}
	auto moveDir = moveSpeed;
	moveDir.Normalize();
	if (fabsf(moveDir.Dot(CVector3::AxisX) - 1.0f) > FLT_EPSILON) {
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
