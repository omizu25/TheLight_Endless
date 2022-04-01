//**************************************************
//
// Hackathon ( answer.h )
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _ANSWER_H_	//このマクロ定義がされてなかったら
#define _ANSWER_H_	//２重インクルード防止のマクロ定義

//==================================================
// プロトタイプ宣言
//==================================================
//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitAnswer(void);

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitAnswer(void);

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateAnswer(void);

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawAnswer(void);

//--------------------------------------------------
// 設定
// 引数  : int nNowLight / ライトの数
//--------------------------------------------------
void SetAnswer(int nNowLight);

//--------------------------------------------------
// 取得
// 返値  : bool / 正解になったかどうか
//--------------------------------------------------
bool GetAnswer(void);

#endif // !_ANSWER_H_
