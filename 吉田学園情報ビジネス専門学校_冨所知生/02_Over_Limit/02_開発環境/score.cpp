//========================================================
//�X�R�A��ʂ̏���
//========================================================
#include "main.h"
#include "score.h"
#include "input.h"

#define MAX_NUMBER (3)			//�X�R�A�Ɏg������

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;
D3DXVECTOR3 g_posScore;			//�X�R�A�̈ʒu
int g_nScore;					//�X�R�A�̒l

//========================================================
//�X�R�A�̏���������
//========================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntS;
	g_nScore = 0;											//�l������������
	g_posScore = D3DXVECTOR3(50.0f, 650.0f, 0.0f);			//�ʒu������������

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"Data\\TEXTURE\\number001.png",
		&g_pTextureScore);

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_NUMBER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntS = 0; nCntS < MAX_NUMBER; nCntS++)
	{
		//���_���W�̎w��
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x - 30, g_posScore.y - 50, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + 30, g_posScore.y - 50, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x - 30, g_posScore.y + 50, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + 30, g_posScore.y + 50, 0.0f);

		g_posScore += D3DXVECTOR3(50.0f, 0.0f, 0.0f);

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
	g_pVtxBuffScore->Unlock();
}

//========================================================
//�X�R�A�̏I������
//========================================================
void UninitScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pVtxBuffScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//========================================================
//�X�R�A�̍X�V����
//========================================================
void UpdateScore(void)
{
}

//========================================================
//�X�R�A�̕`�揈��
//========================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntS;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	for (nCntS = 0; nCntS < MAX_NUMBER; nCntS++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
			nCntS * 4,										//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);												//�v���~�e�B�u(�|���S��)��
	}
}

//========================================================
//�X�R�A�̐ݒ菈��
//========================================================
void SetScore(int nScore)
{
	int aPosTexU[8];		//�e���̐������i�[
	int nCntS;

	g_nScore = nScore;

	aPosTexU[0] = (g_nScore % 1000) / 100;
	aPosTexU[1] = (g_nScore % 100) / 10;
	aPosTexU[2] = (g_nScore % 10) / 1;

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	for (nCntS = 0; nCntS < MAX_NUMBER; nCntS++)
	{
		pVtx[0].tex = D3DXVECTOR2(aPosTexU[nCntS] * TEXTURE_SIZE, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(aPosTexU[nCntS] * TEXTURE_SIZE + TEXTURE_SIZE, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(aPosTexU[nCntS] * TEXTURE_SIZE, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(aPosTexU[nCntS] * TEXTURE_SIZE + TEXTURE_SIZE, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}
//========================================================
//�X�R�A�̉��Z����
//========================================================
void AddScore(int nValue)
{
	int aPosTexU[8];		//�e���̐������i�[
	int nCntS;

	g_nScore += nValue;

	aPosTexU[0] = (g_nScore % 1000) / 100;
	aPosTexU[1] = (g_nScore % 100) / 10;
	aPosTexU[2] = (g_nScore % 10) / 1;

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntS = 0; nCntS < MAX_NUMBER; nCntS++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(aPosTexU[nCntS] * 0.08333f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(aPosTexU[nCntS] * 0.08333f + 0.08333f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(aPosTexU[nCntS] * 0.08333f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(aPosTexU[nCntS] * 0.08333f + 0.08333f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//========================================================
//�X�R�A�̎擾
//========================================================
int GetScore(void)
{
	return g_nScore;
}