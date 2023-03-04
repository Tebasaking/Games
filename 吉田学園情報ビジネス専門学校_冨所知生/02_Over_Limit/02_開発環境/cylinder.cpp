//=========================================
//
//	円柱の入出力処理
//	Author : 冨所知生
//
//=========================================
#include "main.h"
#include "cylinder.h"
#include "wall.h"
#include "model.h"

//================================================================
//グローバル変数宣言
//================================================================
LPDIRECT3DTEXTURE9 g_pTextureCylinderField = NULL;				//円柱のテクスチャ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCylinderField = NULL;			//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9  g_pIdxBuffCylinderField = NULL;			//インデックスバッファへのポインタ
D3DXVECTOR3 g_posCylinderField;									//位置
D3DXVECTOR3 g_rotCylinderField;									//向き
D3DXMATRIX g_mtxWorldCylinder;									//ワールドマトリックス

#define CYLINDER_X_BLOCK (8)
#define CYLINDER_Z_BLOCK (2)
#define CYLINDER_SIZE (10.0f)

#define CYLINDER_VERTEX_NUM ((CYLINDER_X_BLOCK + 1) * (CYLINDER_Z_BLOCK + 1))
#define CYLINDER_INDEX_NUM  (((CYLINDER_X_BLOCK + 1) * 2) * ( CYLINDER_Z_BLOCK  *(CYLINDER_Z_BLOCK - 1)) * CYLINDER_Z_BLOCK * 2)
#define CYLINDER_PRIMITIVE_NUM (CYLINDER_X_BLOCK * CYLINDER_Z_BLOCK * 2 + 4 * (CYLINDER_Z_BLOCK  - 1))

int cLineVtx = (CYLINDER_X_BLOCK + 1);
int fRadius = 10;
//================================================================
//円柱の初期化
//================================================================
void InitCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * CYLINDER_VERTEX_NUM,		//確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,										//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffCylinderField,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * CYLINDER_INDEX_NUM,			//確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,										//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pIdxBuffCylinderField,
		NULL);

	VERTEX_3D* pVtx = NULL;			//頂点情報の取得

									//頂点バッファをロック
	g_pVtxBuffCylinderField->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ <= CYLINDER_Z_BLOCK; nCntZ++)
	{
		for (int nCntX = 0; nCntX <= CYLINDER_X_BLOCK; nCntX++)
		{
			//頂点座標の設定（ワールド座標ではなくローカル座標を指定する）
			pVtx[nCntX + (CYLINDER_X_BLOCK + 1) * nCntZ].pos = D3DXVECTOR3
			(sinf(nCntX * ((D3DX_PI * 2.0f) / CYLINDER_X_BLOCK)) * fRadius,				//x
			0.0f + (nCntZ * 10.0f),														//y
			cosf(nCntX  * ((D3DX_PI * 2.0f) / CYLINDER_X_BLOCK)) * fRadius);			//z

			//各頂点の法線の設定
			pVtx[nCntX + (CYLINDER_X_BLOCK + 1) * nCntZ].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//法線の正規化
			D3DXVec3Normalize(&pVtx[nCntX + (CYLINDER_X_BLOCK + 1) * nCntZ].nor, &pVtx[nCntX + (CYLINDER_X_BLOCK + 1) * nCntZ].nor);

			//頂点カラーの設定
			pVtx[nCntX + (CYLINDER_X_BLOCK + 1) * nCntZ].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	//頂点バッファをアンロック
	g_pVtxBuffCylinderField->Unlock();

	//インデックスバッファをロック
	WORD* pIdx;
	g_pIdxBuffCylinderField->Lock(0, 0, (void**)&pIdx, 0);

	//縦の頂点の数
	for (int nCntZ = 0; nCntZ < CYLINDER_Z_BLOCK; nCntZ++)
	{
		//インデックス
		int nLineTop = nCntZ * (cLineVtx * 2 + 2);

		//横の頂点の数
		for (int nCntX = 0; nCntX < cLineVtx; nCntX++)
		{//上の段の処理
			pIdx[(nCntX * 2 + 1) + nLineTop] = (WORD)(nCntX + cLineVtx * nCntZ);

			//下の段の処理
			pIdx[nCntX * 2 + nLineTop] = (WORD)(pIdx[(nCntX * 2 + 1) + nLineTop] + cLineVtx);
		}

		//縮退ポリゴンを前後と同一にする処理
		if (nCntZ < CYLINDER_Z_BLOCK)
		{
			pIdx[(cLineVtx * 2) + nLineTop] = (WORD)(CYLINDER_X_BLOCK + (cLineVtx)* nCntZ);
			pIdx[(cLineVtx * 2) + nLineTop + 1] = (WORD)(2 * (cLineVtx)+(cLineVtx)* nCntZ);
		}
	}
	//インデックスバッファのアンロック
	g_pIdxBuffCylinderField->Unlock();
}
//================================================================
//円柱の破棄
//================================================================
void UninitCylinder(void)
{
	//インデックスバッファの解放
	if (g_pIdxBuffCylinderField != NULL)
	{
		g_pIdxBuffCylinderField->Release();
		g_pIdxBuffCylinderField = NULL;
	}

	//頂点バッファの解放
	if (g_pVtxBuffCylinderField != NULL)
	{
		g_pVtxBuffCylinderField->Release();
		g_pVtxBuffCylinderField = NULL;
	}
}
//================================================================
//円柱の更新
//================================================================
void UpdateCylinder(void)
{
}

//================================================================
//円柱の描画
//================================================================
void DrawCylinder(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

									//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldCylinder);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_rotCylinderField.y, g_rotCylinderField.x, g_rotCylinderField.z);

	D3DXMatrixMultiply(&g_mtxWorldCylinder, &g_mtxWorldCylinder, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posCylinderField.x, g_posCylinderField.y, g_posCylinderField.z);
	D3DXMatrixMultiply(&g_mtxWorldCylinder, &g_mtxWorldCylinder, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldCylinder);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffCylinderField, 0, sizeof(VERTEX_3D));

	//インデックスバッファのデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffCylinderField);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// 円柱の描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, CYLINDER_VERTEX_NUM, 0, CYLINDER_PRIMITIVE_NUM);
}