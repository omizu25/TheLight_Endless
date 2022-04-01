//**************************************************
//
// Hackathon ( player.cpp )
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
#include "answer.h"
#include "time.h"
#include "bg.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
namespace
{
const int	MAX_LIGHT = 16;		// ライトの最大数
const float	LIGHT_SIZE = 50.0f;	// ライトのサイズ

typedef enum
{
	LIGHT_COLOR_RED = 0,	// 赤
	LIGHT_COLOR_GREEN,		// 緑
	LIGHT_COLOR_BLUE,		// 青
	LIGHT_COLOR_YELLOW,		// 黄色
	LIGHT_COLOR_MAX,
}LIGHT_COLOR;
}// namespaceはここまで

 //==================================================
 // スタティック変数
 //==================================================
namespace
{
COLOR	s_aColor[LIGHT_COLOR_MAX];		// ライトの色
int		s_nIdxSelect;					// メニューの配列のインデックス
int		s_nIdxFrame;					// 枠の配列のインデックス
int		s_nIdxColor[MAX_LIGHT];			// 色の番号
TEXTURE	s_aTexture[LIGHT_COLOR_MAX];	// テクスチャ
}// namespaceはここまで

 //==================================================
 // スタティック関数プロトタイプ宣言
 //==================================================
namespace
{
void ResetDrawPlayer(void);
}// namespaceはここまで

 //--------------------------------------------------
 // 初期化
 //--------------------------------------------------
