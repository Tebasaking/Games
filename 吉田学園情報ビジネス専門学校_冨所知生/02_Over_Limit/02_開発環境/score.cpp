//========================================================
//スコア画面の処理
//========================================================
#include "main.h"
#include "score.h"
#include "input.h"

#define MAX_NUMBER (3)			//スコアに使う数字

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;
D3DXVECTOR3 g_posScore;			//スコアの位置
int g_nScore;					//スコアの値

//========================================================
//スコアの初期化処理
//========================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntS;
	g_nScore = 0;											//値を初期化する
	g_posScore = D3DXVECTOR3(50.0f, 650.0f, 0.0f);			//位置を初期化する

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"Data\\TEXTURE\\number001.png",
		&g_pTextureScore);

	//頂点バッファの生成・頂点情報の設定
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_NUMBER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntS = 0; nCntS < MAX_NUMBER; nCntS++)
	{
		//頂点座標の指定
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x - 30, g_posScore.y - 50, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + 30, g_posScore.y - 50, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x - 30, g_posScore.y + 50, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + 30, g_posScore.y + 50, 0.0f);

		g_posScore += D3DXVECTOR3(50.0f, 0.0f, 0.0f);

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
	g_pVtxBuffScore->Unlock();
}

//========================================================
//スコアの終了処理
//========================================================
void UninitScore(void)
{
	//テクスチャの破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//========================================================
//スコアの更新処理
//========================================================
void UpdateScore(void)
{
}

//========================================================
//スコアの描画処理
//========================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntS;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureScore);

	for (nCntS = 0; nCntS < MAX_NUMBER; nCntS++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
			nCntS * 4,										//描画する最初の頂点インデックス
			2);												//プリミティブ(ポリゴン)数
	}
}

//========================================================
//スコアの設定処理
//========================================================
void SetScore(int nScore)
{
	int aPosTexU[8];		//各桁の数字を格納
	int nCntS;

	g_nScore = nScore;

	aPosTexU[0] = (g_nScore % 1000) / 100;
	aPosTexU[1] = (g_nScore % 100) / 10;
	aPosTexU[2] = (g_nScore % 10) / 1;

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	for (nCntS = 0; nCntS < MAX_NUMBER; nCntS++)
	{
		pVtx[0].tex = D3DXVECTOR2(aPosTexU[nCntS] * TEXTURE_SIZE, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(aPosTexU[nCntS] * TEXTURE_SIZE + TEXTURE_SIZE, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(aPosTexU[nCntS] * TEXTURE_SIZE, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(aPosTexU[nCntS] * TEXTURE_SIZE + TEXTURE_SIZE, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}
//========================================================
//スコアの加算処理
//========================================================
void AddScore(int nValue)
{
	int aPosTexU[8];		//各桁の数字を格納
	int nCntS;

	g_nScore += nValue;

	aPosTexU[0] = (g_nScore % 1000) / 100;
	aPosTexU[1] = (g_nScore % 100) / 10;
	aPosTexU[2] = (g_nScore % 10) / 1;

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntS = 0; nCntS < MAX_NUMBER; nCntS++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(aPosTexU[nCntS] * 0.08333f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(aPosTexU[nCntS] * 0.08333f + 0.08333f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(aPosTexU[nCntS] * 0.08333f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(aPosTexU[nCntS] * 0.08333f + 0.08333f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//========================================================
//スコアの取得
//========================================================
int GetScore(void)
{
	return g_nScore;
}