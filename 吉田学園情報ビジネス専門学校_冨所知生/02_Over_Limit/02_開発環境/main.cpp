//========================================================
//
// �o��/���͏���
// Author : �g�~�h�R���@�g���L
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

#define CLASS_NAME			"WindowClass"			//�E�B���h�E�N���X�̖��O
#define WINDOW_NAME			"3DGame"	//�E�B���h�E�̖��O
//========================================================
//�v���g�^�C�v�錾
//========================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);

void Uninit(void);

void Update(void);

void Draw(void);

void DrawFPS(void);

bool WIRE;
//========================================================
//�O���[�o���ϐ�
//========================================================
LPDIRECT3D9 g_pD3D = NULL;				//Direct3D�I�u�W�F�N�g�ւ̃|�C���g
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//Direct3D�f�o�C�X�ւ̃|�C���g
LPD3DXFONT g_pFont = NULL;				//�t�H���g�ւ̃|�C���^
MODE g_mode = MODE_TITLE;				//���݂̃��[�h
int g_nCountFPS = 0;					//FPS�J�E���^

//========================================================
//���C���֐�
//========================================================
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hlnstacePrev, LPSTR ipCmdLine, int nCmdShow)
{
	HWND hWnd;	//Window�n���h�����ʎq
	MSG msg;	//���b�Z�[�W���i�[����ϐ�
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//�E�C���h�E�N���X
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),			//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hinstance,
		LoadIcon(NULL,IDI_APPLICATION),		//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),			//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),			//�N���C�A���g�̈�̔w�i�F
		NULL,								//���j���[�o�[
		CLASS_NAME,							//�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)		//�t�@�C���̃A�C�R��	
	};
	
	//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, SCREEN_WIDTH, SCREEN_HEIGHT);

	//�E�C���h�E�𐶐�
	hWnd = CreateWindowEx(0,						//�g���E�C���h�E�X�^�C��
		CLASS_NAME,				//�E�C���h�E�N���X�̖��O
		WINDOW_NAME,			//�E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,	//�E�C���h�E�X�^�C��
		CW_USEDEFAULT,			//�E�C���h�E�̍���X���W
		CW_USEDEFAULT,			//�E�C���h�E�̍���Y���W
		(rect.right - rect.left),//�E�C���h�E�̕�
		(rect.bottom - rect.top),//�E�C���h�E�̍���
		NULL,					//�e�E�C���h�E�̃n���h��
		NULL,					//���j���[�n���h���܂��͎q�E�C���h�EID
		hinstance,				//�C���X�^���X�n���h��
		NULL);					//�E�C���h�E�쐬�f�[�^

	if (FAILED(Init(hinstance, hWnd, TRUE)))
	{//�����������s�����ꍇ
		return -1;
	}

	DWORD dwCurrentTime;							//���ݎ���
	DWORD dwExecLastTime;							//�Ō�ɏ�����������
	DWORD dwFrameCount;								//�t���[���J�E���g
	DWORD dwFPSLastTime;							//�Ō��FPS���v����������

	//�E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);						//�E�C���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);								//�N���C�A���g�̈���X�V

	//����\��ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;								//���Ԃ̏�����
	dwExecLastTime = timeGetTime();
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windows�̐ݒ�
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}

			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();			//���ݎ������擾
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;		//FPS���������������ۑ�
				dwFrameCount = 0;					//�t���[���J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;		//�����J�n�̎���[���ݎ���]��ۑ�

													//�t���[���J�E���g�����Z
				dwFrameCount++;

				//�X�V����
				Update();

				//�`�揈��
				Draw();
			}
		}
	}

	//�I������
	Uninit();

	//���ɖ߂�
	timeEndPeriod(1);

	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//========================================================
//�E�C���h�E�v���V�[�W��
//========================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:				//�E�B���h�E�I�����̏���
									//WM_QUIT�Ƀ��b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:   //�L�[���������Ƃ��̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);			//����̏�����Ԃ�
}

