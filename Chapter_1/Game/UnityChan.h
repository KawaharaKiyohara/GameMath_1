#pragma once
class UnityChan : public IGameObject
{
public:
	UnityChan();
	~UnityChan();
	void Update();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero;
};

