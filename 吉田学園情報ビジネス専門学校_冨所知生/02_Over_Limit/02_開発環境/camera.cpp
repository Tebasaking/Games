//=========================================
//
//	�J�����̐ݒu�Ɛ���Ȃ�
//	Author : �y���m��
//
//=========================================
#include "main.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "fade.h"

//------------------------------------
// �O���[�o���ϐ�
//------------------------------------
Camera g_camera;	// �J�������
float fLengthX;
float fLengthY;
float fLengthZ;
int   AfkCheck;		//���f���𓮂����ĂȂ����Ԃ��v��
//=========================================
// ����������
//=========================================
void InitCamera(D3DXVECTOR3 posV , D3DXVECTOR3 posR)
{
	// ���_�E�����_�E�������ݒ肷��
	g_camera.posV = posV;									//���_
	g_camera.posR = posR;									//�����_
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			//�x�N�g��
	g_camera.rot = D3DXVECTOR3(0.0f , 0.0f, 0.0f);			//�p�x
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posVDis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�����̎Z�o
	fLengthX = g_camera.posV.x - g_camera.posR.x;			//x^2
	fLengthY = g_camera.posV.y - g_camera.posR.y;			//z^2
	fLengthZ = g_camera.posV.z - g_camera.posR.z;			//y^2
	
	//���u���Ă邩�̌��o
	AfkCheck = 0;

	//�����_�̌�����ݒ�
	g_camera.rot.x = atan2f(fLengthY, fLengthZ);

	//�Z�o
	g_camera.fDistance = sqrtf((fLengthX * fLengthX) + (fLengthZ * fLengthZ));		//����
	g_camera.fDistance = sqrtf((fLengthY * fLengthY) + (g_camera.fDistance * g_camera.fDistance));	//����2
}

//=========================================
// �I������
//=========================================
void UninitCamera(void)
{
}

