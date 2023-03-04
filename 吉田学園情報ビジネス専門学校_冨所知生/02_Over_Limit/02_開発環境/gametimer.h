//=========================================
//
//	�Q�[���^�C�}�[�̓��o�͏���
//	Author : �y���m��
//
//=========================================
#ifndef _GAMETIMER_H_								
#define _GAMETIMER_H_							

#include "main.h"

#define MAX_GAMETIMER (36)

typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	D3DXCOLOR   col;					//�F	
	D3DXMATRIX  mtxWorld;				//���[���h�}�g���b�N�X
	LPD3DXMESH  pMeshGameTimer;				//���b�V�����ւ̃|�C���^
	bool  bUse;							//�g�p���Ă��邩���Ă��Ȃ���
}GAMETIMER;

//=========================================
//�v���g�^�C�v�錾
//=========================================
void InitGameTimer(void);
void UninitGameTimer(void);
void UpdateGameTimer(void);
void DrawGameTimer(void);
void SetGameTimer(int nGameTimer);
void SubGameTimer(int nValue);
bool GetGTimer(void);
int GetGameTimer(void);

#endif