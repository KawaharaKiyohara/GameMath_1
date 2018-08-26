#pragma once
class UnityChan;
class Background : public IGameObject
{
public:
	Background();
	~Background();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	prefab::CSkinModelRender* m_sky = nullptr;
};

