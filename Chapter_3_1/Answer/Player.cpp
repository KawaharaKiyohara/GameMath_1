
#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "tkEngine/light/tkDirectionLight.h"


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
	//HandsOn-1 ゲームパッドの左スティックの入力量からキャラクタの移動ベクトルを作成する。
	//GetLStickXF関数は左スティックのX方向の入力具合によって-1.0～1.0の値を返してくる。
	//GetLStickYF関数は左スティックのY方向の入力具合によって-1.0～1.0の値を返してくる。
	vMove.x = pad.GetLStickXF();
	vMove.y = 0.0f;
	vMove.z = pad.GetLStickYF();

	//HandsOn-3 移動速度が遅すぎるので、ベクトルを10倍にする。
	vMove.x *= 10.0f;
	vMove.y *= 10.0f;
	vMove.z *= 10.0f;

	//HandsOn-2 移動ベクトルと座標を足し算する。
	m_position.x = m_position.x + vMove.x;
	m_position.y = m_position.y + vMove.y;
	m_position.z = m_position.z + vMove.z;

	//移動ベクトルを可視化する。
	auto pos = m_position;
	pos.y += 50.0f;
	dbg::DrawVector(
		vMove * 200.0f,	//小さすぎて見えないので200倍にする。
		pos
	);

	//スキンモデルレンダーに座標を伝える。
	m_modelRender->SetPosition( m_position );
}
