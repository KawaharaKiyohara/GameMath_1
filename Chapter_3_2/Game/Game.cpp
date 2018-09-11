#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "tkEngine/light/tkPointLight.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "GameCamera.h"
#include "GameOverControl.h"
#include "GameClearControl.h"
#include "star.h"
#include "StarRenderer.h"
#include "PlayerSilhouette.h"
#include "Fade.h"
#include "Wind.h"

Game::Game()
{
}


Game::~Game()
{
}
void Game::InitSceneLight()
{
	//ライトを配置。
	CVector3 dir = { 1.0f, -1.0f, -1.0f };
	dir.Normalize();
	m_directionLight = NewGO<prefab::CDirectionLight>(0, nullptr);
	m_directionLight->SetDirection(dir);
	m_directionLight->SetColor({30.0f, 30.0f, 30.0f, 1.0f});
	CSkeleton ligLoc;
	ligLoc.Load(L"loc/light.tks");
	for (int i = 1; i < ligLoc.GetNumBones(); i++) {
		CBone* bone = ligLoc.GetBone(i);
		prefab::CPointLight* ptLig = NewGO<prefab::CPointLight>(0, nullptr);
		const CMatrix& mat = bone->GetBindPoseMatrix();
		CVector3 pos;
		pos.x = mat.m[3][0];
		pos.y = mat.m[3][2];
		pos.z = -mat.m[3][1];
		ptLig->SetPosition(pos);
		ptLig->SetColor({
#if 1 //@todo 物理ベースの時のライト。
			400.0f,
			400.0f,
			100.0f,
#else
			100.0f,
			100.0f,
			10.0f,
#endif
			
			1.0f
		});
		ptLig->SetAttn({
			550.0f,
			3.0f,
			0.1f
		});
		m_pointLight.push_back(ptLig);
	}

	LightManager().SetAmbientLight({ 5.0f, 5.0f, 5.0f });

	NewGO< Wind>(0, "砂嵐");
	dbg::SetDrawPhysicsCollisionEnable();
	if (m_directionLight != nullptr) {
		GraphicsEngine().GetShadowMap().SetLightDirection(m_directionLight->GetDirection());
	}


}
bool Game::Start()
{
	//カメラを設定。
	MainCamera().SetTarget({ 0.0f, 50.0f, 0.0f });
	MainCamera().SetPosition({ 0.0f, 300.0f, -300.0f });
	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(10000.0f);
	MainCamera().Update();

	
	m_background = NewGO<Background>(0, nullptr);
	m_gameCamera = NewGO<GameCamera>(0, "GameCamera");
	//シーンライトを初期化。
	InitSceneLight();
	
	//プレイヤーを描画。
	m_player = NewGO<Player>(0, "Player");
	
	m_fade = FindGO<Fade>("Fade");
	GraphicsEngine().GetShadowMap().SetLightDirection(m_directionLight->GetDirection());
	m_bgmSource = NewGO<prefab::CSoundSource>(0, nullptr);
	m_bgmSource->Init(L"sound/normalBGM.wav");
	
	
	//タイマー用のフォントを初期化。
	m_timerFont = std::make_unique<DirectX::SpriteFont>(
		GraphicsEngine().GetD3DDevice(),
		L"font/hato_pop.spritefont"
	);
	m_fontTest.SetFont(m_timerFont.get());
	m_fontTest.SetShadowParam(true, 2.0f, CVector4::Black);

	m_scoreFontPosition.x = -620.0f ;
	m_scoreFontPosition.y = 280.0f;
	
	m_fade->StartFadeIn();
	m_state = enState_FadeIn;
	return true;
}
void Game::OnDestroy() 
{
	DeleteGO(m_player);
	DeleteGO(m_background);
	for (auto pt : m_pointLight) {
		DeleteGO(pt);
	}
	for (auto enemy : m_enemyList) {
		DeleteGO(enemy);
	}
	DeleteGO(m_gameCamera);
	DeleteGO(m_bgmSource);
	//Starを削除。
	FindGameObjectsWithTag(enGameObject_Star, [](IGameObject* go) {
		DeleteGO(go);
	});
	DeleteGO(m_gameClearControl);
	DeleteGO(m_playerSilhouette);
	//ゲーム再起動。
	NewGO<Game>(0, "Game");
	
}
void Game::NotifyGameOver()
{
	if (m_isGameClear) {
		return;
	}
	m_isGameOver = true;
	
	//ゲームオーバー制御を作成。
	m_gameOverControl = NewGO<GameOverControl>(0, nullptr);
}
void Game::NotifyRestart()
{
	m_isGameOver = false;
	m_gameCamera->NotifyRestart();
	for (auto& enemy : m_enemyList) {
		enemy->NotifyRestart();
	}
	m_waitTimer = 0.0f;
	GraphicsEngine().GetTonemap().Reset();
	DeleteGO(m_gameOverControl);
}
void Game::Update()
{
	switch (m_state) {
	case enState_FadeIn:
		GraphicsEngine().GetTonemap().Reset();
		if (!m_fade->IsFade()) {
			m_bgmSource->Play(true);
			m_state = enState_InGame;
		}
		break;
	case enState_InGame: {

	}break;
	}
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY, Pad(0).GetRStickXF() * 0.05f);
	
	CVector3 lightDir = m_directionLight->GetDirection();
	qRot.Apply(lightDir);
	CVector3 rotAxis;
	rotAxis.Cross(lightDir, CVector3::Up);
	qRot.SetRotation(rotAxis, Pad(0).GetRStickYF() * 0.05f);
	qRot.Apply(lightDir);

	m_directionLight->SetDirection(lightDir);
	GraphicsEngine().GetShadowMap().SetLightDirection(m_directionLight->GetDirection());
#endif
}
