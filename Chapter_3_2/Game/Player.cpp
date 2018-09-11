
#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Wind.h"

bool Player::Start()
{
	m_position = { 0.0f, 10.0f, 500.0f };
	//モデルデータをロード。
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
//プレイヤーの更新処理。
void Player::Update()
{
	//ゲームパッドのインスタンスを取得する。
	CPad& pad = Pad(0);

	//移動ベクトルをローカル変数として定義する。
	CVector3 vMove = CVector3::Zero;
	//ゲームパッドから移動ベクトルを作成する。
	vMove.x = pad.GetLStickXF();
	vMove.y = 0.0f;
	vMove.z = pad.GetLStickYF();

	//ゲームパッドからの入力だけでは、移動速度が足りないので、
	//移動ベクトルを10倍にする。
	vMove *= 10.0f;

	//Hands-On 砂嵐と衝突しているか調べて、衝突している場合は吹き飛ばしベクトルを
	//		   キャラの移動速度に合成する。
	//砂嵐ギミックのインスタンスを取得。
	Wind* wind = FindGO<Wind>("砂嵐");
	//風と衝突しているか調べる。
	if (wind->IsHit(m_charaCon) == true) {

	}

	//キャラクターコントローラーを使った移動処理に変更。
	//m_position += vMove;
	m_position = m_charaCon.Execute(vMove, 1.0f);

	//移動ベクトルを可視化する。
	auto pos = m_position;
	pos.y += 50.0f;
	dbg::DrawVector(
		vMove * 200.0f,	//小さすぎて見えないので200倍にする。
		pos
	);
		//スキンモデルレンダーに座標を伝える。
	m_modelRender->SetPosition(m_position);
}
