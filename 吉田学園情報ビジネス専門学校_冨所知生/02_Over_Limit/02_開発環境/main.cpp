//========================================================
//
// 出力/入力処理
// Author : トミドコロ　トモキ
//
//========================================================
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include "dinput.h"						
#include "Xinput.h"						
#include "main.h"
#include "camera.h"
#include "polygon.h"
#include "light.h"
#include "model.h"
#include "input.h"
#include "shadow.h"
#include "wall.h"
#include "billboard.h"
#include "file.h"
#include "meshfield.h"
#include "cylinder.h"
#include "sphere.h"
#include "effect.h"
#include "particle.h"
#include "player.h"
#include "line.h"
#include "item.h"
#include "objectline.h"
#include "Kitchen.h"
#include "contain.h"
#include "game.h"
#include "result.h"
#include "gameover.h"
#include "title.h"
#include "score.h"
#include "fade.h"
#include "sound.h"
#include "ranking.h"

#define CLASS_NAME			"WindowClass"			//ウィンドウクラスの名前
#define WINDOW_NAME			"3DGame"	//ウィンドウの名前
//========================================================
//プロトタイプ宣言
//========================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);

void Uninit(void);

void Update(void);

void Draw(void);

void DrawFPS(void);

bool WIRE;
//========================================================
//グローバル変数
//========================================================
LPDIRECT3D9 g_pD3D = NULL;				//Direct3Dオブジェクトへのポイント
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//Direct3Dデバイスへのポイント
LPD3DXFONT g_pFont = NULL;				//フォントへのポインタ
MODE g_mode = MODE_TITLE;				//現在のモード
int g_nCountFPS = 0;					//FPSカウンタ

//========================================================
//メイン関数
//========================================================
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hlnstacePrev, LPSTR ipCmdLine, int nCmdShow)
{
	HWND hWnd;	//Windowハンドル識別子
	MSG msg;	//メッセージを格納する変数
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//ウインドウクラス
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),			//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hinstance,
		LoadIcon(NULL,IDI_APPLICATION),		//タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),			//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),			//クライアント領域の背景色
		NULL,								//メニューバー
		CLASS_NAME,							//ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)		//ファイルのアイコン	
	};
	
	//ウインドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, SCREEN_WIDTH, SCREEN_HEIGHT);

	//ウインドウを生成
	hWnd = CreateWindowEx(0,						//拡張ウインドウスタイル
		CLASS_NAME,				//ウインドウクラスの名前
		WINDOW_NAME,			//ウインドウの名前
		WS_OVERLAPPEDWINDOW,	//ウインドウスタイル
		CW_USEDEFAULT,			//ウインドウの左上X座標
		CW_USEDEFAULT,			//ウインドウの左上Y座標
		(rect.right - rect.left),//ウインドウの幅
		(rect.bottom - rect.top),//ウインドウの高さ
		NULL,					//親ウインドウのハンドル
		NULL,					//メニューハンドルまたは子ウインドウID
		hinstance,				//インスタンスハンドル
		NULL);					//ウインドウ作成データ

	if (FAILED(Init(hinstance, hWnd, TRUE)))
	{//初期化が失敗した場合
		return -1;
	}

	DWORD dwCurrentTime;							//現在時刻
	DWORD dwExecLastTime;							//最後に処理した時刻
	DWORD dwFrameCount;								//フレームカウント
	DWORD dwFPSLastTime;							//最後にFPSを計測した時刻

	//ウインドウの表示
	ShowWindow(hWnd, nCmdShow);						//ウインドウの表示状態を設定
	UpdateWindow(hWnd);								//クライアント領域を更新

	//分解能を設定
	timeBeginPeriod(1);

	dwCurrentTime = 0;								//時間の初期化
	dwExecLastTime = timeGetTime();
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windowsの設定
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}

			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();			//現在時刻を取得
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;		//FPSを九艇した時刻を保存
				dwFrameCount = 0;					//フレームカウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;		//処理開始の時刻[現在時刻]を保存

													//フレームカウントを加算
				dwFrameCount++;

				//更新処理
				Update();

				//描画処理
				Draw();
			}
		}
	}

	//終了処理
	Uninit();

	//元に戻す
	timeEndPeriod(1);

	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//========================================================
//ウインドウプロシージャ
//========================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:				//ウィンドウ終了時の処理
									//WM_QUITにメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:   //キーを押したときのメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);			//既定の処理を返す
}