void InitPlayer(void)
{
	s_aColor[LIGHT_COLOR_RED] = COLOR_RED;
	s_aColor[LIGHT_COLOR_GREEN] = COLOR_GREEN;
	s_aColor[LIGHT_COLOR_BLUE] = COLOR_BLUE;
	s_aColor[LIGHT_COLOR_YELLOW] = COLOR_YELLOW;
	s_aTexture[LIGHT_COLOR_RED] = TEXTURE_Red;
	s_aTexture[LIGHT_COLOR_GREEN] = TEXTURE_Green;
	s_aTexture[LIGHT_COLOR_BLUE] = TEXTURE_Bule;
	s_aTexture[LIGHT_COLOR_YELLOW] = TEXTURE_Yellow;

	{// 枠
		SelectArgument select;
		select.nNumUse = MAX_LIGHT;
		select.fLeft = 0.0f;
		select.fRight = SCREEN_WIDTH;
		select.fTop = SCREEN_HEIGHT * 0.5f;
		select.fBottom = SCREEN_HEIGHT * 0.5f;
		select.fWidth = LIGHT_SIZE;
		select.fHeight = LIGHT_SIZE;
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
		select.fTop = SCREEN_HEIGHT * 0.5f;
		select.fBottom = SCREEN_HEIGHT * 0.5f;
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

	// 描画のリセット
	ResetDrawPlayer();
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitPlayer(void)
{
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdatePlayer(void)
{
	if (GetFade() != FADE_NONE)
	{
		return;
	}

	if (!GetAnswer())
	{// 不正解
		return;
	}

	if (GetLightKeyTrigger(LIGHT_KEY_RED))
	{// 赤
		PlaySound(SOUND_LABEL_SE_SELECT);
		s_nIdxColor[0] = LIGHT_COLOR_RED;

		// セレクトのテクスチャの設定
		ChangeTextuteSelect(s_nIdxSelect, 0, s_aTexture[LIGHT_COLOR_RED]);

		// セレクトの描画するかどうか
		SetDrawSelect(s_nIdxSelect, 0, true);

		// 答え合わせ
		SetAnswer(0);

		// 矩形の色の設定
		SetColorRectangle(GetIdxBG(0), GetColor(COLOR_RED));

		// 枠の設定
		SetFramePlayer(0);

		// エフェクトの設定
		SetEffect(GetPosSelect(s_nIdxSelect, 0), EFFECT_TYPE_000, GetColor(s_aColor[s_nIdxColor[0]]));
	}
	else if (GetLightKeyTrigger(LIGHT_KEY_GREEN))
	{// 緑
		PlaySound(SOUND_LABEL_SE_SELECT);
		s_nIdxColor[0] = LIGHT_COLOR_GREEN;

		// セレクトのテクスチャの設定
		ChangeTextuteSelect(s_nIdxSelect, 0, s_aTexture[LIGHT_COLOR_GREEN]);

		// セレクトの描画するかどうか
		SetDrawSelect(s_nIdxSelect, 0, true);

		// 答え合わせ
		SetAnswer(0);

		// 矩形の色の設定
		SetColorRectangle(GetIdxBG(0), GetColor(COLOR_GREEN));

		// 枠の設定
		SetFramePlayer(0);

		// エフェクトの設定
		SetEffect(GetPosSelect(s_nIdxSelect, 0), EFFECT_TYPE_000, GetColor(s_aColor[s_nIdxColor[0]]));
	}
	else if (GetLightKeyTrigger(LIGHT_KEY_BLUE))
	{// 青
		PlaySound(SOUND_LABEL_SE_SELECT);
		s_nIdxColor[0] = LIGHT_COLOR_BLUE;

		// セレクトのテクスチャの設定
		ChangeTextuteSelect(s_nIdxSelect, 0, s_aTexture[LIGHT_COLOR_BLUE]);

		// セレクトの描画するかどうか
		SetDrawSelect(s_nIdxSelect, 0, true);

		// 答え合わせ
		SetAnswer(0);

		// 矩形の色の設定
		SetColorRectangle(GetIdxBG(0), GetColor(COLOR_BLUE));

		// 枠の設定
		SetFramePlayer(0);

		// エフェクトの設定
		SetEffect(GetPosSelect(s_nIdxSelect, 0), EFFECT_TYPE_000, GetColor(s_aColor[s_nIdxColor[0]]));
	}
	else if (GetLightKeyTrigger(LIGHT_KEY_YELLOW))
	{// 黄色
		PlaySound(SOUND_LABEL_SE_SELECT);
		s_nIdxColor[0] = LIGHT_COLOR_YELLOW;

		// セレクトのテクスチャの設定
		ChangeTextuteSelect(s_nIdxSelect, 0, s_aTexture[LIGHT_COLOR_YELLOW]);

		// セレクトの描画するかどうか
		SetDrawSelect(s_nIdxSelect, 0, true);

		// 答え合わせ
		SetAnswer(0);

		// 矩形の色の設定
		SetColorRectangle(GetIdxBG(0), GetColor(COLOR_YELLOW));

		// 枠の設定
		SetFramePlayer(0);

		// エフェクトの設定
		SetEffect(GetPosSelect(s_nIdxSelect, 0), EFFECT_TYPE_000, GetColor(s_aColor[s_nIdxColor[0]]));
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawPlayer(void)
{
}

//--------------------------------------------------
// 色の取得
//--------------------------------------------------
int GetColorPlayer(int nNowLight)
{
	assert(nNowLight >= 0 && nNowLight <= MAX_LIGHT);

	return s_nIdxColor[nNowLight];
}

//--------------------------------------------------
// 枠の設定
//--------------------------------------------------
void SetFramePlayer(int nNowLight)
{
	assert(nNowLight >= 0 && nNowLight <= MAX_LIGHT);

	if (GetAnswer())
	{// 最大値
		return;
	}

	// セレクトの描画するかどうか
	SetDrawSelect(s_nIdxFrame, nNowLight, true);
}

namespace
{
//--------------------------------------------------
// 描画のリセット
//--------------------------------------------------
void ResetDrawPlayer(void)
{
	for (int i = 0; i < MAX_LIGHT; i++)
	{
		// セレクトの描画するかどうか
		SetDrawSelect(s_nIdxSelect, i, false);
	}

	for (int i = 0; i < MAX_LIGHT; i++)
	{
		// セレクトの描画するかどうか
		SetDrawSelect(s_nIdxFrame, i, false);
	}

	// セレクトの描画するかどうか
	SetDrawSelect(s_nIdxFrame, 0, true);
}
}// namespaceはここまで