//========================================================
//�Q�[���^�C�}�[��ʂ̏���
//========================================================
#include "main.h"
#include "input.h"
#include "gametimer.h"
#include "ready.h"
#include "fade.h"
#include "sound.h"

#define MAX_NUMBER (4)			//�Q�[���^�C�}�[�Ɏg������

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureGameTimer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameTimer = NULL;
D3DXVECTOR3 g_posGameTimer;			//�Q�[���^�C�}�[�̈ʒu
int g_nGameTimer;					//�^�C�}�[�ɕ\������鐔��
int g_nTimerCount;					//�b�ɕϊ�����O�̐���
int minituCount;
int GameEnd;						//�Q�[���I�����̉��o����
bool bGameTimer;					//�Q�[���^�C�}�[���g���Ă��邩���Ȃ���
//========================================================
//�Q�[���^�C�}�[�̏���������
//========================================================
void InitGameTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntS;
	g_nGameTimer = 360;						//�l������������
	minituCount = 0;
	GameEnd = 0;
	g_posGameTimer = D3DXVECTOR3(1100.0f, 650.0f, 0.0f);			//�ʒu������������
	bGameTimer = false;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"Data\\TEXTURE\\number001.png",
		&g_pTextureGameTimer);

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_NUMBER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGameTimer,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGameTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntS = 0; nCntS < MAX_NUMBER; nCntS++)
	{
		//���_���W�̎w��
		pVtx[0].pos = D3DXVECTOR3(g_posGameTimer.x - 30, g_posGameTimer.y - 50, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posGameTimer.x + 30, g_posGameTimer.y - 50, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posGameTimer.x - 30, g_posGameTimer.y + 50, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posGameTimer.x + 30, g_posGameTimer.y + 50, 0.0f);

		g_posGameTimer += D3DXVECTOR3(50.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGameTimer->Unlock();
}

//========================================================
//�Q�[���^�C�}�[�̏I������
//========================================================
void UninitGameTimer(void)
{
	//�e�N�X�`���̔j��
	if (g_pVtxBuffGameTimer != NULL)
	{
		g_pTextureGameTimer->Release();
		g_pTextureGameTimer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGameTimer != NULL)
	{
		g_pVtxBuffGameTimer->Release();
		g_pVtxBuffGameTimer = NULL;
	}
}

//========================================================
//�Q�[���^�C�}�[�̍X�V����
//========================================================
void UpdateGameTimer(void)
{
	if (bGameTimer)
	{
		GameEnd++;

		if (GameEnd == 360)
		{
			SetFade(MODE_RESULT);
			GameEnd = 0;
		}
	}

	else
	{
		g_nTimerCount++;

		if (g_nTimerCount >= 60)
		{
			g_nTimerCount = 0;
			SubGameTimer(1);
		}
	}
}

//========================================================
//�Q�[���^�C�}�[�̕`�揈��
//========================================================
void DrawGameTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntS;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGameTimer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureGameTimer);

	for (nCntS = 0; nCntS < MAX_NUMBER; nCntS++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
			nCntS * 4,									//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);									//�v���~�e�B�u(�|���S��)��
	}
}

//========================================================
//�Q�[���^�C�}�[�̐ݒ菈��
//========================================================
void SetGameTimer(int nGameTimer)
{
	int aPosTexU[8];		//�e���̐������i�[
	int nCntS;

	g_nGameTimer = nGameTimer;

	if (g_nGameTimer % 60 == 0)
	{
		minituCount += g_nGameTimer / 60;
		g_nGameTimer = 0;
	}

	aPosTexU[0] = (minituCount % 10) / 1;
	aPosTexU[1] = 11;
	aPosTexU[2] = (g_nGameTimer % 100) / 10;
	aPosTexU[3] = (g_nGameTimer % 10) / 1;

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

							//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGameTimer->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	for (nCntS = 0; nCntS < MAX_NUMBER; nCntS++)
	{
		pVtx[0].tex = D3DXVECTOR2(aPosTexU[nCntS] * 0.083333f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(aPosTexU[nCntS] * 0.083333f + 0.083333f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(aPosTexU[nCntS] * 0.083333f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(aPosTexU[nCntS] * 0.083333f + 0.083333f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGameTimer->Unlock();
}
//========================================================
//�Q�[���^�C�}�[�̉��Z����
//========================================================
void SubGameTimer(int nValue)
{
	int aPosTexU[8];		//�e���̐������i�[
	int nCntS;

	g_nGameTimer -= nValue;

	if (g_nGameTimer <= -1)
	{
		minituCount--;
		g_nGameTimer = 59;
	}

	aPosTexU[0] = (minituCount % 10) / 1;
	aPosTexU[1] = 11;
	aPosTexU[2] = (g_nGameTimer % 100) / 10;
	aPosTexU[3] = (g_nGameTimer % 10) / 1;

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGameTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntS = 0; nCntS < MAX_NUMBER; nCntS++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(aPosTexU[nCntS] * 0.083333f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(aPosTexU[nCntS] * 0.083333f + 0.083333f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(aPosTexU[nCntS] * 0.083333f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(aPosTexU[nCntS] * 0.083333f + 0.083333f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGameTimer->Unlock();

	if (g_nGameTimer == 0 && minituCount == 0)
	{
		StopSound(SOUND_LABEL_BGM001);
		bGameTimer = true;
		SetReady(2);
		PlaySound(SOUND_LABEL_WHISTLE);
	}
}

//========================================================
//�Q�[���^�C�}�[�̎擾
//========================================================
int GetGameTimer(void)
{
	return g_nGameTimer;
}

//=========================================
//�Q�[���^�C�}�[�̎g�p�󋵂̎擾
//=========================================
bool GetGTimer()
{
	return bGameTimer;
}