#include "stdafx.h"
#include "Question_6.h"
#include "Player.h"
#include "Star.h"


Question_6::Question_6()
{
	m_star = NewGO<Star>(0);
	m_star->m_position = { -300.0f, 40.0f, 400.0f };
	m_toStarDir = m_star->m_position - m_player->m_position;
	m_toStarDir.y = 0.0f;
	m_toStarDir.Normalize();
}
Question_6::~Question_6()
{
	DeleteGO(m_star);
}
QuestionBase::EnTestResult Question_6::OnTestProgress()
{
	CVector3 starPos = m_star->m_position;
	starPos.y = 0.0f;
	CVector3 playerPos = m_player->m_position;
	playerPos.y = 0.0f;
	CVector3 moveSpeed = GetUnityChanMoveSpeed(starPos, playerPos);
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

	if (fabsf(moveDir.Dot(m_toStarDir) - 1.0f) > FLT_EPSILON) {
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

