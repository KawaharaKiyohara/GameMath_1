#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "UnityChan.h"
#include "Mikyan.h"
#include "Background.h"
#include "Star.h"

//コンストラクタ。
//Gameクラスのインスタンスが作成されたときに、自動的に呼ばれる関数。
Game::Game()
{
	InitCamera();
	//背景のインスタンスを生成する。
	m_bg = NewGO<Background>(0, "背景");

	//Unityちゃん、みきゃん、星のインスタンスを作成する。
	m_unityChan = NewGO<UnityChan>(0, "ユニティちゃん");
	m_mikyan = NewGO<Mikyan>(0, "みきゃん");
	m_star[0] = NewGO<Star>(0);
	m_star[1] = NewGO<Star>(0);
	m_star[2] = NewGO<Star>(0);
	m_star[3] = NewGO<Star>(0);
	m_star[4] = NewGO<Star>(0);

	//
	//1.2 実習課題
	//Unityちゃんと星(0番目)の座標の指定の仕方を参考にして、みきゃん、星を図1-4のようになるように座標を指定しなさい。
	//また、UnityChan、Mikyan、StarクラスはCVector3型のm_positionというメンバ変数を保持している。

	m_unityChan->m_position.x = -450.0f;
	m_unityChan->m_position.y = 0.0f;

	m_star[0]->m_position.x = 300.0f;
	m_star[0]->m_position.y = 100.0f;
	//ここから座標指定のプログラムを記述する。
	
}
//デストラクタ。
Game::~Game()
{
	DeleteGO(m_unityChan);
	DeleteGO(m_mikyan);
	DeleteGO(m_bg);
	for (int i = 0; i < 5; i++) {
		DeleteGO(m_star[i]);
	}
}
//カメラの初期化。
void Game::InitCamera()
{
	//カメラを設定。
	MainCamera().SetTarget({ 0.0f, 200.0f, 0.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(1000.0f);
	MainCamera().SetHeight(720.0f);
	MainCamera().SetWidth(1280.0f);
	MainCamera().SetUpdateProjMatrixFunc(CCamera::enUpdateProjMatrixFunc_Ortho);
	MainCamera().SetPosition({ 0.0f, 200.0f, -200.0f });
	MainCamera().Update();
}
//更新。
void Game::Update()
{
}