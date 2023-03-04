//=========================================
//
//	�e�̓��o�͏���
//	Author : �y���m��
//
//=========================================
#include "main.h"
#include "shadow.h"
#include "input.h"
#include "camera.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureShadow = { NULL };				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;			//���_�o�b�t�@�ւ̃|�C���^
Shadow g_aShadow[MAX_SHADOW];

//=====================================================
//�e�̏�����
//=====================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,			//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,														//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/shadow000.jpg",
		&g_pTextureShadow);

	VERTEX_3D* pVtx = NULL;			//���_���̎擾

	//���_�o�b�t�@�����b�N
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		g_aShadow[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�ʒu�̏����ݒ�
		g_aShadow[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����̏����ݒ�
		g_aShadow[nCnt].bUse = false;										//�g�p���Ă��邩���Ă��Ȃ���
		g_aShadow[nCnt].size = 0.0f;

		//���_���W�̐ݒ�i���[���h���W�ł͂Ȃ����[�J�����W���w�肷��j
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
	g_pVtxBuffShadow->Unlock();
}

//=========================================
//�e�̔j��
//=========================================
void UninitShadow(void)
{
	//���b�V���̔j��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//�}�e���A���̔j��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow ->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=========================================
//�e�̍X�V����
//=========================================
void UpdateShadow(void)
{

}

//=========================================
//�e�̕`�揈��
//=========================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureShadow);

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		if (g_aShadow[nCnt].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aShadow[nCnt].mtxShadow);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aShadow[nCnt].rot.y, g_aShadow[nCnt].rot.x, g_aShadow[nCnt].rot.z);

			D3DXMatrixMultiply(&g_aShadow[nCnt].mtxShadow, &g_aShadow[nCnt].mtxShadow, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCnt].pos.x, g_aShadow[nCnt].pos.y, g_aShadow[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCnt].mtxShadow, &g_aShadow[nCnt].mtxShadow, &mtxTrans);

			//���[���h�}�g���b�N�X���X�V
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCnt].mtxShadow);

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

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=========================================
//�e�̏��̎擾
//=========================================
Shadow* GetShadow()
{
	return g_aShadow;
}

//=========================================
//�e�̐ݒu����
//=========================================
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	int nCntShadow;

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == false)
		{
			g_aShadow[nCntShadow].pos = pos;
			g_aShadow[nCntShadow].rot = rot;
			g_aShadow[nCntShadow].bUse = true;

			break;
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();

	return nCntShadow;						//�e�̔ԍ�(index)������
}

//=========================================
//�e�����̂ɉ����Ĉړ����鏈��
//=========================================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos , float nSize)
{
	if (g_aShadow[nIdxShadow].bUse)
	{
		//�����Ŏw�肳�ꂽ�ԍ��̉e��pos��ݒ�
		g_aShadow[nIdxShadow].pos = pos;

		g_aShadow[nIdxShadow].size = nSize;

		VERTEX_3D* pVtx = NULL;			//���_���̎擾

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nIdxShadow * 4;		//���_�f�[�^�̃|�C���^��4���i�߂�

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(- SHADOW_SIZE - g_aShadow[nIdxShadow].size, 0.0f, + SHADOW_SIZE + g_aShadow[nIdxShadow].size);
		pVtx[1].pos = D3DXVECTOR3(+ SHADOW_SIZE + g_aShadow[nIdxShadow].size, 0.0f, + SHADOW_SIZE + g_aShadow[nIdxShadow].size);
		pVtx[2].pos = D3DXVECTOR3(- SHADOW_SIZE - g_aShadow[nIdxShadow].size, 0.0f, - SHADOW_SIZE - g_aShadow[nIdxShadow].size);
		pVtx[3].pos = D3DXVECTOR3(+ SHADOW_SIZE + g_aShadow[nIdxShadow].size, 0.0f, - SHADOW_SIZE - g_aShadow[nIdxShadow].size);
		
		//���_color�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - g_aShadow[nIdxShadow].size / 2);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - g_aShadow[nIdxShadow].size / 2);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - g_aShadow[nIdxShadow].size / 2);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - g_aShadow[nIdxShadow].size / 2);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffShadow->Unlock();
	}
}