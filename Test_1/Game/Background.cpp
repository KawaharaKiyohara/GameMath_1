#include "stdafx.h"
#include "Background.h"


Background::Background()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/bg/bg.cmo");
	m_skinModelRender->SetShadowReceiverFlag(true);
	m_specTex.CreateFromDDSTextureFromFile(L"modelData/bg/bgSpec.dds");
	m_skinModelRender->FindMaterial([&](CModelEffect* mat) {
		mat->SetSpecularMap(m_specTex.GetBody());
		
	});
}


Background::~Background()
{
	DeleteGO(m_skinModelRender);
}
