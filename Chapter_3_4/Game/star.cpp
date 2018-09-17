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
	m_player = FindGO<Player>("�Ղꂢ��`");
	return true;
}
void Star::Update()
{
	if (!m_isGet) {
		//�R�C�����擾���Ă��Ȏ��̏����B
		CVector3 dist = m_player->m_position - m_position;
		if (dist.Length() < 200.0f) {
			FindGO<Game>("Game")->AddGetStarCount();
			//�R�C���Q�b�g�B
			prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
			s->Init(L"sound/coinGet.wav");
			s->Play(false);
			m_isGet = true;
		}
	}
	else {
		DeleteGO(this);
		//HandsOn-1 ������v���C���[�Ɍ������ĐL�т�x�N�g��v���v�Z����B
	


		//HandsOn-3 ���ƃv���C���[�̋��������l�ȉ��ɂȂ����琯�������B
		

		//HandsOn-2 v�𐳋K�����āA���������ɃX�J���[�{���č��W�ɉ��Z����B
		
		
	}
	m_renderer->UpdateWorldMatrix(m_position, m_rotation, { 20.0f, 20.0f, 20.0f });
}

