//=========================================
//
//	�����L���O�̃w�b�_�[�t�@�C��
//	Author : �y���m��
//
//=========================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"

//------------------------------------
//�}�N����`
//------------------------------------
#define MAX_RANK	(3)	//�����N��
#define MAX_RANKSCORE	(3)	//����
#define FILE_NAME	"data/txt/ranking.txt"

//------------------------------------
//�v���g�^�C�v�錾
//------------------------------------
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void ResetRanking(void);
void SaveRanking(void);
void SetRanking(int nScore);

#endif // !_Ranking_H_