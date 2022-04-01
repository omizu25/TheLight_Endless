//**************************************************
//
// Hackathon ( answer.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// インクルード
//==================================================
#include "main.h"
#include "answer.h"
#include "rectangle.h"
#include "texture.h"
#include "color.h"
#include "mode.h"
#include "light.h"
#include "player.h"
#include "game.h"
#include "bg.h"
#include "sound.h"
#include "ui.h"
#include "score.h"

//==================================================
// 定義
//==================================================
namespace
{
const int	MAX_TIME = 120;	// タイムの最大値
}// namespaceはここまで

 //==================================================
 // スタティック変数
 //==================================================
namespace
{
bool	s_bAnswer;	// あってるかどうか
int		s_nTime;	// タイム
}// namespaceはここまで

 //--------------------------------------------------
 // 初期化
 //--------------------------------------------------
void InitAnswer(void)
{
	s_nTime = 0;
	s_bAnswer = true;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitAnswer(void)
{
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateAnswer(void)
{
	//if (!s_bAnswer)
	//{// 不正解
	//	s_nTime++;

	//	if (s_nTime >= MAX_TIME)
	//	{// 時間が来た
	//		s_nTime = 0;
	//		s_bAnswer = true;

	//		// モードの変更
	//		ChangeMode(MODE_RESULT);
	//	}
	//}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawAnswer(void)
{
	/* 矩形で描画してます */
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void SetAnswer(int nNowLight)
{
	if (GetColorLight(nNowLight) == GetColorPlayer(nNowLight))
	{// 正解
		s_bAnswer = true;

		// 答え
		AnswerLight();

		// スコアの加算
		AddScore(1);
	}
	else
	{// 不正解
		// サウンドの再生
		PlaySound(SOUND_LABEL_SE_MISS);

		// 答え
		AnswerLight();

		if (GetScore() > 0)
		{// スコアがある
			// スコアの加算
			AddScore(-1);
		}
	}
}

//--------------------------------------------------
// 取得
// 返値  : bool / 正解になったかどうか
//--------------------------------------------------
bool GetAnswer(void)
{
	return s_bAnswer;
}