#pragma once

class Fade;

class QuestionSelect : public IGameObject
{
public:
	QuestionSelect();
	~QuestionSelect();
	void Update() override;
	void PostRender(CRenderContext& rc) override;
private:
	enum EnStep {
		enStep_FadeIn,
		enStep_SelectQuestion,
		enStep_FadeOut,
	};
	EnStep m_step = enStep_FadeIn;
	prefab::CSpriteRender* m_spriteRender = nullptr;
	CFont	m_question;
	int		m_selectQuestionNo = 0;
	Fade*	m_fade = nullptr;
};

