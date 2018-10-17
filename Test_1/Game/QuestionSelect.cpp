#include "stdafx.h"
#include "QuestionSelect.h"
#include "Fade.h"
#include "Game.h"

namespace {
	const int NUM_QUESTION = 11;
	const int NUM_QUESTION_ROW = 6;	//Qの行数。
	void PlayCursorSE()
	{
		auto ss = NewGO<prefab::CSoundSource >(0);
		ss->Init(L"sound/cursor.wav");
		ss->Play(false);
	}
	void PlayDecisionSE()
	{
		auto ss = NewGO<prefab::CSoundSource >(0);
		ss->Init(L"sound/decision.wav");
		ss->Play(false);
	}
}
QuestionSelect::QuestionSelect()
{
	m_fade = FindGO<Fade>("フェード");
	m_fade->StartFadeIn();
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/Title.dds", 1280.0f, 720.0f);
	m_question.SetShadowParam(true, 2.0f, {0.4f, 0.4f, 0.4f, 1.0f});
}


QuestionSelect::~QuestionSelect()
{
	DeleteGO(m_spriteRender);
}
void QuestionSelect::Update()
{
	switch (m_step) {
	case enStep_FadeIn:
		if (m_fade->IsFade() == false) {
			m_step = enStep_SelectQuestion;
		}
		break;
	case enStep_SelectQuestion: {
		auto& pad = Pad(0);
		if (pad.IsTrigger(enButtonDown) == true) {
			PlayCursorSE();
			m_selectQuestionNo = min(m_selectQuestionNo + 1, NUM_QUESTION - 1);
		}
		if (pad.IsTrigger(enButtonUp) == true) {
			PlayCursorSE();
			m_selectQuestionNo = max(m_selectQuestionNo - 1, 0);
		}
		if (pad.IsTrigger(enButtonRight) == true && m_selectQuestionNo < NUM_QUESTION_ROW) {
			PlayCursorSE();
			m_selectQuestionNo = min(m_selectQuestionNo + NUM_QUESTION_ROW, NUM_QUESTION - 1);
		}
		if (pad.IsTrigger(enButtonLeft) == true && m_selectQuestionNo >= NUM_QUESTION_ROW) {
			PlayCursorSE();
			m_selectQuestionNo = max(m_selectQuestionNo - NUM_QUESTION_ROW, 0);
		}
		if (pad.IsPress(enButtonA) == true) {
			PlayDecisionSE();
			Fade* f = FindGO<Fade>("フェード");
			f->StartFadeOut();
			m_step = enStep_FadeOut;
		}
	}break;
	case enStep_FadeOut:
		if (m_fade->IsFade() == false) {
			DeleteGO(this);
			auto g = NewGO<Game>(0, "ゲーム");
			g->SetCurrentQuesition(m_selectQuestionNo);
		}
		break;
	}
}
void QuestionSelect::PostRender(CRenderContext& rc)
{
	m_question.Begin(rc);
	const wchar_t* questionFormat =
		L"%c ミッション　１　　　　%c ミッション　７\n"
		L" %c ミッション　２　　　　%c ミッション　８\n"
		L"  %c ミッション　３　　　　%c ミッション　９\n"
		L"   %c ミッション　４　　　　%c ミッション１０\n"
		L"    %c ミッション　５        %c ミッション１１\n"
		L"     %c ミッション　６";

	static wchar_t questionTxt[1024];
	swprintf(
		questionTxt,
		questionFormat,
		m_selectQuestionNo == 0 ? '>' : ' ',
		m_selectQuestionNo == 6 ? '>' : ' ',
		m_selectQuestionNo == 1 ? '>' : ' ',
		m_selectQuestionNo == 7 ? '>' : ' ',
		m_selectQuestionNo == 2 ? '>' : ' ',
		m_selectQuestionNo == 8 ? '>' : ' ',
		m_selectQuestionNo == 3 ? '>' : ' ',
		m_selectQuestionNo == 9 ? '>' : ' ',
		m_selectQuestionNo == 4 ? '>' : ' ',
		m_selectQuestionNo == 10 ? '>' : ' ',
		m_selectQuestionNo == 5 ? '>' : ' '
	);
	m_question.Draw(
		questionTxt,
		{ -590.0f, 150.0f },
		CVector4::White,
		0.0f,
		1.1f,
		{0.0f, 0.0f}
	);
	m_question.End(rc);

}