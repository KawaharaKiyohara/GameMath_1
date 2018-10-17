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
		m_failedMessage = L"��������������I";
		return enTestResult_Failed;
	}
	if ((len - answer) > 0.001f) {
		m_failedMessage = L"�������Z������I";
		return enTestResult_Failed;
	}
	m_player->m_moveSpeed = v;
	//�e�X�g��������B
	if (m_star != nullptr) {
		if (len < 50.0f) {
			//�e�X�g�����B
			m_star->Get();
			//�����������ŏ���Ɏ��ʂ̂�null���w�肷��B
			m_star = nullptr;
			return enTestResult_Success;
		}
	}
	//�e�X�g���s���B
	return enTestResult_Progress;
}

