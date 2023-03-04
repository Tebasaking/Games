//========================================================
//��̒������Ԃ̃w�b�_�[�t�@�C��
//========================================================
#ifndef _ORDERTIMER_H_
#define _ORDERTIMER_H_

#define MAX_ORDERTIMER (12)

#define OTIMER_WIDTH (8.0f)
#define OTIMER_HEIGHT (3.0f)

#include "main.h"

//=========================================
//�\���̂̐錾
//=========================================
typedef enum
{
	OTIMER_CONTAIN,				//�^�C�}�[�̗e��
	OTIMER_BAR					//�^�C�}�[�̃o�[
}OTIMER_STATE;

typedef struct
{
	D3DXVECTOR3		pos;			//���W
	D3DXVECTOR3		rot;			//�p�x
	D3DCOLOR		col;			//�F
	D3DXMATRIX		mtxWorld;		//���[���h�}�g���b�N�X
	OTIMER_STATE	state;			//�L�b�`���̃X�e�[�g
	int				nNumber;		//�I�[�_�[�̔ԍ��A�^�C�}�[�������Ƃ��Ɏg��
	bool			bUse;			//�g���Ă��邩
	int				KitchenNumber;	//��ԋ߂������L�b�`���̔ԍ���ۑ�����
}OTIMER;

//�v���g�^�C�v�錾
void InitOTimer(void);
void UninitOTimer(void);
void UpdateOTimer(void);
void DrawOTimer(void);
void SetOTimer(D3DXVECTOR3 pos, int nNumber);
void SetOTimerBar(D3DXVECTOR3 pos, int nNumber);
void MoveOTimer(int nNumber);
OTIMER *GetOTimer();

#endif