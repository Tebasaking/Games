//=========================================
//
//	影の入出力処理
//	Author : 冨所知生
//
//=========================================
#include "main.h"
#include "shadow.h"
#include "input.h"
#include "camera.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureShadow = { NULL };				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;			//頂点バッファへのポインタ
Shadow g_aShadow[MAX_SHADOW];

//=====================================================
//影の初期化
//=====================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,			//確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,														//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/shadow000.jpg",
		&g_pTextureShadow);

	VERTEX_3D* pVtx = NULL;			//頂点情報の取得

	//頂点バッファをロック
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		g_aShadow[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//位置の初期設定
		g_aShadow[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向きの初期設定
		g_aShadow[nCnt].bUse = false;										//使用しているかしていないか
		g_aShadow[nCnt].size = 0.0f;

		//頂点座標の設定（ワールド座標ではなくローカル座標を指定する）
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//各頂点の法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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
	g_pVtxBuffShadow->Unlock();
}

//=========================================
//影の破棄
//=========================================
void UninitShadow(void)
{
	//メッシュの破棄
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//マテリアルの破棄
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow ->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=========================================
//影の更新処理
//=========================================
void UpdateShadow(void)
{

}

//=========================================
//影の描画処理
//=========================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureShadow);

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		if (g_aShadow[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aShadow[nCnt].mtxShadow);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aShadow[nCnt].rot.y, g_aShadow[nCnt].rot.x, g_aShadow[nCnt].rot.z);

			D3DXMatrixMultiply(&g_aShadow[nCnt].mtxShadow, &g_aShadow[nCnt].mtxShadow, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCnt].pos.x, g_aShadow[nCnt].pos.y, g_aShadow[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCnt].mtxShadow, &g_aShadow[nCnt].mtxShadow, &mtxTrans);

			//ワールドマトリックスを更新
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCnt].mtxShadow);

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

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=========================================
//影の情報の取得
//=========================================
Shadow* GetShadow()
{
	return g_aShadow;
}

//=========================================
//影の設置処理
//=========================================
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	int nCntShadow;

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == false)
		{
			g_aShadow[nCntShadow].pos = pos;
			g_aShadow[nCntShadow].rot = rot;
			g_aShadow[nCntShadow].bUse = true;

			break;
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();

	return nCntShadow;						//影の番号(index)をつける
}

//=========================================
//影が物体に応じて移動する処理
//=========================================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos , float nSize)
{
	if (g_aShadow[nIdxShadow].bUse)
	{
		//引数で指定された番号の影のposを設定
		g_aShadow[nIdxShadow].pos = pos;

		g_aShadow[nIdxShadow].size = nSize;

		VERTEX_3D* pVtx = NULL;			//頂点情報の取得

		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nIdxShadow * 4;		//頂点データのポインタを4つ分進める

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(- SHADOW_SIZE - g_aShadow[nIdxShadow].size, 0.0f, + SHADOW_SIZE + g_aShadow[nIdxShadow].size);
		pVtx[1].pos = D3DXVECTOR3(+ SHADOW_SIZE + g_aShadow[nIdxShadow].size, 0.0f, + SHADOW_SIZE + g_aShadow[nIdxShadow].size);
		pVtx[2].pos = D3DXVECTOR3(- SHADOW_SIZE - g_aShadow[nIdxShadow].size, 0.0f, - SHADOW_SIZE - g_aShadow[nIdxShadow].size);
		pVtx[3].pos = D3DXVECTOR3(+ SHADOW_SIZE + g_aShadow[nIdxShadow].size, 0.0f, - SHADOW_SIZE - g_aShadow[nIdxShadow].size);
		
		//頂点colorの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - g_aShadow[nIdxShadow].size / 2);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - g_aShadow[nIdxShadow].size / 2);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - g_aShadow[nIdxShadow].size / 2);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - g_aShadow[nIdxShadow].size / 2);

		//頂点バッファをアンロックする
		g_pVtxBuffShadow->Unlock();
	}
}