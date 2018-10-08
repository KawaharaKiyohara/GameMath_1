#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Question_1.h"
#include "Question_2.h"
#include "Question_3.h"
#include "Question_4.h"
#include "Question_5.h"
#include "Question_6.h"
#include "Question_7.h"
#include "Question_8.h"
#include "Question_9.h"

Game::Game()
{
}
Game::~Game()
{
	DeleteGO(m_question);
}
bool Game::Start()
{
	switch (m_currentQuestion) {
	case 0:
		m_question = NewGO<Question_1>(0);
		break;
	case 1:
		m_question = NewGO<Question_2>(0);
		break;
	case 2:
		m_question = NewGO<Question_3>(0);
		break;
	case 3:
		m_question = NewGO<Question_4>(0);
		break;
	case 4:
		m_question = NewGO<Question_5>(0);
		break;
	case 5:
		m_question = NewGO<Question_6>(0);
		break;
	case 6:
		m_question = NewGO<Question_7>(0);
		break;
	case 7:
		m_question = NewGO<Question_8>(0);
		break;
	case 8:
		m_question = NewGO<Question_9>(0);
		break;
	}
	return true;
}

void Game::Update()
{
}