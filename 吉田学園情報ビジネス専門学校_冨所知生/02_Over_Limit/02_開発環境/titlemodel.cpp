//=========================================
//
//	モデルの入出力処理
//	Author : 冨所知生
//
//=========================================
#include "main.h"
#include "titlemodel.h"

//グローバル変数宣言
TITLEMODEL g_aTitleModel[MAX_TITLEMODEL];
static int s_nIdxShadow;							//影の判別
static int s_nIdxTitleModel;
static int s_TitleModelDistance;							//プレイヤーとモデルの距離
static int s_mathWidth;
static int s_mathHeight;
static int s_mathMIN = 1000000;
static int s_mathBox;
static int s_Submission;							//提出するとことの距離
static int s_nCount;
//=====================================================
//モデルの初期化
//=====================================================
void InitTitleModel(void)
{
	for (int nCntTitleModel = 0; nCntTitleModel < MAX_TITLEMODEL; nCntTitleModel++)
	{
		g_aTitleModel[nCntTitleModel].bUse = false;										//使用していない
		g_aTitleModel[nCntTitleModel].cook = false;
		g_aTitleModel[nCntTitleModel].bIsLanding = false;
		g_aTitleModel[nCntTitleModel].nNumMatTitleModel = 0;									//マテリアルの数の初期化
		g_aTitleModel[nCntTitleModel].CookCount = 0;
		g_aTitleModel[nCntTitleModel].Type = 0;
		g_aTitleModel[nCntTitleModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//位置の初期設定
		g_aTitleModel[nCntTitleModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向きの初期設定
		g_aTitleModel[nCntTitleModel].rotDestTitleModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//目的の向きの初期設定
		g_aTitleModel[nCntTitleModel].vtxMaxTitleModel = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
		g_aTitleModel[nCntTitleModel].vtxMaxTitleModel = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	}
	s_nIdxTitleModel = 0;
	s_nIdxShadow = 0;
	s_mathWidth = 0;
	s_mathHeight = 0;
	s_mathMIN = 1000000;
	s_mathBox = 0;
	s_TitleModelDistance = 0;
}

//=========================================
//モデルの破棄
//=========================================
void UninitTitleModel(void)
{
	for (int nCntTitleModel = 0; nCntTitleModel < MAX_TITLEMODEL; nCntTitleModel++)
	{
		for (int i = 0; i < (int)g_aTitleModel[nCntTitleModel].nNumMatTitleModel; i++)
		{
			if (g_aTitleModel[nCntTitleModel].pTexture[i] != NULL)
			{// テクスチャの解放
				g_aTitleModel[nCntTitleModel].pTexture[i]->Release();
				g_aTitleModel[nCntTitleModel].pTexture[i] = NULL;
			}
		}
		//メッシュの破棄
		if (g_aTitleModel[nCntTitleModel].pMeshTitleModel != NULL)
		{
			g_aTitleModel[nCntTitleModel].pMeshTitleModel->Release();
			g_aTitleModel[nCntTitleModel].pMeshTitleModel = NULL;
		}
		//マテリアルの破棄
		if (g_aTitleModel[nCntTitleModel].pBuffMatTitleModel != NULL)
		{
			g_aTitleModel[nCntTitleModel].pBuffMatTitleModel->Release();
			g_aTitleModel[nCntTitleModel].pBuffMatTitleModel = NULL;
		}
	}
}

//=========================================
//モデルの更新処理
//=========================================
void UpdateTitleModel(void)
{
	//空を動かす
	g_aTitleModel[1].rot.y += 0.003f;
}
//=========================================
//モデルの描画処理
//=========================================
void DrawTitleModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL* pMat;				//マテリアルデータへのポインタ

	for (int nCntTitleModel = 0; nCntTitleModel < MAX_TITLEMODEL; nCntTitleModel++)
	{
		if (g_aTitleModel[nCntTitleModel].bUse)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aTitleModel[nCntTitleModel].mtxWorldTitleModel);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aTitleModel[nCntTitleModel].rot.y, g_aTitleModel[nCntTitleModel].rot.x, g_aTitleModel[nCntTitleModel].rot.z);

			D3DXMatrixMultiply(&g_aTitleModel[nCntTitleModel].mtxWorldTitleModel, &g_aTitleModel[nCntTitleModel].mtxWorldTitleModel, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aTitleModel[nCntTitleModel].pos.x, g_aTitleModel[nCntTitleModel].pos.y, g_aTitleModel[nCntTitleModel].pos.z);
			D3DXMatrixMultiply(&g_aTitleModel[nCntTitleModel].mtxWorldTitleModel, &g_aTitleModel[nCntTitleModel].mtxWorldTitleModel, &mtxTrans);

			//ワールドマトリックスを更新
			pDevice->SetTransform(D3DTS_WORLD, &g_aTitleModel[nCntTitleModel].mtxWorldTitleModel);

			//現在のマテリアルを保持(退避)
			pDevice->GetMaterial(&matDef);

			//マテリアルデータのポインタを取得する
			pMat = (D3DXMATERIAL*)g_aTitleModel[nCntTitleModel].pBuffMatTitleModel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aTitleModel[nCntTitleModel].nNumMatTitleModel; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, g_aTitleModel[nCntTitleModel].pTexture[nCntMat]);

				//モデルパーツの描画
				g_aTitleModel[nCntTitleModel].pMeshTitleModel->DrawSubset(nCntMat);
			}
			//保持していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}
