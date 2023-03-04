//=========================================
//
//	線の入出力処理
//	Author : 冨所知生
//
//=========================================
#include "main.h"
#include "line.h"
#include "input.h"
#include "camera.h"
#include "wall.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLine = NULL;				//頂点バッファへのポインタ
LINE g_aLine[MAX_LINE];										//線の構造体

//=====================================================
//線の初期化
//=====================================================
void InitLine(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2 * MAX_LINE,			//確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,															//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffLine,
		NULL);

	VERTEX_3D* pVtx = NULL;			//頂点情報の取得

	//頂点バッファをロック
	g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_LINE; nCnt++)
	{
		g_aLine[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//位置の初期設定
		g_aLine[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			//色の初期設定
		g_aLine[nCnt].bUse = false;										//使用しているかしていないか

		//各頂点の法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点colorの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 2;
	}
	//頂点バッファをアンロック
	g_pVtxBuffLine->Unlock();
}

//=========================================
//線の破棄
//=========================================
void UninitLine(void)
{
	//バッファの破棄
	if (g_pVtxBuffLine != NULL)
	{
		g_pVtxBuffLine->Release();
		g_pVtxBuffLine = NULL;
	}
}

//=========================================
//線の描画処理
//=========================================
void DrawLine(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//ライトを無効化する
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//カリングをはがす
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffLine, 0, sizeof(VERTEX_3D));

	for (int nCnt = 0; nCnt < MAX_LINE; nCnt++)
	{
		if (g_aLine[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aLine[nCnt].mtxWorld);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aLine[nCnt].pos.x, g_aLine[nCnt].pos.y, g_aLine[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aLine[nCnt].mtxWorld, &g_aLine[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスを更新
			pDevice->SetTransform(D3DTS_WORLD, &g_aLine[nCnt].mtxWorld);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_LINELIST,			//プリミティブの種類
				nCnt * 2,										//描画する最初の頂点インデックス
				1);												//プリミティブ(ポリゴン)数
		}
	}
	//ライトの有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//カリングをはがす
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//=========================================
//線の設置処理
//=========================================
void SetLine(D3DXVECTOR3 pos, D3DXCOLOR col ,D3DXVECTOR3 start , D3DXVECTOR3 end)
{
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);

	int nCntLine;

	for (nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		if (g_aLine[nCntLine].bUse == false)
		{
			g_aLine[nCntLine].pos = pos;
			g_aLine[nCntLine].col = col;
			g_aLine[nCntLine].bUse = true;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(start.x, start.y, start.z);
			pVtx[1].pos = D3DXVECTOR3(end.x, end.y, end.z);

			pVtx[0].col = col;
			pVtx[1].col = col;

			break;
		}
		pVtx += 2;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffLine->Unlock();
}