//========================================================
//�^�C�g����ʂ̃w�b�_�[�t�@�C��
//========================================================
#pragma once
#ifndef _TITLE_H_
#define _TITLE_H_

#define NUM_TITLE (7)

#include "main.h"

//=========================================
//�\���̂̐錾
//=========================================
typedef enum
{
	GAME = 0,			//�Q�[�����n�߂�
	TUTORIAL = 1,		//�`���[�g���A�����n�߂�
	SHUTDOWN = 2		//�Q�[������߂�
}TITLE_SELECT;

//�v���g�^�C�v�錾
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif