//=============================================
//
//	オーダーの入出力処理
//	Auhor : 冨所知生
//
//=============================================
#include <stdio.h>
#include "main.h"
#include "title.h"
#include "player.h"
#include "input.h"
#include "fade.h"
#include "order.h"
#include "ordertimer.h"

#define NUM_OTIMER (200)
#define OTIMER_SIZE (20.0f)
//グローバル関数
LPDIRECT3DTEXTURE9 g_pTextureOTimer = NULL;			//テクスチャ(3枚分)へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOTimer = NULL;									//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureOTimerBar = NULL;										//テクスチャ(3枚分)へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOTimerBar = NULL;									//頂点バッファへのポインタ
OTIMER g_aOTimer[NUM_OTIMER];
//=============================================
//タイトルの初期化処理
//=============================================
void InitOTimer(void)
{
	for (int i = 0; i < NUM_OTIMER; i++)
	{
		g_aOTimer[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aOTimer[i].bUse = false;
	}

	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	//注文内容の画像の読み込みは完成品の数値を使っているので
	//[1]から始めている
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/OTimer001.png",
		&g_pTextureOTimer);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_OTIMER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffOTimer,
		NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_OTIMER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffOTimerBar,
		NULL);

	VERTEX_2D *pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffOTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_OTIMER; nCnt++)
	{
		if (g_aOTimer[nCnt].bUse == false)
		{
			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffOTimer->Unlock();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffOTimerBar->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_OTIMER; nCnt++)
	{
		if (g_aOTimer[nCnt].bUse == false)
		{
			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffOTimerBar->Unlock();
}
//=============================================
//タイトルの終了処理
//=============================================
void UninitOTimer(void)
{
	//テクスチャの破棄
	if (g_pTextureOTimer != NULL)
	{
		g_pTextureOTimer->Release();
		g_pTextureOTimer = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffOTimer != NULL)
	{
		g_pVtxBuffOTimer->Release();
		g_pVtxBuffOTimer = NULL;
	}

	//テクスチャの破棄
	if (g_pTextureOTimerBar != NULL)
	{					
		g_pTextureOTimerBar->Release();
		g_pTextureOTimerBar = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffOTimerBar != NULL)
	{					
		g_pVtxBuffOTimerBar->Release();
		g_pVtxBuffOTimerBar = NULL;
	}
}
//=============================================
//タイトルの更新処理
//=============================================
void UpdateOTimer(void)
{
	VERTEX_2D *pVtx;			//頂点情報へのポインタ
	ORDER *pOrder = GetOrder();

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffOTimerBar->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_OTIMER; nCnt++)
	{
		if (g_aOTimer[nCnt].bUse)
		{
			//オーダーを対応した番号まで進める
			pOrder += g_aOTimer[nCnt].nNumber;

			if (g_aOTimer[nCnt].state == OTIMER_BAR)
			{
				pVtx[0].pos = D3DXVECTOR3(pOrder->pos.x, g_aOTimer[nCnt].pos.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(pOrder->pos.x + pOrder->nLimit / 30,pOrder->pos.y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pOrder->pos.x, g_aOTimer[nCnt].pos.y + OTIMER_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pOrder->pos.x + pOrder->nLimit / 30, pOrder->pos.y + OTIMER_SIZE, 0.0f);
			}
			if (pOrder->bUse == false)
			{//対応したオーダーがfalseだった時
				g_aOTimer[nCnt].bUse = false;
			}
				//ポインターの初期化
				pOrder = GetOrder();
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffOTimerBar->Unlock();

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffOTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_OTIMER; nCnt++)
	{
		if (g_aOTimer[nCnt].bUse)
		{
			//オーダーを対応した番号まで進める
			pOrder += g_aOTimer[nCnt].nNumber;

			if (g_aOTimer[nCnt].state == OTIMER_CONTAIN)
			{
				pVtx[0].pos = D3DXVECTOR3(pOrder->pos.x, g_aOTimer[nCnt].pos.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(pOrder->pos.x + 130.0f, pOrder->pos.y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pOrder->pos.x, g_aOTimer[nCnt].pos.y + OTIMER_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pOrder->pos.x + 130.0f, pOrder->pos.y + OTIMER_SIZE, 0.0f);
			}
			if (pOrder->bUse == false)
			{//対応したオーダーがfalseだった時
				g_aOTimer[nCnt].bUse = false;
			}
			//ポインターの初期化
			pOrder = GetOrder();
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffOTimer->Unlock();
}
//=============================================
//タイトルの描画処理
//=============================================
void DrawOTimer(void)
{
	int nCntOTimer;

	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffOTimer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの描画
	for (nCntOTimer = 0; nCntOTimer < NUM_OTIMER; nCntOTimer++)
	{
		if (g_aOTimer[nCntOTimer].bUse)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureOTimer);

			//ポリゴンの描画 四角
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,				//プリミティブの種類
				nCntOTimer * 4,						//描画する最初の頂点インデックス
				2);									//プリミティブ(ポリゴン)数
		}
	}

	//バーのテクスチャのDraw
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffOTimerBar, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの描画
	for (nCntOTimer = 0; nCntOTimer < NUM_OTIMER; nCntOTimer++)
	{
		if (g_aOTimer[nCntOTimer].bUse)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureOTimerBar);

			//ポリゴンの描画 四角
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,				//プリミティブの種類
				nCntOTimer * 4,						//描画する最初の頂点インデックス
				2);									//プリミティブ(ポリゴン)数
		}
	}
}

//=========================================
//	注文の設置処理
//	* nTypeはcontain内のITEMTYPEの数字と共通 *
//=========================================
void SetOTimer(D3DXVECTOR3 pos, int nNumber)
{
	VERTEX_2D *pVtx;			//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffOTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_OTIMER; nCnt++)
	{
		if (g_aOTimer[nCnt].bUse == false)
		{
			g_aOTimer[nCnt].pos = pos;
			g_aOTimer[nCnt].bUse = true;
			g_aOTimer[nCnt].nNumber = nNumber;

			pVtx[0].pos = D3DXVECTOR3(pos.x, pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pos.x + 130.0f, pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pos.x, pos.y + OTIMER_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pos.x + 130.0f, pos.y + OTIMER_SIZE, 0.0f);

			// rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//頂点colorの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffOTimer->Unlock();

	//オーダータイマーのバーの設置
	SetOTimerBar(pos, nNumber);
}
//=========================================
//	注文の設置処理
//	* nTypeはcontain内のITEMTYPEの数字と共通 *
//=========================================
void SetOTimerBar(D3DXVECTOR3 pos, int nNumber)
{
	VERTEX_2D *pVtx;			//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffOTimerBar->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_OTIMER; nCnt++)
	{
		if (g_aOTimer[nCnt].bUse == false)
		{
			g_aOTimer[nCnt].pos = pos;
			g_aOTimer[nCnt].bUse = true;
			g_aOTimer[nCnt].nNumber = nNumber;
			g_aOTimer[nCnt].state = OTIMER_BAR;

			pVtx[0].pos = D3DXVECTOR3(pos.x, pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pos.x + 130.0f, pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pos.x, pos.y + OTIMER_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pos.x + 130.0f, pos.y + OTIMER_SIZE, 0.0f);

			// rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//頂点colorの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffOTimerBar->Unlock();
}
//=========================================
//注文の情報の取得
//=========================================
OTIMER *GetOTimer()
{
	return g_aOTimer;
}