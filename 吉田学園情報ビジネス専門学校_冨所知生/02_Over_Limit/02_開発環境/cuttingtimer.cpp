//=========================================
//
//	包丁の調理時間の入出力処理
//	Author : 冨所知生
//
//=========================================
#include "main.h"
#include "cuttingtimer.h"
#include "input.h"
#include "camera.h"
#include "item.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureCTimer[MAX_CUTTINGTIMER] = { NULL };			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCTimer = NULL;			//頂点バッファへのポインタ
CTIMER g_aCTimer[MAX_CUTTINGTIMER];							//キッチンタイマーの構造体

//=====================================================
//キッチンタイマーの初期化
//=====================================================
void InitCTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_CUTTINGTIMER,			//確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,															//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffCTimer,
		NULL);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/timer_contain.png",
		&g_pTextureCTimer[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/kitchentimer000.png",
		&g_pTextureCTimer[1]);

	VERTEX_3D* pVtx = NULL;			//頂点情報の取得

	//頂点バッファをロック
	g_pVtxBuffCTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_CUTTINGTIMER; nCnt++)
	{
		// カットタイマーの情報の初期化
		memset(&g_aCTimer[nCnt], 0, sizeof(g_aCTimer[nCnt]));

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-CTIMER_WIDTH, CTIMER_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(+CTIMER_WIDTH, CTIMER_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-CTIMER_WIDTH, -CTIMER_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(+CTIMER_WIDTH, -CTIMER_HEIGHT, 0.0f);

		//各頂点の法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点colorの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffCTimer->Unlock();
}

//=========================================
//キッチンタイマーの破棄
//=========================================
void UninitCTimer(void)
{
	//メッシュの破棄
	for (int i = 0; i < MAX_CUTTINGTIMER; i++)
	{
		if (g_pTextureCTimer[i] != NULL)
		{
			g_pTextureCTimer[i]->Release();
			g_pTextureCTimer[i] = NULL;
		}
	}
	//マテリアルの破棄
	if (g_pVtxBuffCTimer != NULL)
	{
		g_pVtxBuffCTimer->Release();
		g_pVtxBuffCTimer = NULL;
	}
}

//=========================================
//キッチンタイマーの更新処理
//=========================================
void UpdateCTimer(void)
{
	ITEM *pItem = GetItem();
	VERTEX_3D* pVtx = NULL;			//頂点情報の取得

	pItem += GetSelectItem();

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffCTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_CUTTINGTIMER; nCnt++)
	{
		if (g_aCTimer[nCnt].bUse)
		{
			pVtx[4].pos = D3DXVECTOR3(-CTIMER_WIDTH, CTIMER_HEIGHT / 2, 0.0f);
			pVtx[5].pos = D3DXVECTOR3(-CTIMER_WIDTH + (pItem->CuttingTime / 12), CTIMER_HEIGHT / 2, 0.0f);
			pVtx[6].pos = D3DXVECTOR3(-CTIMER_WIDTH, -CTIMER_HEIGHT / 2, 0.0f);
			pVtx[7].pos = D3DXVECTOR3(-CTIMER_WIDTH + (pItem->CuttingTime / 12), -CTIMER_HEIGHT / 2, 0.0f);

			pVtx += 4;
		}
	}
	//頂点バッファをアンロック
	g_pVtxBuffCTimer->Unlock();
}

//=========================================
//キッチンタイマーの描画処理
//=========================================
void DrawCTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

									//ライトを無効化する
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffCTimer, 0, sizeof(VERTEX_3D));

	//Zテストの有効化
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//αテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 132);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCnt = 0; nCnt < MAX_CUTTINGTIMER; nCnt++)
	{
		pDevice->SetTexture(0, g_pTextureCTimer[g_aCTimer[nCnt].state]);

		if (g_aCTimer[nCnt].bUse)
		{//キッチンの情報の取得
			ITEM *pItem = GetItem();

			int SelectItem = GetSelectItem();

			//一番近いキッチンの番号の入力
			pItem += SelectItem;

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aCTimer[nCnt].mtxWorld);

			D3DXMATRIX mtxView;				//ビューマトリックス

			//ビューマトリックスの取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, 0.0f, 5.0f, 5.0f);
			D3DXMatrixMultiply(&g_aCTimer[nCnt].mtxWorld, &mtxTrans, &pItem->mtxWorldItem);

			//カメラの逆行列を設定
			g_aCTimer[nCnt].mtxWorld._11 = mtxView._11;
			g_aCTimer[nCnt].mtxWorld._12 = mtxView._21;
			g_aCTimer[nCnt].mtxWorld._13 = mtxView._31;
			g_aCTimer[nCnt].mtxWorld._31 = mtxView._13;
			g_aCTimer[nCnt].mtxWorld._32 = mtxView._23;
			g_aCTimer[nCnt].mtxWorld._33 = mtxView._33;

			//ワールドマトリックスを更新
			pDevice->SetTransform(D3DTS_WORLD, &g_aCTimer[nCnt].mtxWorld);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
				nCnt * 4,										//描画する最初の頂点インデックス
				2);												//プリミティブ(ポリゴン)数
		}
	}
	//テクスチャの解除
	pDevice->SetTexture(0, NULL);

	//ライトの有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//デバイス設定の初期化
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
//=========================================
//キッチンタイマーの設置処理
//=========================================
void SetCTimer(D3DXVECTOR3 pos)
{
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffCTimer->Lock(0, 0, (void**)&pVtx, 0);

	int nCntCTimer;

	for (nCntCTimer = 0; nCntCTimer < MAX_CUTTINGTIMER; nCntCTimer++)
	{
		if (g_aCTimer[nCntCTimer].bUse == false)
		{
			g_aCTimer[nCntCTimer].pos = pos;
			g_aCTimer[nCntCTimer].bUse = true;

			break;
		}
		pVtx += 4 * nCntCTimer;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffCTimer->Unlock();

	//キッチンタイマーのバーを設置する
	SetCTimerBar(pos);
}
//=========================================
//キッチンタイマーのバーの設置処理
//=========================================
void SetCTimerBar(D3DXVECTOR3 pos)
{
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffCTimer->Lock(0, 0, (void**)&pVtx, 0);

	int nCntCTimer;

	for (nCntCTimer = 0; nCntCTimer < MAX_CUTTINGTIMER; nCntCTimer++)
	{
		if (g_aCTimer[nCntCTimer].bUse == false)
		{
			g_aCTimer[nCntCTimer].pos = pos;
			g_aCTimer[nCntCTimer].bUse = true;
			g_aCTimer[nCntCTimer].state = CTIMER_BAR;

			//頂点座標の設定
			pVtx[4].pos = D3DXVECTOR3(-CTIMER_WIDTH / 2, CTIMER_HEIGHT / 2, 0.0f);
			pVtx[5].pos = D3DXVECTOR3(+CTIMER_WIDTH / 2, CTIMER_HEIGHT / 2, 0.0f);
			pVtx[6].pos = D3DXVECTOR3(-CTIMER_WIDTH / 2, -CTIMER_HEIGHT / 2, 0.0f);
			pVtx[7].pos = D3DXVECTOR3(+CTIMER_WIDTH / 2, -CTIMER_HEIGHT / 2, 0.0f);

			break;
		}
		pVtx += 4 * nCntCTimer;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffCTimer->Unlock();
}
//=========================================
//キッチンタイマーの情報を取得
//=========================================
CTIMER *GetCTimer()
{
	return g_aCTimer;
}