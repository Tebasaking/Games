//========================================================
// 
//	�Q�[����ʂ̏���
//	Author : �y���m��
//
//========================================================
#include "main.h"
#include "camera.h"
#include "polygon.h"
#include "light.h"
#include "model.h"
#include "input.h"
#include "shadow.h"
#include "wall.h"
#include "billboard.h"
#include "file.h"
#include "meshfield.h"
#include "cylinder.h"
#include "sphere.h"
#include "effect.h"
#include "particle.h"
#include "player.h"
#include "line.h"
#include "item.h"
#include "objectline.h"
#include "Kitchen.h"
#include "contain.h"
#include "kitchentimer.h"
#include "cuttingtimer.h"
#include "ordertimer.h"
#include "order.h"
#include "gametimer.h"
#include "score.h"
#include "ready.h"
#include "sound.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureGame = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGame = NULL;
//========================================================
//�Q�[���̏���������
//========================================================
void InitGame(void)
{
	//������ʂ̏���������
	InitReady();

	//�J�����̏���������
	InitCamera(D3DXVECTOR3(0.0f, 120.0f, -70.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�ǂ̏���������
	InitWall();

	//�~���̏�����
	InitSphere();

	////���b�V���t�B�[���h�̏�����
	InitMesh();

	//���C�g�̏���������
	InitLight();

	//�e�̏���������
	InitShadow();

	//�v���C���[�̏������ݒ�
	InitPlayer();

	//���̏������ݒ�
	InitLine();

	//�����\�����C���̏���������
	InitObjectLine();

	//�e��̏������ݒ�
	InitContain();

	//�L�b�`���̏������ݒ�
	InitKitchen();

	//���f���̏���������
	InitModel();

	//�t�@�C���̏������ݒ�
	InitFile();

	//�A�j���[�V�����̏������ݒ�
	MotionFile();

	//�r���{�[�h�̏������ݒ�
	InitBillboard();

	//�G�t�F�N�g�̏������ݒ�
	InitEffect();

	//�p�[�e�B�N���̏������ݒ�
	InitParticle();

	//�A�C�e���̏������ݒ�
	InitItem();

	//�L�b�`���^�C�}�[�̏�����
	InitKTimer();

	//�J�b�g�^�C�}�[�̏�����
	InitCTimer();

	//�I�[�_�[�^�C�}�[�̏�����
	InitOTimer();

	//�����̏�����
	InitOrder();

	//�Q�[���^�C�}�[�̏�����
	InitGameTimer();

	//�X�R�A�̏�����
	InitScore();

	//�ǂ̐ݒu
	SetWall(D3DXVECTOR3(+MESH_SIZE / 2 * MESH_X_BLOCK, +WALL_SIZE, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.5f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//SetWall(D3DXVECTOR3(+MESH_SIZE / 2 * MESH_X_BLOCK, +WALL_SIZE, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI * 0.5f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	//SetWall(D3DXVECTOR3(-MESH_SIZE / 2 * MESH_X_BLOCK, +WALL_SIZE, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.5f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	SetWall(D3DXVECTOR3(-MESH_SIZE / 2 * MESH_X_BLOCK, +WALL_SIZE, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI * 0.5f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//SetWall(D3DXVECTOR3(0.0f, +WALL_SIZE, +MESH_SIZE / 2 * MESH_Z_BLOCK), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, D3DX_PI * 0.5f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	SetWall(D3DXVECTOR3(0.0f, +WALL_SIZE, +MESH_SIZE / 2 * MESH_Z_BLOCK), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, -D3DX_PI * 0.5f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//SetWall(D3DXVECTOR3(0.0f, +WALL_SIZE, -MESH_SIZE / 2 * MESH_Z_BLOCK), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, D3DX_PI * 0.5f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	SetWall(D3DXVECTOR3(0.0f, +WALL_SIZE, -MESH_SIZE / 2 * MESH_Z_BLOCK), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, -D3DX_PI * 0.5f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�r���{�[�h�̐ݒu									   
	SetBillboard(D3DXVECTOR3(MESH_SIZE / 2 + 10.0f, 15.0f, 5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//�r���{�[�h�̐ݒu
	SetBillboard(D3DXVECTOR3(MESH_SIZE / 2 - 10.0f, 15.0f, 5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//�Q�[���^�C�}�[�̐ݒu
	SetGameTimer(120);
	//�X�R�A�̐ݒu
	SetScore(0);

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM001);
}

//========================================================
//�Q�[���̏I������
//========================================================
void UninitGame(void)
{
	//�T�E���h�̏I��
	StopSound();

	//������ʂ̏I������
	UninitReady();

	//���b�V���̏I������
	UninitMesh();

	//�J�����̏I������
	UninitCamera();

	//���C�g�̏I������
	UninitLight();

	//�e�̏I������
	UninitShadow();

	//���f���̏I������
	UninitModel();

	//�v���C���[�̏I������
	UninitPlayer();

	//�ǂ̏I������
	UninitWall();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�p�[�e�B�N���̏I������
	UninitParticle();

	//�r���{�[�h�̏I������
	UninitBillboard();

	//���̏I������
	UninitLine();

	//�����\�����C���̏I������
	UninitObjectLine();

	//�A�C�e���̏I������
	UninitItem();

	//�L�b�`���̏I������
	UninitKitchen();

	//�e��̏������ݒ�
	UninitContain();

	//�L�b�`���^�C�}�[�̏I������
	UninitKTimer();

	//�J�b�g�^�C�}�[�̏I������
	UninitCTimer();

	//�I�[�_�[�^�C�}�[�̏I������
	UninitOTimer();

	//�����̏I������
	UninitOrder();

	//�Q�[���^�C�}�[�̏I������
	UninitGameTimer();

	//�X�R�A�̏I������
	UninitScore();
}

//========================================================
//�Q�[���̍X�V����
//========================================================
void UpdateGame(void)
{
	//�����̏��̎擾
	bool bReady = GetReady();
	//�Q�[���^�C�}�[�̎g�p�󋵂̎擾
	bool bGTimer = GetGTimer();

	//������ʂ̍X�V����
	UpdateReady();

	//���������������Ƃ�
	if (bReady)
	{
		if (!bGTimer)
		{
			//�~���̍X�V����
			UpdateSphere();

			//���b�V���̍X�V����
			UpdateMesh();

			//�J�����̍X�V����
			UpdateCamera();

			//���C�g�̍X�V����
			UpdateLight();

			//�e�̍X�V����
			UpdateShadow();

			//�v���C���[�̍X�V����
			UpdatePlayer();

			//�����\�����C���̍X�V����
			UpdateObjectLine();

			//���f���̍X�V����
			UpdateModel();

			//�ǂ̍X�V����
			UpdateWall();

			//�G�t�F�N�g�̍X�V����
			UpdateEffect();

			//�p�[�e�B�N���̍X�V����
			UpdateParticle();

			//�r���{�[�h�̍X�V����
			UpdateBillboard();

			//�e��̍X�V�ݒ�
			UpdateContain();

			//�L�b�`���̍X�V����
			UpdateKitchen();

			//�A�C�e���̍X�V����
			UpdateItem();

			//�v���C���[�̋߂��̃��C�������点�鏈��
			PlayerDistanceModel();

			//�L�b�`���^�C�}�[�̍X�V����
			UpdateKTimer();

			//�J�b�g�^�C�}�[�̍X�V����
			UpdateCTimer();

			//�I�[�_�[�^�C�}�[�̍X�V����
			UpdateOTimer();

			//�����̍X�V����
			UpdateOrder();

			//�����������_���ň�莞�Ԗ��ɐ������鏈��
			RandamOrder();

			//�X�R�A�̍X�V����
			UpdateScore();
		}
		//�Q�[���^�C�}�[�̍X�V����
		UpdateGameTimer();
	}

	//if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A, 0))
	//{
	//	SetMode(MODE_RESULT);
	//}
}

//========================================================
//�Q�[���̕`�揈��
//========================================================
void DrawGame(void)
{	
	//�J�����̐ݒ菈��
	SetCamera();

	////�ǂ̕`�揈��
	DrawWall();

	//////�|���S���̕`�揈��
	//DrawPolygon();

	////���b�V���̕`�揈��
	DrawMesh();

	//�e�̕`�揈��
	DrawShadow();

	//�v���C���[�̕`�揈��
	DrawPlayer();

	//���f���̕`�揈��
	DrawModel();

	////�~���̕`�揈��
	//DrawSphere();

	////�r���{�[�h�̕`�揈��
	//DrawBillboard();

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();

	//�p�[�e�B�N���̂̕`�揈��
	DrawParticle();

	//���C���̕`�揈��
	DrawLine();

	//�����\�����C���̕`�揈��
	DrawObjectLine();

	//�e��̕`��ݒ�
	DrawContain();

	//�A�C�e���̕`�揈��
	DrawItem();

	//�L�b�`���̕`�揈��
	DrawKitchen();

	//�L�b�`���^�C�}�[�̕`�揈��
	DrawKTimer();

	//�J�b�g�^�C�}�[�̕`�揈��
	DrawCTimer();

	//�I�[�_�[�^�C�}�[�̕`�揈��
	DrawOTimer();

	//�����̕`�揈��
	DrawOrder();

	//�Q�[���^�C�}�[�̕`�揈��
	DrawGameTimer();

	//�X�R�A�̕`�揈��
	DrawScore();

	//������ʂ̕`�揈��
	DrawReady();
}