//========================================================
//����������
//========================================================
HRESULT Init(HINSTANCE hlnstance, HWND hWnd, BOOL bWindow)
{
	// �ϐ��錾
	D3DDISPLAYMODE				d3ddm;			// �f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS		d3dpp;			// �v���[���e�[�V�����p�����[�^

	// Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	// ���������^�̏ꍇ���s
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h�̎擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));		// �p�����[�^�̃[���N���A

											// �A�h���X�̑��
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;							// �o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;										// �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// �_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;							// �f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;										// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��

																	// Direct3D�f�o�C�X�̐���
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		// Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_������CPU�ōs��)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{// Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_������CPU�ōs��)
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

	// �����_�\�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �T���v���[�X�e�\�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//�e�N�X�`�������j�A�⊮����
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//�e�N�X�`�������j�A�⊮����
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// �f�o�b�N�\���p�̃t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH, "Terminal", &g_pFont);

	WIRE = false;

	//���͏����̏���������
	if (FAILED(InitInput(hlnstance, hWnd)))
	{
		return E_FAIL;
	}

	//�T�E���h�̏������ݒ�
	InitSound(hWnd);

	//�t�F�[�h�̐ݒ�
	InitFade(g_mode);

	//�����L���O�̃��Z�b�g
	ResetRanking();

	return S_OK;
}
//========================================================
//�I������
//========================================================
void Uninit(void)
{
	//�C���v�b�g�̏I������
	UninitInput();

	//�^�C�g���̏I������
	UninitTitle();

	//�Q�[���̏I������
	UninitGame();

	//���U���g�̐��ʏ���
	UninitResult();

	//�Q�[���I�[�o�[�̏I������
	UninitGameOver();

	//�����L���O�̏I������
	UninitRanking();

	//�t�F�[�h�̏I������
	UninitFade();

	//�T�E���h�̏I������
	UninitSound();

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	//�f�o�b�O�\���p�t�H���g�̔j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
}

//========================================================
//�X�V����
//========================================================
void Update(void)
{
	//  time�֐����g���������̎�̐ݒ�
	srand((unsigned int)time(NULL));

	//�C���v�b�g�̍X�V����
	UpdateInput();

	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();			//�^�C�g�����
		break;

	case MODE_GAME:				//�Q�[�����
		UpdateGame();
		break;

	case MODE_RESULT:			//���U���g���
		UpdateResult();
		break;

	case MODE_GAMEOVER:
		UpdateGameOver();
		break;
	
	case MODE_RANKING:
		UpdateRanking();
		break;
	}

	//�t�F�[�h�̍X�V����
	UpdateFade();

	//if (g_mode == MODE_GAME)
	//{
	//	//���C���[�t���[��
	//	if (GetKeyboardTrigger(DIK_RETURN))
	//	{
	//		WIRE = !WIRE;
	//		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, WIRE ? D3DFILL_WIREFRAME : D3DFILL_FORCE_DWORD);
	//	}
	//}
}

//========================================================
//�`�揈��
//========================================================
void Draw(void)
{
	//��ʃN���A(�o�b�N�o�b�t�@&�y�o�b�t�@�̃N���A)
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();			//�^�C�g�����
			break;

		case MODE_GAME:				//�Q�[�����
			DrawGame();
			break;

		case MODE_RESULT:			//���U���g���
			DrawResult();
			break;

		case MODE_GAMEOVER:			//�Q�[���I�[�o�[���
			DrawGameOver();
			break;

		case MODE_RANKING:
			DrawRanking();			//�����L���O���
			break;
		}

		//�t�F�[�h�̕`�揈��
		DrawFade();

		//FPS�̕`��
		//DrawFPS();

		//�`��̏I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}

//==================================================
//�f�o�C�X�̎擾����
//==================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//==================================================
//tex�̊ȈՏ���
//==================================================
void SetTexture(VERTEX_2D *pVtx, float left, float right, float top, float bottom)
{
	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(left, top);
	pVtx[1].tex = D3DXVECTOR2(right, top);
	pVtx[2].tex = D3DXVECTOR2(left, bottom);
	pVtx[3].tex = D3DXVECTOR2(right, bottom);
}

