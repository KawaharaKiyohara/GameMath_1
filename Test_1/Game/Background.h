#pragma once

class Background :
	public IGameObject
{
public:
	Background();
	~Background();
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CShaderResourceView m_specTex;
};

