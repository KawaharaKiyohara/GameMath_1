#include "stdafx.h"
#include "Question_3.h"
#include "Player.h"
#include "Star.h"

/////////////////////////////////////////////////
//
// Mission3 ���j�e�B�������X�^�[�̕����ɓ������I�I�I
//
// �y���z
//		GetUnityChanMoveDirection�֐��́A���j�e�B����񂩂琯�Ɍ�����
//		�����x�N�g��(�傫���P�̃x�N�g��)��Ԃ����Ƃ����߂��Ă���֐��ł��B
//		�֐��̒��g��K�؂Ɏ������Ȃ����B
//		�܂��A�x�N�g����傫���P�ɂ��邽�߂ɂ͐��K�����s���K�v������܂��B
//		�x�N�g���𐳋K����CVector3�̃����o��Normalize�֐��𗘗p����ƍs���܂��B
//		�T���v���R�[�h���Q�Ƃ��Ă��������B
//
// �y�����z
//		starPos		���̍��W
//		unityPos	���j�e�B�����̍��W
//
// �y�T���v���R�[�h�z
//		CVector3 v = {10.0f, 2.0f, 3.0f};
//		v.Normalize();	//�x�N�g��v�𐳋K������B
//
/////////////////////////////////////////////////
CVector3 Question_3::GetUnityChanMoveDirection(CVector3 starPos, CVector3 unityPos)
{
	CVector3 v = { 0.0f, 0.0f, 0.0f };
	return v;
}