#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//�}�N����`
#define MAX_PARTICLE				(1024)				//�p�[�e�B�N���̍ő吔

//�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 move;					//�ړ���
	D3DXCOLOR col;						//�F
	D3DXMATRIX  mtxWorld;				//���[���h�}�g���b�N�X
	int nType;							//���
	int nLife;							//����
	float fRadius;						//���a
	bool bUse;							//�g�p���Ă��邩�ǂ���
}Particle;

//�p�[�e�B�N����3D��2D��
typedef enum
{
	PARTICLE_3D,
	PARTICLE_2D
}PARTICLESTATE;

//�v���g�^�C�v�錾
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, int nType);
Particle* GetParticle();

#endif // _PARTICLE_H_