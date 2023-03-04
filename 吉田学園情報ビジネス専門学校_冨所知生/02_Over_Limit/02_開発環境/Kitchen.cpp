//=========================================
//
//	キッチンの入出力処理
//	Author : 冨所知生
//
//=========================================
#include <stdio.h>
#include "main.h"
#include "player.h"
#include "input.h"
#include "polygon.h"
#include "camera.h"
#include "shadow.h"
#include "model.h"
#include "wall.h"
#include "meshfield.h"
#include "particle.h"
#include "line.h"
#include "kitchen.h"
#include "objectline.h"
#include "contain.h"
#include "kitchentimer.h"
#include "sound.h"

//グローバル変数宣言
KITCHEN g_aKitchen[MAX_KITCHEN];
static int s_nIdxShadow;							//影の判別
static int nCntNumKeySet = 0;						//現在再生中のKeySet番号
static int g_nCntFrame = 0;							//フレーム数
static int s_mathMIN;								//最小数
static int SelectKitchen = 0;						//近いキッチンの番号
//=====================================================
//キッチンの初期化
//=====================================================
void InitKitchen(void)
{
	for (int nCntKitchen = 0; nCntKitchen < MAX_KITCHEN; nCntKitchen++)
	{
		// キッチンの情報の初期化
		memset(&g_aKitchen[nCntKitchen], 0, sizeof(g_aKitchen[nCntKitchen]));

		g_aKitchen[nCntKitchen].state = KITCHEN_NORMAL;										//キッチンの状態の初期化
		g_aKitchen[nCntKitchen].cook = KITCHEN_NONE;

		for (int nCntParts = 0; nCntParts < MAX_KITCHEN_PARTS; nCntParts++)
		{
			g_aKitchen[nCntKitchen].aParts[nCntParts].bUse = false;
			g_aKitchen[nCntKitchen].aParts[nCntParts].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aKitchen[nCntKitchen].aParts[nCntParts].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aKitchen[nCntKitchen].aParts[nCntParts].nIdxModelParent = 0;
			g_aKitchen[nCntKitchen].aParts[nCntParts].fFrame = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//アニメーションのフレーム数の初期化
		}
	}
}

//=========================================
//キッチンの破棄
//=========================================
void UninitKitchen(void)
{
	for (int nCntKitchen = 0; nCntKitchen < MAX_KITCHEN; nCntKitchen++)
	{
		//メッシュの破棄
		if (g_aKitchen[nCntKitchen].pMeshKitchen != NULL)
		{
			g_aKitchen[nCntKitchen].pMeshKitchen->Release();
			g_aKitchen[nCntKitchen].pMeshKitchen = NULL;
		}

		//マテリアルの破棄
		if (g_aKitchen[nCntKitchen].pBuffMatKitchen != NULL)
		{
			g_aKitchen[nCntKitchen].pBuffMatKitchen->Release();
			g_aKitchen[nCntKitchen].pBuffMatKitchen = NULL;
		}

		for (int nCntParts = 0; nCntParts < MAX_KITCHEN_PARTS; nCntParts++)
		{
			//メッシュの破棄
			if (g_aKitchen[nCntKitchen].aParts[nCntParts].pMesh != NULL)
			{
				g_aKitchen[nCntKitchen].aParts[nCntParts].pMesh->Release();
				g_aKitchen[nCntKitchen].aParts[nCntParts].pMesh = NULL;
			}

			//マテリアルの破棄
			if (g_aKitchen[nCntKitchen].aParts[nCntParts].pBuffMat != NULL)
			{
				g_aKitchen[nCntKitchen].aParts[nCntParts].pBuffMat->Release();
				g_aKitchen[nCntKitchen].aParts[nCntParts].pBuffMat = NULL;
			}
		}
	}
}

