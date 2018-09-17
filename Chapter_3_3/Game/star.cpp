#include "stdafx.h"
#include "star.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Player.h"
#include "StarRenderer.h"
#include "Game.h"

prefab::CDirectionLight* Star::m_starLight = nullptr;

Star::Star()
{
}
Star::~Star()
{
}
bool Star::Start()
{
	if (m_starLight == nullptr) {
		m_starLight = NewGO<prefab::CDirectionLight>(0);
		m_starLight->SetDirection({ 0.0f, 0.0f, -1.0f });
		m_starLight->SetLightingMaterialIDGroup(1 << enMaterialID_Star);
		m_starLight->SetColor({ 30.0f, 30.0f, 30.0f, 1.0f });
	}
	//�v���C���[�̃C���X�^���X�̃A�h���X�������o�ϐ��ɋL�����Ă����B
	m_player = FindGO<Player>("�Ղꂢ��`");
	return true;
}
void Star::Update()
{
	//�v���C���[�̃C���X�^���X�������B
	
	if (!m_isGet) {
		CVector3 dist = m_player->m_position - m_position;
		if (dist.Length() < 200.0f) {
			FindGO<Game>("Game")->AddGetStarCount();
			//�R�C���Q�b�g�����o���B
			prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
			s->Init(L"sound/coinGet.wav");
			s->Play(false);
			m_isGet = true;
		}
	}
	else {
		DeleteGO(this);
	}
	m_renderer->UpdateWorldMatrix(m_position, m_rotation, { 20.0f, 20.0f, 20.0f });
}

