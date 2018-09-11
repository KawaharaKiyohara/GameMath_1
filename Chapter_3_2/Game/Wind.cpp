#include "stdafx.h"
#include "Wind.h"


Wind::Wind()
{
	CVector3 pos = { 100.0f, 10.0f, 800.0f };
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY, 30.0f);
	//ゴーストを作成。
	m_windowGhostObject.CreateBox(
		{ pos.x, pos.y + 100.0f, pos.z },
		qRot,
		{800.0f, 200.0f, 200.0f}
	);
	EmitEffect();
}


Wind::~Wind()
{
}
void Wind::EmitEffect()
{
	CVector3 pos = { -400.0f, 100.0f, 1100.0f };
	m_effect = NewGO<prefab::CEffect>(0);
	m_effect->Play(L"effect/wind.efk");
	m_effect->SetPosition(pos);
	m_effect->SetScale({ 10.0f, 10.0f, 15.0f });
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY, 120.0f);
	m_effect->SetRotation(qRot);
	m_effect->AddEventListener([&](IGameObject::SEventParam& eventParam) {
		if (eventParam.eEvent == IGameObject::enEvent_Destroy) {
			EmitEffect();
			m_timer = 0.0f;
		}
	});
}
void Wind::Update()
{
	m_timer += GameTime().GetFrameDeltaTime();
}
bool Wind::IsHit(CCharacterController& charaCon) const
{
	if (m_timer < 2.0f) {
		return false;
	}
	bool result = false;
	//キャラクターコントローラーが風と衝突しているか判定。
	PhysicsWorld().ContactTest(charaCon, [&](const btCollisionObject& contactCollision) {
		if (m_windowGhostObject.IsSelf(contactCollision)) {
			//ぶつかった、
			result = true;
		}
	});
	return result;
}