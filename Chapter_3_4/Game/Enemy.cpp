#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
Enemy::Enemy() :
	m_pathMoveLoop(this, m_movePath)
{
}


Enemy::~Enemy()
{
	DeleteGO(m_modelRender);
}
bool Enemy::Start()
{
	

	m_animClip[enAnimationClip_idle].Load(L"animData/enemy/idle.tka");
	m_animClip[enAnimationClip_idle].SetLoopFlag(true);
	m_animClip[enAnimationClip_run].Load(L"animData/enemy/run.tka");
	m_animClip[enAnimationClip_run].SetLoopFlag(true);

	m_modelRender = NewGO<prefab::CSkinModelRender>(0);
	m_modelRender->Init(L"modelData/enemy.cmo", m_animClip, enAnimationClip_num);

	m_modelRender->SetShadowCasterFlag(true);
	m_modelRender->SetShadowReceiverFlag(true);
	m_modelRender->PlayAnimation(enAnimationClip_idle);

	m_charaCon.Init(20.0f, 100.0f, m_position);
	m_player = FindGO<Player>("ぷれいや～");
	m_game = FindGO<Game>("Game");
	return true;
}
void Enemy::Update()
{
	if (!m_game->IsGameOver() && !m_game->IsGameClear()) {
		SearchPlayer();

		auto* pl = FindGO<Player>("ぷれいや～");
		auto toPlayer = pl->m_position - m_position;
		auto len = toPlayer.Length();
		if (len < 400.0f) {
			m_isFindPlayer = true;
		}
		m_pathMoveLoop.Update();
	}
	const auto scale = CVector3(3.0f, 3.0f, 3.0f);
	m_modelRender->SetPRS(m_position, m_rotation, scale);

	auto mRot = CMatrix::Identity;
	mRot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = mRot.m[2][0];
	m_forward.y = mRot.m[2][1];
	m_forward.z = mRot.m[2][2];
}
void Enemy::NotifyRestart()
{
	m_isFindPlayer = false;
}
////////////////////////////////////////////
//プレイヤーを索敵する関数。
////////////////////////////////////////////
void Enemy::SearchPlayer()
{
	//プレイヤーのインスタンスを検索する。
	Player* pl = FindGO<Player>("ぷれいや～");
	//0ベクトルで初期化しておく。
	CVector3 toPlayer = { 0.0f, 0.0f, 0.0f };
	
	//Hands-On-1 エネミーからプレイヤーに向かって伸びるベクトルを計算する。
	

	
	//Hands-On-2 toPlayerの距離を計算する。
	

	//Hands-On-3 ゲームオーバー判定。
	


	//toPlayerを可視化してみる。
	dbg::DrawVector(
		toPlayer,
		m_position);
}

