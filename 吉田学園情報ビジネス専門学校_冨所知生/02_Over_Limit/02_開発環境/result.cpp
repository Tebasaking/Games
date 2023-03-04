//========================================================
//���U���g��ʂ̏���
//========================================================
#include "main.h"
#include "Result.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "score.h"
#include "contain.h"

#define SCORE_SIZE (10)
#define MAN_SCORE_NUM (4)
#define MAX_RESULT_SCORE (30)
#define RESULT_SCORE (0.1f)

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;
LPDIRECT3DTEXTURE9 g_pTextureResultScore = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultScore = NULL;
RESULT g_aResult[MAX_RESULT_SCORE];
//========================================================
//���U���g�̏���������
//========================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"Data\\TEXTURE\\result_number000.png",
		&g_pTextureResult);

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̎w��
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM002);

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"Data\\TEXTURE\\number000.png",
		&g_pTextureResultScore);

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_RESULT_SCORE * MAN_SCORE_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultScore,
		NULL);

	for (int nCnt = 0; nCnt < MAX_RESULT_SCORE; nCnt++)
	{
		// ���U���g�̏��̏�����
		memset(&g_aResult[nCnt], 0, sizeof(g_aResult[nCnt]));
	}

	//�X�R�A�̐ݒu����
	int pScore = GetScore();
	FOOD_COUNT *pFCount = GetFoodCount();

	SetResult(0 , pFCount->meat);
	SetResult(1 , pFCount->cabbage);
	SetResult(2 , pFCount->vegetable);
	SetResult(3 , pScore);
}

//========================================================
//���U���g�̏I������
//========================================================
void UninitResult(void)
{
	//�T�E���h�̒�~
	StopSound();

	//�e�N�X�`���̔j��
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	//�e�N�X�`���̔j��
	if (g_pTextureResultScore != NULL)
	{
		g_pTextureResultScore->Release();
		g_pTextureResultScore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResultScore != NULL)
	{
		g_pVtxBuffResultScore->Release();
		g_pVtxBuffResultScore = NULL;
	}
}

//========================================================
//���U���g�̍X�V����
//========================================================
void UpdateResult(void)
{
	FADE pFade = GetFade();

	//����(ENTER�L�[)�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_X,0) || GetJoypadTrigger(JOYKEY_B,0))
	{
		if (pFade == FADE_NONE)
		{
			SetFade(MODE_RANKING);
		}
	}
}
//========================================================
//���U���g�̕`�揈��
//========================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;			//�f�o�C�X�̃|�C���g

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResult);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
		0,												//�`�悷��ŏ��̒��_�C���f�b�N�X
		2);												//�v���~�e�B�u(�|���S��)��

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResultScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResultScore);

	for (int nCntS = 0; nCntS < MAX_RESULT_SCORE; nCntS++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
			nCntS * 4,									//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);									//�v���~�e�B�u(�|���S��)��
	}
}
//=========================================
//�����̔z�u
//=========================================
void SetResult(int nType ,int nScore)
{
	int g_nScore = nScore;
	int aPosTexU[3];		//�e���̐������i�[

	aPosTexU[0] = (g_nScore % 1000) / 100;
	aPosTexU[1] = (g_nScore % 100) / 10;
	aPosTexU[2] = (g_nScore % 10) / 1;

	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResultScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < MAX_RESULT_SCORE; nCntScore++)
	{
		if (g_aResult[nCntScore].bUse == false)
		{
			//�G���g�p����Ă��Ȃ�
			g_aResult[nCntScore].nType = nType;
			g_aResult[nCntScore].bUse = true;

			for (int nCntS = 0; nCntS < MAN_SCORE_NUM; nCntS++)
			{
				if (g_aResult[nCntScore].nType == 0)
				{
					//���_���W�̎w��
					pVtx[0].pos = D3DXVECTOR3(525.0f + nCntS * 50, 225.0f, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(575.0f + nCntS * 50, 225.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(525.0f + nCntS * 50, 275.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(575.0f + nCntS * 50, 275.0f, 0.0f);
				}
				else if (g_aResult[nCntScore].nType == 1)
				{
					//���_���W�̎w��
					pVtx[0].pos = D3DXVECTOR3(525.0f + nCntS * 50, 375.0f, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(575.0f + nCntS * 50, 375.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(525.0f + nCntS * 50, 425.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(575.0f + nCntS * 50, 425.0f, 0.0f);
				}
				else if (g_aResult[nCntScore].nType == 2)
				{
					//���_���W�̎w��
					pVtx[0].pos = D3DXVECTOR3(525.0f + nCntS * 50, 510.0f, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(575.0f + nCntS * 50, 510.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(525.0f + nCntS * 50, 560.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(575.0f + nCntS * 50, 560.0f, 0.0f);
				}
				else if (g_aResult[nCntScore].nType == 3)
				{
					//���_���W�̎w��
					pVtx[0].pos = D3DXVECTOR3(525.0f + nCntS * 50, 110.0f, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(575.0f + nCntS * 50, 110.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(525.0f + nCntS * 50, 160.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(575.0f + nCntS * 50, 160.0f, 0.0f);
				}

				for (int nCnt = 0; nCnt < MAN_SCORE_NUM; nCnt++)
				{
					//�e�N�X�`�����W�̐ݒ�
					pVtx[0].tex = D3DXVECTOR2(aPosTexU[nCntS] * RESULT_SCORE, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(aPosTexU[nCntS] * RESULT_SCORE + RESULT_SCORE, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(aPosTexU[nCntS] * RESULT_SCORE, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(aPosTexU[nCntS] * RESULT_SCORE + RESULT_SCORE, 1.0f);

					// rhw�̐ݒ�
					pVtx[0].rhw = 1.0f;
					pVtx[1].rhw = 1.0f;
					pVtx[2].rhw = 1.0f;
					pVtx[3].rhw = 1.0f;

					//���_color�̐ݒ�
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
				pVtx += 4;
			}
			break;
		}
		pVtx += 4 * MAN_SCORE_NUM;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResultScore->Unlock();
}