#include "stdafx.h"
#include "QuestionBase.h"
#include "Background.h"
#include "Player.h"
#include "GameCamera.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Fade.h"
#include "Game.h"

namespace {
	const CVector2 titleInEndPos = { 0.0f, 200.0f };
	class BgmFadeOut : public IGameObject {
	public:
		prefab::CSoundSource* m_targetBgm = nullptr;
		float m_vol = 0.0f;
		bool Start()
		{
			m_vol = m_targetBgm->GetVolume();
			return true;
		}
		void Update() override
		{
			m_vol -= 1.0f * GameTime().GetFrameDeltaTime();
			m_vol = max(0.0f, m_vol);
			m_targetBgm->SetVolume(m_vol);
			if (m_vol <= 0.0f) {
				DeleteGO(this);
			}
		}
	};
}
QuestionBase::QuestionBase()
{
	m_background = NewGO<Background>(0);
	m_player = NewGO<Player>(0, "�v���C���[");
	m_gameCamera = NewGO<GameCamera>(0);

	//���z���B
	auto dirLight = NewGO<prefab::CDirectionLight>(0);
	auto dir = CVector3(1.0f, -1.0f, -1.0f);
	dir.Normalize();
	dirLight->SetDirection(dir);
	dirLight->SetColor({ 0.7f, 0.7f, 0.7f, 1.0f });
	GraphicsEngine().GetShadowMap().SetLightDirection(dir);
	//���ˌ�
	dirLight = NewGO<prefab::CDirectionLight>(0);
	dir *= -1.0f;
	dirLight->SetDirection(dir);
	dirLight->SetColor({ 0.3f, 0.3f, 0.3f, 1.0f });
	m_font.SetShadowParam(true, 2.0f, CVector4::Black);
	m_bgm = NewGO<prefab::CSoundSource>(0);
	m_bgm->Init(L"sound/normalBGM.wav");
	m_bgm->SetVolume(0.5f);
	m_bgm->Play(true);
}


QuestionBase::~QuestionBase()
{
	DeleteGO(m_background);
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
	DeleteGO(m_bgm);
}
void QuestionBase::Update()
{
	switch (m_step) {
	case enStep_FadeInStart:
		m_fade = FindGO<Fade>("�t�F�[�h");
		m_fade->StartFadeIn();
		m_step = enStep_FadeIn;
		break;
	case enStep_FadeIn:
		if (m_fade->IsFade() == false) {
			//�t�F�[�h�I���B
			m_step = enStep_TitleIn;
			m_fontText = GetTitleText();
			m_timer = 0.0f;
		}
		break;
	case enStep_TitleIn: {
		//�^�C�g�����C�[��
		
		m_timer = min(m_timer + 0.5f * GameTime().GetFrameDeltaTime(), 1.0f);
		m_titlePos.Lerp(m_timer, m_titleInStartPos, titleInEndPos);
		if (m_timer >= 1.0f) {
			m_step = enStep_TitleDisp;
			m_timer = 0.0f;
		}
	}break;
	case enStep_TitleDisp:
		m_timer += GameTime().GetFrameDeltaTime();
		if (m_timer >= 2.0f) {
			//2�b�ԕ\������B
			m_timer = 0.0f;
			m_tatileOutStartPos = m_titlePos;
			m_step = enStep_TitleOut;
		}
		break;
	case enStep_TitleOut: {
		const CVector2 titleOutEndPos = { 1300.0f, 200.0f };
		m_timer = min(m_timer + 0.5f * GameTime().GetFrameDeltaTime(), 1.0f);
		m_titlePos.Lerp(m_timer, m_tatileOutStartPos, titleOutEndPos);
		if (m_timer >= 1.0f) {
			m_step = enStep_TestProgress;
			m_timer = 0.0f;
		}
	}break;
	case enStep_TestProgress:{
		EnTestResult testResult = OnTestProgress();
		if (testResult == enTestResult_Failed) {
			//�e�X�g�Ɏ��s�B
			m_fontText = L"�~�b�V�������s�E�E�E\n" ;
			m_fontText += GetFailedText();
			m_timer = 0.0f;
			m_step = enStep_TestFailedIn;
		}
		else if (testResult == enTestResult_Success) {
			//�e�X�g�ɐ����B
			m_fontText = L"�~�b�V�����N���A�I�I�I";
			m_titlePos = titleInEndPos;
			m_player->NotifyTestSuccess();
			m_gameCamera->NotifyTestSuccess();
			//�~�b�V�����N���A�̈���c���B
			auto g = FindGO<Game>("�Q�[��");
			char filePath[256];
			sprintf(filePath, "../../Result/%d", g->GetCurrentQuestion()+1);
			FILE* fp = fopen(filePath, "w");
			fputs("clear", fp);
			fclose(fp);
			m_step = enStep_TestSuccess;
		}
	}break;
	case enStep_TestFailedIn: {
		const CVector2 titleOutStarPos = { 0.0f, 600.0f };
		m_timer = min(m_timer + 0.5f * GameTime().GetFrameDeltaTime(), 1.0f);
		m_titlePos.Lerp(m_timer, titleOutStarPos, titleInEndPos);
		if (m_timer >= 1.0f) {
			m_player->NotifyTestFailed();
			m_step = enStep_TestFailed;
			m_timer = 0.0f;
		}
		OnTestProgress();
	}break;
	case enStep_TestFailed: {
		m_timer += GameTime().GetFrameDeltaTime();
		if (m_timer > 6.0f) {
			auto fade = FindGO<Fade>("�t�F�[�h");
			fade->StartFadeOut();
			auto bgmFade = NewGO< BgmFadeOut>(0);
			bgmFade->m_targetBgm = m_bgm;
			m_step = enStep_GameOver;
		}
		OnTestProgress();
	}break;
	case enStep_TestSuccess: {
		m_timer += GameTime().GetFrameDeltaTime();
		if (m_timer > 6.0f) {
			auto fade = FindGO<Fade>("�t�F�[�h");
			fade->StartFadeOut();
			auto bgmFade = NewGO< BgmFadeOut>(0);
			bgmFade->m_targetBgm = m_bgm;
			m_step = enStep_GameOver;
		}
	}break;
	case enStep_GameOver: {
		auto fade = FindGO<Fade>("�t�F�[�h");
		if (fade->IsFade() == false) {
			//�Q�[���I���B
			DestroyWindow(Engine().GetWindowHandle());
		}
	}break;

	}
}
void QuestionBase::PostRender(CRenderContext& rc)
{
	m_font.Begin(rc);
	m_font.Draw(m_fontText.c_str(), m_titlePos, CVector4::Yellow);
	m_font.End(rc);
}