//=========================================
//キッチンの更新処理
//=========================================
void UpdateKitchen(void)
{
	//プレイヤーの情報を取得する
	PLAYER *pPlayer = GetPlayer();
	//モデルの情報を取得する
	MODEL *pModel = GetModel();
	//容器の情報を取得する
	CONTAIN *pContain = GetContain();
	//キッチンタイマーの情報を取得する
	KTIMER *pKTimer = GetKTimer();
	//モデルとプレイヤーの距離
	int ModelDistance = GetObjectDistance();
	//容器とプレイヤーの距離
	int ContainDistance = GetContainDistance();

	//最も近いモデルと容器の番号
	int SelectModel = GetSelectObject();
	int SelectContain = GetSelectContain();

	//ポインターを最も近いものに加算する
	pModel += SelectModel;
	pContain += SelectContain;

	//キッチンとキッチンの距離を測る
	PlayerDistanceKitchen();

	//キッチンで調理する処理
	LetsCooking();

	if (s_mathMIN <= 10)
	{
		if (ModelDistance <= 10)
		{
			if (((GetKeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_B, 0))) &&
				pPlayer->state == PLAYER_NORMAL && g_aKitchen[SelectKitchen].state == KITCHEN_NORMAL && pModel->bIsLanding == true)
			{//ブロックの上から調理道具を回収する処理
				if (g_aKitchen[SelectKitchen].bUse)
				{
					pPlayer->state = PLAYER_HAVE;											//プレイヤーを持っている状態にする
					g_aKitchen[SelectKitchen].state = KITCHEN_HAVE;							//調理器具を持たれている状態にする
					pModel->bIsLanding = false;												//モデルの上に何もない状態にする

					//一番近いモデルが調理道具(1)なら
					if (pModel->Type == 1)
					{
						if (g_aKitchen[SelectKitchen].cook == KITCHEN_COOK)
						{//調理中だった場合
							g_aKitchen[SelectKitchen].cook = KITCHEN_MATERIAL;				//調理器具の状態を中に素材がある状態にする
							pModel->cook = false;
							StopSound(SOUND_LABEL_HOT);
							PlaySound(SOUND_LABEL_OPEN);
						}
						if (g_aKitchen[SelectKitchen].cook == KITCHEN_OVER)
						{//完成したあとだった場合
							g_aKitchen[SelectKitchen].cook = KITCHEN_COMPLETE;				//調理器具の状態を完成した状態にする
							StopSound(SOUND_LABEL_HOTOVER);
							PlaySound(SOUND_LABEL_OPEN);
							pModel->cook = false;
						}
						for (int nCnt = 0; nCnt < MAX_KITCHENTIMER; nCnt++)
						{
							pKTimer->bUse = false;											//キッチンタイマーを使用していない状態にする
							pKTimer++;
						}
						pKTimer = GetKTimer();

						g_aKitchen[SelectKitchen].bTimer = false;							//タイマーを使われてない状態にする
					}
				}
			}
			else if ((GetKeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_B, 0)) 
				&& pPlayer->state == PLAYER_HAVE && g_aKitchen[SelectKitchen].state == KITCHEN_HAVE && pModel->Type != 5)
			{//ブロックの上に調理道具を設置する処理
				if (ContainDistance <= 10)
				{//容器の近くに調理道具があった場合
					//調理道具が完成した状態だった場合
					if (g_aKitchen[SelectKitchen].cook == KITCHEN_COMPLETE)
					{//皿に盛り付ける
						g_aKitchen[SelectKitchen].CookCount = 0;							//調理時間のカウントを0にする

						if (pContain->food != g_aKitchen[SelectKitchen].type)
						{
							pContain->bUse = false;
							//ファイル名をtypeから入力させる
							g_aKitchen[SelectKitchen].cook = KITCHEN_NONE;						//調理していない状態にする
							g_aKitchen[SelectKitchen].aParts[2].bUse = false;					//調理器具の中で焼かれているものをfalseにする
							PlaySound(SOUND_LABEL_SELECT);

							TSContain(pContain->pos, CONTAIN_NORMAL, CONTAIN_COMPLETE, g_aKitchen[SelectKitchen].type);	//皿の中身をキッチンの中に入っていたものにする
						}
					}
				}
				else
				{
					if (pModel->bIsLanding == false)
					{
						pPlayer->state = PLAYER_NORMAL;																					//プレイヤーを何も持っていない状態にする
						g_aKitchen[SelectKitchen].state = KITCHEN_NORMAL;																//調理器具を持たれていない状態にする
						g_aKitchen[SelectKitchen].pos = D3DXVECTOR3(pModel->pos.x, pModel->pos.y + 10.0f, pModel->pos.z);				//調理器具をモデルの真上に設置する
						g_aKitchen[SelectKitchen].rot = D3DXVECTOR3(pPlayer->rot.x, pPlayer->rot.y + D3DX_PI, -pPlayer->rot.z);			//調理器具の角度を調整する
						pModel->bIsLanding = true;																						//モデルの上に物がある状態にする

						//一番近いモデルが調理道具(1)なら
						if (pModel->Type == 1)
						{
							if (g_aKitchen[SelectKitchen].cook == KITCHEN_MATERIAL)
							{//設置したものが調理完了前だったとき
								g_aKitchen[SelectKitchen].cook = KITCHEN_COOK;					//調理器具の状態を調理中にする
								PlaySound(SOUND_LABEL_HOT);
								pModel->cook = true;											//モデルを調理中にする
							}
							else if (g_aKitchen[SelectKitchen].cook == KITCHEN_COMPLETE)
							{//設置したものの調理が完了後だった時
								g_aKitchen[SelectKitchen].cook = KITCHEN_OVER;					//調理器具の状態を焦げた状態にする
								PlaySound(SOUND_LABEL_HOTOVER);
								pModel->cook = true;											//モデルを調理中にする
							}
							if (g_aKitchen[SelectKitchen].bTimer == false)
							{//キッチンタイマーが作動しているかしていないか
								g_aKitchen[SelectKitchen].bTimer = true;
								//キッチンタイマーを設置する
								SetKTimer(g_aKitchen[SelectKitchen].pos);
							}
							PlaySound(SOUND_LABEL_SELECT);
						}
					}
				}
			}
			else if ((GetKeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_B, 0)) 
				&& pPlayer->state == PLAYER_HAVE && g_aKitchen[SelectKitchen].state == KITCHEN_HAVE && pModel->Type == 5)
			{//ゴミ箱(5)に調理器具の中にあるものを捨てる
				g_aKitchen[SelectKitchen].aParts[2].bUse = false;					//調理器具の中で焼かれているものをfalseにする
				//pKTimer->bUse = false;											//キッチンタイマーを使用していない状態にする
				g_aKitchen[SelectKitchen].cook = KITCHEN_NONE;						//モデルを何もしていない状態にする
				g_aKitchen[SelectKitchen].CookCount = 0;							//調理時間を初期化する
				g_aKitchen[SelectKitchen].bTimer = false;							//タイマーを使われてない状態にする

				for (int nCnt = 0; nCnt < MAX_KITCHENTIMER; nCnt++)
				{
					pKTimer->bUse = false;											//キッチンタイマーを使用していない状態にする
					pKTimer++;
				}
				pKTimer = GetKTimer();
			}
		}
	}
	//すべてのキッチンで回す処理
	for (int nCnt = 0; nCnt < MAX_KITCHEN; nCnt++)
	{
		if (g_aKitchen[nCnt].state == KITCHEN_HAVE)
		{//キッチンを持っている状態
			g_aKitchen[nCnt].pos = pPlayer->pos;			//キッチンの位置をプレイヤーの位置にする
		}
	}
}

