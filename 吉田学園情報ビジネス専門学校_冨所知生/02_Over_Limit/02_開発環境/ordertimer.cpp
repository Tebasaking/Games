//=============================================
//
//	�I�[�_�[�̓��o�͏���
//	Auhor : �y���m��
//
//=============================================
#include <stdio.h>
#include "main.h"
#include "title.h"
#include "player.h"
#include "input.h"
#include "fade.h"
#include "order.h"
#include "ordertimer.h"

#define NUM_OTIMER (200)
#define OTIMER_SIZE (20.0f)
//�O���[�o���֐�
LPDIRECT3DTEXTURE9 g_pTextureOTimer = NULL;			//�e�N�X�`��(3����)�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOTimer = NULL;									//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureOTimerBar = NULL;										//�e�N�X�`��(3����)�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOTimerBar = NULL;									//���_�o�b�t�@�ւ̃|�C���^
OTIMER g_aOTimer[NUM_OTIMER];
//=============================================
//�^�C�g���̏���������
//=============================================
void InitOTimer(void)
{
	for (int i = 0; i < NUM_OTIMER; i++)
	{
		g_aOTimer[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aOTimer[i].bUse = false;
	}

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	//�������e�̉摜�̓ǂݍ��݂͊����i�̐��l���g���Ă���̂�
	//[1]����n�߂Ă���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/OTimer001.png",
		&g_pTextureOTimer);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_OTIMER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffOTimer,
		NULL);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_OTIMER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffOTimerBar,
		NULL);

	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffOTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_OTIMER; nCnt++)
	{
		if (g_aOTimer[nCnt].bUse == false)
		{
			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`���̍��W�ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffOTimer->Unlock();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffOTimerBar->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_OTIMER; nCnt++)
	{
		if (g_aOTimer[nCnt].bUse == false)
		{
			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`���̍��W�ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffOTimerBar->Unlock();
}
//=============================================
//�^�C�g���̏I������
//=============================================
void UninitOTimer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureOTimer != NULL)
	{
		g_pTextureOTimer->Release();
		g_pTextureOTimer = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffOTimer != NULL)
	{
		g_pVtxBuffOTimer->Release();
		g_pVtxBuffOTimer = NULL;
	}

	//�e�N�X�`���̔j��
	if (g_pTextureOTimerBar != NULL)
	{					
		g_pTextureOTimerBar->Release();
		g_pTextureOTimerBar = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffOTimerBar != NULL)
	{					
		g_pVtxBuffOTimerBar->Release();
		g_pVtxBuffOTimerBar = NULL;
	}
}
//=============================================
//�^�C�g���̍X�V����
//=============================================
void UpdateOTimer(void)
{
	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^
	ORDER *pOrder = GetOrder();

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffOTimerBar->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_OTIMER; nCnt++)
	{
		if (g_aOTimer[nCnt].bUse)
		{
			//�I�[�_�[��Ή������ԍ��܂Ői�߂�
			pOrder += g_aOTimer[nCnt].nNumber;

			if (g_aOTimer[nCnt].state == OTIMER_BAR)
			{
				pVtx[0].pos = D3DXVECTOR3(pOrder->pos.x, g_aOTimer[nCnt].pos.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(pOrder->pos.x + pOrder->nLimit / 30,pOrder->pos.y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pOrder->pos.x, g_aOTimer[nCnt].pos.y + OTIMER_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pOrder->pos.x + pOrder->nLimit / 30, pOrder->pos.y + OTIMER_SIZE, 0.0f);
			}
			if (pOrder->bUse == false)
			{//�Ή������I�[�_�[��false��������
				g_aOTimer[nCnt].bUse = false;
			}
				//�|�C���^�[�̏�����
				pOrder = GetOrder();
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffOTimerBar->Unlock();

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffOTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_OTIMER; nCnt++)
	{
		if (g_aOTimer[nCnt].bUse)
		{
			//�I�[�_�[��Ή������ԍ��܂Ői�߂�
			pOrder += g_aOTimer[nCnt].nNumber;

			if (g_aOTimer[nCnt].state == OTIMER_CONTAIN)
			{
				pVtx[0].pos = D3DXVECTOR3(pOrder->pos.x, g_aOTimer[nCnt].pos.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(pOrder->pos.x + 130.0f, pOrder->pos.y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pOrder->pos.x, g_aOTimer[nCnt].pos.y + OTIMER_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pOrder->pos.x + 130.0f, pOrder->pos.y + OTIMER_SIZE, 0.0f);
			}
			if (pOrder->bUse == false)
			{//�Ή������I�[�_�[��false��������
				g_aOTimer[nCnt].bUse = false;
			}
			//�|�C���^�[�̏�����
			pOrder = GetOrder();
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffOTimer->Unlock();
}
//=============================================
//�^�C�g���̕`�揈��
//=============================================
void DrawOTimer(void)
{
	int nCntOTimer;

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffOTimer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̕`��
	for (nCntOTimer = 0; nCntOTimer < NUM_OTIMER; nCntOTimer++)
	{
		if (g_aOTimer[nCntOTimer].bUse)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureOTimer);

			//�|���S���̕`�� �l�p
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,				//�v���~�e�B�u�̎��
				nCntOTimer * 4,						//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);									//�v���~�e�B�u(�|���S��)��
		}
	}

	//�o�[�̃e�N�X�`����Draw
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffOTimerBar, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̕`��
	for (nCntOTimer = 0; nCntOTimer < NUM_OTIMER; nCntOTimer++)
	{
		if (g_aOTimer[nCntOTimer].bUse)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureOTimerBar);

			//�|���S���̕`�� �l�p
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,				//�v���~�e�B�u�̎��
				nCntOTimer * 4,						//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);									//�v���~�e�B�u(�|���S��)��
		}
	}
}

