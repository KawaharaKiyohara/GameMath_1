#include "stdafx.h"
#include "UnityChan.h"


UnityChan::UnityChan()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY, 180.0f);
	m_skinModelRender->SetRotation(qRot);
}
UnityChan::~UnityChan()
{
	DeleteGO(m_skinModelRender);
}

void UnityChan::Update()
{
	//À•W‚ð‹³‚¦‚éB
	m_skinModelRender->SetPosition(m_position);
}
