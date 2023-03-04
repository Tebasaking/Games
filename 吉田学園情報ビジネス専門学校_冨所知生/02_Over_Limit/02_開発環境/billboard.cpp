//=========================================
//
//	ビルボードの入出力処理
//	Author : 冨所知生
//
//=========================================
#include "main.h"
#include "billboard.h"
#include "input.h"
#include "camera.h"
#include "wall.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureBillboard = { NULL };				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;				//頂点バッファへのポインタ
Billboard g_aBillboard[MAX_BILLBOARD];							//ビルボードの構造体

//=====================================================
//ビルボードの初期化
//=====================================================
void InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,			//確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,															//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bullet000.png",
		&g_pTextureBillboard);

	VERTEX_3D* pVtx = NULL;			//頂点情報の取得

	//頂点バッファをロック
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		g_aBillboard[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//位置の初期設定
		g_aBillboard[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向きの初期設定
		g_aBillboard[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			//色の初期設定
		g_aBillboard[nCnt].bUse = false;										//使用しているかしていないか
		g_aBillboard[nCnt].size = 0.0f;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-BILLBOARD_SIZE, BILLBOARD_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(+BILLBOARD_SIZE, BILLBOARD_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BILLBOARD_SIZE, -BILLBOARD_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(+BILLBOARD_SIZE, -BILLBOARD_SIZE, 0.0f);

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
	g_pVtxBuffBillboard->Unlock();
}

//=========================================
//ビルボードの破棄
//=========================================
void UninitBillboard(void)
{
	//メッシュの破棄
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}

	//マテリアルの破棄
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//=========================================
//ビルボードの更新処理
//=========================================
void UpdateBillboard(void)
{

}

//=========================================
//ビルボードの描画処理
//=========================================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//ライトを無効化する
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

	//Zテストの有効化
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//αテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 132);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBillboard);

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		if (g_aBillboard[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aBillboard[nCnt].mtxWorld);

			D3DXMATRIX mtxView;				//ビューマトリックス

			//ビューマトリックスの取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//カメラの逆行列を設定
			g_aBillboard[nCnt].mtxWorld._11 = mtxView._11;
			g_aBillboard[nCnt].mtxWorld._12 = mtxView._21;
			g_aBillboard[nCnt].mtxWorld._13 = mtxView._31;
			g_aBillboard[nCnt].mtxWorld._31 = mtxView._13;
			g_aBillboard[nCnt].mtxWorld._32 = mtxView._23;
			g_aBillboard[nCnt].mtxWorld._33 = mtxView._33;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBillboard[nCnt].pos.x, g_aBillboard[nCnt].pos.y, g_aBillboard[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aBillboard[nCnt].mtxWorld, &g_aBillboard[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスを更新
			pDevice->SetTransform(D3DTS_WORLD, &g_aBillboard[nCnt].mtxWorld);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//ポリゴンの描画00
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
//ビルボードの情報の取得
//=========================================
Billboard* GetBillboard()
{
	return g_aBillboard;
}

//=========================================
//ビルボードの設置処理
//=========================================
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	int nCntBillboard;

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_aBillboard[nCntBillboard].bUse == false)
		{
			g_aBillboard[nCntBillboard].pos = pos;
			g_aBillboard[nCntBillboard].rot = rot;
			g_aBillboard[nCntBillboard].bUse = true;

			break;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBillboard->Unlock();
}