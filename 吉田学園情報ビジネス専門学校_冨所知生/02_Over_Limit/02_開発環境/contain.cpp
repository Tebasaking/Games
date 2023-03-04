//=========================================
//
//	容器の入出力処理
//	Author : 冨所知生
//
//=========================================
#include <stdio.h>
#include "main.h"
#include "contain.h"
#include "input.h"
#include "polygon.h"
#include "camera.h"
#include "shadow.h"
#include "wall.h"
#include "player.h"
#include "meshfield.h"
#include "particle.h"
#include "line.h"
#include "model.h"
#include "objectline.h"
#include "order.h"
#include "score.h"
#include "sound.h"

//グローバル変数宣言
CONTAIN g_aContain[MAX_CONTAIN];
FOOD_COUNT g_aFoodCount;							//食べ物を何個入れたかのカウント
static int s_nIdxShadow;							//影の判別
static int SelectModel;								//一番近くにあるブロックが何番目か
static int SelectContain;							//何番目の容器を持っているか

//一番近くの容器を判定するのに必要な数値一式
static float s_mathWidth;
static float s_mathHeight;
static int s_mathMIN;
static int s_mathBox;
static int State;

//汚れた皿をカウントする
static int s_ConutDContain;
//出現させる容器のファイル名を代入する
static char filename[255];
//=====================================================
//容器の初期化
//=====================================================
void InitContain(void)
{
	for (int nCntContain = 0; nCntContain < MAX_CONTAIN; nCntContain++)
	{
		// カットタイマーの情報の初期化
		memset(&g_aContain[nCntContain], 0, sizeof(g_aContain[nCntContain]));

		g_aContain[nCntContain].vtxMaxContain = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
		g_aContain[nCntContain].vtxMaxContain = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	}

	//食べ物が何個取得されたかのカウント
	memset(&g_aFoodCount, 0, sizeof(g_aFoodCount));

	s_ConutDContain = 0;
	SelectContain = 0;
	s_mathWidth = 0;
	s_mathHeight = 0;
	s_mathMIN = 1000000;
	s_mathBox = 0;
	SelectModel = 0;
}

//=========================================
//容器の破棄
//=========================================
void UninitContain(void)
{
	for (int nCntContain = 0; nCntContain < MAX_CONTAIN; nCntContain++)
	{
		//メッシュの破棄
		if (g_aContain[nCntContain].pMeshContain != NULL)
		{
			g_aContain[nCntContain].pMeshContain->Release();
			g_aContain[nCntContain].pMeshContain = NULL;
		}

		//マテリアルの破棄
		if (g_aContain[nCntContain].pBuffMatContain != NULL)
		{
			g_aContain[nCntContain].pBuffMatContain->Release();
			g_aContain[nCntContain].pBuffMatContain = NULL;
		}
	}
}