//=========================================
//キッチンの描画処理
//=========================================
void DrawKitchen(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL* pMat;				//マテリアルデータへのポインタ
	
	PLAYER *pPlayer = GetPlayer();

	for (int nCntKitchen = 0; nCntKitchen < MAX_KITCHEN; nCntKitchen++)
	{
		if (g_aKitchen[nCntKitchen].bUse)
		{//調理器具を使用しているかしていないか
			if (g_aKitchen[nCntKitchen].state == KITCHEN_NORMAL)
			{//向きを反映
			 //ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_aKitchen[nCntKitchen].mtxWorldKitchen);

				//向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot,
					g_aKitchen[nCntKitchen].rot.y, g_aKitchen[nCntKitchen].rot.x, g_aKitchen[nCntKitchen].rot.z);

				D3DXMatrixMultiply(&g_aKitchen[nCntKitchen].mtxWorldKitchen, &g_aKitchen[nCntKitchen].mtxWorldKitchen, &mtxRot);

				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_aKitchen[nCntKitchen].pos.x, g_aKitchen[nCntKitchen].pos.y, g_aKitchen[nCntKitchen].pos.z);
				D3DXMatrixMultiply(&g_aKitchen[nCntKitchen].mtxWorldKitchen, &g_aKitchen[nCntKitchen].mtxWorldKitchen, &mtxTrans);
			}
			else if (g_aKitchen[nCntKitchen].state == KITCHEN_HAVE)
			{//調理道具が持たれているとき
				if (pPlayer->state == PLAYER_HAVE)
				{//向きの反映
					D3DXMATRIX Kichen_have;

					//ワールドマトリックスの初期化
					D3DXMatrixIdentity(&Kichen_have);

					//向きを反映
					D3DXMatrixRotationYawPitchRoll(&mtxRot, D3DX_PI, 0.0f, 0.0f);

					D3DXMatrixMultiply(&Kichen_have, &Kichen_have, &mtxRot);

					//位置を反映
					D3DXMatrixTranslation(&mtxTrans, 0.0f, 3.0f, -10.0f);
					D3DXMatrixMultiply(&Kichen_have, &Kichen_have, &mtxTrans);
					
					D3DXMatrixMultiply(&g_aKitchen[nCntKitchen].mtxWorldKitchen, &Kichen_have,&pPlayer->mtxWorldPlayer);
				}
			}

			for (int nCntParts = 0; nCntParts < MAX_KITCHEN_PARTS; nCntParts++)
			{
				if (g_aKitchen[nCntKitchen].aParts[nCntParts].bUse)
				{//調理器具の持つ部分が有効な時
					//ワールドマトリックスの初期化
					D3DXMatrixIdentity(&g_aKitchen[nCntKitchen].aParts[nCntParts].mtxWorld);

					//向きを反映
					D3DXMatrixRotationYawPitchRoll(&mtxRot,
						g_aKitchen[nCntKitchen].aParts[nCntParts].rot.y, g_aKitchen[nCntKitchen].aParts[nCntParts].rot.x, g_aKitchen[nCntKitchen].aParts[nCntParts].rot.z);

					D3DXMatrixMultiply(&g_aKitchen[nCntKitchen].aParts[nCntParts].mtxWorld, &g_aKitchen[nCntKitchen].aParts[nCntParts].mtxWorld, &mtxRot);

					//位置を反映
					D3DXMatrixTranslation(&mtxTrans, g_aKitchen[nCntKitchen].aParts[nCntParts].pos.x, g_aKitchen[nCntKitchen].aParts[nCntParts].pos.y, g_aKitchen[nCntKitchen].aParts[nCntParts].pos.z);
					D3DXMatrixMultiply(&g_aKitchen[nCntKitchen].aParts[nCntParts].mtxWorld, &g_aKitchen[nCntKitchen].aParts[nCntParts].mtxWorld, &mtxTrans);

					D3DXMATRIX mtxParent;

					//親のワールドマトリクスの設定
					if (nCntParts == g_aKitchen[nCntKitchen].aParts[nCntParts].nIdxModelParent)
					{
						mtxParent = g_aKitchen[nCntKitchen].mtxWorldKitchen;
					}
					else
					{
						//自分の親のマトリクスを代入
						mtxParent = g_aKitchen[nCntKitchen].aParts[g_aKitchen[nCntKitchen].aParts[nCntParts].nIdxModelParent].mtxWorld;
					}

					//ローカル座標をワールド座標に適応させる
					D3DXMatrixMultiply(&g_aKitchen[nCntKitchen].aParts[nCntParts].mtxWorld, &g_aKitchen[nCntKitchen].aParts[nCntParts].mtxWorld, &mtxParent);

					//ワールドマトリックスを更新
					pDevice->SetTransform(D3DTS_WORLD, &g_aKitchen[nCntKitchen].aParts[nCntParts].mtxWorld);

					//現在のマテリアルを保持(退避)
					pDevice->GetMaterial(&matDef);

					//マテリアルデータのポインタを取得する
					pMat = (D3DXMATERIAL*)g_aKitchen[nCntKitchen].aParts[nCntParts].pBuffMat->GetBufferPointer();

					for (int nCntMat = 0; nCntMat < (int)g_aKitchen[nCntKitchen].aParts[nCntParts].nNumMat; nCntMat++)
					{
						//マテリアルの設定
						pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

						//キッチンパーツの描画
						g_aKitchen[nCntKitchen].aParts[nCntParts].pMesh->DrawSubset(nCntMat);
					}

					//保持していたマテリアルを戻す
					pDevice->SetMaterial(&matDef);
				}
			}
		}
	}
}

