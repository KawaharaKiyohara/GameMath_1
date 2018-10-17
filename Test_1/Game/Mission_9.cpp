#include "stdafx.h"
#include "Question_9.h"
#include "Player.h"
#include "Star.h"

/////////////////////////////////////////////////
//
// ミッション９ ユニティちゃんをスターの方向に動かせ！！！
//
// 【問題】
//		GetUnityChanNextPosition関数は、ユニティちゃんの次の移動先となる
//		座標を戻り値として返すことが求められている関数です。
//		ユニティちゃんはスターの方向に毎フレーム5の速度で移動する必要があります。
//		関数の中身を適切に実装しなさい
//
// 【引数】
//		starPos		星の座標
//		unityPos	ユニティちゃんの座標
//
//
/////////////////////////////////////////////////
CVector3 Question_9::GetUnityChanNextPosition(CVector3 starPos, CVector3 unityPos)
{
	//スターの方向に５移動した、ユニティちゃんの座標を計算して
	//それを戻り値として返すようにプログラムを変更しなさい。。

	return unityPos;
}