//=========================================
//容器の更新処理
//=========================================
void UpdateContain(void)
{
	PLAYER *pPlayer = GetPlayer();
	MODEL *pModel = GetModel();
	ORDER *pOrder = GetOrder();

	SelectModel = GetSelectObject();
	pModel += SelectModel;

	int ModelDistance = GetObjectDistance();

	//プレイヤーと容器の距離を測る
	PlayerDistanceContain();

	if (ModelDistance <= 10)
	{
		if (pPlayer->state == PLAYER_NORMAL)
		{
			if ((GetKeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_B, 0)))
			{//スペースを押したとき
				if (pModel->Type == 2 && s_ConutDContain < MAX_CONTAIN)
				{//モデルのタイプが2(皿が出る場所)だった場合
					SetContain(D3DXVECTOR3(pModel->pos.x, pModel->pos.y + DISH_SIZE, pModel->pos.z),
						"data/MODEL/Object/Contain/dish.x", CONTAIN_HAVE);
					//現在場に出ている皿の数を加算する
					s_ConutDContain++;

					//プレイヤーを持っている状態にする
					pPlayer->state = PLAYER_HAVE;
				}
			}
		}

		if (s_mathMIN <= 10)
		{
			if ((GetKeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_B, 0)) &&
				pPlayer->state == PLAYER_NORMAL && g_aContain[SelectContain].state == CONTAIN_NORMAL && pModel->bIsLanding)
			{//ブロックの上から容器を回収する処理
				if (g_aContain[SelectContain].bUse)
				{
					PlaySound(SOUND_LABEL_OPEN);
					pPlayer->state = PLAYER_HAVE;
					g_aContain[SelectContain].state = CONTAIN_HAVE;
					pModel->bIsLanding = false;
				}
			}
			else if ((GetKeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_B, 0)) &&
				pPlayer->state == PLAYER_HAVE && g_aContain[SelectContain].state == CONTAIN_HAVE && !pModel->bIsLanding)
			{//ブロックの上に容器を設置する処理
				if (pModel->Type == 3)
				{//カウンター(3)に提出する。
					int NumberCount;
					bool ForCheck = false;
					UninitCalculation();

					for (NumberCount = 0; NumberCount < NUM_ORDER + 1; NumberCount++)
					{
						for (int nCntOrder = 0; nCntOrder < NUM_ORDER; nCntOrder++)
						{//オーダーのnType(注文内容)とできた料理が同じだった時
							if (pOrder->bUse)
							{//有効なオーダーのみ通す
								if (pOrder->nType == (ITEMTYPE)g_aContain[SelectContain].food && pOrder->nNumber == NumberCount)
								{//オーダーをfalseにして、スコアを加算する
									pOrder->bUse = false;
									//オーダーを動かす
									MoveOrder(pOrder->nNumber);
									//オーダーの個数を一個減らす
									SubOrderCount();
									//オーダーと注文内容を比較するfor文が通った場合trueにする
									ForCheck = true;
									//容器をfalseにする
									g_aContain[SelectContain].bUse = false;
									//皿の数をデクリメントする
									s_ConutDContain--;
									//プレイヤーの状態を何も持っていない状態に
									pPlayer->state = PLAYER_NORMAL;
									//できた料理の初期化
									g_aContain[SelectContain].food = 0;

									if (pOrder->nType == 1)
									{
										g_aFoodCount.meat++;
										//スコアの加算
										AddScore(10);
									}
									else if (pOrder->nType == 2)
									{
										g_aFoodCount.cabbage++;
										//スコアの加算
										AddScore(10);
									}
									else if (pOrder->nType == 3)
									{
										g_aFoodCount.vegetable++;
										//スコアの加算
										AddScore(30);
									}
									PlaySound(SOUND_LABEL_REGI);
									break;
								}
							}
							//オーダーの内容を全て確認するためにポインターを進める
							pOrder += 1;
						}
						//オーダーのポインターを初期化する
						pOrder = GetOrder();

						if (ForCheck)
						{//trueの時、二重ループを破棄するためにbreakする。
							ForCheck = false;
							break;
						}
					}
					//番号をカウントする数値を初期化する
					NumberCount = 0;
				}
				else if (pModel->Type == 2)
				{
					//何もしない
				}
				else
				{
					pPlayer->state = PLAYER_NORMAL;
					g_aContain[SelectContain].state = CONTAIN_NORMAL;
					g_aContain[SelectContain].pos = D3DXVECTOR3(pModel->pos.x, pModel->pos.y + 10.0f, pModel->pos.z);
					pModel->bIsLanding = true;
				}
				PlaySound(SOUND_LABEL_OPEN);
			}
		}

		for (int nCnt = 0; nCnt < MAX_CONTAIN; nCnt++)
		{
			if (g_aContain[nCnt].state == CONTAIN_HAVE)
			{//容器が持たれているとき
				if (pPlayer->state == PLAYER_HAVE)
				{
					g_aContain[nCnt].pos = D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 10.0f, pPlayer->pos.z);
				}
			}
		}
	}
}

