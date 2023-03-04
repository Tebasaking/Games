//=============================================
//
//	準備の出力処理
//	Auhor : 冨所知生
//
//=============================================
#include "main.h"
#include "ready.h"

//グローバル関数
LPDIRECT3DTEXTURE9 g_pTextureReady[NUM_READY] = { NULL, NULL , NULL };			//テクスチャ(3枚分)へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffReady = NULL;		//頂点バッファへのポインタ
D3DXCOLOR g_ReadyColor;
READY g_aReady[NUM_READY];
int g_ReadyTimer;
int StopCnt;
int ZeroNumber;
bool bUsePicture;	//レディーの画像が出終わった
bool bReady;		//準備が完了したかしていないか

#define READY_WIDTH (200.0f)
#define READY_HEIGHT (100.0f)
//=============================================
//タイトルの初期化処理
//=============================================
void InitReady(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ

	StopCnt = 0;
	g_ReadyTimer = 0;
	g_ReadyColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	bReady = false;
	bUsePicture = false;
	ZeroNumber = 0;

	for (int i = 0; i < NUM_READY; i++)
	{
		g_aReady[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aReady[i].bUse = false;
	}

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Ready000.png",
		&g_pTextureReady[0]);

	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Ready001.png",
		&g_pTextureReady[1]);

	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Ready002.png",
		&g_pTextureReady[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_READY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffReady,
		NULL);

	VERTEX_2D *pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffReady->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_READY; nCnt++)
	{
		if (g_aReady[nCnt].bUse == false)
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
	g_pVtxBuffReady->Unlock();

	//準備画面の設置
	SetReady(0);
}
//=============================================
//タイトルの終了処理
//=============================================
void UninitReady(void)
{
	//テクスチャの破棄
	for (int nCntReady = 0; nCntReady < NUM_READY; nCntReady++)
	{
		if (g_pTextureReady[nCntReady] != NULL)
		{
			g_pTextureReady[nCntReady]->Release();
			g_pTextureReady[nCntReady] = NULL;
		}
		//頂点バッファの破棄
		if (g_pVtxBuffReady != NULL)
		{
			g_pVtxBuffReady->Release();
			g_pVtxBuffReady = NULL;
		}
	}
}
//=============================================
//タイトルの更新処理
//=============================================
void UpdateReady(void)
{
	if (g_ReadyTimer < 100)
	{
		g_ReadyTimer++;
	}

	VERTEX_2D *pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffReady->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_READY; nCnt++)
	{
		if (g_aReady[nCnt].bUse)
		{
			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (float)g_ReadyTimer * 2, SCREEN_HEIGHT / 2 - (float)g_ReadyTimer, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + (float)g_ReadyTimer * 2, SCREEN_HEIGHT / 2 - (float)g_ReadyTimer, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (float)g_ReadyTimer * 2, SCREEN_HEIGHT / 2 + (float)g_ReadyTimer, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + (float)g_ReadyTimer * 2, SCREEN_HEIGHT / 2 + (float)g_ReadyTimer, 0.0f);
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffReady->Unlock();

	if (g_ReadyTimer >= 100)
	{
		StopCnt++;

		if (StopCnt == 30)
		{//画像が最大になってから経過した時間
			if (bUsePicture == false)
			{
				g_ReadyTimer = 0;
				bUsePicture = true;
				//準備画面の設置
				SetReady(1);
				StopCnt = 0;
				g_aReady[0].bUse = false;
			}
			else
			{
				g_aReady[1].bUse = false;
				bReady = true;
			}
		}
	}
}
//=============================================
//タイトルの描画処理
//=============================================
void DrawReady(void)
{
	int nCntReady;

	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffReady, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの描画
	for (nCntReady = 0; nCntReady < NUM_READY; nCntReady++)
	{
		if (g_aReady[nCntReady].bUse)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureReady[g_aReady[nCntReady].nType]);

			//ポリゴンの描画 四角
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,				//プリミティブの種類
				nCntReady * 4,						//描画する最初の頂点インデックス
				2);									//プリミティブ(ポリゴン)数
		}
	}
}
//=========================================
//準備画面の設置処理
//=========================================
void SetReady(int nType)
{
	VERTEX_2D *pVtx;			//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffReady->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_READY; nCnt++)
	{
		if (g_aReady[nCnt].bUse == false)
		{
			if (nType == 0)
			{
				ZeroNumber = nType;
			}

			g_ReadyTimer = 0;
			g_aReady[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aReady[nCnt].bUse = true;
			g_aReady[nCnt].nType = nType;

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
	g_pVtxBuffReady->Unlock();
}
//=========================================
// 準備が完了したかしていないかの取得
//=========================================
bool GetReady()
{
	return bReady;
}