#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera()
{
	//カメラを設定。
	MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(10000.0f);
	MainCamera().SetPosition({ 0.0f, 70.0f, 200.0f });
	
	m_player = FindGO<Player>("プレイヤー");
	m_springCamera.Init(MainCamera(), 1200.0f, false, 20.0f);
}
GameCamera::~GameCamera()
{
}
void GameCamera::Update()
{
	//カメラの視点と注視点を更新。
	auto target = m_player->m_position;
	
	CVector3 pos = CVector3::Zero;
	
	if (m_isTestSuccess == true) {
		target.y += 50.0f;
		pos = target;
		pos += {120.0f, 0.0f, 120.0f};
	}
	else {
		target.y += 100.0f;
		pos = target;
		pos += {0.0f, 100.0f, -300.0f};
	}
	m_springCamera.SetTarget(target);
	m_springCamera.SetPosition(pos);
	m_springCamera.Update();
}
void GameCamera::NotifyTestSuccess()
{
	m_isTestSuccess = true;
	m_springCamera.SetDampingRate(3.0f);
}