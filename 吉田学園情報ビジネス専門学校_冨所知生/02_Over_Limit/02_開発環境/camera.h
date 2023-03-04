//=========================================
//
//	camera.h
//	Author : �y���m��
//
//=========================================
#ifndef _CAMERA_H_
#define _CAMERA_H_
#define MAX_SPEED (1.0f)
#define CAMERA_HEIGHT (100.0f)

typedef struct
{
	D3DXVECTOR3 posV;			// ���_
	D3DXVECTOR3 posR;			// �����_
	D3DXVECTOR3 vecU;			// ������x�N�g��
	D3DXVECTOR3 posVDest;		//�ړI�̎��_
	D3DXVECTOR3 posRDest;		//�ړI�̒����_
	D3DXVECTOR3 posVDis;		//���S����v���C���[�܂ł̋����𐳋K�����邽�߂̊֐�
	D3DXVECTOR3 rotDest;		//�ړI�̊p�x
	D3DXVECTOR3 rot;			//����
	D3DXMATRIX mtxProjection;	// �v���W�F�N�g�}�g���b�N�X
	D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X
	float fDistance;			//���_���璍���_�̋���
}Camera;

//=========================================
// �v���g�^�C�v�錾
//=========================================
void InitCamera(D3DXVECTOR3 posV, D3DXVECTOR3 posR);	// �|���S���̏���������
void UninitCamera(void);								// �|���S���̏I������
void UpdateCamera(void);								// �|���S���̍X�V����
void SetCamera(void);									// �|���S���̕`�揈��
Camera* GetCamera();									//�J�����̏��̎擾
float NormalizePos(float fPos);							//���W�̕␳

#endif

