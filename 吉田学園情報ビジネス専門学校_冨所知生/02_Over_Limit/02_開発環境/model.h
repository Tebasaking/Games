//=========================================
//
//	model.h
//	Author : �y���m��
//
//=========================================
#ifndef _MODEL_H_								
#define _MODEL_H_							

#define MAX_MODEL (20)
#define KITCHEN_SIZE (10)
#define DISH_SIZE	(8)
#define MAX_TEXTURE (10)

#include "contain.h"

typedef enum
{
	MODEL_FOOD1_BOX = 0,				//�H�ו��̔�1
	MODEL_FOOD2_BOX = 4,				//�H�ו��̔�2
	MODEL_KITCHEN = 1,					//������
	MODEL_CONTAIN = 2,
	MODEL_COUNTER = 3					//�J�E���^�[
}TYPE;

typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 rot;					//����
	D3DXCOLOR	col;					//���f���̐F
	D3DXVECTOR3 move;					//�ړ�
	D3DXVECTOR3 rotDestModel;			//�ړI�̍��W
	D3DXVECTOR3 vtxMinModel;			//���f���̍ŏ��l
	D3DXVECTOR3 vtxMaxModel;			//���f���̍ő�l
	D3DXMATRIX  mtxWorldModel;			//���[���h�}�g���b�N�X
	LPD3DXMESH pMeshModel;				//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMatModel;			//�}�e���A�����ւ̃|�C���^
	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DTEXTURE9	pTexture[MAX_TEXTURE];
	DWORD nNumMatModel;					//�}�e���A�����̐�
	int  Type;							//���f���̃^�C�v
	int	  Shadow;						//���f���̉��ɂ���e
	int	  CookCount;					//�������Ă��鎞��
	float ShadowSize;					//���f���Ɖe�̋��������߂�
	bool  bUse;							//�g�p���Ă��邩���Ă��Ȃ���
	bool  bIsLanding;					//��ɃA�C�e�����Ȃ���
	bool  cook;							//���������ǂ���
	char MODEL_NAME[128];				//�t�@�C���̖��O
}MODEL;

//=========================================
//�v���g�^�C�v�錾
//=========================================
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void UpdateHot(void);
void DrawModel(void);
void PlayerDistanceModel(void);
void Cutting(void);
MODEL* GetModel(void);
void SetModel(D3DXVECTOR3 pos, char MODEL_NAME[128], int nCnt ,int nType);
void CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 size);
float VertexMAXChange(float vtx, float max);
float VertexMINChange(float vtx, float min);
int GetSelectObject();
int GetObjectDistance();
void SubDContain();

#endif