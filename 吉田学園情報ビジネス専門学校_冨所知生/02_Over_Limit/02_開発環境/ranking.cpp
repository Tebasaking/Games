//=========================================
//
//	�����L���O�̓��o�͏���
//	Author : �y���m��
//
//=========================================
#include <stdio.h>
#include "ranking.h"
#include "score.h"
#include "main.h"
#include "fade.h"
#include "input.h"
#include "sound.h"

//========================================================
//�����L���O�X�R�A�\����
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nScore;			//�X�R�A
}RankScore;

//========================================================
//�O���[�o���ϐ�
//========================================================
LPDIRECT3DTEXTURE9 g_pTextureRank = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRankScore = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRankBG = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankScore = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankBG = NULL;	//�w�i�o�b�t�@�ւ̃|�C���^
RankScore g_aRankScore[MAX_RANK];	//�����L���O�X�R�A���
int g_nRankUpdate = -1;				//�X�V�����NNo.
int g_nTimerRanking;				//�����L���O��ʕ\���^�C�}�[
int g_RankingTime = 0;

//========================================================
//�����L���O�̏���������
//========================================================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;
	int nCntR;
	int nCntS;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ�
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ranking000.png",
		&g_pTextureRank);

	//�e�N�X�`���̓Ǎ�
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureRankScore);

	//�e�N�X�`���̓Ǎ�
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ranking000.png",
		&g_pTextureRankBG);

	//�����L���O�̏��̏�����
	for (nCntR = 0; nCntR < MAX_RANK; nCntR++)
	{
		g_aRankScore[nCntR].pos = D3DXVECTOR3(365.0f, 265.0f, 0.0f);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK * MAX_RANKSCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankScore,
		NULL);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankBG,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntR = 0; nCntR < MAX_RANK; nCntR++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos.x = 0.0f;
		pVtx[0].pos.y = 0.0f;
		pVtx[0].pos.z = 0.0f;
					
		pVtx[1].pos.x = 0.0f;
		pVtx[1].pos.y = 0.0f;
		pVtx[1].pos.z = 0.0f;
						
		pVtx[2].pos.x = 0.0f;
		pVtx[2].pos.y = 0.0f;
		pVtx[2].pos.z = 0.0f;
					
		pVtx[3].pos.x = 0.0f;
		pVtx[3].pos.y = 0.0f;
		pVtx[3].pos.z = 0.0f;

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + 0.2f * nCntR);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + 0.2f * nCntR);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.2f + 0.2f * nCntR);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.2f + 0.2f * nCntR);

		pVtx += 4;

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRank->Unlock();


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntR = 0; nCntR < MAX_RANK; nCntR++)
	{
		g_aRankScore[nCntR].pos.x += 150;	//�X�R�A�\���ꏊ�ֈړ�
		for (nCntS = 0; nCntS < MAX_RANKSCORE; nCntS++)
		{
			pVtx[0].pos.x = g_aRankScore[nCntR].pos.x - 40.0f + nCntS * 80;
			pVtx[0].pos.y = g_aRankScore[nCntR].pos.y - 40.0f + nCntR * 150;
			pVtx[0].pos.z = g_aRankScore[nCntR].pos.z + 0.0f;

			pVtx[1].pos.x = g_aRankScore[nCntR].pos.x + 40.0f + nCntS * 80;
			pVtx[1].pos.y = g_aRankScore[nCntR].pos.y - 40.0f + nCntR * 150;
			pVtx[1].pos.z = g_aRankScore[nCntR].pos.z + 0.0f;

			pVtx[2].pos.x = g_aRankScore[nCntR].pos.x - 40.0f + nCntS * 80;
			pVtx[2].pos.y = g_aRankScore[nCntR].pos.y + 40.0f + nCntR * 150;
			pVtx[2].pos.z = g_aRankScore[nCntR].pos.z + 0.0f;

			pVtx[3].pos.x = g_aRankScore[nCntR].pos.x + 40.0f + nCntS * 80;
			pVtx[3].pos.y = g_aRankScore[nCntR].pos.y + 40.0f + nCntR * 150;
			pVtx[3].pos.z = g_aRankScore[nCntR].pos.z + 0.0f;


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
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankScore->Unlock();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRankBG->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffRankBG->Unlock();
}

//=========================================
//�����L���O�̏I������
//=========================================
void UninitRanking(void)
{
	StopSound();

	//�e�N�X�`���̔j��
	if (g_pTextureRank != NULL)
	{
		g_pTextureRank->Release();
		g_pTextureRank = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}

	//�e�N�X�`���̔j��
	if (g_pTextureRankScore != NULL)
	{
		g_pTextureRankScore->Release();
		g_pTextureRankScore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRankScore != NULL)
	{
		g_pVtxBuffRankScore->Release();
		g_pVtxBuffRankScore = NULL;
	}

	//�e�N�X�`���̔j��
	if (g_pTextureRankBG != NULL)
	{
		g_pTextureRankBG->Release();
		g_pTextureRankBG = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRankBG != NULL)
	{
		g_pVtxBuffRankBG->Release();
		g_pVtxBuffRankBG = NULL;
	}
}

//=========================================
//�����L���O�̍X�V����
//=========================================
void UpdateRanking(void)
{
	FADE pFade = GetFade();

	g_RankingTime++;

	if ((GetKeyboardTrigger(DIK_RETURN) == true || g_RankingTime >= 240) && pFade == FADE_NONE)
	{
		SetFade(MODE_TITLE);
	}
}

//=========================================
//�����L���O�̕`�揈��
//=========================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntR;
	int nCntS;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRankBG);

	//�|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//���_�o�b�t�@���f�[�^�X�g���[���ݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (nCntR = 0; nCntR < MAX_RANK; nCntR++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRank);

		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntR * 4, 2);
	}

	//���_�o�b�t�@���f�[�^�X�g���[���ݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (nCntR = 0; nCntR < MAX_RANK; nCntR++)
	{
		for (nCntS = 0; nCntS < MAX_RANKSCORE; nCntS++)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureRankScore);

			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntR * 4 * MAX_RANKSCORE) + (nCntS * 4), 2);
		}
	}
}

