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
		//�e�X�g���s�B
		//�x�N�g���̑傫�����P���傫�����B
		m_failedMessage = L"�x�N�g���̑傫�����P���傫���I";
		return enTestResult_Failed;
	}
	if (moveDirection.Length() < 0.98f) {
		//�e�X�g���s�B
		//�x�N�g���̑傫�����P��菬�������B
		m_failedMessage = L"�x�N�g���̑傫�����P��菬�����I";
		return enTestResult_Failed;
	}
	if (fabsf(moveDirection.Dot(CVector3::AxisZ) + 1.0f) > FLT_EPSILON) {
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