//=========================================
//キッチンの情報の取得
//=========================================
KITCHEN* GetKitchen()
{
	return g_aKitchen;
}

//=========================================
//キッチンの設置
//=========================================
void SetKitchen(D3DXVECTOR3 pos,KITCHEN_STATE state)
{
	for (int nCntKitchen = 0; nCntKitchen < MAX_KITCHEN; nCntKitchen++)
	{
		if (g_aKitchen[nCntKitchen].bUse == false)
		{
			g_aKitchen[nCntKitchen].pos = pos;
			g_aKitchen[nCntKitchen].bUse = true;
			g_aKitchen[nCntKitchen].Shadow = SetShadow(g_aKitchen[nCntKitchen].pos, g_aKitchen[nCntKitchen].rot);		//影の設置処理
			g_aKitchen[nCntKitchen].state = state;

			break;
		}
	}
}

//=========================================
//モデルのパーツの設置
//=========================================
void SetKitchenParts(D3DXVECTOR3 pos, char KITCHEN_NAME[128], int nCntParts)
{
	for (int nCntKitchen = 0; nCntKitchen < MAX_KITCHEN; nCntKitchen++)
	{
		g_aKitchen[nCntKitchen].aParts[nCntParts].pos = pos;
		g_aKitchen[nCntKitchen].aParts[1].rot = D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f);

		g_aKitchen[nCntKitchen].aParts[nCntParts].posOrigin = g_aKitchen[nCntKitchen].aParts[nCntParts].pos;
		g_aKitchen[nCntKitchen].aParts[nCntParts].rotOrigin = g_aKitchen[nCntKitchen].aParts[nCntParts].rot;
		g_aKitchen[nCntKitchen].aParts[nCntParts].bUse = true;

		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//Xファイルの読み込み
		D3DXLoadMeshFromX(KITCHEN_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aKitchen[nCntKitchen].aParts[nCntParts].pBuffMat,
			NULL,
			&g_aKitchen[nCntKitchen].aParts[nCntParts].nNumMat,
			&g_aKitchen[nCntKitchen].aParts[nCntParts].pMesh);

		int nNumVtx;			//頂点数
		DWORD sizeFVF;			//頂点フォーマットのサイズ
		BYTE *pVtxBuff;			//頂点バッファへのポインタ

		//頂点数の取得
		nNumVtx = g_aKitchen[nCntKitchen].aParts[nCntParts].pMesh->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_aKitchen[nCntKitchen].aParts[nCntParts].pMesh->GetFVF());

		//頂点バッファのロック
		g_aKitchen[nCntKitchen].aParts[nCntParts].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)& pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標を取得
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//頂点座標を比較してキッチンの最小値/最大値を取得
			g_aKitchen[nCntKitchen].aParts[nCntParts].vtxMax.x = VertexMAXChange(vtx.x, g_aKitchen[nCntKitchen].aParts[nCntParts].vtxMax.x);
			g_aKitchen[nCntKitchen].aParts[nCntParts].vtxMax.y = VertexMAXChange(vtx.y, g_aKitchen[nCntKitchen].aParts[nCntParts].vtxMax.y);
			g_aKitchen[nCntKitchen].aParts[nCntParts].vtxMax.z = VertexMAXChange(vtx.z, g_aKitchen[nCntKitchen].aParts[nCntParts].vtxMax.z);

			g_aKitchen[nCntKitchen].aParts[nCntParts].vtxMin.x = VertexMINChange(vtx.x, g_aKitchen[nCntKitchen].aParts[nCntParts].vtxMin.x);
			g_aKitchen[nCntKitchen].aParts[nCntParts].vtxMin.y = VertexMINChange(vtx.y, g_aKitchen[nCntKitchen].aParts[nCntParts].vtxMin.y);
			g_aKitchen[nCntKitchen].aParts[nCntParts].vtxMin.z = VertexMINChange(vtx.z, g_aKitchen[nCntKitchen].aParts[nCntParts].vtxMin.z);

			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}
		//頂点バッファのアンロック
		g_aKitchen[nCntKitchen].aParts[nCntParts].pMesh->UnlockVertexBuffer();
	}
}

