#include "stdafx.h"
#include "Question_10.h"
#include "Player.h"
#include  "Star.h"

Question_10::Question_10()
{
	m_star = NewGO<Star>(0);
	CRandom& rand = Random();
	m_star->m_position.x = CMath::Lerp(rand.GetRandDouble(), -400.0f, 400.0f);
	m_star->m_position.y = 40.0f;
	m_star->m_position.z = CMath::Lerp(rand.GetRandDouble(), -0.0f, 1000.0f);
	auto diff = m_player->m_position - m_star->m_position;
	m_distUnityToStar = diff.Length();
}


Question_10::~Question_10()
{
}

QuestionBase::EnTestResult Question_10::OnTestProgress()
{
	auto v = m_star->m_position - m_player->m_position;
	auto len = v.Length();
	v.Normalize();
	v *= 5.0f;
	
	auto answer = GetUnityToStarLength(m_star->m_position, m_player->m_position);
	if ((len - answer) < -0.001f) {
		m_failedMessage = L"距離が長すぎる！";
		return enTestResult_Failed;
	}
	if ((len - answer) > 0.001f) {
		m_failedMessage = L"距離が短すぎる！";
		return enTestResult_Failed;
	}
	m_player->m_moveSpeed = v;
	//テスト成功判定。
	if (m_star != nullptr) {
		if (len < 50.0f) {
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

