//=========================================
// �X�R�A�̃w�b�_�[�t�@�C��
//=========================================

#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

#define MAX_SCORE (8)
#define TEXTURE_SIZE (0.08333f)		//�����ꎚ�̃T�C�Y

//�v���g�^�C�v�錾
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore);
void AddScore(int nValue);
int GetScore(void);

#endif