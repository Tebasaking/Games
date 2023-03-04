//========================================================
//�Q�[����ʂ̃w�b�_�[�t�@�C��
//========================================================
#pragma once
#ifndef _GAME_H_
#define _GAME_H_

#define NUM_ORDER (5)
#define ORDER_SIZE (150.0f)

#include "main.h"
#include "contain.h"

typedef struct
{
	D3DXVECTOR3 pos;		//���W
	D3DXCOLOR	col;		//�F
	bool		bUse;		//�g���Ă��邩���Ȃ���
	ITEMTYPE	nType;		//�����̎��
	int			nNumber;	//�I�[�_�[�̔z��̔ԍ������锠
	int			nLimit;		//����
}ORDER;

//�v���g�^�C�v�錾
void InitOrder(void);
void UninitOrder(void);
void UpdateOrder(void);
void DrawOrder(void);
void SetOrder(D3DXVECTOR3 pos, ITEMTYPE Type);
void RandamOrder(void);
ORDER *GetOrder(void);
void SubOrderCount();
void MoveOrder(int nNumber);


#endif