//========================================================
//��̒������Ԃ̃w�b�_�[�t�@�C��
//========================================================
#ifndef _CUTTINGTIMER_H_
#define _CUTTINGTIMER_H_

#define MAX_CUTTINGTIMER (100)

#define CTIMER_WIDTH (8.0f)
#define CTIMER_HEIGHT (3.0f)

#include "main.h"

//=========================================
//�\���̂̐錾
//=========================================
typedef enum
{
	CTIMER_CONTAIN,				//�^�C�}�[�̗e��
	CTIMER_BAR					//�^�C�}�[�̃o�[
}CTIMER_STATE;

typedef struct
{
	D3DXVECTOR3		pos;			//���W
	D3DXVECTOR3		rot;			//�p�x
	D3DCOLOR		col;			//�F
	D3DXMATRIX		mtxWorld;		//���[���h�}�g���b�N�X
	CTIMER_STATE	state;			//�L�b�`���̃X�e�[�g
	bool			bUse;			//�g���Ă��邩
	int				KitchenNumber;	//��ԋ߂������L�b�`���̔ԍ���ۑ�����
}CTIMER;

//�v���g�^�C�v�錾
void InitCTimer(void);
void UninitCTimer(void);
void UpdateCTimer(void);
void DrawCTimer(void);
void SetCTimer(D3DXVECTOR3 pos);
void SetCTimerBar(D3DXVECTOR3 pos);
CTIMER *GetCTimer();

#endif