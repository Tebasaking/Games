//=========================================
//
//	ライトの設置と制御処理
//	Author : 冨所知生
//
//=========================================
#include "main.h"
#include "light.h"

//マクロ変数
#define MAX_LIGHT (5)

//グローバル変数宣言
D3DLIGHT9 g_light[MAX_LIGHT];		//ライト処理

//=========================================
//ライトの初期化処理
////=========================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir[MAX_LIGHT];				//ライトの方向ベクトル

	//ライトの構造体をクリアする
	ZeroMemory(&g_light[0], sizeof(g_light));

	//ライトの方向を設定
	vecDir[0] = D3DXVECTOR3(0.2f, 0.5f, 0.4f);

	//ライトの方向を設定
	vecDir[1] = D3DXVECTOR3(-1.0f, 0.0f, 0.2f);

	//ライトの方向を設定
	vecDir[2] = D3DXVECTOR3(0.1f, -0.5f, -0.4f);

	//ライトの方向を設定
	vecDir[3] = D3DXVECTOR3(0.1f, 0.9f, -0.4f);

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//正規化する(大きさ1のベクトルにする)
		D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);
		
		//ライトの種類を設定
		g_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;		//平行光源

		//ライトの拡散光を設定
		g_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_light[nCntLight].Direction = vecDir[nCntLight];

		//ライトを設定する↓nCnt番目のLightを設定する
		pDevice->SetLight(nCntLight, &g_light[nCntLight]);

		//ライトを有効化する↓nCnt番目のLightを設定する
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//=========================================
//ライトの破棄
//=========================================
void UninitLight(void)
{

}

//=========================================
//ライトの更新
//=========================================
void UpdateLight(void)
{

}