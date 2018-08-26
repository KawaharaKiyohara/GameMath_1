#pragma once
class Mikyan : public IGameObject
{
public:
	Mikyan();
	~Mikyan();
	void Update();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero;
};

