#include "stdafx.h"
#include "Question_3.h"
#include "Player.h"
#include "Star.h"

/////////////////////////////////////////////////
//
// Mission3 ユニティちゃんをスターの方向に動かせ！！！
//
// 【問題】
//		GetUnityChanMoveDirection関数は、ユニティちゃんから星に向かう
//		方向ベクトル(大きさ１のベクトル)を返すことが求められている関数です。
//		関数の中身を適切に実装しなさい。
//		また、ベクトルを大きさ１にするためには正規化を行う必要があります。
//		ベクトルを正規化はCVector3のメンバのNormalize関数を利用すると行えます。
//		サンプルコードを参照してください。
//
// 【引数】
//		starPos		星の座標
//		unityPos	ユニティちゃんの座標
//
// 【サンプルコード】
//		CVector3 v = {10.0f, 2.0f, 3.0f};
//		v.Normalize();	//ベクトルvを正規化する。
//
/////////////////////////////////////////////////
CVector3 Question_3::GetUnityChanMoveDirection(CVector3 starPos, CVector3 unityPos)
{
	CVector3 v = { 0.0f, 0.0f, 0.0f };
	return v;
}