//=========================================
//キッチンの見た目の状態の変化
//=========================================
void TSKitchen(D3DXVECTOR3 pos, char KITCHEN_NAME[128],int nCnt)
{
		g_aKitchen[nCnt].aParts[2].posOrigin = g_aKitchen[nCnt].aParts[2].pos;
		g_aKitchen[nCnt].aParts[2].rotOrigin = g_aKitchen[nCnt].aParts[2].rot;
		g_aKitchen[nCnt].aParts[2].pos = pos;
		g_aKitchen[nCnt].aParts[2].bUse = true;

		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//Xファイルの読み込み
		D3DXLoadMeshFromX(KITCHEN_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aKitchen[nCnt].aParts[2].pBuffMat,
			NULL,
			&g_aKitchen[nCnt].aParts[2].nNumMat,
			&g_aKitchen[nCnt].aParts[2].pMesh);

		int nNumVtx;			//頂点数
		DWORD sizeFVF;			//頂点フォーマットのサイズ
		BYTE *pVtxBuff;			//頂点バッファへのポインタ

		//頂点数の取得
		nNumVtx = g_aKitchen[nCnt].aParts[2].pMesh->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_aKitchen[nCnt].aParts[2].pMesh->GetFVF());

		//頂点バッファのロック
		g_aKitchen[nCnt].aParts[2].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)& pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標を取得
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//頂点座標を比較してキッチンの最小値/最大値を取得
			g_aKitchen[nCnt].aParts[2].vtxMax.x = VertexMAXChange(vtx.x, g_aKitchen[nCnt].aParts[2].vtxMax.x);
			g_aKitchen[nCnt].aParts[2].vtxMax.y = VertexMAXChange(vtx.y, g_aKitchen[nCnt].aParts[2].vtxMax.y);
			g_aKitchen[nCnt].aParts[2].vtxMax.z = VertexMAXChange(vtx.z, g_aKitchen[nCnt].aParts[2].vtxMax.z);

			g_aKitchen[nCnt].aParts[2].vtxMin.x = VertexMINChange(vtx.x, g_aKitchen[nCnt].aParts[2].vtxMin.x);
			g_aKitchen[nCnt].aParts[2].vtxMin.y = VertexMINChange(vtx.y, g_aKitchen[nCnt].aParts[2].vtxMin.y);
			g_aKitchen[nCnt].aParts[2].vtxMin.z = VertexMINChange(vtx.z, g_aKitchen[nCnt].aParts[2].vtxMin.z);

			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}
		//頂点バッファのアンロック
		g_aKitchen[nCnt].aParts[2].pMesh->UnlockVertexBuffer();
}
//=========================================
//調理中の処理
//=========================================
void LetsCooking()
{
	//キッチンタイマーの情報を取得
	KTIMER *pKTimer = GetKTimer();

	//enumをファイル名にするための関数
	char KitchenFile[255];

	for (int nCnt = 0; nCnt < MAX_KITCHEN; nCnt++)
	{
		if (g_aKitchen[nCnt].cook == KITCHEN_COOK)
		{//モデルが調理中だった場合
			g_aKitchen[nCnt].CookCount++;

			if (g_aKitchen[nCnt].CookCount == 360)
			{//2秒たったら
				g_aKitchen[nCnt].CookCount = 0;
				sprintf(KitchenFile, "data/MODEL/FOOD/food_%d_cook.x", g_aKitchen[nCnt].type);				//typeをTSKitchenに入力するための処理
				TSKitchen(D3DXVECTOR3(0.0f,0.0f,0.0f), KitchenFile,nCnt);
				PlaySound(SOUND_LABEL_HOTOVER);
				g_aKitchen[nCnt].cook = KITCHEN_OVER;
			}
		}
		else if (g_aKitchen[nCnt].cook == KITCHEN_OVER)
		{//モデルが調理完了後も加熱されていた場合
			g_aKitchen[nCnt].CookCount++;

			if (g_aKitchen[nCnt].CookCount == 360)
			{//6秒たったら
				g_aKitchen[nCnt].CookCount = 0;
				sprintf(KitchenFile, "data/MODEL/FOOD/food_%d_over.x", g_aKitchen[nCnt].type);				//typeをTSKitchenに入力するための処理
				TSKitchen(D3DXVECTOR3(0.0f,0.0f,0.0f), KitchenFile,nCnt);
				g_aKitchen[nCnt].cook = KITCHEN_BURN;
				g_aKitchen[nCnt].bTimer = false;							//タイマーを使っていない状態にする
				
				for (int i = 0; i < MAX_KITCHENTIMER; i++)
				{
					pKTimer->bUse = false;										//キッチンタイマーをfalseにする
					pKTimer++;
				}
				pKTimer = GetKTimer();
			}
		}
	}
}
//=========================================
//一番近くのキッチンを判定する
//=========================================
void PlayerDistanceKitchen()
{
	PLAYER *pPlayer = GetPlayer();
	s_mathMIN = 1000000;

	float mathWidth = 0;
	float mathHeight = 0;
	float mathBox = 0;

	for (int nCnt = 0; nCnt < MAX_KITCHEN; nCnt++)
	{
		if (g_aKitchen[nCnt].bUse == true)
		{
			mathWidth = (pPlayer->pos.x - g_aKitchen[nCnt].pos.x);
			mathHeight = (pPlayer->pos.z - g_aKitchen[nCnt].pos.z);

			mathBox = sqrtf(mathWidth * mathWidth + mathHeight * mathHeight);

			if (mathBox <= s_mathMIN)
			{
				s_mathMIN = (int)mathBox;
				SelectKitchen = nCnt;
			}
		}
	}

	if (s_mathMIN <= 10)
	{
		SetObjectLine(g_aKitchen[SelectKitchen].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aKitchen[SelectKitchen].vtxMaxKitchen, D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMinKitchen.x, g_aKitchen[SelectKitchen].vtxMaxKitchen.y, g_aKitchen[SelectKitchen].vtxMaxKitchen.z));
		SetObjectLine(g_aKitchen[SelectKitchen].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aKitchen[SelectKitchen].vtxMaxKitchen, D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMaxKitchen.x, g_aKitchen[SelectKitchen].vtxMaxKitchen.y, g_aKitchen[SelectKitchen].vtxMinKitchen.z));
		SetObjectLine(g_aKitchen[SelectKitchen].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMinKitchen.x, g_aKitchen[SelectKitchen].vtxMaxKitchen.y, g_aKitchen[SelectKitchen].vtxMinKitchen.z), D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMaxKitchen.x, g_aKitchen[SelectKitchen].vtxMaxKitchen.y, g_aKitchen[SelectKitchen].vtxMinKitchen.z));
		SetObjectLine(g_aKitchen[SelectKitchen].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMinKitchen.x, g_aKitchen[SelectKitchen].vtxMaxKitchen.y, g_aKitchen[SelectKitchen].vtxMinKitchen.z), D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMinKitchen.x, g_aKitchen[SelectKitchen].vtxMaxKitchen.y, g_aKitchen[SelectKitchen].vtxMaxKitchen.z));

		SetObjectLine(g_aKitchen[SelectKitchen].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aKitchen[SelectKitchen].vtxMinKitchen, D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMaxKitchen.x, g_aKitchen[SelectKitchen].vtxMinKitchen.y, g_aKitchen[SelectKitchen].vtxMinKitchen.z));
		SetObjectLine(g_aKitchen[SelectKitchen].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aKitchen[SelectKitchen].vtxMinKitchen, D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMinKitchen.x, g_aKitchen[SelectKitchen].vtxMinKitchen.y, g_aKitchen[SelectKitchen].vtxMaxKitchen.z));
		SetObjectLine(g_aKitchen[SelectKitchen].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMaxKitchen.x, g_aKitchen[SelectKitchen].vtxMinKitchen.y, g_aKitchen[SelectKitchen].vtxMaxKitchen.z), D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMaxKitchen.x, g_aKitchen[SelectKitchen].vtxMinKitchen.y, g_aKitchen[SelectKitchen].vtxMinKitchen.z));
		SetObjectLine(g_aKitchen[SelectKitchen].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMaxKitchen.x, g_aKitchen[SelectKitchen].vtxMinKitchen.y, g_aKitchen[SelectKitchen].vtxMaxKitchen.z), D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMinKitchen.x, g_aKitchen[SelectKitchen].vtxMinKitchen.y, g_aKitchen[SelectKitchen].vtxMaxKitchen.z));

		SetObjectLine(g_aKitchen[SelectKitchen].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMaxKitchen.x, g_aKitchen[SelectKitchen].vtxMaxKitchen.y, g_aKitchen[SelectKitchen].vtxMinKitchen.z), D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMaxKitchen.x, g_aKitchen[SelectKitchen].vtxMinKitchen.y, g_aKitchen[SelectKitchen].vtxMinKitchen.z));
		SetObjectLine(g_aKitchen[SelectKitchen].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMinKitchen.x, g_aKitchen[SelectKitchen].vtxMaxKitchen.y, g_aKitchen[SelectKitchen].vtxMaxKitchen.z), D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMinKitchen.x, g_aKitchen[SelectKitchen].vtxMinKitchen.y, g_aKitchen[SelectKitchen].vtxMaxKitchen.z));
		SetObjectLine(g_aKitchen[SelectKitchen].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aKitchen[SelectKitchen].vtxMaxKitchen, D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMaxKitchen.x, g_aKitchen[SelectKitchen].vtxMinKitchen.y, g_aKitchen[SelectKitchen].vtxMaxKitchen.z));
		SetObjectLine(g_aKitchen[SelectKitchen].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aKitchen[SelectKitchen].vtxMinKitchen, D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMinKitchen.x, g_aKitchen[SelectKitchen].vtxMaxKitchen.y, g_aKitchen[SelectKitchen].vtxMinKitchen.z));
	}
}
//=========================================
//調理道具とプレイヤーの距離の取得
//=========================================
int GetKitchenDistance()
{
	return s_mathMIN;
}

//=========================================
//どのキッチンが一番近いかの情報の取得
//=========================================
int GetSelectKitchen()
{
	return SelectKitchen;
}