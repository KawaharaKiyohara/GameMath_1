#include "stdafx.h"
#include "Star.h"
#include "tkEngine/light/tkPointLight.h"


Star::Star()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/star/star.cmo");
	m_skinModelRender->SetScale({ 20.0f, 20.0f, 20.0f });
	m_skinModelRender->SetShadowCasterFlag(true);
	/*m_pointLig = NewGO<prefab::CPointLight>(0);
	m_pointLig->SetColor({ 2.0f, 2.0f, 0.0f, 1.0f });
	m_pointLig->SetAttn({ 300.0f, 1.0f, 0.0f });*/
}


Star::~Star()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_pointLig);
}
void Star::Update()
{
//	m_pointLig->SetPosition(m_position);
	auto dt = GameTime().GetFrameDeltaTime();
	if (m_isGet == true) {
		m_moveSpeed.y -= 980.0f * GameTime().GetFrameDeltaTime();
		m_position += m_moveSpeed * dt;
		if (m_position.y < -100) {
			//Ž€–S‚¿‚á‚ñB
			DeleteGO(this);
		}
	}
	CQuaternion qAddRot;
	qAddRot.SetRotation(CVector3::AxisY,3.0f * dt);
	m_rotation *= qAddRot;
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetPosition(m_position);
}
void Star::Get()
{
	m_moveSpeed.y = 600.0f;
	m_isGet = true;
	auto ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/coinGet.wav");
	ss->Play(false);
}