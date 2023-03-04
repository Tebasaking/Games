//========================================================
//�L�b�`���^�C�}�[�̃w�b�_�[�t�@�C��
//========================================================
#ifndef _KITCHENTIMER_H_
#define _KITCHENTIMER_H_

#define MAX_KITCHENTIMER (100)

#define KTIMER_WIDTH (8.0f)
#define KTIMER_HEIGHT (3.0f)

#include "main.h"

//=========================================
//�\���̂̐錾
//=========================================
typedef enum
{
	KTIMER_CONTAIN,				//�^�C�}�[�̗e��
	KTIMER_BAR					//�^�C�}�[�̃o�[
}KTIMER_STATE;

typedef struct
{
	D3DXVECTOR3		pos;			//���W
	D3DXVECTOR3		rot;			//�p�x
	D3DCOLOR		col;			//�F
	D3DXMATRIX		mtxWorld;		//���[���h�}�g���b�N�X
	KTIMER_STATE	state;			//�L�b�`���̃X�e�[�g
	bool			bUse;			//�g���Ă��邩
	int				KitchenNumber;	//��ԋ߂������L�b�`���̔ԍ���ۑ�����
}KTIMER;

//�v���g�^�C�v�錾
void InitKTimer(void);
void UninitKTimer(void);
void UpdateKTimer(void);
void DrawKTimer(void);
void SetKTimer(D3DXVECTOR3 pos);
void SetKTimerBar(D3DXVECTOR3 pos);
KTIMER *GetKTimer();

#endif