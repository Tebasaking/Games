//=========================================
//
//	shadow.h
//	Author : �y���m��
//
//=========================================
#ifndef _BILLBOARD_H_								
#define _BILLBOARD_H_							

#define MAX_BILLBOARD (100)				//�r���{�[�h�̍ő吔
#define BILLBOARD_SIZE (10.0f)			//�r���{�[�h�̃T�C�Y

typedef struct
{
	D3DXVECTOR3 pos;					//���W
	D3DXVECTOR3 move;					//�ړ�
	D3DXVECTOR3 rot;					//��]
	D3DXCOLOR	col;					//�F
	D3DXMATRIX  mtxWorld;				//���[���h�}�g���b�N�X
	bool bUse;							//�g�p���Ă��邩���Ă��Ȃ���
	float size;							//�r���{�[�h�̃T�C�Y
}Billboard;

//=========================================
//�v���g�^�C�v�錾
//=========================================
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
Billboard* GetBillboard(void);
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					//�r���{�[�h�̐ݒu

#endif