//=========================================
//容器の描画処理
//=========================================
void DrawContain(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL* pMat;				//マテリアルデータへのポインタ
	//プレイヤーの情報を取得
	PLAYER *pPlayer = GetPlayer();

	for (int nCntContain = 0; nCntContain < MAX_CONTAIN; nCntContain++)
	{
		if (g_aContain[nCntContain].bUse)
		{
			if (g_aContain[nCntContain].state == CONTAIN_NORMAL)
			{
				//ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_aContain[nCntContain].mtxWorldContain);

				//向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot,
					g_aContain[nCntContain].rot.y, g_aContain[nCntContain].rot.x, g_aContain[nCntContain].rot.z);

				D3DXMatrixMultiply(&g_aContain[nCntContain].mtxWorldContain, &g_aContain[nCntContain].mtxWorldContain, &mtxRot);

				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_aContain[nCntContain].pos.x, g_aContain[nCntContain].pos.y, g_aContain[nCntContain].pos.z);
				D3DXMatrixMultiply(&g_aContain[nCntContain].mtxWorldContain, &g_aContain[nCntContain].mtxWorldContain, &mtxTrans);
			}
			else if (g_aContain[nCntContain].state == CONTAIN_HAVE)
			{//容器が持たれているとき
				if (pPlayer->state == PLAYER_HAVE)
				{//向きの反映
					D3DXMATRIX Kichen_have;

					D3DXMatrixIdentity(&Kichen_have);

					D3DXMatrixRotationYawPitchRoll(&mtxRot, D3DX_PI, 0.0f, 0.0f);

					D3DXMatrixMultiply(&Kichen_have, &Kichen_have, &mtxRot);

					//位置を反映
					D3DXMatrixTranslation(&mtxTrans, 0.0f, 5.0f, -5.0f);
					D3DXMatrixMultiply(&Kichen_have, &Kichen_have, &mtxTrans);

					D3DXMatrixMultiply(&g_aContain[nCntContain].mtxWorldContain, &Kichen_have, &pPlayer->mtxWorldPlayer);
				}
		}
			//ワールドマトリックスを更新
			pDevice->SetTransform(D3DTS_WORLD, &g_aContain[nCntContain].mtxWorldContain);

			//現在のマテリアルを保持(退避)
			pDevice->GetMaterial(&matDef);

			//マテリアルデータのポインタを取得する
			pMat = (D3DXMATERIAL*)g_aContain[nCntContain].pBuffMatContain->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aContain[nCntContain].nNumMatContain; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//容器パーツの描画
				g_aContain[nCntContain].pMeshContain->DrawSubset(nCntMat);
			}

			//保持していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=========================================
//容器の情報の取得
//=========================================
CONTAIN* GetContain()
{
	return g_aContain;
}

//=========================================
//どの容器が一番近いかの情報の取得
//=========================================
int GetSelectContain()
{
	return SelectContain;
}

//=========================================
//容器の設置
//=========================================
void SetContain(D3DXVECTOR3 pos, char CONTAIN_NAME[128], CONTAIN_STATE state)
{
	for (int nCntContain = 0; nCntContain < MAX_CONTAIN; nCntContain++)
	{
		if (g_aContain[nCntContain].bUse == false)
		{
			g_aContain[nCntContain].pos = pos;
			g_aContain[nCntContain].bUse = true;
			g_aContain[nCntContain].Shadow = SetShadow(g_aContain[nCntContain].pos, g_aContain[nCntContain].rot);		//影の設置処理
			g_aContain[nCntContain].state = state;

			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			//Xファイルの読み込み
			D3DXLoadMeshFromX(CONTAIN_NAME,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_aContain[nCntContain].pBuffMatContain,
				NULL,
				&g_aContain[nCntContain].nNumMatContain,
				&g_aContain[nCntContain].pMeshContain);

			int nNumVtx;			//頂点数
			DWORD sizeFVF;			//頂点フォーマットのサイズ
			BYTE *pVtxBuff;			//頂点バッファへのポインタ

			//頂点数の取得
			nNumVtx = g_aContain[nCntContain].pMeshContain->GetNumVertices();
			//頂点フォーマットのサイズを取得
			sizeFVF = D3DXGetFVFVertexSize(g_aContain[nCntContain].pMeshContain->GetFVF());

			//頂点バッファのロック
			g_aContain[nCntContain].pMeshContain->LockVertexBuffer(D3DLOCK_READONLY, (void**)& pVtxBuff);

			//頂点バッファのアンロック
			g_aContain[nCntContain].pMeshContain->UnlockVertexBuffer();

			break;
		}
	}
}

