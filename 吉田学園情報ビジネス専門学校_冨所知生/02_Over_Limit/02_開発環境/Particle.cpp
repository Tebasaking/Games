//========================================================
//�p�[�e�B�N���̏���
//========================================================
#include "particle.h"
#include "effect.h"
#include "main.h"

LPDIRECT3DTEXTURE9 g_pTextureParticle = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Particle g_aParticle[MAX_PARTICLE];

//========================================================
//�p�[�e�B�N���̏���������
//========================================================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCntParticle;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/effect000.jpg",
		&g_pTextureParticle);

	//�e�̏��̏�����
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].fRadius = 0.0f;
		g_aParticle[nCntParticle].nLife = 0;
		g_aParticle[nCntParticle].bUse = false;			//�g�p���Ă��Ȃ���Ԃɂ���
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_PARTICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffParticle,
		NULL);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_aParticle[nCntParticle].fRadius,-g_aParticle[nCntParticle].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(+g_aParticle[nCntParticle].fRadius,-g_aParticle[nCntParticle].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aParticle[nCntParticle].fRadius,+g_aParticle[nCntParticle].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(+g_aParticle[nCntParticle].fRadius,+g_aParticle[nCntParticle].fRadius, 0.0f);

			//���_color�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		pVtx += 4;			//���_�f�[�^�̃|�C���^��4���i�߂�

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffParticle->Unlock();
}

//========================================================
//�p�[�e�B�N���̏I������
//========================================================
void UninitParticle(void)
{
	if (g_pTextureParticle != NULL)
	{//�e�N�X�`���̔j��
		g_pTextureParticle->Release();
		g_pTextureParticle = NULL;
	}

	if (g_pVtxBuffParticle != NULL)
	{//���_�o�b�t�@�̔j��
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}
}
//========================================================
//�p�[�e�B�N���̍X�V����
//========================================================
void UpdateParticle(void)
{
	int nCntParticle;

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{
			SetEffect(g_aParticle[nCntParticle].pos , g_aParticle[nCntParticle].col , g_aParticle[nCntParticle].fRadius ,g_aParticle[nCntParticle].nLife);

			g_aParticle[nCntParticle].pos += g_aParticle[nCntParticle].move;
			g_aParticle[nCntParticle].col.a -= 0.05f;
			g_aParticle[nCntParticle].nLife--;

			if (g_aParticle[nCntParticle].nLife <= 0)
			{
				g_aParticle[nCntParticle].bUse = false;
			}

			//���_color�̐ݒ�
			pVtx[0].col = g_aParticle[nCntParticle].col;
			pVtx[1].col = g_aParticle[nCntParticle].col;
			pVtx[2].col = g_aParticle[nCntParticle].col;
			pVtx[3].col = g_aParticle[nCntParticle].col;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffParticle->Unlock();
}

//========================================================
//�G�t�F�N�g�̕`�揈��
//========================================================
void DrawParticle(void)
{
}

//========================================================
//�p�[�e�B�N���̐ݒ菈��
//========================================================
void SetParticle(D3DXVECTOR3 pos, int nType)
{
	int nCntParticle;

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{//�p�[�e�B�N�����g�p����Ă��Ȃ�

			g_aParticle[nCntParticle].nType = nType;

			switch (nType)
			{
			case 0:	
				g_aParticle[nCntParticle].pos = pos;
				g_aParticle[nCntParticle].move.x = cosf((float)(rand() % 600 - 314) / 100) * ((float)(rand() % 5) / 100 + 0.25f);
				g_aParticle[nCntParticle].move.y = (rand()% 1) / 10 + 0.1f;
				g_aParticle[nCntParticle].move.z = 0.0f;
				g_aParticle[nCntParticle].col = D3DXCOLOR(1.0f, 0.5f, 1.0f, 1.0f);
				g_aParticle[nCntParticle].fRadius = (float)(rand() % 1 + 1);
				g_aParticle[nCntParticle].nLife = (rand() % 10) + 10;
				g_aParticle[nCntParticle].bUse = true;

				break;

			default:
				break;
			}
			break;
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffParticle->Unlock();
}
//========================================================
//�p�[�e�B�N���̎擾����
//========================================================
Particle* GetParticle()
{
	return g_aParticle;
}