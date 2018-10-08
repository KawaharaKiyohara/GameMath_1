#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"

class QuestionBase;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void SetCurrentQuesition(int no)
	{
		m_currentQuestion = no;
	}
private:
	QuestionBase*	m_question = nullptr;
	int m_currentQuestion = 0;
};

