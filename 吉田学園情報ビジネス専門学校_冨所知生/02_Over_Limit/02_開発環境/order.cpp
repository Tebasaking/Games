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

//�O���[�o���֐�
LPDIRECT3DTEXTURE9 g_pTextureOrder[NUM_ORDER] = { NULL, NULL , NULL };			//�e�N�X�`��(3����)�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOrder = NULL;									//���_�o�b�t�@�ւ̃|�C���^
ORDER g_aOrder[NUM_ORDER];
int g_OrderCount;																//���̃I�[�_�[���o��܂ł̃J�E���g
int g_OrderCheck;																//���߂̃I�[�_�[�̐�
//=============================================
//�^�C�g���̏���������
//=============================================
void InitOrder(void)
{
	//�I�[�_�[�̃J�E���g�̃��Z�b�g
	g_OrderCount = 3500;			//�������o��܂ł̎��Ԃ̃��Z�b�g
	g_OrderCheck = 0;				//�����̌��̃J�E���g�̃��Z�b�g

	for (int i = 0; i < NUM_ORDER; i++)
	{
		g_aOrder[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aOrder[i].nNumber = 0;
		g_aOrder[i].nType = ITEM_NULL;
		g_aOrder[i].bUse = false;
		g_aOrder[i].nLimit = 0;
		g_aOrder[i].nNumber = 0;
	}

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	//�������e�̉摜�̓ǂݍ��݂͊����i�̐��l���g���Ă���̂�
	//[1]����n�߂Ă���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Order001.png",
		&g_pTextureOrder[1]);

	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Order002.png",
		&g_pTextureOrder[2]);

	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Order003.png",
		&g_pTextureOrder[3]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_ORDER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffOrder,
		NULL);

	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffOrder->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_ORDER; nCnt++)
	{
		if (g_aOrder[nCnt].bUse == false)
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

			g_aOrder[nCnt].nType = ITEM_NULL;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffOrder->Unlock();
}
//=============================================
//�^�C�g���̏I������
//=============================================
void UninitOrder(void)
{
	int nCntOrder;

	//�e�N�X�`���̔j��
	for (nCntOrder = 0; nCntOrder < NUM_ORDER; nCntOrder++)
	{
		if (g_pTextureOrder[nCntOrder] != NULL)
		{
			g_pTextureOrder[nCntOrder]->Release();
			g_pTextureOrder[nCntOrder] = NULL;
		}
		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffOrder != NULL)
		{
			g_pVtxBuffOrder->Release();
			g_pVtxBuffOrder = NULL;
		}
	}
}
//=============================================
//�^�C�g���̍X�V����
//=============================================
void UpdateOrder(void)
{
	for (int nCnt = 0; nCnt < NUM_ORDER; nCnt++)
	{//�I�[�_�[�̊����𐧌䂷�鏈��
		if (g_aOrder[nCnt].bUse)
		{
			g_aOrder[nCnt].nLimit--;			//�I�[�_�[�̊��������炷

			if (g_aOrder[nCnt].nLimit == 0)
			{//���~�b�g��0�ɂȂ�����
				g_aOrder[nCnt].bUse = false;					//�I�[�_�[��false�ɂ���
				MoveOrder(g_aOrder[nCnt].nNumber);				//�I�[�_�[���ړ�������
				SubOrderCount();								//�I�[�_�[�̌�������炷
			}
		}
	}
}
//=============================================
//�^�C�g���̕`�揈��
//=============================================
void DrawOrder(void)
{
	int nCntOrder;

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffOrder, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̕`��
	for (nCntOrder = 0; nCntOrder < NUM_ORDER; nCntOrder++)
	{
		if (g_aOrder[nCntOrder].bUse)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureOrder[g_aOrder[nCntOrder].nType]);

			//�|���S���̕`�� �l�p
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,				//�v���~�e�B�u�̎��
				nCntOrder * 4,						//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);									//�v���~�e�B�u(�|���S��)��
		}
	}
}

//=========================================
//	�����̐ݒu����
//	* nType��contain����ITEMTYPE�̐����Ƌ��� *
//=========================================
void SetOrder(D3DXVECTOR3 pos ,ITEMTYPE nType)
{
	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffOrder->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_ORDER; nCnt++)
	{
		if (g_aOrder[nCnt].bUse == false)
		{
			//�����C���N�������g����
			g_OrderCheck++;
		
			g_aOrder[nCnt].pos = pos;
			g_aOrder[nCnt].bUse = true;
			g_aOrder[nCnt].nType = nType;
			g_aOrder[nCnt].nNumber = g_OrderCheck;
			g_aOrder[nCnt].nLimit = 3600;

			pVtx[0].pos = D3DXVECTOR3(pos.x, pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pos.x + ORDER_SIZE, pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pos.x, pos.y + ORDER_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pos.x + ORDER_SIZE, pos.y + ORDER_SIZE, 0.0f);

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

			//�I�[�_�[�^�C�}�[�̐ݒu
			SetOTimer(pos, nCnt);

			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffOrder->Unlock();
}
//=========================================
//�����̏��̎擾
//=========================================
ORDER *GetOrder()
{
	return g_aOrder;
}

//=========================================
//�������e�̃����_������
//=========================================
void RandamOrder()
{
	g_OrderCount++;

	if (g_OrderCheck <= NUM_ORDER)
	{
		if (g_OrderCount >= 360)
		{
			//1����3�܂ł̗����𐶐�
			SetOrder(D3DXVECTOR3(0.0f + (ORDER_SIZE * g_OrderCheck), 0.0f, 0.0f), (ITEMTYPE)(rand() % 3 + 1));
			g_OrderCount = 0;
		}
	}
}
//=========================================
//�I�[�_�[�����ɂ��炷����
//=========================================
void MoveOrder(int nNumber)
{
	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffOrder->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_ORDER; nCnt++)
	{
		if (g_aOrder[nCnt].nNumber >= nNumber)
		{//�擾����nNumber�����I�[�_�[�̔ԍ�������ȏ�̎�
			g_aOrder[nCnt].nNumber--;
		}

		if (g_aOrder[nCnt].bUse == true)
		{
			g_aOrder[nCnt].pos = D3DXVECTOR3((g_aOrder[nCnt].nNumber - 1) * ORDER_SIZE, 0.0f, 0.0f);

			pVtx[0].pos = D3DXVECTOR3(g_aOrder[nCnt].pos.x, g_aOrder[nCnt].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aOrder[nCnt].pos.x + ORDER_SIZE, g_aOrder[nCnt].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aOrder[nCnt].pos.x, g_aOrder[nCnt].pos.y + ORDER_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aOrder[nCnt].pos.x + ORDER_SIZE, g_aOrder[nCnt].pos.y + ORDER_SIZE, 0.0f);
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffOrder->Unlock();
}
//=========================================
//���݂��钍���̌����f�N�������g���鏈��
//=========================================
void SubOrderCount()
{
	g_OrderCheck--;
}