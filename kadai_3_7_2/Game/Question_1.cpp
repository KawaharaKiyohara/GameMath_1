#include "stdafx.h"
#include "Question_1.h"
#include "Player.h"
#include "Star.h"

Question_1::Question_1()
{
	m_star = NewGO<Star>(0);
	m_star->m_position = { 0.0f, 40.0f, 500.0f };
}
Question_1::~Question_1()
{
	DeleteGO(m_star);
}
Question_1::EnTestResult Question_1::OnTestProgress()
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
	if (fabsf(moveDirection.Dot(CVector3::AxisZ) - 1.0f) > FLT_EPSILON) {
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

