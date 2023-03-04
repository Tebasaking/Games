//========================================================
//�Q�[���J�n�̍��}�̃w�b�_�[�t�@�C��
//========================================================
#pragma once
#ifndef _READY_H_
#define _READY_H_

#define NUM_READY (7)

typedef struct
{
	D3DXVECTOR3 pos;		//���W
	D3DXCOLOR	col;		//�F
	bool		bUse;		//�g���Ă��邩���Ȃ���
	int			nType;		//�^�C�v
}READY;

//�v���g�^�C�v�錾
void InitReady(void);
void UninitReady(void);
void UpdateReady(void);
void DrawReady(void);
void SetReady(int nType);
bool GetReady(void);


#endif