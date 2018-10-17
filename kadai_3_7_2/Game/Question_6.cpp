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
		//�e�X�g���s�B
		//�x�N�g���̑傫�����P���傫�����B
		m_failedMessage = L"�x�N�g���̑傫�����T���傫���I";
		return enTestResult_Failed;
	}
	if (moveSpeed.Length() < 4.98f) {
		//�e�X�g���s�B
		//�x�N�g���̑傫�����P��菬�������B
		m_failedMessage = L"�x�N�g���̑傫�����T��菬�����I";
		return enTestResult_Failed;
	}
	auto moveDir = moveSpeed;
	moveDir.Normalize();

	if (fabsf(moveDir.Dot(m_toStarDir) - 1.0f) > FLT_EPSILON) {
		//�e�X�g���s�B
		//�x�N�g���̌������Ⴄ�B
		m_failedMessage = L"�x�N�g���̌������Ⴄ�I";
		return enTestResult_Failed;
	}
	//�e�X�g��������B
	if (m_star != nullptr) {
		CVector3 diff = m_star->m_position - m_player->m_position;
		if (diff.Length() < 50.0f) {
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
