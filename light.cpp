//**************************************************
//
// Hackathon ( light.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// インクルード
//==================================================
#include "main.h" 
#include "fade.h"
#include "input.h"
#include "select.h"
#include "mode.h"
#include "rectangle.h"
#include "light.h"
#include "color.h"
#include "sound.h"
#include "texture.h"
#include "utility.h"
#include "game.h"
#include "effect.h"
#include "player.h"
#include "time.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
namespace
{
const int	MAX_LIGHT = 16;		// ライトの最大数
const int	MAX_TIME = 90;		// タイムの最大値
const int	REPEAT_TIME = 30;	// タイムの繰り返し
const float	LIGHT_SIZE = 50.0f;	// ライトのサイズ

typedef enum
{
	LIGHT_RED = 0,	// 赤
	LIGHT_GREEN,	// 緑
	LIGHT_BLUE,		// 青
	LIGHT_YELLOW,	// 黄色
	LIGHT_MAX,
}LIGHT;
}// namespaceはここまで

//==================================================
// スタティック変数
//==================================================
namespace
{
int		s_nIdxSelect;			// メニューの配列のインデックス
int		s_nIdxFrame;			// 枠の配列のインデックス
int		s_nTime;				// タイム
int		s_nIdxColor[MAX_LIGHT];	// 色の番号
TEXTURE	s_aTexture[LIGHT_MAX];	// テクスチャ
}// namespaceはここまで

//==================================================
// スタティック関数プロトタイプ宣言
//==================================================
namespace
{
}// namespaceはここまで

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitLight(void)
{
	s_aTexture[LIGHT_RED] = TEXTURE_Red;
	s_aTexture[LIGHT_GREEN] = TEXTURE_Green;
	s_aTexture[LIGHT_BLUE] = TEXTURE_Bule;
	s_aTexture[LIGHT_YELLOW] = TEXTURE_Yellow;

	{// 枠
		SelectArgument select;
		select.nNumUse = MAX_LIGHT;
		select.fLeft = 0.0f;
		select.fRight = SCREEN_WIDTH;
		select.fTop = SCREEN_HEIGHT * 0.35f;
		select.fBottom = SCREEN_HEIGHT * 0.35f;
		select.fWidth = LIGHT_SIZE * 1.5f;
		select.fHeight = LIGHT_SIZE * 1.5f;
		select.bSort = false;

		for (int i = 0; i < MAX_LIGHT; i++)
		{
			select.texture[i] = TEXTURE_Hackathon_Ring;
		}

		// セレクトの設定
		s_nIdxFrame = SetSelect(select);
	}

	{// メニュー
		SelectArgument select;
		select.nNumUse = MAX_LIGHT;
		select.fLeft = 0.0f;
		select.fRight = SCREEN_WIDTH;
		select.fTop = SCREEN_HEIGHT * 0.35f;
		select.fBottom = SCREEN_HEIGHT * 0.35f;
		select.fWidth = LIGHT_SIZE;
		select.fHeight = LIGHT_SIZE;
		select.bSort = false;

		for (int i = 0; i < MAX_LIGHT; i++)
		{
			select.texture[i] = TEXTURE_effect_000;
		}

		// セレクトの設定
		s_nIdxSelect = SetSelect(select);
	}

	for (int i = 0; i < MAX_LIGHT; i++)
	{
		// 矩形の描画するかどうか
		SetDrawSelect(s_nIdxFrame, i, false);
	}

	// 矩形の描画するかどうか
	SetDrawSelect(s_nIdxFrame, 0, true);

	for (int i = 0; i < MAX_LIGHT; i++)
	{
		s_nIdxColor[i] = IntRandam(LIGHT_MAX, 0);

		// セレクトのテクスチャの設定
		ChangeTextuteSelect(s_nIdxSelect, i, s_aTexture[s_nIdxColor[i]]);
	}

	// 応急処置
	s_nIdxColor[0] = IntRandam(LIGHT_MAX, 0);

	// セレクトのテクスチャの設定
	ChangeTextuteSelect(s_nIdxSelect, 0, s_aTexture[s_nIdxColor[0]]);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitLight(void)
{
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateLight(void)
{
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawLight(void)
{
}

//--------------------------------------------------
// 色の取得
//--------------------------------------------------
int GetColorLight(int nNowLight)
{
	assert(nNowLight >= 0 && nNowLight < MAX_LIGHT);

	return s_nIdxColor[nNowLight];
}

//--------------------------------------------------
// 正解
//--------------------------------------------------
void CorrectAnswerLight(void)
{
	for (int i = 0; i < MAX_LIGHT - 1; i++)
	{
		s_nIdxColor[i] = s_nIdxColor[i + 1];
	}

	s_nIdxColor[MAX_LIGHT - 1] = IntRandam(LIGHT_MAX, 0);

	for (int i = 0; i < MAX_LIGHT; i++)
	{
		// セレクトのテクスチャの設定
		ChangeTextuteSelect(s_nIdxSelect, i, s_aTexture[s_nIdxColor[i]]);
	}
}