//========================================================
//初期化処理
//========================================================
HRESULT Init(HINSTANCE hlnstance, HWND hWnd, BOOL bWindow)
{
	// 変数宣言
	D3DDISPLAYMODE				d3ddm;			// ディスプレイモード
	D3DPRESENT_PARAMETERS		d3dpp;			// プレゼンテーションパラメータ

	// Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	// 条件式が真の場合実行
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードの取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));		// パラメータのゼロクリア

											// アドレスの代入
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;							// バックバッファの形式
	d3dpp.BackBufferCount = 1;										// バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;							// デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						// デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;										// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル

																	// Direct3Dデバイスの生成
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		// Direct3Dデバイスの生成(描画処理と頂点処理をCPUで行う)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{// Direct3Dデバイスの生成(描画処理と頂点処理をCPUで行う)
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	// レンダ―ステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// サンプラーステ―トの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//テクスチャをリニア補完する
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//テクスチャをリニア補完する
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	// テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// デバック表示用のフォントの生成
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH, "Terminal", &g_pFont);

	WIRE = false;

	//入力処理の初期化処理
	if (FAILED(InitInput(hlnstance, hWnd)))
	{
		return E_FAIL;
	}

	//サウンドの初期化設定
	InitSound(hWnd);

	//フェードの設定
	InitFade(g_mode);

	//ランキングのリセット
	ResetRanking();

	return S_OK;
}
//========================================================
//終了処理
//========================================================
void Uninit(void)
{
	//インプットの終了処理
	UninitInput();

	//タイトルの終了処理
	UninitTitle();

	//ゲームの終了処理
	UninitGame();

	//リザルトの数量処理
	UninitResult();

	//ゲームオーバーの終了処理
	UninitGameOver();

	//ランキングの終了処理
	UninitRanking();

	//フェードの終了処理
	UninitFade();

	//サウンドの終了処理
	UninitSound();

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	//デバッグ表示用フォントの破棄
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
}

//========================================================
//更新処理
//========================================================
void Update(void)
{
	//  time関数を使った乱数の種の設定
	srand((unsigned int)time(NULL));

	//インプットの更新処理
	UpdateInput();

	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();			//タイトル画面
		break;

	case MODE_GAME:				//ゲーム画面
		UpdateGame();
		break;

	case MODE_RESULT:			//リザルト画面
		UpdateResult();
		break;

	case MODE_GAMEOVER:
		UpdateGameOver();
		break;
	
	case MODE_RANKING:
		UpdateRanking();
		break;
	}

	//フェードの更新処理
	UpdateFade();

	//if (g_mode == MODE_GAME)
	//{
	//	//ワイヤーフレーム
	//	if (GetKeyboardTrigger(DIK_RETURN))
	//	{
	//		WIRE = !WIRE;
	//		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, WIRE ? D3DFILL_WIREFRAME : D3DFILL_FORCE_DWORD);
	//	}
	//}
}

//========================================================
//描画処理
//========================================================
void Draw(void)
{
	//画面クリア(バックバッファ&Ｚバッファのクリア)
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();			//タイトル画面
			break;

		case MODE_GAME:				//ゲーム画面
			DrawGame();
			break;

		case MODE_RESULT:			//リザルト画面
			DrawResult();
			break;

		case MODE_GAMEOVER:			//ゲームオーバー画面
			DrawGameOver();
			break;

		case MODE_RANKING:
			DrawRanking();			//ランキング画面
			break;
		}

		//フェードの描画処理
		DrawFade();

		//FPSの描画
		//DrawFPS();

		//描画の終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}

//==================================================
//デバイスの取得処理
//==================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//==================================================
//texの簡易処理
//==================================================
void SetTexture(VERTEX_2D *pVtx, float left, float right, float top, float bottom)
{
	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(left, top);
	pVtx[1].tex = D3DXVECTOR2(right, top);
	pVtx[2].tex = D3DXVECTOR2(left, bottom);
	pVtx[3].tex = D3DXVECTOR2(right, bottom);
}

