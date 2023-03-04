//=========================================
// result.h
//=========================================
#ifndef _Result_H_
#define _Result_H_

#include"main.h"

typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffResultScore;		//���_�o�b�t�@
	D3DXVECTOR3 pos;
	int nType;
	bool bUse;
}RESULT;

//�v���g�^�C�v�錾
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
void SetResult(int nType,int nScore);

#endif