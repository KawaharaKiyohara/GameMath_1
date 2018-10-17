#pragma once
class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Update()override;
	//テスト成功を通知。
	void NotifyTestSuccess();
	//テスト失敗を通知。
	void NotifyTestFailed();
	CVector3 m_position = CVector3::Zero;	//座標。
	CVector3 m_moveSpeed = CVector3::Zero;
	CCharacterController& GetCharaCon()
	{
		return m_charaCon;
	}
private:
	void InitSkinModelRender();
	void Turn();
	bool IsPossibleMove() const
	{
		return m_state != enAnim_Down && m_state != enAnim_Clear;
	}
	
private:
	//アニメーション
	enum EnAnim {
		enAnim_Idle,
		enAnim_Run,
		enAnim_Down,
		enAnim_Clear,
		enAnim_Num
	};
	//状態。
	enum EnState {
		enState_Idle,
		enState_Run,
		enState_Down,
		enState_Clear,
		enState_Num
	};
	CShaderResourceView m_normalMap;		//法線マップ。
	CShaderResourceView m_specularMap;		//スペキュラマップ。
	CAnimationClip m_animClips[enAnim_Num];	//アニメーションクリップ
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CCharacterController m_charaCon;

	CQuaternion m_rotation = CQuaternion::Identity;	//回転。
	EnState m_state = enState_Idle;
};

