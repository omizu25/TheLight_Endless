//**************************************************
// 
// Hackathon ( rectangle.cpp )
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "fanangle.h"
#include "color.h"
#include "texture.h"
#include "utility.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
namespace
{
const int	MAX_FANANGLE = 1024;	// 矩形の最大数
const int	NUM_VERTEX = 100;		// 頂点の数
const int	NUM_POLYGON = NUM_VERTEX - 2;		// ポリゴンの数

typedef struct
{
	LPDIRECT3DTEXTURE9		pTexture;	// テクスチャ
	LPDIRECT3DVERTEXBUFFER9	pVtxBuff;	// 頂点バッファ
	int						nMaxBuff;	// 表示する頂点バッファの最大値
	bool					bUse;		// 使用しているかどうか
	bool					bDraw;		// 描画するかどうか
	bool					bAdd;		// 加算合成するかどうか
}MyFanangle;
}// namespaceはここまで

 //==================================================
 // スタティック変数
 //==================================================
namespace
{
MyFanangle	s_aFanangle[MAX_FANANGLE];	// 矩形の情報
}// namespaceはここまで

 //--------------------------------------------------
 // 初期化
 //--------------------------------------------------
void InitFanangle(void)
{
	// メモリのクリア
	memset(s_aFanangle, 0, sizeof(s_aFanangle));
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitFanangle(void)
{
	for (int i = 0; i < MAX_FANANGLE; i++)
	{
		MyFanangle *pFanangle = &s_aFanangle[i];

		if (pFanangle->pVtxBuff != NULL)
		{// 頂点バッファの解放
			pFanangle->pVtxBuff->Release();
			pFanangle->pVtxBuff = NULL;
		}
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawFanangle(void)
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < MAX_FANANGLE; i++)
	{
		MyFanangle *pFanangle = &s_aFanangle[i];

		if (!pFanangle->bUse || !pFanangle->bDraw)
		{// 使用していない、描画するしない
			continue;
		}

		/*↓ 使用している、描画する ↓*/

		if (pFanangle->bAdd)
		{// 加算合成する
		 // レンダーステートの設定
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, pFanangle->pVtxBuff, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, pFanangle->pTexture);

		// ポリゴンの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLEFAN,			// プリミティブの種類
			0,							// 描画する最初の頂点インデックス
			pFanangle->nMaxBuff);		// プリミティブ(ポリゴン)数

										// テクスチャの解除
		pDevice->SetTexture(0, NULL);

		if (pFanangle->bAdd)
		{// 加算合成する
		 // レンダーステートを元に戻す
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
int SetFanangle(TEXTURE texture)
{
	// 設定 [ テクスチャあり ]
	return SetFanangleWithTex(GetTexture(texture));
}

//--------------------------------------------------
// 設定 [ テクスチャあり ]
//--------------------------------------------------
int SetFanangleWithTex(LPDIRECT3DTEXTURE9 pTexture)
{
	for (int i = 0; i < MAX_FANANGLE; i++)
	{
		MyFanangle *pFanangle = &s_aFanangle[i];

		if (pFanangle->bUse)
		{// 使用している
			continue;
		}

		/*↓ 使用していない ↓*/

		pFanangle->pTexture = pTexture;
		pFanangle->nMaxBuff = NUM_POLYGON;
		pFanangle->bUse = true;
		pFanangle->bDraw = true;
		pFanangle->bAdd = false;

		// 頂点バッファの生成
		GetDevice()->CreateVertexBuffer(
			sizeof(VERTEX_2D) * NUM_VERTEX,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&pFanangle->pVtxBuff,
			NULL);

		VERTEX_2D *pVtx = NULL;		// 頂点情報へのポインタ

		// 頂点情報をロックし、頂点情報へのポインタを取得
		pFanangle->pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点バッファをアンロックする
		pFanangle->pVtxBuff->Unlock();

		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		float fLength = 0.0f;

		// 位置の設定
		SetPosFanangle(i, pos, fLength,true);

		//色の設定
		SetColorFanangle(i, GetColor(COLOR_WHITE));

		D3DXVECTOR2 texU = D3DXVECTOR2(0.0f, 1.0f);
		D3DXVECTOR2 texV = D3DXVECTOR2(0.0f, 1.0f);

		// テクスチャ座標の設定
		SetTexFanangle(i);

		return i;
	}

	assert(false);
	return -1;
}

//--------------------------------------------------
// 使用をやめる
//--------------------------------------------------
void StopUseFanangle(int nIdx)
{
	assert(nIdx >= 0 && nIdx < MAX_FANANGLE);

	MyFanangle *pFanangle = &s_aFanangle[nIdx];

	pFanangle->bUse = false;

	if (pFanangle->pVtxBuff != NULL)
	{// 頂点バッファの解放
		pFanangle->pVtxBuff->Release();
		pFanangle->pVtxBuff = NULL;
	}
}

//--------------------------------------------------
// 位置の設定
//--------------------------------------------------
void SetPosFanangle(int nIdx, const D3DXVECTOR3 &pos, const float &fLength, bool bSide)
{
	assert(nIdx >= 0 && nIdx < MAX_FANANGLE);

	MyFanangle *pFanangle = &s_aFanangle[nIdx];

	if (!pFanangle->bUse)
	{// 使用していない
		return;
	}

	/*↓ 使用している ↓*/

	VERTEX_2D *pVtx = NULL;		// 頂点情報へのポインタ

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuffFanangle(nIdx);

	// 頂点情報をロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = pos;
	DEBUG_PRINT("%f	%f\n", pVtx[0].pos.x, pVtx[0].pos.y);

	for (int i = 1; i < NUM_VERTEX; i++)
	{
		float fRot = (D3DX_PI * 2.0f / NUM_POLYGON) * (i - 1);

		// 角度の正規化
		NormalizeAngle(&fRot);

		if (bSide)
		{
			// 頂点座標の設定
			pVtx[i].pos.x = pos.x + cosf(fRot) * fLength;
			pVtx[i].pos.y = pos.y + sinf(fRot) * fLength;
			pVtx[i].pos.z = pos.z;
		
		}
		else
		{
			// 頂点座標の設定
			pVtx[i].pos.x = pos.x + cosf(fRot) * fLength;
			pVtx[i].pos.y = pos.y + sinf(fRot) * fLength;
			pVtx[i].pos.z = pos.z;
		}

		DEBUG_PRINT("%f	%f\n", pVtx[i].pos.x, pVtx[i].pos.y);
	}

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();
}

//--------------------------------------------------
// 回転する位置の設定
//--------------------------------------------------
void SetRotationPosFanangle(int nIdx, const D3DXVECTOR3 &pos, float fRot, float fLength, bool bSide)
{
	assert(nIdx >= 0 && nIdx < MAX_FANANGLE);

	MyFanangle *pFanangle = &s_aFanangle[nIdx];

	if (!pFanangle->bUse)
	{// 使用していない
		return;
	}

	/*↓ 使用している ↓*/

	VERTEX_2D *pVtx = NULL;		// 頂点情報へのポインタ

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuffFanangle(nIdx);

	// 頂点情報をロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = pos;
	DEBUG_PRINT("%f	%f\n", pVtx[0].pos.x, pVtx[0].pos.y);

	for (int i = 1; i < NUM_VERTEX; i++)
	{
		float fRotData = ((D3DX_PI * 2.0f / NUM_POLYGON) * (i - 1)) - fRot;

		// 角度の正規化
		NormalizeAngle(&fRotData);

		if (bSide)
		{
			// 頂点座標の設定
			pVtx[i].pos.x = pos.x + cosf(fRotData) * fLength;
			pVtx[i].pos.y = pos.y + sinf(fRotData) * fLength;
			pVtx[i].pos.z = pos.z;

		}
		else
		{
			// 頂点座標の設定
			pVtx[i].pos.x = pos.x + sinf(fRotData) * fLength;
			pVtx[i].pos.y = pos.y + cosf(fRotData) * fLength;
			pVtx[i].pos.z = pos.z;
		}

		DEBUG_PRINT("%f	%f\n", pVtx[i].pos.x, pVtx[i].pos.y);
	}

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();
}

//--------------------------------------------------
// 色の設定
//--------------------------------------------------
void SetColorFanangle(int nIdx, const D3DXCOLOR &color)
{
	assert(nIdx >= 0 && nIdx < MAX_FANANGLE);

	MyFanangle *pFanangle = &s_aFanangle[nIdx];

	if (!pFanangle->bUse)
	{// 使用していない
		return;
	}

	/*↓ 使用している ↓*/

	VERTEX_2D *pVtx = NULL;		// 頂点情報へのポインタ

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuffFanangle(nIdx);

	// 頂点情報をロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	for (int i = 0; i < NUM_VERTEX; i++)
	{
		float fRot = (D3DX_PI * 2.0f / NUM_POLYGON) * (i - 1);

		// 角度の正規化
		NormalizeAngle(&fRot);

		// 頂点カラーの設定
		pVtx[i].col = color;
	}

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();
}

//--------------------------------------------------
// 色の設定
//--------------------------------------------------
void SetColorCenterFanangle(int nIdx, const D3DXCOLOR & color)
{
	assert(nIdx >= 0 && nIdx < MAX_FANANGLE);

	MyFanangle *pFanangle = &s_aFanangle[nIdx];

	if (!pFanangle->bUse)
	{// 使用していない
		return;
	}

	/*↓ 使用している ↓*/

	VERTEX_2D *pVtx = NULL;		// 頂点情報へのポインタ

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuffFanangle(nIdx);

	// 頂点情報をロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = color;

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();
}

//--------------------------------------------------
// テクスチャ座標の設定
//--------------------------------------------------
void SetTexFanangle(int nIdx)
{
	assert(nIdx >= 0 && nIdx < MAX_FANANGLE);

	MyFanangle *pFanangle = &s_aFanangle[nIdx];

	if (!pFanangle->bUse)
	{// 使用していない
		return;
	}

	/*↓ 使用している ↓*/

	VERTEX_2D *pVtx = NULL;		// 頂点情報へのポインタ

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuffFanangle(nIdx);

	// 頂点情報をロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < NUM_VERTEX; i++)
	{
		// 頂点カラーの設定
		pVtx[i].tex = D3DXVECTOR2(0.0f, 0.0f);
	}

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();
}

//--------------------------------------------------
// 描画するかどうか
//--------------------------------------------------
void SetDrawFanangle(int nIdx, bool bDraw)
{
	assert(nIdx >= 0 && nIdx < MAX_FANANGLE);

	MyFanangle *pFanangle = &s_aFanangle[nIdx];

	if (!pFanangle->bUse)
	{// 使用していない
		return;
	}

	/*↓ 使用している ↓*/

	pFanangle->bDraw = bDraw;
}

//--------------------------------------------------
// 加算合成するかどうか
//--------------------------------------------------
void SetAddFanangle(int nIdx, bool bAdd)
{
	assert(nIdx >= 0 && nIdx < MAX_FANANGLE);

	MyFanangle *pFanangle = &s_aFanangle[nIdx];

	if (!pFanangle->bUse)
	{// 使用していない
		return;
	}

	/*↓ 使用している ↓*/

	pFanangle->bAdd = bAdd;
}

//--------------------------------------------------
// テクスチャの変更
//--------------------------------------------------
void ChangeTextureFanangle(int nIdx, TEXTURE texture)
{
	// テクスチャの変更 [ テクスチャあり ]
	ChangeTextureFanangleWithTex(nIdx, GetTexture(texture));
}

//--------------------------------------------------
// テクスチャの変更 [ テクスチャあり ]
//--------------------------------------------------
void ChangeTextureFanangleWithTex(int nIdx, LPDIRECT3DTEXTURE9 pTexture)
{
	assert(nIdx >= 0 && nIdx < MAX_FANANGLE);

	MyFanangle *pFanangle = &s_aFanangle[nIdx];

	if (!pFanangle->bUse)
	{// 使用していない
		return;
	}

	/*↓ 使用している ↓*/

	pFanangle->pTexture = pTexture;
}

//--------------------------------------------------
// 頂点バッファを取得
//--------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 GetVtxBuffFanangle(int nIdx)
{
	assert(nIdx >= 0 && nIdx < MAX_FANANGLE);

	MyFanangle *pFanangle = &s_aFanangle[nIdx];

	if (!pFanangle->bUse)
	{// 使用していない
		return NULL;
	}

	/*↓ 使用している ↓*/

	return s_aFanangle[nIdx].pVtxBuff;
}

//--------------------------------------------------
// 描画する円の量を設定
//--------------------------------------------------
void AddDrawFanangle(int nIdx, int nVolume)
{
	assert(nIdx >= 0 && nIdx < MAX_FANANGLE);

	MyFanangle *pFanangle = &s_aFanangle[nIdx];

	pFanangle->nMaxBuff += nVolume;

	if (pFanangle->nMaxBuff > NUM_POLYGON)
	{
		pFanangle->nMaxBuff = NUM_POLYGON;
	}
	else if (pFanangle->nMaxBuff < 0)
	{
		pFanangle->nMaxBuff = 0;
	}
}

void ResetDrawFanangle(int nIdx)
{
	assert(nIdx >= 0 && nIdx < MAX_FANANGLE);

	MyFanangle *pFanangle = &s_aFanangle[nIdx];
	
	pFanangle->nMaxBuff = NUM_POLYGON;
}
