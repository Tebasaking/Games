//=========================================
//
//	shadow.h
//	Author : �y���m��
//
//=========================================
#ifndef _SHADOW_H_								
#define _SHADOW_H_							

#define MAX_SHADOW (100)				//�e�̍ő吔
#define SHADOW_SIZE (1.5f)

typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 move;					//�ړ�
	D3DXVECTOR3 rot;					//��]
	D3DXMATRIX  mtxShadow;				//���[���h�}�g���b�N�X
	bool bUse;							//�g�p���Ă��邩���Ă��Ȃ���
	float size;							//�e�̃T�C�Y
}Shadow;

//=========================================
//�v���g�^�C�v�錾
//=========================================
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
Shadow* GetShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);						//�e�̐ݒu
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos, float nSize);				//���f���ɉ����ĉe�̈ʒu��ς��鏈��

#endif