//=========================================
// �X�V����
//=========================================
void UpdateCamera(void)
{
	PLAYER *pPlayer = GetPlayer();

	//�ړI�̊p�x�̐ݒ�
	g_camera.rotDest.y = pPlayer->rot.y + D3DX_PI;

	////�����_�̐���
	//{
	//	if (GetKeyboardPress(DIK_Z))
	//	{
	//		g_camera.rot.y -= 0.01f;
	//	}
	//	else if (GetKeyboardPress(DIK_C))
	//	{
	//		g_camera.rot.y += 0.01f;
	//	}
	//	else if (GetKeyboardPress(DIK_U))
	//	{// ��Ɉړ�����
	//		g_camera.rot.x -= 0.01f;
	//	}
	//	else if (GetKeyboardPress(DIK_J))
	//	{// ���Ɉړ�����
	//		g_camera.rot.x += 0.01f;
	//	}
	//}

	//{
	//	//���_�̈ړ�
	//	if (GetKeyboardPress(DIK_UP))
	//	{//�O�Ɉړ�����
	//		g_camera.posV.x += sinf(g_camera.rot.y) * 0.5f;
	//		g_camera.posV.z += cosf(g_camera.rot.y) * 0.5f;
	//	}
	//	else if (GetKeyboardPress(DIK_DOWN))
	//	{//���Ɉړ�����
	//		g_camera.posV.x -= sinf(g_camera.rot.y) * 0.5f;
	//		g_camera.posV.z -= cosf(g_camera.rot.y) * 0.5f;
	//	}
	//	else if (GetKeyboardPress(DIK_LEFT))
	//	{//���Ɉړ�����
	//		g_camera.posV.x -= sinf(D3DX_PI * 0.5f + g_camera.rot.y) * 0.5f;
	//		g_camera.posV.z -= cosf(D3DX_PI * 0.5f + g_camera.rot.y) * 0.5f;
	//	}
	//	else if (GetKeyboardPress(DIK_RIGHT))
	//	{//�E�Ɉړ�����
	//		g_camera.posV.x += sinf(D3DX_PI * 0.5f + g_camera.rot.y) * 0.5f;
	//		g_camera.posV.z += cosf(D3DX_PI * 0.5f + g_camera.rot.y) * 0.5f;
	//	}
	//	if (GetKeyboardPress(DIK_N))
	//	{
	//		g_camera.posV.y -= 0.1f;
	//	}
	//	else if (GetKeyboardPress(DIK_M))
	//	{
	//		g_camera.posV.y += 0.1f;
	//	}
	//}

	//{
	//	//���_�̐���
	//	if (GetKeyboardPress(DIK_Q))
	//	{
	//		g_camera.rot.y -= 0.01f;
	//	}
	//	else if (GetKeyboardPress(DIK_E))
	//	{
	//		g_camera.rot.y += 0.01f;
	//	}
	//}

	//�p�x�̖ړI�n�̐��K��
	if (g_camera.rotDest.y - g_camera.rot.y > D3DX_PI)
	{
		g_camera.rotDest.y -= D3DX_PI * 2.0f;
	}
	else if (g_camera.rotDest.y - g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rotDest.y += D3DX_PI * 2.0f;
	}

	////�J�����̌����Ă���������v���C���[�̌����Ă�������Ɋ񂹂�
	//if(!GetKeyboardPress(DIK_W) && !GetKeyboardPress(DIK_A) && !GetKeyboardPress(DIK_S) && !GetKeyboardPress(DIK_D))
	//{
	//	//AFK�����m��������Z
	//	AfkCheck++;

	//	if (AfkCheck >= 180)
	//	{
	//		g_camera.rot.y += (g_camera.rotDest.y - g_camera.rot.y) * 0.05f;
	//	}
	//}
	//else
	//{
	//	AfkCheck = 0;
	//}

	//�v���C���[�̍��W��������
	g_camera.posVDis = pPlayer->pos;

	//���W�̕␳���s��
	g_camera.posVDis.x = NormalizePos(g_camera.posVDis.x);
	g_camera.posVDis.y = NormalizePos(g_camera.posVDis.y);
	g_camera.posVDis.z = NormalizePos(g_camera.posVDis.z);

	//�p�x�̐��K��
	if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y -= D3DX_PI * 2.0f;
	}
	else if (g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rot.y += D3DX_PI * 2.0f;
	}

	//�p�x�̐��K��
	if (g_camera.rot.x > D3DX_PI)
	{
		g_camera.rot.x -= D3DX_PI * 2.0f;
	}
	else if (g_camera.rot.x < -D3DX_PI)
	{
		g_camera.rot.x += D3DX_PI * 2.0f;
	}

	//�ړI�̒����_�̐ݒ�
	/*g_camera.posRDest.x = pPlayer->pos.x * 0.1f ;
	g_camera.posRDest.z = pPlayer->pos.z * 0.1f ;*/

	//�ړI�̎��_�̐ݒ�
	//g_camera.posVDest.x = pPlayer->pos.x * 0.1f;
	g_camera.posVDest.y = g_camera.posVDis.x / 5.0f + g_camera.posVDis.z / 5.0f + CAMERA_HEIGHT;		//�}�W�b�N�i���o�[
	//g_camera.posVDest.z = pPlayer->pos.z * 0.1f;

	//���_�̌�������
	//g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.1f;.
	//g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.1f;

	/*g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.1f;*/
	g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * 0.1f;
	//g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.1f;
}

//=========================================
// �ݒ菈��
//=========================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView, &g_camera.posV, &g_camera.posR, &g_camera.vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);	// �r���[���W�s��̐ݒ�

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),	// ����p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	// �A�X�y�N�g��
		0.1f, 10000000.0f);	// �ǂ�����(�j�A)(��T����)�ǂ��܂�(�t�@�[)(��U����)��\�����邩�ݒ� 

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
}

//=========================================
// �J�����̏��̎擾
//=========================================
Camera* GetCamera()
{
	return &g_camera;
}

//=========================================
// pos�̐��K��
//=========================================
float NormalizePos(float fPos)
{
	if (fPos < 0)
	{
		fPos = -fPos;
	}
	return fPos;
}