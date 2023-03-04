//=========================================
//
//	�v���C���[�̍ł��߂������ɂ���I�u�W�F�N�g��
//	���̓��o�͏���
//	Author : �y���m��
//
//=========================================
#include "main.h"
#include "objectline.h"
#include "input.h"
#include "camera.h"
#include "wall.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffObjectLine = NULL;				//���_�o�b�t�@�ւ̃|�C���^
OBJECTLINE g_aObjectLine[MAX_OBJECTLINE];							//���̍\����
static int g_ObjectLine;
//=====================================================
//���̏�����
//=====================================================
void InitObjectLine(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2 * MAX_OBJECTLINE,			//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,															//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffObjectLine,
		NULL);

	VERTEX_3D* pVtx = NULL;			//���_���̎擾

	//�����\�����C���̃J�E���g�̏�����
	g_ObjectLine = 0;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffObjectLine->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_OBJECTLINE; nCnt++)
	{
		g_aObjectLine[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�ʒu�̏����ݒ�
		g_aObjectLine[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			//�F�̏����ݒ�
		g_aObjectLine[nCnt].bUse = false;										//�g�p���Ă��邩���Ă��Ȃ���

		//�e���_�̖@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_color�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 2;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffObjectLine->Unlock();
}

//=========================================
//���̔j��
//=========================================
void UninitObjectLine(void)
{
	//�o�b�t�@�̔j��
	if (g_pVtxBuffObjectLine != NULL)
	{
		g_pVtxBuffObjectLine->Release();
		g_pVtxBuffObjectLine = NULL;
	}
}

//=========================================
//���̍X�V����
//=========================================
void UpdateObjectLine(void)
{
	for (int nCnt = 0; nCnt < MAX_OBJECTLINE; nCnt++)
	{
		g_aObjectLine[nCnt].bUse = false;
	}
}

//=========================================
//���̕`�揈��
//=========================================
void DrawObjectLine(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���C�g�𖳌�������
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�J�����O���͂���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffObjectLine, 0, sizeof(VERTEX_3D));

	for (int nCnt = 0; nCnt < MAX_OBJECTLINE; nCnt++)
	{
		if (g_aObjectLine[nCnt].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aObjectLine[nCnt].mtxWorld);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aObjectLine[nCnt].pos.x, g_aObjectLine[nCnt].pos.y, g_aObjectLine[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aObjectLine[nCnt].mtxWorld, &g_aObjectLine[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X���X�V
			pDevice->SetTransform(D3DTS_WORLD, &g_aObjectLine[nCnt].mtxWorld);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_LINELIST,			//�v���~�e�B�u�̎��
				nCnt * 2,										//�`�悷��ŏ��̒��_�C���f�b�N�X
				1);												//�v���~�e�B�u(�|���S��)��
		}
	}
	//���C�g�̗L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//�J�����O���͂���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//=========================================
//���̐ݒu����
//=========================================
void SetObjectLine(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 start, D3DXVECTOR3 end)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffObjectLine->Lock(0, 0, (void**)&pVtx, 0);

	int nCntObjectLine;

	for (nCntObjectLine = 0; nCntObjectLine < MAX_OBJECTLINE; nCntObjectLine++)
	{
		if (g_aObjectLine[nCntObjectLine].bUse == false)
		{
			g_aObjectLine[nCntObjectLine].pos = pos;
			g_aObjectLine[nCntObjectLine].col = col;
			g_aObjectLine[nCntObjectLine].bUse = true;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(start.x, start.y, start.z);
			pVtx[1].pos = D3DXVECTOR3(end.x, end.y, end.z);

			pVtx[0].col = col;
			pVtx[1].col = col;

			break;
		}
		pVtx += 2;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffObjectLine->Unlock();
}