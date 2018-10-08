#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	InitSkinModelRender();
	

	m_normalMap.CreateFromDDSTextureFromFile(L"modelData/utc_nomal.dds");
	m_specularMap.CreateFromDDSTextureFromFile(L"modelData/utc_spec.dds");

	m_skinModelRender->FindMaterial([&](CModelEffect* material) {
		//法線マップとスペキュラマップを設定。
		material->SetNormalMap(m_normalMap.GetBody());
		material->SetSpecularMap(m_specularMap.GetBody());
	});
}


Player::~Player()
{
}
void Player::InitSkinModelRender()
{
	m_animClips[enAnim_Idle].Load(L"animData/unityChan/idle.tka");
	m_animClips[enAnim_Run].Load(L"animData/unityChan/run.tka");
	m_animClips[enAnim_Down].Load(L"animData/unityChan/KneelDown.tka");
	m_animClips[enAnim_Clear].Load(L"animData/unityChan/clear.tka");

	m_animClips[enAnim_Idle].SetLoopFlag(true);
	m_animClips[enAnim_Run].SetLoopFlag(true);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo", m_animClips, enAnim_Num, enFbxUpAxisY);
	m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
}
void Player::Turn()
{
	m_rotation.SetRotation(CVector3::AxisY, atan2f(m_moveSpeed.x, m_moveSpeed.z));
}
//テスト成功を通知。
void Player::NotifyTestSuccess()
{
	auto ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/uni1518.wav");
	ss->Play(false);
	m_state = enState_Clear;
}
//テスト失敗を通知。
void Player::NotifyTestFailed()
{
	//失敗サウンドをランダム再生。
	int t = Random().GetRandInt() % 3;
	static wchar_t* filePath[] = {
		L"sound/uni1479.wav",
		L"sound/uni1482.wav",
		L"sound/uni1519.wav",
	};
	auto ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(filePath[t]);
	ss->Play(false);
	m_state = enState_Down;
}
void Player::Update()
{
	switch (m_state) {
	case enState_Idle:
		if (m_moveSpeed.LengthSq() > 0.1f) {
			//移動速度が設定された。
			m_state = enState_Run;
		}
		m_skinModelRender->PlayAnimation(enAnim_Idle, 0.2f);
		break;
	case enState_Run:
		if (m_moveSpeed.LengthSq() < 0.1f) {
			//移動速度が失われた。
			m_state = enState_Idle;
		}
		else {
			//旋回処理。
			Turn();
			m_skinModelRender->PlayAnimation(enAnim_Run, 0.2f);
		}
		break;
	case enState_Clear:
		m_skinModelRender->PlayAnimation(enAnim_Clear, 0.2f);
		break;
	case enState_Down:
		m_skinModelRender->PlayAnimation(enAnim_Down, 0.2f);
		break;
	}
	if (IsPossibleMove() == true) {
		m_position += m_moveSpeed;
		m_skinModelRender->SetPosition(m_position);
		m_skinModelRender->SetRotation(m_rotation);

	}
}
