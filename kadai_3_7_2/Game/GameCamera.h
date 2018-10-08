#pragma once

#include "tkEngine/camera/tkSpringCamera.h"

class Player;

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	void Update() override;
	//�e�X�g������ʒm�B
	void NotifyTestSuccess();
private:
	bool m_isTestSuccess = false;
	CSpringCamera m_springCamera;
	Player* m_player = nullptr;
};

