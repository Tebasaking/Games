//=========================================
//
//	objectline.h
//	Author : �y���m��
//
//=========================================
#ifndef _OBJECTLINE_H_								
#define _OBJECTLINE_H_							

#define MAX_OBJECTLINE (36)

typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	D3DXCOLOR   col;					//�F	
	D3DXMATRIX  mtxWorld;				//���[���h�}�g���b�N�X
	LPD3DXMESH  pMeshObjectLine;				//���b�V�����ւ̃|�C���^
	bool  bUse;							//�g�p���Ă��邩���Ă��Ȃ���
}OBJECTLINE;

//=========================================
//�v���g�^�C�v�錾
//=========================================
void InitObjectLine(void);
void UninitObjectLine(void);
void UpdateObjectLine(void);
void DrawObjectLine(void);
void SetObjectLine(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 start, D3DXVECTOR3 end);

#endif