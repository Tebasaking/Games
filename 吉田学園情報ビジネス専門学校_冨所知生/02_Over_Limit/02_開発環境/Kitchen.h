//=========================================
//
//	model.h
//	Author : �y���m��
//
//=========================================
#ifndef _KITCHEN_H_								
#define _KITCHEN_H_							

#define MAX_KITCHEN (3)
#define MAX_KITCHEN_PARTS (3)

#include "contain.h"

typedef enum
{
	KITCHEN_NONE,							//��������ɉ��������Ă��Ȃ����
	KITCHEN_MATERIAL,						//��������O�A�f�ނ�����Ă��邾��
	KITCHEN_COOK,							//������
	KITCHEN_COMPLETE,						//�����������
	KITCHEN_OVER,							//���M�������Ă�����
	KITCHEN_BURN							//�ł��Ďg���Ȃ��Ȃ������
}KITCHEN_COOKING;

//�v���C���[�̃p�[�c�̍\����
typedef struct
{
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;
	DWORD nNumMat;
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 rot;			//�p�x
	D3DXVECTOR3 posOrigin;		//���̈ʒu
	D3DXVECTOR3 rotOrigin;		//���̊p�x
	D3DXVECTOR3 posDest;		//�ړI�̈ʒu
	D3DXVECTOR3 rotDest;		//�ړI�̌���
	D3DXVECTOR3 vtxMin;			//�v���C���[�̍ŏ��l
	D3DXVECTOR3 vtxMax;			//�v���C���[�̍ő�l
	D3DXVECTOR3 MovePos;		//���[�V�����̂Ƃ���Pos
	D3DXVECTOR3 fFrame;			//�t���[�����ŃA�j���[�V���������������l���i�[����
	bool bUse;					//�g���Ă��邩���Ȃ���
	int nIdxModelParent;		//�e���f���̃C���f�b�N�X
	int nType;					//�p�[�c�̃^�C�v
}KITCHENPARTS;

typedef enum
{
	KITCHEN_NORMAL = 0,						//�A�C�e���̒ʏ���
	KITCHEN_HAVE = 1						//�A�C�e���������Ă��邩�����Ă��Ȃ���
}KITCHEN_STATE;

typedef struct
{
	D3DXVECTOR3 pos;							//�ʒu
	D3DXVECTOR3 rot;							//����
	D3DXVECTOR3 rotOld;							//�v���C���[���u�������̈ʒu��ۑ�����
	D3DXVECTOR3 move;							//�ړ�
	D3DXVECTOR3 rotDestKitchen;					//�ړI�̍��W
	D3DXVECTOR3 vtxMinKitchen;					//���f���̍ŏ��l
	D3DXVECTOR3 vtxMaxKitchen;					//���f���̍ő�l
	D3DXMATRIX  mtxWorldKitchen;				//���[���h�}�g���b�N�X
	LPD3DXMESH pMeshKitchen;					//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMatKitchen;				//�}�e���A�����ւ̃|�C���^
	DWORD nNumMatKitchen;						//�}�e���A�����̐�
	KITCHEN_STATE state;						//�L�b�`���̃X�e�[�g
	KITCHEN_COOKING cook;						//�L�b�`���̕ω�������
	KITCHENPARTS aParts[MAX_KITCHEN_PARTS];		//�L�b�`���̃p�[�c
	ITEMTYPE type;								//�A�C�e���̃^�C�v
	bool  bUse;									//�g�p���Ă��邩���Ă��Ȃ���
	bool  bTimer;								//�L�b�`���^�C�}�[���g�p���Ă��邩���Ȃ���
	float ShadowSize;							//���f���Ɖe�̋��������߂�
	int  Shadow;								//���f���̉��ɂ���e
	char KITCHEN_NAME[128];						//�t�@�C���̖��O
	int CookCount;								//��������
}KITCHEN;

//=========================================
//�v���g�^�C�v�錾
//=========================================
void InitKitchen(void);
void UninitKitchen(void);
void UpdateKitchen(void);
void DrawKitchen(void);
KITCHEN* GetKitchen(void);
void SetKitchen(D3DXVECTOR3 pos, KITCHEN_STATE state);
void TSKitchen(D3DXVECTOR3 pos, char KITCHEN_NAME[128], int nCnt);
int GetSelectKitchen();
int GetKitchenDistance();
float VertexMAXChange(float vtx, float max);
float VertexMINChange(float vtx, float min);
void PlayerDistanceKitchen(void);
void SetKitchenParts(D3DXVECTOR3 pos, char PLAYER_NAME[128], int nCount);
void LetsCooking(void);

#endif