//**************************************************
//
// Hackathon ( ui.h )
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _UI_H_	// このマクロ定義がされてなかったら
#define _UI_H_	// ２重インクルード防止のマクロ定義

//==================================================
// プロトタイプ宣言
//==================================================
//--------------------------------------------------
// ゲージの設定
//--------------------------------------------------
void SetGaugeUI(void);

//--------------------------------------------------
// ゲージの更新
//--------------------------------------------------
void UpdateGaugeUI(void);

//--------------------------------------------------
// 月のエフェクトの更新
//--------------------------------------------------
void UpdateEffectMoonUI(void);


#endif // !_UI_H_
