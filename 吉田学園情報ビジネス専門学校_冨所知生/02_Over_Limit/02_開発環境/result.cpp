//========================================================
//リザルト画面の処理
//========================================================
#include "main.h"
#include "Result.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "score.h"
#include "contain.h"

#define SCORE_SIZE (10)
#define MAN_SCORE_NUM (4)
#define MAX_RESULT_SCORE (30)
#define RESULT_SCORE (0.1f)

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;
LPDIRECT3DTEXTURE9 g_pTextureResultScore = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultScore = NULL;
RESULT g_aResult[MAX_RESULT_SCORE];
//========================================================
//リザルトの初期化処理
//========================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"Data\\TEXTURE\\result_number000.png",
		&g_pTextureResult);

	//頂点バッファの生成・頂点情報の設定
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の指定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffResult->Unlock();

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM002);

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"Data\\TEXTURE\\number000.png",
		&g_pTextureResultScore);

	//頂点バッファの生成・頂点情報の設定
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_RESULT_SCORE * MAN_SCORE_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultScore,
		NULL);

	for (int nCnt = 0; nCnt < MAX_RESULT_SCORE; nCnt++)
	{
		// リザルトの情報の初期化
		memset(&g_aResult[nCnt], 0, sizeof(g_aResult[nCnt]));
	}

	//スコアの設置処理
	int pScore = GetScore();
	FOOD_COUNT *pFCount = GetFoodCount();

	SetResult(0 , pFCount->meat);
	SetResult(1 , pFCount->cabbage);
	SetResult(2 , pFCount->vegetable);
	SetResult(3 , pScore);
}

//========================================================
//リザルトの終了処理
//========================================================
void UninitResult(void)
{
	//サウンドの停止
	StopSound();

	//テクスチャの破棄
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	//テクスチャの破棄
	if (g_pTextureResultScore != NULL)
	{
		g_pTextureResultScore->Release();
		g_pTextureResultScore = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffResultScore != NULL)
	{
		g_pVtxBuffResultScore->Release();
		g_pVtxBuffResultScore = NULL;
	}
}

//========================================================
//リザルトの更新処理
//========================================================
void UpdateResult(void)
{
	FADE pFade = GetFade();

	//決定(ENTERキー)が押されたかどうか
	if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_X,0) || GetJoypadTrigger(JOYKEY_B,0))
	{
		if (pFade == FADE_NONE)
		{
			SetFade(MODE_RANKING);
		}
	}
}
//========================================================
//リザルトの描画処理
//========================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;			//デバイスのポイント

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResult);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
		0,												//描画する最初の頂点インデックス
		2);												//プリミティブ(ポリゴン)数

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResultScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResultScore);

	for (int nCntS = 0; nCntS < MAX_RESULT_SCORE; nCntS++)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
			nCntS * 4,									//描画する最初の頂点インデックス
			2);									//プリミティブ(ポリゴン)数
	}
}
//=========================================
//数字の配置
//=========================================
void SetResult(int nType ,int nScore)
{
	int g_nScore = nScore;
	int aPosTexU[3];		//各桁の数字を格納

	aPosTexU[0] = (g_nScore % 1000) / 100;
	aPosTexU[1] = (g_nScore % 100) / 10;
	aPosTexU[2] = (g_nScore % 10) / 1;

	VERTEX_2D *pVtx;			//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffResultScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < MAX_RESULT_SCORE; nCntScore++)
	{
		if (g_aResult[nCntScore].bUse == false)
		{
			//敵が使用されていない
			g_aResult[nCntScore].nType = nType;
			g_aResult[nCntScore].bUse = true;

			for (int nCntS = 0; nCntS < MAN_SCORE_NUM; nCntS++)
			{
				if (g_aResult[nCntScore].nType == 0)
				{
					//頂点座標の指定
					pVtx[0].pos = D3DXVECTOR3(525.0f + nCntS * 50, 225.0f, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(575.0f + nCntS * 50, 225.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(525.0f + nCntS * 50, 275.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(575.0f + nCntS * 50, 275.0f, 0.0f);
				}
				else if (g_aResult[nCntScore].nType == 1)
				{
					//頂点座標の指定
					pVtx[0].pos = D3DXVECTOR3(525.0f + nCntS * 50, 375.0f, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(575.0f + nCntS * 50, 375.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(525.0f + nCntS * 50, 425.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(575.0f + nCntS * 50, 425.0f, 0.0f);
				}
				else if (g_aResult[nCntScore].nType == 2)
				{
					//頂点座標の指定
					pVtx[0].pos = D3DXVECTOR3(525.0f + nCntS * 50, 510.0f, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(575.0f + nCntS * 50, 510.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(525.0f + nCntS * 50, 560.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(575.0f + nCntS * 50, 560.0f, 0.0f);
				}
				else if (g_aResult[nCntScore].nType == 3)
				{
					//頂点座標の指定
					pVtx[0].pos = D3DXVECTOR3(525.0f + nCntS * 50, 110.0f, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(575.0f + nCntS * 50, 110.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(525.0f + nCntS * 50, 160.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(575.0f + nCntS * 50, 160.0f, 0.0f);
				}

				for (int nCnt = 0; nCnt < MAN_SCORE_NUM; nCnt++)
				{
					//テクスチャ座標の設定
					pVtx[0].tex = D3DXVECTOR2(aPosTexU[nCntS] * RESULT_SCORE, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(aPosTexU[nCntS] * RESULT_SCORE + RESULT_SCORE, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(aPosTexU[nCntS] * RESULT_SCORE, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(aPosTexU[nCntS] * RESULT_SCORE + RESULT_SCORE, 1.0f);

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
				}
				pVtx += 4;
			}
			break;
		}
		pVtx += 4 * MAN_SCORE_NUM;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffResultScore->Unlock();
}