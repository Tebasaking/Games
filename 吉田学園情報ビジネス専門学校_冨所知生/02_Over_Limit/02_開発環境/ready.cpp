//=============================================
//
//	�����̏o�͏���
//	Auhor : �y���m��
//
//=============================================
#include "main.h"
#include "ready.h"

//�O���[�o���֐�
LPDIRECT3DTEXTURE9 g_pTextureReady[NUM_READY] = { NULL, NULL , NULL };			//�e�N�X�`��(3����)�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffReady = NULL;		//���_�o�b�t�@�ւ̃|�C���^
D3DXCOLOR g_ReadyColor;
READY g_aReady[NUM_READY];
int g_ReadyTimer;
int StopCnt;
int ZeroNumber;
bool bUsePicture;	//���f�B�[�̉摜���o�I�����
bool bReady;		//�������������������Ă��Ȃ���

#define READY_WIDTH (200.0f)
#define READY_HEIGHT (100.0f)
//=============================================
//�^�C�g���̏���������
//=============================================
void InitReady(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^

	StopCnt = 0;
	g_ReadyTimer = 0;
	g_ReadyColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	bReady = false;
	bUsePicture = false;
	ZeroNumber = 0;

	for (int i = 0; i < NUM_READY; i++)
	{
		g_aReady[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aReady[i].bUse = false;
	}

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Ready000.png",
		&g_pTextureReady[0]);

	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Ready001.png",
		&g_pTextureReady[1]);

	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Ready002.png",
		&g_pTextureReady[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_READY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffReady,
		NULL);

	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffReady->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_READY; nCnt++)
	{
		if (g_aReady[nCnt].bUse == false)
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
	g_pVtxBuffReady->Unlock();

	//������ʂ̐ݒu
	SetReady(0);
}
//=============================================
//�^�C�g���̏I������
//=============================================
void UninitReady(void)
{
	//�e�N�X�`���̔j��
	for (int nCntReady = 0; nCntReady < NUM_READY; nCntReady++)
	{
		if (g_pTextureReady[nCntReady] != NULL)
		{
			g_pTextureReady[nCntReady]->Release();
			g_pTextureReady[nCntReady] = NULL;
		}
		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffReady != NULL)
		{
			g_pVtxBuffReady->Release();
			g_pVtxBuffReady = NULL;
		}
	}
}
//=============================================
//�^�C�g���̍X�V����
//=============================================
void UpdateReady(void)
{
	if (g_ReadyTimer < 100)
	{
		g_ReadyTimer++;
	}

	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffReady->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_READY; nCnt++)
	{
		if (g_aReady[nCnt].bUse)
		{
			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (float)g_ReadyTimer * 2, SCREEN_HEIGHT / 2 - (float)g_ReadyTimer, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + (float)g_ReadyTimer * 2, SCREEN_HEIGHT / 2 - (float)g_ReadyTimer, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (float)g_ReadyTimer * 2, SCREEN_HEIGHT / 2 + (float)g_ReadyTimer, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + (float)g_ReadyTimer * 2, SCREEN_HEIGHT / 2 + (float)g_ReadyTimer, 0.0f);
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffReady->Unlock();

	if (g_ReadyTimer >= 100)
	{
		StopCnt++;

		if (StopCnt == 30)
		{//�摜���ő�ɂȂ��Ă���o�߂�������
			if (bUsePicture == false)
			{
				g_ReadyTimer = 0;
				bUsePicture = true;
				//������ʂ̐ݒu
				SetReady(1);
				StopCnt = 0;
				g_aReady[0].bUse = false;
			}
			else
			{
				g_aReady[1].bUse = false;
				bReady = true;
			}
		}
	}
}
//=============================================
//�^�C�g���̕`�揈��
//=============================================
void DrawReady(void)
{
	int nCntReady;

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffReady, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̕`��
	for (nCntReady = 0; nCntReady < NUM_READY; nCntReady++)
	{
		if (g_aReady[nCntReady].bUse)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureReady[g_aReady[nCntReady].nType]);

			//�|���S���̕`�� �l�p
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,				//�v���~�e�B�u�̎��
				nCntReady * 4,						//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);									//�v���~�e�B�u(�|���S��)��
		}
	}
}
//=========================================
//������ʂ̐ݒu����
//=========================================
void SetReady(int nType)
{
	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffReady->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_READY; nCnt++)
	{
		if (g_aReady[nCnt].bUse == false)
		{
			if (nType == 0)
			{
				ZeroNumber = nType;
			}

			g_ReadyTimer = 0;
			g_aReady[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aReady[nCnt].bUse = true;
			g_aReady[nCnt].nType = nType;

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
	g_pVtxBuffReady->Unlock();
}
//=========================================
// �������������������Ă��Ȃ����̎擾
//=========================================
bool GetReady()
{
	return bReady;
}