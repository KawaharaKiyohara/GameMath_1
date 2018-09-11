
#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "tkEngine/light/tkDirectionLight.h"


bool Player::Start()
{
	m_position = { 0.0f, 10.0f, 500.0f };
	//���f���f�[�^�����[�h�B
	m_modelRender = NewGO<prefab::CSkinModelRender>(0);
	m_modelRender->Init(L"modelData/unityChan.cmo");
	
	m_modelRender->SetShadowCasterFlag(true);
	m_modelRender->SetShadowReceiverFlag(true);

	m_charaLight = NewGO<prefab::CDirectionLight>(0);
	m_charaLight->SetDirection({ 1.0f, 0.0f, 0.0f });
	m_charaLight->SetLightingMaterialIDGroup(1 << enMaterialID_Chara);
	m_charaLight->SetColor({ 10.0f, 10.0f, 10.0f, 1.0f });
	m_charaCon.Init(20.0f, 68.0f, m_position);
	return true;
}


void Player::OnDestroy()
{
	DeleteGO(m_charaLight);
	DeleteGO(m_modelRender);
}
//�v���C���[�̍X�V�����B
void Player::Update()
{
	//�Q�[���p�b�h�̃C���X�^���X���擾����B
	CPad& pad = Pad(0);
	
	//�ړ��x�N�g�������[�J���ϐ��Ƃ��Ē�`����B
	CVector3 vMove = CVector3::Zero;
	//HandsOn-1 �Q�[���p�b�h�̍��X�e�B�b�N�̓��͗ʂ���L�����N�^�̈ړ��x�N�g�����쐬����B
	

	//HandsOn-3 �ړ����x���x������̂ŁA�x�N�g����10�{�ɂ���B
	


	//HandsOn-2 �ړ��x�N�g���ƍ��W�𑫂��Z����B
	


	//�ړ��x�N�g������������B
	auto pos = m_position;
	pos.y += 50.0f;
	dbg::DrawVector(
		vMove * 200.0f,	//���������Č����Ȃ��̂�200�{�ɂ���B
		pos
	);

	//�X�L�����f�������_�[�ɍ��W��`����B
	m_modelRender->SetPosition( m_position );
}