//=========================================
//	�����̐ݒu����
//	* nType��contain����ITEMTYPE�̐����Ƌ��� *
//=========================================
void SetOTimer(D3DXVECTOR3 pos, int nNumber)
{
	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffOTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_OTIMER; nCnt++)
	{
		if (g_aOTimer[nCnt].bUse == false)
		{
			g_aOTimer[nCnt].pos = pos;
			g_aOTimer[nCnt].bUse = true;
			g_aOTimer[nCnt].nNumber = nNumber;

			pVtx[0].pos = D3DXVECTOR3(pos.x, pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pos.x + 130.0f, pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pos.x, pos.y + OTIMER_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pos.x + 130.0f, pos.y + OTIMER_SIZE, 0.0f);

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

			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffOTimer->Unlock();

	//�I�[�_�[�^�C�}�[�̃o�[�̐ݒu
	SetOTimerBar(pos, nNumber);
}
//=========================================
//	�����̐ݒu����
//	* nType��contain����ITEMTYPE�̐����Ƌ��� *
//=========================================
void SetOTimerBar(D3DXVECTOR3 pos, int nNumber)
{
	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffOTimerBar->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_OTIMER; nCnt++)
	{
		if (g_aOTimer[nCnt].bUse == false)
		{
			g_aOTimer[nCnt].pos = pos;
			g_aOTimer[nCnt].bUse = true;
			g_aOTimer[nCnt].nNumber = nNumber;
			g_aOTimer[nCnt].state = OTIMER_BAR;

			pVtx[0].pos = D3DXVECTOR3(pos.x, pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pos.x + 130.0f, pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pos.x, pos.y + OTIMER_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pos.x + 130.0f, pos.y + OTIMER_SIZE, 0.0f);

			// rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_color�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffOTimerBar->Unlock();
}
//=========================================
//�����̏��̎擾
//=========================================
OTIMER *GetOTimer()
{
	return g_aOTimer;
}