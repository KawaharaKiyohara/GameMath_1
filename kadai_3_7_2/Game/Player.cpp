#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	InitSkinModelRender();
	

	m_normalMap.CreateFromDDSTextureFromFile(L"modelData/utc_nomal.dds");
	m_specularMap.CreateFromDDSTextureFromFile(L"modelData/utc_spec.dds");

	m_skinModelRender->FindMaterial([&](CModelEffect* material) {
		//�@���}�b�v�ƃX�y�L�����}�b�v��ݒ�B
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
//�e�X�g������ʒm�B
void Player::NotifyTestSuccess()
{
	auto ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/uni1518.wav");
	ss->Play(false);
	m_state = enState_Clear;
}
//�e�X�g���s��ʒm�B
void Player::NotifyTestFailed()
{
	//���s�T�E���h�������_���Đ��B
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
			//�ړ����x���ݒ肳�ꂽ�B
			m_state = enState_Run;
		}
		m_skinModelRender->PlayAnimation(enAnim_Idle, 0.2f);
		break;
	case enState_Run:
		if (m_moveSpeed.LengthSq() < 0.1f) {
			//�ړ����x������ꂽ�B
			m_state = enState_Idle;
		}
		else {
			//���񏈗��B
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
