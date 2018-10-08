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
		//�e�X�g���s�B
		m_failedMessage = L"�ړ����x����������I";
		return enTestResult_Failed;
	}
	if (moveSpeed.Length() < 4.98f) {
		//�e�X�g���s�B
		//�x�N�g���̑傫�����P��菬�������B
		m_failedMessage = L"�ړ����x���x������I";
		return enTestResult_Failed;
	}
	auto moveDir = moveSpeed;
	moveDir.Normalize();
	if (fabsf(moveDir.Dot(CVector3::AxisX) - 1.0f) > FLT_EPSILON) {
		//�e�X�g���s�B
		//�x�N�g���̌������Ⴄ�B
		m_failedMessage = L"�i�s�������ԈႦ�Ă���I";
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