//=========================================
//�����L���O�̃��Z�b�g
//=========================================
void ResetRanking(void)
{
	FILE *pFile;	//�t�@�C���|�C���^��錾
	int nCntR;

	g_nRankUpdate = -1;	//�X�V�����NNo.�̏�����

						//�t�@�C�����J��
	pFile = fopen(FILE_NAME, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		for (nCntR = 0; nCntR < MAX_RANK; nCntR++)
		{//�����L���O�̓ǂݍ���
			fscanf(pFile, "%d", &g_aRankScore[nCntR].nScore);
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ��ꍇ
		FADE pFade = GetFade();

		if (pFade == FADE_NONE)
		{//�������Ă��Ȃ����
		 //�t�F�[�h�̐ݒ�
			SetFade(MODE_TITLE);
		}
	}
}

//=========================================
//�����L���O�̃Z�[�u
//=========================================
void SaveRanking(void)
{
	FILE *pFile;	//�t�@�C���|�C���^��錾
	int nCntR;

	g_nRankUpdate = -1;	//�X�V�����NNo.�̏�����

						//�t�@�C�����J��
	pFile = fopen(FILE_NAME, "w");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		for (nCntR = 0; nCntR < MAX_RANK; nCntR++)
		{//�����L���O�̏�������
			fprintf(pFile, "%d\n", g_aRankScore[nCntR].nScore);
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ��ꍇ
		FADE pFade = GetFade();

		if (pFade == FADE_NONE)
		{//�������Ă��Ȃ����

		 //�t�F�[�h�̐ݒ�
			SetFade(MODE_TITLE);
		}
	}

}

//=========================================
//�����L���O�̐ݒ菈��
//=========================================
void SetRanking(int nScore)
{
	VERTEX_2D *pVtx;
	int nCntR;		//�J��Ԃ�
	int nCntR2;		//�J��Ԃ�2
	int nCheckMin;	//���������Ƃ̒l���r

					//�����L���O�̍ŉ��ʂƍ���̃X�R�A���ׂ�
	if (nScore >= g_aRankScore[MAX_RANK - 1].nScore)
	{
		g_nRankUpdate = 5;
		//��r�������l������B
		g_aRankScore[MAX_RANK - 1].nScore = nScore;
	}

	for (nCntR = 0; nCntR < MAX_RANK - 1; nCntR++)
	{
		for (nCntR2 = nCntR + 1; nCntR2 < MAX_RANK; nCntR2++)
		{//��L�̌J��Ԃ����i�ނ��тɌJ��Ԃ��񐔂�-1�������B

			if (g_aRankScore[nCntR].nScore <= g_aRankScore[nCntR2].nScore)
			{
				//�ϐ����ꎞ�i�[
				nCheckMin = g_aRankScore[nCntR2].nScore;

				//��r�������l������
				g_aRankScore[nCntR2].nScore = g_aRankScore[nCntR].nScore;
				g_aRankScore[nCntR].nScore = nCheckMin;
			}
		}

	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	//������for�����邱�ƂŃ����L���O�������ς��o����
	for (nCntR = 0; nCntR < MAX_RANK; nCntR++)
	{
		int aPosTexU[3];

		aPosTexU[0] = g_aRankScore[nCntR].nScore % 1000 / 100;
		aPosTexU[1] = g_aRankScore[nCntR].nScore % 100 / 10;
		aPosTexU[2] = g_aRankScore[nCntR].nScore % 10 / 1;

		for (nCntR2 = 0; nCntR2 < MAX_RANKSCORE; nCntR2++)
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + 0.1f * aPosTexU[nCntR2], 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + 0.1f * aPosTexU[nCntR2], 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + 0.1f * aPosTexU[nCntR2], 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + 0.1f * aPosTexU[nCntR2], 1.0f);

			pVtx += 4;
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankScore->Unlock();

	//�Z�[�u����
	SaveRanking();
}