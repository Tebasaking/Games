//=========================================
//
//	���b�V���̓��o�͏���
//	Author : �y���m��
//
//=========================================
#include "main.h"
#include "meshfield.h"
#include "wall.h"
#include "model.h"
#include "wall.h"

//================================================================
//�O���[�o���ϐ��錾
//================================================================
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;				//���b�V���t�B�[���h�̃e�N�X�`��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;			//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9  g_pIdxBuffMeshField = NULL;			//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posMeshField;									//�ʒu
D3DXVECTOR3 g_rotMeshField;									//����
D3DXMATRIX g_mtxWorldMesh;									//���[���h�}�g���b�N�X

#define MESH_VERTEX_NUM ((MESH_X_BLOCK + 1) * (MESH_Z_BLOCK + 1))
#define MESH_INDEX_NUM  (((MESH_X_BLOCK + 1) * 2) * ( MESH_Z_BLOCK  *(MESH_Z_BLOCK - 1)) * MESH_Z_BLOCK * 2)
#define MESH_PRIMITIVE_NUM (MESH_X_BLOCK * MESH_Z_BLOCK * 2 + 4 * (MESH_Z_BLOCK  - 1))

int nLineVtx = (MESH_X_BLOCK + 1);
//================================================================
//���b�V���̏�����
//================================================================
void InitMesh(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESH_VERTEX_NUM,	//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,													//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESH_INDEX_NUM,			//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,													//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/float.jpg",
		&g_pTextureMeshField);

	VERTEX_3D* pVtx = NULL;			//���_���̎擾

	//���_�o�b�t�@�����b�N
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ <= MESH_Z_BLOCK; nCntZ++)
	{
		for (int nCntX = 0; nCntX <= MESH_X_BLOCK; nCntX++)
		{
			//���_���W�̐ݒ�i���[���h���W�ł͂Ȃ����[�J�����W���w�肷��j
			pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].pos = D3DXVECTOR3(-(MESH_SIZE * MESH_X_BLOCK) / 2 + nCntX * MESH_SIZE, 0.0f,(MESH_SIZE * MESH_Z_BLOCK) / 2 - nCntZ * MESH_SIZE);

			//�e���_�̖@���̐ݒ�
			pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`���̐ݒ�
			pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].tex = D3DXVECTOR2((float)nCntX, (float)nCntZ);
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffMeshField->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIdx;
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);
	
	//�c�̒��_�̐�
	for (int nCntZ = 0; nCntZ < MESH_Z_BLOCK; nCntZ++)
	{
		//�C���f�b�N�X
		int nLineTop = nCntZ * (nLineVtx * 2 + 2);

		//���̒��_�̐�
		for (int nCntX = 0; nCntX < nLineVtx; nCntX++)
		{//��̒i�̏���
			pIdx[(nCntX * 2 + 1) + nLineTop] = (WORD)(nCntX + nLineVtx * nCntZ);

		//���̒i�̏���
			pIdx[nCntX * 2 + nLineTop] = (WORD)(pIdx[(nCntX * 2 + 1) + nLineTop] + nLineVtx);
		}

		//�k�ރ|���S����O��Ɠ���ɂ��鏈��
		if (nCntZ < MESH_Z_BLOCK)
		{
			pIdx[(nLineVtx * 2) + nLineTop] = (WORD)(MESH_X_BLOCK + (nLineVtx) * nCntZ);
			pIdx[(nLineVtx * 2) + nLineTop + 1] = (WORD)(2 * (nLineVtx) + (nLineVtx) * nCntZ);
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBuffMeshField->Unlock();
}
//================================================================
//���b�V���̔j��
//================================================================
void UninitMesh(void)
{
	//���b�V���t�B�[���h�̃e�N�X�`��
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
	//���_�o�b�t�@�̉��
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}
}
//================================================================
//���b�V���̍X�V
//================================================================
void UpdateMesh(void)
{
}

//================================================================
//���b�V���̕`��
//================================================================
void DrawMesh(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMesh);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);

	D3DXMatrixMultiply(&g_mtxWorldMesh, &g_mtxWorldMesh, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMesh, &g_mtxWorldMesh, &mtxTrans);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshField);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMesh);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@�̃f�[�^�X�g���[���ɐݒ�
	pDevice -> SetIndices(g_pIdxBuffMeshField);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ���b�V���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0,0, MESH_VERTEX_NUM ,0, MESH_PRIMITIVE_NUM);
}