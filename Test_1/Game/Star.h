#pragma once
class Star : public IGameObject
{
public:
	Star();
	~Star();
	void Update() override;
	CVector3 m_position = CVector3::Zero;	//ç¿ïWÅB
	void Get();
private:
	CQuaternion m_rotation = CQuaternion::Identity;
	CVector3 m_moveSpeed = CVector3::Zero;
	bool m_isGet = false;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	prefab::CPointLight* m_pointLig = nullptr;
};

