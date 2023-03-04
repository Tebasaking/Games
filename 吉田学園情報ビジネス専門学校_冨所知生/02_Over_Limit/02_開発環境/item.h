//=========================================
//
//	item.h
//	Author : �y���m��
//
//=========================================
#ifndef _ITEM_H_								
#define _ITEM_H_							

#define MAX_ITEM (1000)

#include "contain.h"

typedef enum
{
	ITEM_NORMAL = 0,						//�A�C�e���̒ʏ���
	ITEM_HAVE = 1							//�A�C�e���������Ă��邩�����Ă��Ȃ���
}ITEM_STATE;

typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 rot;					//����
	D3DXVECTOR3 move;					//�ړ�
	D3DXVECTOR3 rotDestItem;			//�ړI�̍��W
	D3DXVECTOR3 vtxMinItem;				//���f���̍ŏ��l
	D3DXVECTOR3 vtxMaxItem;				//���f���̍ő�l
	D3DXMATRIX  mtxWorldItem;			//���[���h�}�g���b�N�X
	LPD3DXMESH pMeshItem;				//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMatItem;			//�}�e���A�����ւ̃|�C���^
	DWORD nNumMatItem;					//�}�e���A�����̐�
	ITEM_STATE state;					//�A�C�e���̃X�e�[�g
	ITEMTYPE type;						//�A�C�e���̃^�C�v
	bool  bUse;							//�g�p���Ă��邩���Ă��Ȃ���
	bool  bCook;						//���������ǂ���
	bool  bCut;							//�J�b�g����Ă��邩���Ȃ���
	float ShadowSize;					//���f���Ɖe�̋��������߂�
	int  Shadow;						//���f���̉��ɂ���e
	int  CuttingTime;					//�A�C�e���̒�������(��̂�)
	char ITEM_NAME[128];				//�t�@�C���̖��O
}ITEM;
//=========================================
//�v���g�^�C�v�錾
//=========================================
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
ITEM* GetItem(void);
void SetItem(D3DXVECTOR3 pos, char ITEM_NAME[128], ITEM_STATE state, ITEMTYPE type, bool cut);
void CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 size);
void SetMoveItem(D3DXVECTOR3 pos);
float VertexMAXChange(float vtx, float max);
float VertexMINChange(float vtx, float min);
void PlayerDistanceItem(void);
void KitchenInput(void);
int GetSelectItem();

#endif