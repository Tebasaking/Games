//========================================================
//ゲームタイマー画面の処理
//========================================================
#include "main.h"
#include "input.h"
#include "gametimer.h"
#include "ready.h"
#include "fade.h"
#include "sound.h"

#define MAX_NUMBER (4)			//ゲームタイマーに使う数字

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureGameTimer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameTimer = NULL;
D3DXVECTOR3 g_posGameTimer;			//ゲームタイマーの位置
int g_nGameTimer;					//タイマーに表示される数字
int g_nTimerCount;					//秒に変換する前の数字
int minituCount;
int GameEnd;						//ゲーム終了時の演出時間
bool bGameTimer;					//ゲームタイマーが使われているかいないか
//========================================================
//ゲームタイマーの初期化処理
//========================================================
void InitGameTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntS;
	g_nGameTimer = 360;						//値を初期化する
	minituCount = 0;
	GameEnd = 0;
	g_posGameTimer = D3DXVECTOR3(1100.0f, 650.0f, 0.0f);			//位置を初期化する
	bGameTimer = false;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"Data\\TEXTURE\\number001.png",
		&g_pTextureGameTimer);

	//頂点バッファの生成・頂点情報の設定
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_NUMBER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGameTimer,
		NULL);

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffGameTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntS = 0; nCntS < MAX_NUMBER; nCntS++)
	{
		//頂点座標の指定
		pVtx[0].pos = D3DXVECTOR3(g_posGameTimer.x - 30, g_posGameTimer.y - 50, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posGameTimer.x + 30, g_posGameTimer.y - 50, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posGameTimer.x - 30, g_posGameTimer.y + 50, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posGameTimer.x + 30, g_posGameTimer.y + 50, 0.0f);

		g_posGameTimer += D3DXVECTOR3(50.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffGameTimer->Unlock();
}

//========================================================
//ゲームタイマーの終了処理
//========================================================
void UninitGameTimer(void)
{
	//テクスチャの破棄
	if (g_pVtxBuffGameTimer != NULL)
	{
		g_pTextureGameTimer->Release();
		g_pTextureGameTimer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffGameTimer != NULL)
	{
		g_pVtxBuffGameTimer->Release();
		g_pVtxBuffGameTimer = NULL;
	}
}

//========================================================
//ゲームタイマーの更新処理
//========================================================
void UpdateGameTimer(void)
{
	if (bGameTimer)
	{
		GameEnd++;

		if (GameEnd == 360)
		{
			SetFade(MODE_RESULT);
			GameEnd = 0;
		}
	}

	else
	{
		g_nTimerCount++;

		if (g_nTimerCount >= 60)
		{
			g_nTimerCount = 0;
			SubGameTimer(1);
		}
	}
}

//========================================================
//ゲームタイマーの描画処理
//========================================================
void DrawGameTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntS;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGameTimer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureGameTimer);

	for (nCntS = 0; nCntS < MAX_NUMBER; nCntS++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
			nCntS * 4,									//描画する最初の頂点インデックス
			2);									//プリミティブ(ポリゴン)数
	}
}

//========================================================
//ゲームタイマーの設定処理
//========================================================
void SetGameTimer(int nGameTimer)
{
	int aPosTexU[8];		//各桁の数字を格納
	int nCntS;

	g_nGameTimer = nGameTimer;

	if (g_nGameTimer % 60 == 0)
	{
		minituCount += g_nGameTimer / 60;
		g_nGameTimer = 0;
	}

	aPosTexU[0] = (minituCount % 10) / 1;
	aPosTexU[1] = 11;
	aPosTexU[2] = (g_nGameTimer % 100) / 10;
	aPosTexU[3] = (g_nGameTimer % 10) / 1;

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

							//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffGameTimer->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	for (nCntS = 0; nCntS < MAX_NUMBER; nCntS++)
	{
		pVtx[0].tex = D3DXVECTOR2(aPosTexU[nCntS] * 0.083333f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(aPosTexU[nCntS] * 0.083333f + 0.083333f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(aPosTexU[nCntS] * 0.083333f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(aPosTexU[nCntS] * 0.083333f + 0.083333f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffGameTimer->Unlock();
}
//========================================================
//ゲームタイマーの加算処理
//========================================================
void SubGameTimer(int nValue)
{
	int aPosTexU[8];		//各桁の数字を格納
	int nCntS;

	g_nGameTimer -= nValue;

	if (g_nGameTimer <= -1)
	{
		minituCount--;
		g_nGameTimer = 59;
	}

	aPosTexU[0] = (minituCount % 10) / 1;
	aPosTexU[1] = 11;
	aPosTexU[2] = (g_nGameTimer % 100) / 10;
	aPosTexU[3] = (g_nGameTimer % 10) / 1;

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffGameTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntS = 0; nCntS < MAX_NUMBER; nCntS++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(aPosTexU[nCntS] * 0.083333f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(aPosTexU[nCntS] * 0.083333f + 0.083333f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(aPosTexU[nCntS] * 0.083333f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(aPosTexU[nCntS] * 0.083333f + 0.083333f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffGameTimer->Unlock();

	if (g_nGameTimer == 0 && minituCount == 0)
	{
		StopSound(SOUND_LABEL_BGM001);
		bGameTimer = true;
		SetReady(2);
		PlaySound(SOUND_LABEL_WHISTLE);
	}
}

//========================================================
//ゲームタイマーの取得
//========================================================
int GetGameTimer(void)
{
	return g_nGameTimer;
}

//=========================================
//ゲームタイマーの使用状況の取得
//=========================================
bool GetGTimer()
{
	return bGameTimer;
}