//=========================================
//容器の見た目の状態の変化
//=========================================
void TSContain(D3DXVECTOR3 pos, CONTAIN_STATE state, CONTAIN_COOKING cook, ITEMTYPE type)
{
	for (int nCntContain = 0; nCntContain < MAX_CONTAIN; nCntContain++)
	{
		if (g_aContain[nCntContain].bUse == false)
		{
			g_aContain[nCntContain].pos = pos;
			g_aContain[nCntContain].bUse = true;
			g_aContain[nCntContain].Shadow = SetShadow(g_aContain[nCntContain].pos, g_aContain[nCntContain].rot);		//影の設置処理
			Calculation(type);
			g_aContain[nCntContain].state = state;
			g_aContain[nCntContain].cook = cook;

			LPDIRECT3DDEVICE9 pDevice = GetDevice();
			
			//Xファイルの読み込み
			D3DXLoadMeshFromX(filename,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_aContain[nCntContain].pBuffMatContain,
				NULL,
				&g_aContain[nCntContain].nNumMatContain,
				&g_aContain[nCntContain].pMeshContain);

			int nNumVtx;			//頂点数
			DWORD sizeFVF;			//頂点フォーマットのサイズ
			BYTE *pVtxBuff;			//頂点バッファへのポインタ

									//頂点数の取得
			nNumVtx = g_aContain[nCntContain].pMeshContain->GetNumVertices();
			//頂点フォーマットのサイズを取得
			sizeFVF = D3DXGetFVFVertexSize(g_aContain[nCntContain].pMeshContain->GetFVF());

			//頂点バッファのロック
			g_aContain[nCntContain].pMeshContain->LockVertexBuffer(D3DLOCK_READONLY, (void**)& pVtxBuff);

			for (int nCntContainVtx = 0; nCntContainVtx < nNumVtx; nCntContainVtx++)
			{
				//頂点座標を取得
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				//頂点座標を比較して容器の最小値/最大値を取得
				g_aContain[nCntContain].vtxMaxContain.x = VertexMAXChange(vtx.x, g_aContain[nCntContain].vtxMaxContain.x);
				g_aContain[nCntContain].vtxMaxContain.y = VertexMAXChange(vtx.y, g_aContain[nCntContain].vtxMaxContain.y);
				g_aContain[nCntContain].vtxMaxContain.z = VertexMAXChange(vtx.z, g_aContain[nCntContain].vtxMaxContain.z);

				g_aContain[nCntContain].vtxMinContain.x = VertexMINChange(vtx.x, g_aContain[nCntContain].vtxMinContain.x);
				g_aContain[nCntContain].vtxMinContain.y = VertexMINChange(vtx.y, g_aContain[nCntContain].vtxMinContain.y);
				g_aContain[nCntContain].vtxMinContain.z = VertexMINChange(vtx.z, g_aContain[nCntContain].vtxMinContain.z);

				//頂点フォーマットのサイズ分ポインタを進める
				pVtxBuff += sizeFVF;
			}
			//頂点バッファのアンロック
			g_aContain[nCntContain].pMeshContain->UnlockVertexBuffer();

			break;
		}
	}
}
//=========================================
//容器の当たり判定の生成
//=========================================
void CollisionContain(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 size)
{
	for (int i = 0; i < MAX_CONTAIN; i++)
	{//横のめり込み判定
		if (pPos->z - size.z / 2.0f > g_aContain[i].pos.z + g_aContain[i].vtxMaxContain.z
			&& pPos->z + size.z / 2.0f < g_aContain[i].pos.z + g_aContain[i].vtxMinContain.z)
		{
			//左の当たり判定の設定
			if (pPosOld->x - size.z / 2.0f <= g_aContain[i].pos.x - g_aContain[i].vtxMinContain.x
				&& pPos->x - size.z / 2.0f > g_aContain[i].pos.x - g_aContain[i].vtxMinContain.x)
			{
				pPos->x = g_aContain[i].pos.x - g_aContain[i].vtxMinContain.x + size.z / 2.0f;
			}
			//右の当たり判定の設定
			if (pPosOld->x + size.z / 2.0f >= g_aContain[i].pos.x + g_aContain[i].vtxMinContain.x
				&& pPos->x + size.z / 2.0f < g_aContain[i].pos.x + g_aContain[i].vtxMinContain.x)
			{
				pPos->x = g_aContain[i].pos.x + g_aContain[i].vtxMinContain.x - size.z / 2.0f;
			}
		}

		//上下の当たり判定
		if (pPos->x - size.z / 2.0f > g_aContain[i].pos.x + g_aContain[i].vtxMaxContain.x
			&& pPos->x + size.z / 2.0f < g_aContain[i].pos.x + g_aContain[i].vtxMinContain.x)
		{
			//下の当たり判定の設定
			if (pPosOld->z - size.z / 2.0f <= g_aContain[i].pos.z - g_aContain[i].vtxMinContain.z
				&& pPos->z - size.z / 2.0f > g_aContain[i].pos.z - g_aContain[i].vtxMinContain.z)
			{
				pPos->z = g_aContain[i].pos.z - g_aContain[i].vtxMinContain.z + size.z / 2.0f - 0.1f;
			}

			//右の当たり判定の設定
			if (pPosOld->z + size.z / 2.0f >= g_aContain[i].pos.z + g_aContain[i].vtxMinContain.z
				&& pPos->z + size.z / 2.0f < g_aContain[i].pos.z + g_aContain[i].vtxMinContain.z)
			{
				pPos->z = g_aContain[i].pos.z + g_aContain[i].vtxMinContain.z - size.z / 2.0f + 0.1f;
			}
		}
	}
}

