#pragma once
class Star : public IGameObject
{
public:
	Star();
	~Star();
	void Update();
	prefab::CSkinModelRender* m_modelRender = nullptr;
	CVector3 m_position = CVector3::Zero;
};

