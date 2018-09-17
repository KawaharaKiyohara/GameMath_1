#pragma once
#include "tkEngine/physics/tkPhysicsGhostObject.h"

class Wind : public IGameObject
{
public:
	Wind();
	~Wind();
	bool IsHit( CCharacterController& charaCon) const;
	void Update() override final;
private:
	void EmitEffect();
private:
	CPhysicsGhostObject m_windowGhostObject;	//�S�[�X�g�I�u�W�F�N�g�B
	prefab::CEffect* m_effect = nullptr;
	float m_timer = 0.0f;
};

