#include "stdafx.h"
#include "QuestionSelect.h"
#include "Fade.h"
#include "Game.h"

namespace {
	const int NUM_QUESTION = 11;
	const int NUM_QUESTION_ROW = 6;	//Q�̍s���B
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
	m_fade = FindGO<Fade>("�t�F�[�h");
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
			Fade* f = FindGO<Fade>("�t�F�[�h");
			f->StartFadeOut();
			m_step = enStep_FadeOut;
		}
	}break;
	case enStep_FadeOut:
		if (m_fade->IsFade() == false) {
			DeleteGO(this);
			auto g = NewGO<Game>(0, "�Q�[��");
			g->SetCurrentQuesition(m_selectQuestionNo);
		}
		break;
	}
}
void QuestionSelect::PostRender(CRenderContext& rc)
{
	m_question.Begin(rc);
	const wchar_t* questionFormat =
		L"%c �~�b�V�����@�P�@�@�@�@%c �~�b�V�����@�V\n"
		L" %c �~�b�V�����@�Q�@�@�@�@%c �~�b�V�����@�W\n"
		L"  %c �~�b�V�����@�R�@�@�@�@%c �~�b�V�����@�X\n"
		L"   %c �~�b�V�����@�S�@�@�@�@%c �~�b�V�����P�O\n"
		L"    %c �~�b�V�����@�T        %c �~�b�V�����P�P\n"
		L"     %c �~�b�V�����@�U";

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