//=========================================
//FPSの表示
//=========================================
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[1256];
	char aStr2[256];

	//モデルとカメラの情報を取得
	Camera *pCamera = GetCamera();
	PLAYER *pPlayer = GetPlayer();
	MODEL *pModel = GetModel();
	CONTAIN *pContain = GetContain();
	KITCHEN *pKitchen = GetKitchen();

	int SelectModel = GetSelectObject();
	int SelectContain = GetSelectContain();
	int SelectKitchen = GetSelectKitchen();

	pKitchen += SelectKitchen;
	pContain += SelectContain;
	pModel += SelectModel;

	// 文字列の代入
	wsprintf(&aStr[0], "FPS %d\n", g_nCountFPS);

	// めんどいから雑に下げる処理
	sprintf(&aStr2[0], "  \n\n\n\n\n\n\n\n\n");
	strcat(&aStr[0], &aStr2[0]);

	// カメラの視点
	sprintf(&aStr2[0], "  カメラの視点 | %0.1f | %0.1f | %0.1f |\n", pCamera->posV.x, pCamera->posV.y, pCamera->posV.z);
	strcat(&aStr[0], &aStr2[0]);

	// カメラの注視点
	sprintf(&aStr2[0], "  カメラの注視点 | %0.1f | %0.1f | %0.1f |\n", pCamera->posR.x, pCamera->posR.y, pCamera->posR.z);
	strcat(&aStr[0], &aStr2[0]);

	// カメラの注視点までの向き
	sprintf(&aStr2[0], "  注視点までの向き | %0.3f | %0.3f\n\n", pCamera->rot.x, pCamera->rot.y);
	strcat(&aStr[0], &aStr2[0]);

	// モデルの位置
	sprintf(&aStr2[0], "  モデルの位置 | %0.1f | %0.1f | %0.1f |\n", pPlayer->pos.x, pPlayer->pos.y, pPlayer->pos.z);
	strcat(&aStr[0], &aStr2[0]);

	//モデルの向き
	sprintf(&aStr2[0], "  モデルの向き | %0.3f | %0.3f | %0.3f |\n", pPlayer->rot.x, pPlayer->rot.y, pPlayer->rot.z);
	strcat(&aStr[0], &aStr2[0]);

	//操作説明
	sprintf(&aStr2[0], "\n操作説明\n [W A S D] モデルの移動\n [O / L] モデルの上下(Trigger)");
	strcat(&aStr[0], &aStr2[0]);

	//プレイヤーの状態
	sprintf(&aStr2[0], "\nプレイヤーの状態      %d\n [ 0 / 何ももってない] [ 1 / 持ってる ]",pPlayer->state);
	strcat(&aStr[0], &aStr2[0]);

	//一番近くのオブジェクトの状態
	sprintf(&aStr2[0], "\n直近のオブジェクトの状態      %d\n [ 0 / 乗ってない] [ 1 / 乗ってる ]", pModel->bIsLanding);
	strcat(&aStr[0], &aStr2[0]);

	//一番近くのキッチンの状態
	sprintf(&aStr2[0], "\n直近のキッチンの状態      %d\n [ 0 / 置いてある] [ 1 / 持たれている]", pKitchen->state);
	strcat(&aStr[0], &aStr2[0]);

	//一番近くの容器の状態
	sprintf(&aStr2[0], "\n直近の容器の状態      %d\n [ 0 / 置いてある] [ 1 / 持たれている]", pContain->state);
	strcat(&aStr[0], &aStr2[0]);

	// テキスト描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//=========================================
//角度の正規化処理
//=========================================
float NormalizRot(float fRot)
{
	if (fRot < -D3DX_PI)
	{
		fRot += D3DX_PI * 2;
	}
	else if (fRot > D3DX_PI)
	{
		fRot -= D3DX_PI * 2;
	}
	return fRot;
}
//===========================================
//モードの設定
//===========================================
void SetMode(MODE mode)
{
	//現在の画面(モード)の終了処理
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();			//タイトル画面
		break;

	case MODE_GAME:					//ゲーム画面
		UninitGame();
		break;

	case MODE_RESULT:			//リザルト画面
		UninitResult();
		break;

	case MODE_GAMEOVER:			//ゲームオーバー画面
		UninitGameOver();
		break;

	case MODE_RANKING:			//ランキング画面
		UninitRanking();
	}

	//新しい画面(モード)の初期化処理
	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();			//タイトル画面
		break;

	case MODE_GAME:				//ゲーム画面
		InitGame();
		break;

	case MODE_RESULT:			//リザルト画面
		InitResult();
		break;

	case MODE_GAMEOVER:			//ゲームオーバー画面
		InitGameOver();
		break;

	case MODE_RANKING:			//ランキング画面
		InitRanking();
		SetRanking(GetScore());
		break;
	}
	g_mode = mode;			//現在の画面(モード)を切り替える
}

//モードの取得
MODE GetMode(void)
{
	return g_mode;
}