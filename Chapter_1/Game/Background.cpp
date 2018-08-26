#include "stdafx.h"
#include "Background.h"
#include "UnityChan.h"

Background::Background()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/background/bg.cmo");
	m_sky = NewGO<prefab::CSkinModelRender>(0);
	m_sky->Init(L"modelData/background/sky.cmo");
}


Background::~Background()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_sky);
}
