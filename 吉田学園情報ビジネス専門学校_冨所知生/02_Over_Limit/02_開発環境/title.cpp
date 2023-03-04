//=============================================
//
//	�^�C�g����ʂ̏o�͏���
//	Auhor : �y���m��
//
//=============================================
#include "main.h"
#include "title.h"
#include "player.h"
#include "input.h"
#include "fade.h"
#include "particle.h"
#include "titlemodel.h"
#include "file.h"
#include "camera.h"
#include "light.h"
#include "sound.h"

//�O���[�o���֐�
LPDIRECT3DTEXTURE9 g_pTextureTitle[NUM_TITLE] = { NULL, NULL , NULL };			//�e�N�X�`��(3����)�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//���_�o�b�t�@�ւ̃|�C���^
D3DXCOLOR g_TitleColor;
D3DXCOLOR g_TutorialColor;
int g_TitleColTimer;
int TutorialCnt = 0;
bool g_TitleColBlinking;
bool g_tutorial;
static int g_move;
bool MoveStart;
bool tutorial;
//�^�C�g���̏��
TITLE_SELECT TitleSelect;
//=============================================
//�^�C�g���̏���������
//=============================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^

	g_TitleColTimer = 0;
	g_move = 0;
	g_TitleColBlinking = false;
	g_TitleColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_TutorialColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	g_tutorial = false;
	MoveStart = false;
	TitleSelect = GAME;					//�^�C�g���Z���N�g�̏����ʒu�̐ݒ�

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�J�����̏�����
	InitCamera(D3DXVECTOR3(0.0f, 10.0f, 360.0f), D3DXVECTOR3(0.0f, 100.0f, -50.0f));

	//�p�[�e�B�N���̏�����
	InitParticle();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/ol_logo.png",
		&g_pTextureTitle[0]);

	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/title001.png",
		&g_pTextureTitle[1]);

	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/GAME_START.png",
		&g_pTextureTitle[2]);

	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/TUTORIAL.png",
		&g_pTextureTitle[3]);

	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/tutorial000.png",
		&g_pTextureTitle[4]);

	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/tutorial001.png",
		&g_pTextureTitle[5]);

	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/tutorial_true.png",
		&g_pTextureTitle[6]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̍X�V
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 , 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 4, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_���W�̍X�V
	pVtx[4].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200.0f, SCREEN_HEIGHT / 2 + 250.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, SCREEN_HEIGHT / 2 + 250.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200.0f, SCREEN_HEIGHT - 25, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, SCREEN_HEIGHT - 25, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_���W�̍X�V
	pVtx[8].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200.0f, SCREEN_HEIGHT / 2, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, SCREEN_HEIGHT / 2, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200.0f, SCREEN_HEIGHT - 200.0f, 0.0f);
	pVtx[11].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, SCREEN_HEIGHT - 200.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_���W�̍X�V
	pVtx[12].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200.0f, SCREEN_HEIGHT / 2 + 100.0f, 0.0f);
	pVtx[13].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, SCREEN_HEIGHT / 2 + 100.0f, 0.0f);
	pVtx[14].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200.0f, SCREEN_HEIGHT - 100.0f, 0.0f);
	pVtx[15].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, SCREEN_HEIGHT - 100.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_���W�̍X�V
	pVtx[16].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[17].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[18].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[19].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[18].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[19].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	//���_���W�̍X�V
	pVtx[20].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[21].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[22].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[23].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//�`���[�g���A����\�����鏈��
	pVtx[20].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[21].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[22].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[23].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	//���_���W�̍X�V
	pVtx[24].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[25].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[26].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[27].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//�`���[�g���A����\�����鏈��
	pVtx[24].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[25].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[26].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[27].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);


