//=========================================
//
//	shadow.h
//	Author : �y���m��
//
//=========================================
#ifndef _WALL_H_								
#define _WALL_H_							

#include "meshfield.h"

#define MAX_WALL (100)							//�ǂ̍ő吔
#define WALL_SIZE (5.0f * MESH_X_BLOCK)			//�ǂ̃T�C�Y

typedef struct
{
	D3DXVECTOR3 pos;					//���W
	D3DXVECTOR3 move;					//�ړ�
	D3DXVECTOR3 rot;					//��]
	D3DXCOLOR	col;					//�F
	D3DXMATRIX  mtxWall;				//���[���h�}�g���b�N�X
	bool bUse;							//�g�p���Ă��邩���Ă��Ȃ���
	float size;							//�ǂ̃T�C�Y
}Wall;

//=========================================
//�v���g�^�C�v�錾
//=========================================
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
Wall* GetWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot , D3DXCOLOR col);					//�ǂ̐ݒu

#endif