//=========================================
//一番近くの容器を判定する
//=========================================
void PlayerDistanceContain()
{
	PLAYER *pPlayer = GetPlayer();
	s_mathMIN = 1000000;

	for (int nCnt = 0; nCnt < MAX_CONTAIN; nCnt++)
	{
		if (g_aContain[nCnt].bUse == true)
		{
			s_mathWidth = pPlayer->pos.x - g_aContain[nCnt].pos.x;
			s_mathHeight = pPlayer->pos.z - g_aContain[nCnt].pos.z;

			s_mathBox = (int)sqrtf(s_mathWidth * s_mathWidth + s_mathHeight * s_mathHeight);

			if (s_mathBox <= s_mathMIN)
			{
				s_mathMIN = s_mathBox;
				SelectContain = nCnt;
			}
		}
	}

	if (s_mathMIN <= 10)
	{
		SetObjectLine(g_aContain[SelectContain].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aContain[SelectContain].vtxMaxContain, D3DXVECTOR3(g_aContain[SelectContain].vtxMinContain.x, g_aContain[SelectContain].vtxMaxContain.y, g_aContain[SelectContain].vtxMaxContain.z));
		SetObjectLine(g_aContain[SelectContain].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aContain[SelectContain].vtxMaxContain, D3DXVECTOR3(g_aContain[SelectContain].vtxMaxContain.x, g_aContain[SelectContain].vtxMaxContain.y, g_aContain[SelectContain].vtxMinContain.z));
		SetObjectLine(g_aContain[SelectContain].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aContain[SelectContain].vtxMinContain.x, g_aContain[SelectContain].vtxMaxContain.y, g_aContain[SelectContain].vtxMinContain.z), D3DXVECTOR3(g_aContain[SelectContain].vtxMaxContain.x, g_aContain[SelectContain].vtxMaxContain.y, g_aContain[SelectContain].vtxMinContain.z));
		SetObjectLine(g_aContain[SelectContain].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aContain[SelectContain].vtxMinContain.x, g_aContain[SelectContain].vtxMaxContain.y, g_aContain[SelectContain].vtxMinContain.z), D3DXVECTOR3(g_aContain[SelectContain].vtxMinContain.x, g_aContain[SelectContain].vtxMaxContain.y, g_aContain[SelectContain].vtxMaxContain.z));

		SetObjectLine(g_aContain[SelectContain].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aContain[SelectContain].vtxMinContain, D3DXVECTOR3(g_aContain[SelectContain].vtxMaxContain.x, g_aContain[SelectContain].vtxMinContain.y, g_aContain[SelectContain].vtxMinContain.z));
		SetObjectLine(g_aContain[SelectContain].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aContain[SelectContain].vtxMinContain, D3DXVECTOR3(g_aContain[SelectContain].vtxMinContain.x, g_aContain[SelectContain].vtxMinContain.y, g_aContain[SelectContain].vtxMaxContain.z));
		SetObjectLine(g_aContain[SelectContain].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aContain[SelectContain].vtxMaxContain.x, g_aContain[SelectContain].vtxMinContain.y, g_aContain[SelectContain].vtxMaxContain.z), D3DXVECTOR3(g_aContain[SelectContain].vtxMaxContain.x, g_aContain[SelectContain].vtxMinContain.y, g_aContain[SelectContain].vtxMinContain.z));
		SetObjectLine(g_aContain[SelectContain].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aContain[SelectContain].vtxMaxContain.x, g_aContain[SelectContain].vtxMinContain.y, g_aContain[SelectContain].vtxMaxContain.z), D3DXVECTOR3(g_aContain[SelectContain].vtxMinContain.x, g_aContain[SelectContain].vtxMinContain.y, g_aContain[SelectContain].vtxMaxContain.z));

		SetObjectLine(g_aContain[SelectContain].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aContain[SelectContain].vtxMaxContain.x, g_aContain[SelectContain].vtxMaxContain.y, g_aContain[SelectContain].vtxMinContain.z), D3DXVECTOR3(g_aContain[SelectContain].vtxMaxContain.x, g_aContain[SelectContain].vtxMinContain.y, g_aContain[SelectContain].vtxMinContain.z));
		SetObjectLine(g_aContain[SelectContain].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aContain[SelectContain].vtxMinContain.x, g_aContain[SelectContain].vtxMaxContain.y, g_aContain[SelectContain].vtxMaxContain.z), D3DXVECTOR3(g_aContain[SelectContain].vtxMinContain.x, g_aContain[SelectContain].vtxMinContain.y, g_aContain[SelectContain].vtxMaxContain.z));
		SetObjectLine(g_aContain[SelectContain].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aContain[SelectContain].vtxMaxContain, D3DXVECTOR3(g_aContain[SelectContain].vtxMaxContain.x, g_aContain[SelectContain].vtxMinContain.y, g_aContain[SelectContain].vtxMaxContain.z));
		SetObjectLine(g_aContain[SelectContain].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aContain[SelectContain].vtxMinContain, D3DXVECTOR3(g_aContain[SelectContain].vtxMinContain.x, g_aContain[SelectContain].vtxMaxContain.y, g_aContain[SelectContain].vtxMinContain.z));
	}
}
//=========================================
//容器とプレイヤーの距離の取得
//=========================================
int GetContainDistance()
{
	return s_mathMIN;
}
//=========================================
//bit演算の計算
//=========================================
void Calculation(ITEMTYPE item)
{
	//プレイヤーと容器の距離を測る
	PlayerDistanceContain();

	//Item番号の加算
	g_aContain[SelectContain].food |= item;

	if (UseFood(ITEM_CABBAGE, g_aContain[SelectContain].food)
		&& UseFood(ITEM_MEAT, g_aContain[SelectContain].food))
	{
		sprintf(filename, "data/MODEL/FOOD/complete_1.x");
	}
	else if (UseFood(item , g_aContain[SelectContain].food))
	{
		sprintf(filename,"data/MODEL/Object/Contain/food_%d.x", item);
	}
}

//=========================================
//容器に何が加えられているか判定する処理
//=========================================
bool UseFood(ITEMTYPE type, unsigned int dish)
{
	return (type & dish) != 0;
}
//=========================================
//フラグの無効処理
//=========================================
void UninitCalculation()
{
	//すべてのフラグを無効にする
	State = 0;
}

//=========================================
//どの食べ物を入れたかカウントした数値を取得する
//=========================================
FOOD_COUNT* GetFoodCount()
{
	return &g_aFoodCount;
}