for (int nCnt = 0; nCnt < NUM_TITLE; nCnt++)
	{
		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	//�^�C�g���̃��f���̏�����
	InitTitleModel();

	//�v���C���[�̏�����
	InitPlayer();

	//���f���̃t�@�C���̓ǂݍ���
	TitleFile();

	//���C�g�̏�����
	InitLight();

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM000);
}
//=============================================
//�^�C�g���̏I������
//=============================================
void UninitTitle(void)
{
	//�T�E���h�̒�~
	StopSound();

	//�J�����̏I������
	UninitCamera();

	int nCntTitle;

	//�v���C���[�̔j��
	UninitPlayer();

	//�p�[�e�B�N���̔j��
	UninitParticle();

	//�^�C�g���̃��f���̏I������
	UninitTitleModel();

	//���C�g�̏I������
	UninitLight();

	//�e�N�X�`���̔j��
	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		if (g_pTextureTitle[nCntTitle] != NULL)
		{
			g_pTextureTitle[nCntTitle]->Release();
			g_pTextureTitle[nCntTitle] = NULL;
		}
		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffTitle != NULL)
		{
			g_pVtxBuffTitle->Release();
			g_pVtxBuffTitle = NULL;
		}
	}
}
//=============================================
//�^�C�g���̍X�V����
//=============================================
void UpdateTitle(void)
{
	//�J�����̍X�V����
	UpdateCamera();

	//�v���C���[�̍X�V����
	UpdatePlayer();

	//�p�[�e�B�N���̍X�V����
	UpdateParticle();

	//�^�C�g���̃��f���̍X�V����
	UpdateTitleModel();

	//���C�g�̍X�V����
	UpdateLight();

	FADE pFade = GetFade();

	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//�^�C�g���̑I���̏���
	switch (TitleSelect)
	{
		case GAME:
		{
			//�Q�[�����J�n���鏈��
			if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_X, 0) || GetJoypadTrigger(JOYKEY_B, 0))
			{
				if (pFade == FADE_NONE)
				{
					//�T�E���h�̍Đ�
					PlaySound(SOUND_LABEL_BELL);

					SetFade(MODE_GAME);
				}
			}
			//�^�C�g���̑I�������炷����
			if (GetKeyboardTrigger(DIK_DOWN) || GetKeyboardTrigger(DIK_UP) || GetKeyboardTrigger(DIK_W) || GetKeyboardTrigger(DIK_S)
				|| GetJoypadTrigger(JOYKEY_UP, 0) || GetJoypadTrigger(JOYKEY_DOWN, 0))
			{
				PlaySound(SOUND_LABEL_SELECT);
				TitleSelect = TUTORIAL;
			}
			break;
		}
		case TUTORIAL:
		{
			//�^�C�g���̑I�������炷����
			if (GetKeyboardTrigger(DIK_DOWN) || GetKeyboardTrigger(DIK_UP) || GetKeyboardTrigger(DIK_W) || GetKeyboardTrigger(DIK_S) 
				|| GetJoypadTrigger(JOYKEY_UP, 0) || GetJoypadTrigger(JOYKEY_DOWN, 0) && tutorial == false)
			{
				PlaySound(SOUND_LABEL_SELECT);
				TitleSelect = GAME;
			}
			else if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_B,0 ))
			{
				//�`���[�g���A�����g�p����Ă����Ԃɂ���
				tutorial = true;
				PlaySound(SOUND_LABEL_PAGE);

				switch(TutorialCnt)
				{
					case 0:
					{
						//�`���[�g���A����\�����鏈��
						pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[18].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[19].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

						TutorialCnt++;
						break;
					}
					case 1:
					{
						//�`���[�g���A����\�����鏈��
						pVtx[20].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[21].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[22].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[23].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

						TutorialCnt++;
						break;
					}
					case 2:
					{
						//�`���[�g���A����\�����鏈��
						pVtx[24].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[25].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[26].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[27].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

						TutorialCnt++;
						break;
					}
					case 3:
					{
						//�`���[�g���A����\�����鏈��
						pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
						pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
						pVtx[18].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
						pVtx[19].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
						pVtx[20].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
						pVtx[21].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
						pVtx[22].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
						pVtx[23].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
						pVtx[24].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
						pVtx[25].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
						pVtx[26].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
						pVtx[27].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

						tutorial = false;
						TutorialCnt = 0;
						break;
					}
				}
			}
			break;
		}
	}
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	if (MoveStart == false)
	{
		g_move++;

		if (g_move == 30)
		{
			MoveStart = true;
		}
	}
	else
	{
		g_move--;

		if (g_move == 0)
		{
			MoveStart = false;
		}
	}

	switch (TitleSelect)
	{
	case GAME:
		//���_���W�̍X�V
		pVtx[8].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200.0f, SCREEN_HEIGHT / 2 - pos.y * g_move / 2, 0.0f);
		pVtx[9].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, SCREEN_HEIGHT / 2 - pos.y * g_move / 2, 0.0f);
		pVtx[10].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200.0f, SCREEN_HEIGHT - 200.0f - pos.y * g_move / 2, 0.0f);
		pVtx[11].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, SCREEN_HEIGHT - 200.0f - pos.y * g_move / 2, 0.0f);
		break;

	case TUTORIAL:
		//���_���W�̍X�V
		pVtx[12].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200.0f, SCREEN_HEIGHT / 2 + 100.0f - pos.y * g_move / 2, 0.0f);
		pVtx[13].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, SCREEN_HEIGHT / 2 + 100.0f - pos.y * g_move / 2, 0.0f);
		pVtx[14].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200.0f, SCREEN_HEIGHT - 100.0f - pos.y * g_move / 2, 0.0f);
		pVtx[15].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, SCREEN_HEIGHT - 100.0f - pos.y * g_move / 2, 0.0f);
		break;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();
}
//=============================================
//�^�C�g���̕`�揈��
//=============================================
void DrawTitle(void)
{
	//�J�����̐ݒ菈��
	SetCamera();

	//�^�C�g���̃��f���̕`��
	DrawTitleModel();

	int nCntTitle;

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̕`��
	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[nCntTitle]);

		//�|���S���̕`�� �l�p
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,				//�v���~�e�B�u�̎��
			nCntTitle * 4,						//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);									//�v���~�e�B�u(�|���S��)��
	}

	//�p�[�e�B�N���̕`��
	DrawParticle();
}