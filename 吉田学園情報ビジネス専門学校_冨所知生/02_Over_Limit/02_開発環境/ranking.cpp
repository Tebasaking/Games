//=========================================
//
//	ランキングの入出力処理
//	Author : 冨所知生
//
//=========================================
#include <stdio.h>
#include "ranking.h"
#include "score.h"
#include "main.h"
#include "fade.h"
#include "input.h"
#include "sound.h"

//========================================================
//ランキングスコア構造体
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	int nScore;			//スコア
}RankScore;

//========================================================
//グローバル変数
//========================================================
LPDIRECT3DTEXTURE9 g_pTextureRank = NULL;			//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRankScore = NULL;		//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRankBG = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;		//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankScore = NULL;	//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankBG = NULL;	//背景バッファへのポインタ
RankScore g_aRankScore[MAX_RANK];	//ランキングスコア情報
int g_nRankUpdate = -1;				//更新ランクNo.
int g_nTimerRanking;				//ランキング画面表示タイマー
int g_RankingTime = 0;

//========================================================
//ランキングの初期化処理
//========================================================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;
	int nCntR;
	int nCntS;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読込
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ranking000.png",
		&g_pTextureRank);

	//テクスチャの読込
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureRankScore);

	//テクスチャの読込
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ranking000.png",
		&g_pTextureRankBG);

	//ランキングの情報の初期化
	for (nCntR = 0; nCntR < MAX_RANK; nCntR++)
	{
		g_aRankScore[nCntR].pos = D3DXVECTOR3(365.0f, 265.0f, 0.0f);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK * MAX_RANKSCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankScore,
		NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankBG,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntR = 0; nCntR < MAX_RANK; nCntR++)
	{
		//頂点座標の設定
		pVtx[0].pos.x = 0.0f;
		pVtx[0].pos.y = 0.0f;
		pVtx[0].pos.z = 0.0f;
					
		pVtx[1].pos.x = 0.0f;
		pVtx[1].pos.y = 0.0f;
		pVtx[1].pos.z = 0.0f;
						
		pVtx[2].pos.x = 0.0f;
		pVtx[2].pos.y = 0.0f;
		pVtx[2].pos.z = 0.0f;
					
		pVtx[3].pos.x = 0.0f;
		pVtx[3].pos.y = 0.0f;
		pVtx[3].pos.z = 0.0f;

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + 0.2f * nCntR);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + 0.2f * nCntR);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.2f + 0.2f * nCntR);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.2f + 0.2f * nCntR);

		pVtx += 4;

	}
	//頂点バッファをアンロックする
	g_pVtxBuffRank->Unlock();


	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntR = 0; nCntR < MAX_RANK; nCntR++)
	{
		g_aRankScore[nCntR].pos.x += 150;	//スコア表示場所へ移動
		for (nCntS = 0; nCntS < MAX_RANKSCORE; nCntS++)
		{
			pVtx[0].pos.x = g_aRankScore[nCntR].pos.x - 40.0f + nCntS * 80;
			pVtx[0].pos.y = g_aRankScore[nCntR].pos.y - 40.0f + nCntR * 150;
			pVtx[0].pos.z = g_aRankScore[nCntR].pos.z + 0.0f;

			pVtx[1].pos.x = g_aRankScore[nCntR].pos.x + 40.0f + nCntS * 80;
			pVtx[1].pos.y = g_aRankScore[nCntR].pos.y - 40.0f + nCntR * 150;
			pVtx[1].pos.z = g_aRankScore[nCntR].pos.z + 0.0f;

			pVtx[2].pos.x = g_aRankScore[nCntR].pos.x - 40.0f + nCntS * 80;
			pVtx[2].pos.y = g_aRankScore[nCntR].pos.y + 40.0f + nCntR * 150;
			pVtx[2].pos.z = g_aRankScore[nCntR].pos.z + 0.0f;

			pVtx[3].pos.x = g_aRankScore[nCntR].pos.x + 40.0f + nCntS * 80;
			pVtx[3].pos.y = g_aRankScore[nCntR].pos.y + 40.0f + nCntR * 150;
			pVtx[3].pos.z = g_aRankScore[nCntR].pos.z + 0.0f;


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
	}

	//頂点バッファをアンロックする
	g_pVtxBuffRankScore->Unlock();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankBG->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffRankBG->Unlock();
}

//=========================================
//ランキングの終了処理
//=========================================
void UninitRanking(void)
{
	StopSound();

	//テクスチャの破棄
	if (g_pTextureRank != NULL)
	{
		g_pTextureRank->Release();
		g_pTextureRank = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}

	//テクスチャの破棄
	if (g_pTextureRankScore != NULL)
	{
		g_pTextureRankScore->Release();
		g_pTextureRankScore = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRankScore != NULL)
	{
		g_pVtxBuffRankScore->Release();
		g_pVtxBuffRankScore = NULL;
	}

	//テクスチャの破棄
	if (g_pTextureRankBG != NULL)
	{
		g_pTextureRankBG->Release();
		g_pTextureRankBG = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRankBG != NULL)
	{
		g_pVtxBuffRankBG->Release();
		g_pVtxBuffRankBG = NULL;
	}
}

