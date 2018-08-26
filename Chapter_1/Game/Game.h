#pragma once

class UnityChan;
class Mikyan;
class Background;
class Star;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	void Update();
	void InitCamera();
	UnityChan* m_unityChan = nullptr;
	Mikyan* m_mikyan = nullptr;
	Background* m_bg = nullptr;
	Star* m_star[5] = { nullptr };
};

