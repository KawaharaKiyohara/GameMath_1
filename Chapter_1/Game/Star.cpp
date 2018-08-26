#include "stdafx.h"
#include "Star.h"


Star::Star()
{
	m_modelRender = NewGO<prefab::CSkinModelRender>(0);
	m_modelRender->Init(L"modelData/star/star.cmo");

}


Star::~Star()
{
	DeleteGO(m_modelRender);
}
void Star::Update()
{
	m_modelRender->SetPosition(m_position);
}