//=========================================
//ランキングの更新処理
//=========================================
void UpdateRanking(void)
{
	FADE pFade = GetFade();

	g_RankingTime++;

	if ((GetKeyboardTrigger(DIK_RETURN) == true || g_RankingTime >= 240) && pFade == FADE_NONE)
	{
		SetFade(MODE_TITLE);
	}
}

//=========================================
//ランキングの描画処理
//=========================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntR;
	int nCntS;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリーム設定
	pDevice->SetStreamSource(0, g_pVtxBuffRankBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRankBG);

	//ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//頂点バッファをデータストリーム設定
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (nCntR = 0; nCntR < MAX_RANK; nCntR++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureRank);

		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntR * 4, 2);
	}

	//頂点バッファをデータストリーム設定
	pDevice->SetStreamSource(0, g_pVtxBuffRankScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (nCntR = 0; nCntR < MAX_RANK; nCntR++)
	{
		for (nCntS = 0; nCntS < MAX_RANKSCORE; nCntS++)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureRankScore);

			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntR * 4 * MAX_RANKSCORE) + (nCntS * 4), 2);
		}
	}
}

//=========================================
//ランキングのリセット
//=========================================
void ResetRanking(void)
{
	FILE *pFile;	//ファイルポインタを宣言
	int nCntR;

	g_nRankUpdate = -1;	//更新ランクNo.の初期化

						//ファイルを開く
	pFile = fopen(FILE_NAME, "r");

	if (pFile != NULL)
	{//ファイルが開いた場合
		for (nCntR = 0; nCntR < MAX_RANK; nCntR++)
		{//ランキングの読み込み
			fscanf(pFile, "%d", &g_aRankScore[nCntR].nScore);
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開かない場合
		FADE pFade = GetFade();

		if (pFade == FADE_NONE)
		{//何もしていない状態
		 //フェードの設定
			SetFade(MODE_TITLE);
		}
	}
}

//=========================================
//ランキングのセーブ
//=========================================
void SaveRanking(void)
{
	FILE *pFile;	//ファイルポインタを宣言
	int nCntR;

	g_nRankUpdate = -1;	//更新ランクNo.の初期化

						//ファイルを開く
	pFile = fopen(FILE_NAME, "w");

	if (pFile != NULL)
	{//ファイルが開いた場合
		for (nCntR = 0; nCntR < MAX_RANK; nCntR++)
		{//ランキングの書き込み
			fprintf(pFile, "%d\n", g_aRankScore[nCntR].nScore);
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開かない場合
		FADE pFade = GetFade();

		if (pFade == FADE_NONE)
		{//何もしていない状態

		 //フェードの設定
			SetFade(MODE_TITLE);
		}
	}

}

//=========================================
//ランキングの設定処理
//=========================================
void SetRanking(int nScore)
{
	VERTEX_2D *pVtx;
	int nCntR;		//繰り返し
	int nCntR2;		//繰り返し2
	int nCheckMin;	//小さい方との値を比較

					//ランキングの最下位と今回のスコアを比べる
	if (nScore >= g_aRankScore[MAX_RANK - 1].nScore)
	{
		g_nRankUpdate = 5;
		//比較した数値を入れる。
		g_aRankScore[MAX_RANK - 1].nScore = nScore;
	}

	for (nCntR = 0; nCntR < MAX_RANK - 1; nCntR++)
	{
		for (nCntR2 = nCntR + 1; nCntR2 < MAX_RANK; nCntR2++)
		{//上記の繰り返しが進むたびに繰り返し回数が-1ずつされる。

			if (g_aRankScore[nCntR].nScore <= g_aRankScore[nCntR2].nScore)
			{
				//変数を一時格納
				nCheckMin = g_aRankScore[nCntR2].nScore;

				//比較した数値を入れる
				g_aRankScore[nCntR2].nScore = g_aRankScore[nCntR].nScore;
				g_aRankScore[nCntR].nScore = nCheckMin;
			}
		}

	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	//複数回for文することでランキングをいっぱい出せる
	for (nCntR = 0; nCntR < MAX_RANK; nCntR++)
	{
		int aPosTexU[3];

		aPosTexU[0] = g_aRankScore[nCntR].nScore % 1000 / 100;
		aPosTexU[1] = g_aRankScore[nCntR].nScore % 100 / 10;
		aPosTexU[2] = g_aRankScore[nCntR].nScore % 10 / 1;

		for (nCntR2 = 0; nCntR2 < MAX_RANKSCORE; nCntR2++)
		{
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + 0.1f * aPosTexU[nCntR2], 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + 0.1f * aPosTexU[nCntR2], 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + 0.1f * aPosTexU[nCntR2], 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + 0.1f * aPosTexU[nCntR2], 1.0f);

			pVtx += 4;
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffRankScore->Unlock();

	//セーブ処理
	SaveRanking();
}