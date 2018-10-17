#pragma once
class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Update()override;
	//�e�X�g������ʒm�B
	void NotifyTestSuccess();
	//�e�X�g���s��ʒm�B
	void NotifyTestFailed();
	CVector3 m_position = CVector3::Zero;	//���W�B
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
	//�A�j���[�V����
	enum EnAnim {
		enAnim_Idle,
		enAnim_Run,
		enAnim_Down,
		enAnim_Clear,
		enAnim_Num
	};
	//��ԁB
	enum EnState {
		enState_Idle,
		enState_Run,
		enState_Down,
		enState_Clear,
		enState_Num
	};
	CShaderResourceView m_normalMap;		//�@���}�b�v�B
	CShaderResourceView m_specularMap;		//�X�y�L�����}�b�v�B
	CAnimationClip m_animClips[enAnim_Num];	//�A�j���[�V�����N���b�v
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CCharacterController m_charaCon;

	CQuaternion m_rotation = CQuaternion::Identity;	//��]�B
	EnState m_state = enState_Idle;
};

