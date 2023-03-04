//========================================================
//�Q�[���I�[�o�[��ʂ̏���
//========================================================
#include "main.h"
#include "GameOver.h"
#include "input.h"
#include "fade.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureGameOver = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameOver = NULL;
//========================================================
//�Q�[���I�[�o�[�̏���������
//========================================================
void InitGameOver(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();
	//�f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"Data\\TEXTURE\\gameover001.jpg",
		&g_pTextureGameOver);

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGameOver,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

							//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGameOver->Lock(0, 0, (void**)&pVtx, 0);


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
	g_pVtxBuffGameOver->Unlock();

}

//========================================================
//�Q�[���I�[�o�[�̏I������
//========================================================
void UninitGameOver(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureGameOver != NULL)
	{
		g_pTextureGameOver->Release();
		g_pTextureGameOver = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGameOver != NULL)
	{
		g_pVtxBuffGameOver->Release();
		g_pVtxBuffGameOver = NULL;
	}
}

//========================================================
//�Q�[���I�[�o�[�̍X�V����
//========================================================
void UpdateGameOver(void)
{
	FADE pFade = GetFade();

	//����(ENTER�L�[)�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_RETURN)|| GetJoypadTrigger(JOYKEY_X, 0) || GetJoypadTrigger(JOYKEY_B, 0))
	{
		if (pFade == FADE_NONE)
		{
			SetFade(MODE_TITLE);
		}
	}
}

//========================================================
//�Q�[���I�[�o�[�̕`�揈��
//========================================================
void DrawGameOver(void)
{
	LPDIRECT3DDEVICE9 pDevice;			//�f�o�C�X�̃|�C���g

										//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGameOver, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureGameOver);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
		0,									//�`�悷��ŏ��̒��_�C���f�b�N�X
		2);									//�v���~�e�B�u(�|���S��)��
}