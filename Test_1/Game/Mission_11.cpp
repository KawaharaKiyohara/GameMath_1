#include "stdafx.h"
#include "Question_11.h"
#include "Player.h"

/////////////////////////////////////////////////
//
// �~�b�V���� �P�P\n���j�e�B�����𗒂Ő�����΂��I�I�I
//
// �y���z
//		UpdateUnityChanPosition�֐��́A���t���[���Ă΂��֐��ŁA
//		���j�e�B�����̍��W���X�V���Ă����܂��B
//		���j�e�B�����́A�����œn���ꂽmoveSpeed��unityPos�ɉ��Z���邱�Ƃ�
//		�ړ����Ă����܂��B
//		  �������A������f�B���N�^�[����u���j�e�B�����𗒂Ő�����΂������v�Ƃ���
//		�v�]���󂯂܂����B
//		�@���̗v�]�ɑΉ����邽�߂ɁA���j�e�B����񂪗��Ő�����΂����悤�ɁA
//		���̊֐����̃R�����g���悭�ǂ�ł��������Ă��������B
// �y�����z
//		unityPos	���j�e�B�����̍��W�̎Q�ƁB
//		moveSpeed	�ړ����x�B
//
//
/////////////////////////////////////////////////
void Question_11::UpdateUnityChanPosition(CVector3& unityPos, CVector3 moveSpeed)
{
	//���ƏՓ˂��Ă��邩���ׂ�B
	if (IsContactStorm() == true) {
		//���ƏՓ˂����Ƃ��́A����if�����������܂��B
		//�����ɁA���̗̓x�N�g����moveSpeed�ɉ��Z����v���O������ǉ����Ă��������B
		//�܂��A���̗̓x�N�g���͉��L�̂悤�ȃx�N�g���ł���B
		//			�����x�N�g�� = { 0.936329, 0.000000, -0.351123 }
		//			�傫��       = 8.544003




	}
	unityPos += moveSpeed;
}