//=========================================
//
//	壁の入出力処理
//	Author : 冨所知生
//
//=========================================
#include "main.h"
#include "wall.h"
#include "input.h"
#include "camera.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureWall = { NULL };				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;				//頂点バッファへのポインタ
Wall g_aWall[MAX_WALL];

//=====================================================
//壁の初期化
//=====================================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,			//確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,														//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/wall.jpg",
		&g_pTextureWall);

	VERTEX_3D* pVtx = NULL;			//頂点情報の取得

	//頂点バッファをロック
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		g_aWall[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//位置の初期設定
		g_aWall[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向きの初期設定
		g_aWall[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			//色の初期設定
		g_aWall[nCnt].bUse = false;										//使用しているかしていないか
		g_aWall[nCnt].size = 0.0f;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-WALL_SIZE, 0.0f, +WALL_SIZE);
		pVtx[1].pos = D3DXVECTOR3(+WALL_SIZE, 0.0f, +WALL_SIZE);
		pVtx[2].pos = D3DXVECTOR3(-WALL_SIZE, 0.0f, -WALL_SIZE);
		pVtx[3].pos = D3DXVECTOR3(+WALL_SIZE, 0.0f, -WALL_SIZE);

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
	g_pVtxBuffWall->Unlock();
}

//=========================================
//壁の破棄
//=========================================
void UninitWall(void)
{
	//メッシュの破棄
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//マテリアルの破棄
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//=========================================
//壁の更新処理
//=========================================
void UpdateWall(void)
{

}

//=========================================
//壁の描画処理
//=========================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureWall);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (g_aWall[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aWall[nCnt].mtxWall);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aWall[nCnt].rot.y, g_aWall[nCnt].rot.x, g_aWall[nCnt].rot.z);

			D3DXMatrixMultiply(&g_aWall[nCnt].mtxWall, &g_aWall[nCnt].mtxWall, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCnt].pos.x, g_aWall[nCnt].pos.y, g_aWall[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCnt].mtxWall, &g_aWall[nCnt].mtxWall, &mtxTrans);

			//ワールドマトリックスを更新
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCnt].mtxWall);

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
}

//=========================================
//壁の情報の取得
//=========================================
Wall* GetWall()
{
	return g_aWall;
}

//=========================================
//壁の設置処理
//=========================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot , D3DXCOLOR col)
{
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	int nCntWall;

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{
			g_aWall[nCntWall].pos = pos;
			g_aWall[nCntWall].rot = rot;
			g_aWall[nCntWall].col = col;
			g_aWall[nCntWall].bUse = true;

			pVtx[0].col = g_aWall[nCntWall].col;
			pVtx[1].col = g_aWall[nCntWall].col;
			pVtx[2].col = g_aWall[nCntWall].col;
			pVtx[3].col = g_aWall[nCntWall].col;

			break;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();
}