//=========================================
//モデルの情報の取得
//=========================================
TITLEMODEL* GetTitleModel()
{
	return &g_aTitleModel[0];
}

//=========================================
//モデルの設置
//=========================================
void SetTitleModel(D3DXVECTOR3 pos, char TITLEMODEL_NAME[128], int nCnt, int nType)
{
	if (g_aTitleModel[nCnt].bUse == false)
	{
		g_aTitleModel[nCnt].pos = pos;
		g_aTitleModel[nCnt].bUse = true;
		g_aTitleModel[nCnt].Type = nType;

		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//Xファイルの読み込み
		D3DXLoadMeshFromX(TITLEMODEL_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aTitleModel[nCnt].pBuffMatTitleModel,
			NULL,
			&g_aTitleModel[nCnt].nNumMatTitleModel,
			&g_aTitleModel[nCnt].pMeshTitleModel);

		// バッファの先頭ポインタをD3DXMATERIALにキャストして取得
		D3DXMATERIAL *pMat = (D3DXMATERIAL*)g_aTitleModel[nCnt].pBuffMatTitleModel->GetBufferPointer();

		// 各メッシュのマテリアル情報を取得する
		for (int i = 0; i < (int)g_aTitleModel[nCnt].nNumMatTitleModel; i++)
		{
			g_aTitleModel[nCnt].pTexture[i] = NULL;

			if (pMat[i].pTextureFilename != NULL)
			{// マテリアルで設定されているテクスチャ読み込み
				D3DXCreateTextureFromFileA(pDevice,
					pMat[i].pTextureFilename,
					&g_aTitleModel[nCnt].pTexture[i]);
			}
		}

		int nNumVtx;			//頂点数
		DWORD sizeFVF;			//頂点フォーマットのサイズ
		BYTE *pVtxBuff;			//頂点バッファへのポインタ

		//頂点数の取得
		nNumVtx = g_aTitleModel[nCnt].pMeshTitleModel->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_aTitleModel[nCnt].pMeshTitleModel->GetFVF());

		//頂点バッファのロック
		g_aTitleModel[nCnt].pMeshTitleModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)& pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標を取得
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//頂点座標を比較してモデルの最小値/最大値を取得
			g_aTitleModel[nCnt].vtxMaxTitleModel.x = VertexMAXChange(vtx.x, g_aTitleModel[nCnt].vtxMaxTitleModel.x);
			g_aTitleModel[nCnt].vtxMaxTitleModel.y = VertexMAXChange(vtx.y, g_aTitleModel[nCnt].vtxMaxTitleModel.y);
			g_aTitleModel[nCnt].vtxMaxTitleModel.z = VertexMAXChange(vtx.z, g_aTitleModel[nCnt].vtxMaxTitleModel.z);

			g_aTitleModel[nCnt].vtxMinTitleModel.x = VertexMINChange(vtx.x, g_aTitleModel[nCnt].vtxMinTitleModel.x);
			g_aTitleModel[nCnt].vtxMinTitleModel.y = VertexMINChange(vtx.y, g_aTitleModel[nCnt].vtxMinTitleModel.y);
			g_aTitleModel[nCnt].vtxMinTitleModel.z = VertexMINChange(vtx.z, g_aTitleModel[nCnt].vtxMinTitleModel.z);

			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}
		//頂点バッファのアンロック
		g_aTitleModel[nCnt].pMeshTitleModel->UnlockVertexBuffer();
	}
}