//=========================================
//
//	�ǂ̓��o�͏���
//	Author : �y���m��
//
//=========================================
#include "main.h"
#include "wall.h"
#include "input.h"
#include "camera.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureWall = { NULL };				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;				//���_�o�b�t�@�ւ̃|�C���^
Wall g_aWall[MAX_WALL];

//=====================================================
//�ǂ̏�����
//=====================================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,			//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,														//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/wall.jpg",
		&g_pTextureWall);

	VERTEX_3D* pVtx = NULL;			//���_���̎擾

	//���_�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		g_aWall[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�ʒu�̏����ݒ�
		g_aWall[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����̏����ݒ�
		g_aWall[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			//�F�̏����ݒ�
		g_aWall[nCnt].bUse = false;										//�g�p���Ă��邩���Ă��Ȃ���
		g_aWall[nCnt].size = 0.0f;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-WALL_SIZE, 0.0f, +WALL_SIZE);
		pVtx[1].pos = D3DXVECTOR3(+WALL_SIZE, 0.0f, +WALL_SIZE);
		pVtx[2].pos = D3DXVECTOR3(-WALL_SIZE, 0.0f, -WALL_SIZE);
		pVtx[3].pos = D3DXVECTOR3(+WALL_SIZE, 0.0f, -WALL_SIZE);

		//�e���_�̖@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_color�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffWall->Unlock();
}

//=========================================
//�ǂ̔j��
//=========================================
void UninitWall(void)
{
	//���b�V���̔j��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//�}�e���A���̔j��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//=========================================
//�ǂ̍X�V����
//=========================================
void UpdateWall(void)
{

}

//=========================================
//�ǂ̕`�揈��
//=========================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureWall);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (g_aWall[nCnt].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aWall[nCnt].mtxWall);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aWall[nCnt].rot.y, g_aWall[nCnt].rot.x, g_aWall[nCnt].rot.z);

			D3DXMatrixMultiply(&g_aWall[nCnt].mtxWall, &g_aWall[nCnt].mtxWall, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCnt].pos.x, g_aWall[nCnt].pos.y, g_aWall[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCnt].mtxWall, &g_aWall[nCnt].mtxWall, &mtxTrans);

			//���[���h�}�g���b�N�X���X�V
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCnt].mtxWall);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
				nCnt * 4,										//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);												//�v���~�e�B�u(�|���S��)��
		}
	}

	//�e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);
}

//=========================================
//�ǂ̏��̎擾
//=========================================
Wall* GetWall()
{
	return g_aWall;
}

//=========================================
//�ǂ̐ݒu����
//=========================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot , D3DXCOLOR col)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	int nCntWall;

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{
			g_aWall[nCntWall].pos = pos;
			g_aWall[nCntWall].rot = rot;
			g_aWall[nCntWall].col = col;
			g_aWall[nCntWall].bUse = true;

			pVtx[0].col = g_aWall[nCntWall].col;
			pVtx[1].col = g_aWall[nCntWall].col;
			pVtx[2].col = g_aWall[nCntWall].col;
			pVtx[3].col = g_aWall[nCntWall].col;

			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();
}