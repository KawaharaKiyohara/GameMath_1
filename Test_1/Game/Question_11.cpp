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
			//衝突したのでテスト開始。
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
			//コリジョンは遅れて発生。
			CVector3 pos = { -50.0f, 10.0f, 600.0f };
			CQuaternion qRot;
			qRot.SetRotationDeg(CVector3::AxisY, 30.0f);
			//ゴーストを作成。
			m_windowGhostObject.CreateBox(
				{ pos.x, pos.y + 100.0f, pos.z },
				qRot,
				{ 800.0f, 200.0f, 200.0f }
			);
			
			m_timer = 0;
			//嵐発生。
			m_isStormEmit = true;
		}
	}
	else {
		if (IsContactStorm() == true) {
			//嵐と衝突したのでテストスタート。
			m_isTestStart = true;
		}
	}
	
	auto unityPos = m_player->m_position;
	const CVector3 moveSpeed = { 0.0f, 0.0f, 5.0f };
	UpdateUnityChanPosition( unityPos, moveSpeed );
	m_player->m_moveSpeed = unityPos - m_player->m_position;

	if (m_isTestStart == true) {
		//テストの合否を調べる。
		//嵐の力ベクトルは、方向ベクトルが{ 0.936329, 0.000000, -0.351123 }で大きさは8.544003のベクトルです
		CVector3 stormDir = { 0.936329f, 0.000000f, -0.351123f };
		//まずベクトルの向きを調べる。
		if (IsContactStorm() == true) {
			if (m_isTestSuccess == true) {
				auto stormPower = m_player->m_moveSpeed - moveSpeed;
				auto moveDir = stormPower;
				moveDir.Normalize();
				if (Dot(moveDir, stormDir) < 0.998f) {
					//ベクトルの向きが違う。
					m_isTestSuccess = false;	//テスト失敗。
					m_failedMessage = L"嵐の向きが違う！！！\n";
				}
				//続いて嵐の強さを調べる。
				if (fabsf(8.544003f - stormPower.Length()) > 0.01f) {
					m_isTestSuccess = false;	//テスト失敗。
					m_failedMessage += L"嵐の強さが違う！！！\n";
				}
			}
			m_timer = 0;
		}else {
			m_timer++;
			if (m_timer == 40) {
				//嵐から抜けて120フレーム経過したので　。テストクリア。
				if (m_isTestSuccess) {
					return enTestResult_Success;
				}
				else {
					return enTestResult_Failed;
				}
			}
		}
	}
	//テスト実行中。
	return enTestResult_Progress;
}
