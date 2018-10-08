#include "stdafx.h"
#include "Question_8.h"
#include "Player.h"
#include "Star.h"


Question_8::Question_8()
{
	m_star = NewGO<Star>(0);
	m_star->m_position = { 500.0f, 40.0f, 5.0f };
}
Question_8::~Question_8()
{
	DeleteGO(m_star);
}
QuestionBase::EnTestResult Question_8::OnTestProgress()
{
	CVector3 nextPos = GetUnityChanNextPosition( m_player->m_position );
	CVector3 nextPosAnswer = m_player->m_position;
	nextPosAnswer.z += 5.0f;
	auto moveSpeed = nextPos - m_player->m_position;
	m_player->m_moveSpeed = moveSpeed;

	if (moveSpeed.Length() > 5.02f) {
		//テスト失敗。
		m_failedMessage = L"移動速度が速すぎる！";
		return enTestResult_Failed;
	}
	if (moveSpeed.Length() < 4.98f) {
		//テスト失敗。
		//ベクトルの大きさが１より小さいぞ。
		m_failedMessage = L"移動速度が遅すぎる！";
		return enTestResult_Failed;
	}
	auto moveDir = moveSpeed;
	moveDir.Normalize();
	if (fabsf(moveDir.Dot(CVector3::AxisX) - 1.0f) > FLT_EPSILON) {
		//テスト失敗。
		//ベクトルの向きが違う。
		m_failedMessage = L"進行方向を間違えている！";
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