//=========================================
//FPS�̕\��
//=========================================
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[1256];
	char aStr2[256];

	//���f���ƃJ�����̏����擾
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

	// ������̑��
	wsprintf(&aStr[0], "FPS %d\n", g_nCountFPS);

	// �߂�ǂ�����G�ɉ����鏈��
	sprintf(&aStr2[0], "  \n\n\n\n\n\n\n\n\n");
	strcat(&aStr[0], &aStr2[0]);

	// �J�����̎��_
	sprintf(&aStr2[0], "  �J�����̎��_ | %0.1f | %0.1f | %0.1f |\n", pCamera->posV.x, pCamera->posV.y, pCamera->posV.z);
	strcat(&aStr[0], &aStr2[0]);

	// �J�����̒����_
	sprintf(&aStr2[0], "  �J�����̒����_ | %0.1f | %0.1f | %0.1f |\n", pCamera->posR.x, pCamera->posR.y, pCamera->posR.z);
	strcat(&aStr[0], &aStr2[0]);

	// �J�����̒����_�܂ł̌���
	sprintf(&aStr2[0], "  �����_�܂ł̌��� | %0.3f | %0.3f\n\n", pCamera->rot.x, pCamera->rot.y);
	strcat(&aStr[0], &aStr2[0]);

	// ���f���̈ʒu
	sprintf(&aStr2[0], "  ���f���̈ʒu | %0.1f | %0.1f | %0.1f |\n", pPlayer->pos.x, pPlayer->pos.y, pPlayer->pos.z);
	strcat(&aStr[0], &aStr2[0]);

	//���f���̌���
	sprintf(&aStr2[0], "  ���f���̌��� | %0.3f | %0.3f | %0.3f |\n", pPlayer->rot.x, pPlayer->rot.y, pPlayer->rot.z);
	strcat(&aStr[0], &aStr2[0]);

	//�������
	sprintf(&aStr2[0], "\n�������\n [W A S D] ���f���̈ړ�\n [O / L] ���f���̏㉺(Trigger)");
	strcat(&aStr[0], &aStr2[0]);

	//�v���C���[�̏��
	sprintf(&aStr2[0], "\n�v���C���[�̏��      %d\n [ 0 / ���������ĂȂ�] [ 1 / �����Ă� ]",pPlayer->state);
	strcat(&aStr[0], &aStr2[0]);

	//��ԋ߂��̃I�u�W�F�N�g�̏��
	sprintf(&aStr2[0], "\n���߂̃I�u�W�F�N�g�̏��      %d\n [ 0 / ����ĂȂ�] [ 1 / ����Ă� ]", pModel->bIsLanding);
	strcat(&aStr[0], &aStr2[0]);

	//��ԋ߂��̃L�b�`���̏��
	sprintf(&aStr2[0], "\n���߂̃L�b�`���̏��      %d\n [ 0 / �u���Ă���] [ 1 / ������Ă���]", pKitchen->state);
	strcat(&aStr[0], &aStr2[0]);

	//��ԋ߂��̗e��̏��
	sprintf(&aStr2[0], "\n���߂̗e��̏��      %d\n [ 0 / �u���Ă���] [ 1 / ������Ă���]", pContain->state);
	strcat(&aStr[0], &aStr2[0]);

	// �e�L�X�g�`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//=========================================
//�p�x�̐��K������
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
//���[�h�̐ݒ�
//===========================================
void SetMode(MODE mode)
{
	//���݂̉��(���[�h)�̏I������
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();			//�^�C�g�����
		break;

	case MODE_GAME:					//�Q�[�����
		UninitGame();
		break;

	case MODE_RESULT:			//���U���g���
		UninitResult();
		break;

	case MODE_GAMEOVER:			//�Q�[���I�[�o�[���
		UninitGameOver();
		break;

	case MODE_RANKING:			//�����L���O���
		UninitRanking();
	}

	//�V�������(���[�h)�̏���������
	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();			//�^�C�g�����
		break;

	case MODE_GAME:				//�Q�[�����
		InitGame();
		break;

	case MODE_RESULT:			//���U���g���
		InitResult();
		break;

	case MODE_GAMEOVER:			//�Q�[���I�[�o�[���
		InitGameOver();
		break;

	case MODE_RANKING:			//�����L���O���
		InitRanking();
		SetRanking(GetScore());
		break;
	}
	g_mode = mode;			//���݂̉��(���[�h)��؂�ւ���
}

//���[�h�̎擾
MODE GetMode(void)
{
	return g_mode;
}