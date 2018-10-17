#include "stdafx.h"
#include "Question_11.h"
#include "Player.h"

/////////////////////////////////////////////////
//
// ミッション １１\nユニティちゃんを嵐で吹き飛ばせ！！！
//
// 【問題】
//		UpdateUnityChanPosition関数は、毎フレーム呼ばれる関数で、
//		ユニティちゃんの座標を更新していきます。
//		ユニティちゃんは、引数で渡されたmoveSpeedをunityPosに加算することで
//		移動していきます。
//		  しかし、ある日ディレクターから「ユニティちゃんを嵐で吹き飛ばしたい」という
//		要望を受けました。
//		　この要望に対応するために、ユニティちゃんが嵐で吹き飛ばされるように、
//		この関数内のコメントをよく読んでを改造してください。
// 【引数】
//		unityPos	ユニティちゃんの座標の参照。
//		moveSpeed	移動速度。
//
//
/////////////////////////////////////////////////
void Question_11::UpdateUnityChanPosition(CVector3& unityPos, CVector3 moveSpeed)
{
	//嵐と衝突しているか調べる。
	if (IsContactStorm() == true) {
		//嵐と衝突したときは、このif文が成立します。
		//ここに、嵐の力ベクトルをmoveSpeedに加算するプログラムを追加してください。
		//また、嵐の力ベクトルは下記のようなベクトルである。
		//			方向ベクトル = { 0.936329, 0.000000, -0.351123 }
		//			大きさ       = 8.544003




	}
	unityPos += moveSpeed;
}