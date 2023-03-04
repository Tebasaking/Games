//=========================================
//
//	line.h
//	Author : �y���m��
//
//=========================================
#ifndef _LINE_H_								
#define _LINE_H_							

#define MAX_LINE (1000)

typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	D3DXCOLOR   col;					//�F	
	D3DXMATRIX  mtxWorld;				//���[���h�}�g���b�N�X
	LPD3DXMESH  pMeshLine;				//���b�V�����ւ̃|�C���^
	bool  bUse;							//�g�p���Ă��邩���Ă��Ȃ���
}LINE;

//=========================================
//�v���g�^�C�v�錾
//=========================================
void InitLine(void);
void UninitLine(void);
void DrawLine(void);
void SetLine(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 start, D3DXVECTOR3 end);

#endif