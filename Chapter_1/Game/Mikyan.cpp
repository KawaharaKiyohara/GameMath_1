#include "stdafx.h"
#include "Mikyan.h"


Mikyan::Mikyan()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/mikyan/mikyan.cmo");
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY, 180.0f);
	m_skinModelRender->SetRotation(qRot);

}
Mikyan::~Mikyan()
{
	DeleteGO(m_skinModelRender);
}
void Mikyan::Update()
{
	m_skinModelRender->SetPosition(m_position);
}
