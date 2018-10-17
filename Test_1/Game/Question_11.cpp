#include "stdafx.h"
#include "Question_11.h"
#include "Player.h"

Question_11::Question_11()
{
	dbg::SetDrawPhysicsCollisionEnable();
}


Question_11::~Question_11()
{
}
bool Question_11::IsContactStorm() const
{
	bool isContact = false;
	PhysicsWorld().ContactTest(m_player->GetCharaCon(), [&](const auto& colliObj) {
		if (m_windowGhostObject.IsSelf(colliObj)) {
			//�Փ˂����̂Ńe�X�g�J�n�B
			isContact = true;
		}
	});
	return isContact;
}
QuestionBase::EnTestResult Question_11::OnTestProgress()
{
	if (m_isStormEmit == false) {
		if (m_effect == nullptr) {
			CVector3 pos = { -550.0f, 100.0f, 900.0f };
			m_effect = NewGO<prefab::CEffect>(0);
			m_effect->Play(L"effect/wind.efk");
			m_effect->SetPosition(pos);
			m_effect->SetScale({ 10.0f, 10.0f, 15.0f });
			CQuaternion qRot;
			qRot.SetRotationDeg(CVector3::AxisY, 120.0f);
			m_effect->SetRotation(qRot);
		}
		m_timer++;
		if (m_timer == 10) {
			//�R���W�����͒x��Ĕ����B
			CVector3 pos = { -50.0f, 10.0f, 600.0f };
			CQuaternion qRot;
			qRot.SetRotationDeg(CVector3::AxisY, 30.0f);
			//�S�[�X�g���쐬�B
			m_windowGhostObject.CreateBox(
				{ pos.x, pos.y + 100.0f, pos.z },
				qRot,
				{ 800.0f, 200.0f, 200.0f }
			);
			
			m_timer = 0;
			//�������B
			m_isStormEmit = true;
		}
	}
	else {
		if (IsContactStorm() == true) {
			//���ƏՓ˂����̂Ńe�X�g�X�^�[�g�B
			m_isTestStart = true;
		}
	}
	
	auto unityPos = m_player->m_position;
	const CVector3 moveSpeed = { 0.0f, 0.0f, 5.0f };
	UpdateUnityChanPosition( unityPos, moveSpeed );
	m_player->m_moveSpeed = unityPos - m_player->m_position;

	if (m_isTestStart == true) {
		//�e�X�g�̍��ۂ𒲂ׂ�B
		//���̗̓x�N�g���́A�����x�N�g����{ 0.936329, 0.000000, -0.351123 }�ő傫����8.544003�̃x�N�g���ł�
		CVector3 stormDir = { 0.936329f, 0.000000f, -0.351123f };
		//�܂��x�N�g���̌����𒲂ׂ�B
		if (IsContactStorm() == true) {
			if (m_isTestSuccess == true) {
				auto stormPower = m_player->m_moveSpeed - moveSpeed;
				auto moveDir = stormPower;
				moveDir.Normalize();
				if (Dot(moveDir, stormDir) < 0.998f) {
					//�x�N�g���̌������Ⴄ�B
					m_isTestSuccess = false;	//�e�X�g���s�B
					m_failedMessage = L"���̌������Ⴄ�I�I�I\n";
				}
				//�����ė��̋����𒲂ׂ�B
				if (fabsf(8.544003f - stormPower.Length()) > 0.01f) {
					m_isTestSuccess = false;	//�e�X�g���s�B
					m_failedMessage += L"���̋������Ⴄ�I�I�I\n";
				}
			}
			m_timer = 0;
		}else {
			m_timer++;
			if (m_timer == 40) {
				//�����甲����120�t���[���o�߂����̂Ł@�B�e�X�g�N���A�B
				if (m_isTestSuccess) {
					return enTestResult_Success;
				}
				else {
					return enTestResult_Failed;
				}
			}
		}
	}
	//�e�X�g���s���B
	return enTestResult_Progress;
}
