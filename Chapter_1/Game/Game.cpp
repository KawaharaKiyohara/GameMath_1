#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "UnityChan.h"
#include "Mikyan.h"
#include "Background.h"
#include "Star.h"

//�R���X�g���N�^�B
//Game�N���X�̃C���X�^���X���쐬���ꂽ�Ƃ��ɁA�����I�ɌĂ΂��֐��B
Game::Game()
{
	InitCamera();
	//�w�i�̃C���X�^���X�𐶐�����B
	m_bg = NewGO<Background>(0, "�w�i");

	//Unity�����A�݂����A���̃C���X�^���X���쐬����B
	m_unityChan = NewGO<UnityChan>(0, "���j�e�B�����");
	m_mikyan = NewGO<Mikyan>(0, "�݂����");
	m_star[0] = NewGO<Star>(0);
	m_star[1] = NewGO<Star>(0);
	m_star[2] = NewGO<Star>(0);
	m_star[3] = NewGO<Star>(0);
	m_star[4] = NewGO<Star>(0);

	//
	//1.2 ���K�ۑ�
	//Unity�����Ɛ�(0�Ԗ�)�̍��W�̎w��̎d�����Q�l�ɂ��āA�݂����A����}1-4�̂悤�ɂȂ�悤�ɍ��W���w�肵�Ȃ����B
	//�܂��AUnityChan�AMikyan�AStar�N���X��CVector3�^��m_position�Ƃ��������o�ϐ���ێ����Ă���B

	m_unityChan->m_position.x = -450.0f;
	m_unityChan->m_position.y = 0.0f;

	m_star[0]->m_position.x = 300.0f;
	m_star[0]->m_position.y = 100.0f;
	//����������W�w��̃v���O�������L�q����B
	
}
//�f�X�g���N�^�B
Game::~Game()
{
	DeleteGO(m_unityChan);
	DeleteGO(m_mikyan);
	DeleteGO(m_bg);
	for (int i = 0; i < 5; i++) {
		DeleteGO(m_star[i]);
	}
}
//�J�����̏������B
void Game::InitCamera()
{
	//�J������ݒ�B
	MainCamera().SetTarget({ 0.0f, 200.0f, 0.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(1000.0f);
	MainCamera().SetHeight(720.0f);
	MainCamera().SetWidth(1280.0f);
	MainCamera().SetUpdateProjMatrixFunc(CCamera::enUpdateProjMatrixFunc_Ortho);
	MainCamera().SetPosition({ 0.0f, 200.0f, -200.0f });
	MainCamera().Update();
}
//�X�V�B
void Game::Update()
{
}