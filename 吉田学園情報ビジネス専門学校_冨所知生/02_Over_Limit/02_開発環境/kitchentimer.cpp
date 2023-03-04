//=========================================
//
//	キッチンタイマーの入出力処理
//	Author : 冨所知生
//
//=========================================
#include "main.h"
#include "kitchentimer.h"
#include "input.h"
#include "camera.h"
#include "kitchen.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureKTimer[MAX_KITCHENTIMER] = { NULL };			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffKTimer = NULL;			//頂点バッファへのポインタ
KTIMER g_aKTimer[MAX_KITCHENTIMER];							//キッチンタイマーの構造体

//=====================================================
//キッチンタイマーの初期化
//=====================================================
void InitKTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_KITCHENTIMER,			//確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,															//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffKTimer,
		NULL);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/timer_contain.png",
		&g_pTextureKTimer[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/kitchentimer000.png",
		&g_pTextureKTimer[1]);

	VERTEX_3D* pVtx = NULL;			//頂点情報の取得

	//頂点バッファをロック
	g_pVtxBuffKTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_KITCHENTIMER; nCnt++)
	{
		g_aKTimer[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//位置の初期設定
		g_aKTimer[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向きの初期設定
		g_aKTimer[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			//色の初期設定
		g_aKTimer[nCnt].bUse = false;										//使用しているかしていないか

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-KTIMER_WIDTH, KTIMER_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(+KTIMER_WIDTH, KTIMER_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-KTIMER_WIDTH, -KTIMER_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(+KTIMER_WIDTH, -KTIMER_HEIGHT, 0.0f);

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
	g_pVtxBuffKTimer->Unlock();
}

//=========================================
//キッチンタイマーの破棄
//=========================================
void UninitKTimer(void)
{
	//メッシュの破棄
	for (int i = 0; i < MAX_KITCHENTIMER; i++)
	{
		if (g_pTextureKTimer[i] != NULL)
		{					
			g_pTextureKTimer[i]->Release();
			g_pTextureKTimer[i] = NULL;
		}
	}
	//マテリアルの破棄
	if (g_pVtxBuffKTimer != NULL)
	{
		g_pVtxBuffKTimer->Release();
		g_pVtxBuffKTimer = NULL;
	}
}

//=========================================
//キッチンタイマーの更新処理
//=========================================
void UpdateKTimer(void)
{
	KITCHEN *pKitchen = GetKitchen();
	VERTEX_3D* pVtx = NULL;			//頂点情報の取得

	pKitchen += GetSelectKitchen();

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffKTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_KITCHENTIMER; nCnt++)
	{
		if (g_aKTimer[nCnt].bUse)
		{
			pVtx[4].pos = D3DXVECTOR3(-KTIMER_WIDTH, KTIMER_HEIGHT / 2, 0.0f);
			pVtx[5].pos = D3DXVECTOR3(-KTIMER_WIDTH + (pKitchen->CookCount / 24), KTIMER_HEIGHT / 2, 0.0f);
			pVtx[6].pos = D3DXVECTOR3(-KTIMER_WIDTH, -KTIMER_HEIGHT / 2, 0.0f);
			pVtx[7].pos = D3DXVECTOR3(-KTIMER_WIDTH + (pKitchen->CookCount / 24), -KTIMER_HEIGHT / 2, 0.0f);

			pVtx += 4 ;
		}
	}
	//頂点バッファをアンロック
	g_pVtxBuffKTimer->Unlock();
}

//=========================================
//キッチンタイマーの描画処理
//=========================================
void DrawKTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//ライトを無効化する
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffKTimer, 0, sizeof(VERTEX_3D));

	//Zテストの有効化
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//αテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 132);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCnt = 0; nCnt < MAX_KITCHENTIMER; nCnt++)
	{
		pDevice->SetTexture(0, g_pTextureKTimer[g_aKTimer[nCnt].state]);
		
		if (g_aKTimer[nCnt].bUse)
		{//キッチンの情報の取得
			KITCHEN *pKitchen = GetKitchen();

			int SelectKitchen = GetSelectKitchen();

			//一番近いキッチンの番号の入力
			pKitchen += SelectKitchen;

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aKTimer[nCnt].mtxWorld);

			D3DXMATRIX mtxView;				//ビューマトリックス

			//ビューマトリックスの取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, 0.0f, 5.0f, 5.0f);
			D3DXMatrixMultiply(&g_aKTimer[nCnt].mtxWorld, &mtxTrans, &pKitchen->mtxWorldKitchen);

			//カメラの逆行列を設定
			g_aKTimer[nCnt].mtxWorld._11 = mtxView._11;
			g_aKTimer[nCnt].mtxWorld._12 = mtxView._21;
			g_aKTimer[nCnt].mtxWorld._13 = mtxView._31;
			g_aKTimer[nCnt].mtxWorld._31 = mtxView._13;
			g_aKTimer[nCnt].mtxWorld._32 = mtxView._23;
			g_aKTimer[nCnt].mtxWorld._33 = mtxView._33;

			//ワールドマトリックスを更新
			pDevice->SetTransform(D3DTS_WORLD, &g_aKTimer[nCnt].mtxWorld);
				
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
void SetKTimer(D3DXVECTOR3 pos)
{
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffKTimer->Lock(0, 0, (void**)&pVtx, 0);

	int nCntKTimer;

	for (nCntKTimer = 0; nCntKTimer < MAX_KITCHENTIMER; nCntKTimer++)
	{
		if (g_aKTimer[nCntKTimer].bUse == false)
		{
			g_aKTimer[nCntKTimer].pos = pos;
			g_aKTimer[nCntKTimer].bUse = true;

			break;
		}
		pVtx += 4 * nCntKTimer;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffKTimer->Unlock();

	//キッチンタイマーのバーを設置する
	SetKTimerBar(pos);
}
//=========================================
//キッチンタイマーのバーの設置処理
//=========================================
void SetKTimerBar(D3DXVECTOR3 pos)
{
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffKTimer->Lock(0, 0, (void**)&pVtx, 0);

	int nCntKTimer;

	for (nCntKTimer = 0; nCntKTimer < MAX_KITCHENTIMER; nCntKTimer++)
	{
		if (g_aKTimer[nCntKTimer].bUse == false)
		{
			g_aKTimer[nCntKTimer].pos = pos;
			g_aKTimer[nCntKTimer].bUse = true;
			g_aKTimer[nCntKTimer].state = KTIMER_BAR;

			//頂点座標の設定
			pVtx[4].pos = D3DXVECTOR3(-KTIMER_WIDTH / 2, KTIMER_HEIGHT / 2, 0.0f);
			pVtx[5].pos = D3DXVECTOR3(+KTIMER_WIDTH / 2, KTIMER_HEIGHT / 2, 0.0f);
			pVtx[6].pos = D3DXVECTOR3(-KTIMER_WIDTH / 2, -KTIMER_HEIGHT / 2, 0.0f);
			pVtx[7].pos = D3DXVECTOR3(+KTIMER_WIDTH / 2, -KTIMER_HEIGHT / 2, 0.0f);

			break;
		}
		pVtx += 4 * nCntKTimer;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffKTimer->Unlock();
}
//=========================================
//キッチンタイマーの情報を取得
//=========================================
KTIMER *GetKTimer()
{
	return g_aKTimer;
}