//=========================================
//
//	model.h
//	Author : �y���m��
//
//=========================================
#ifndef _CONTAIN_H_								
#define _CONTAIN_H_							

#define MAX_CONTAIN (3)

//=========================================
//�A�C�e���̎�ނ̐錾
//=========================================
typedef enum
{
	ITEM_NULL = 0,
	ITEM_MEAT = 1 << 0,
	ITEM_CABBAGE = 1 << 1,
	ITEM_PANS = 1 << 2,
}ITEMTYPE;

//=========================================
//�\���̂̐錾
//=========================================
typedef enum
{
	CONTAIN_NONE,							//��������Ă��Ȃ����
	CONTAIN_COMPLETE,						//�����������
}CONTAIN_COOKING;

typedef enum
{
	CONTAIN_NORMAL = 0,						//�A�C�e���̒ʏ���
	CONTAIN_HAVE = 1						//�A�C�e���������Ă��邩�����Ă��Ȃ���
}CONTAIN_STATE;

typedef enum
{
	MEAT,								//��
	CABBAGE,							//�L���x�c
	PANS,								//�p���Y
	HAMBURGER							//�n���o�[�K�[
}COOK;

typedef struct
{
	int meat;							//��
	int cabbage;						//�L���x�c
	int vegetable;						//����u��
}FOOD_COUNT;

typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 rot;					//����
	D3DXVECTOR3 move;					//�ړ�
	D3DXVECTOR3 rotDestContain;			//�ړI�̍��W
	D3DXVECTOR3 vtxMinContain;			//���f���̍ŏ��l
	D3DXVECTOR3 vtxMaxContain;			//���f���̍ő�l
	D3DXMATRIX  mtxWorldContain;		//���[���h�}�g���b�N�X
	LPD3DXMESH pMeshContain;			//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMatContain;		//�}�e���A�����ւ̃|�C���^
	DWORD nNumMatContain;				//�}�e���A�����̐�
	CONTAIN_STATE state;				//�L�b�`���̃X�e�[�g
	CONTAIN_COOKING cook;				//�L�b�`���̕ω�������
	COOK  cooking;						//�ł��������̏��
	ITEMTYPE type;						//�A�C�e���̎��
	bool  bUse;							//�g�p���Ă��邩���Ă��Ȃ���
	float ShadowSize;					//���f���Ɖe�̋��������߂�
	int  Shadow;						//���f���̉��ɂ���e
	int	 food;							//�A�C�e���̍ŏI�I�Ȏ��
	char CONTAIN_NAME[128];				//�t�@�C���̖��O
	int CookCount;						//��������
}CONTAIN;

//=========================================
//�v���g�^�C�v�錾
//=========================================
void InitContain(void);
void UninitContain(void);	
void UpdateContain(void);
void DrawContain(void);
CONTAIN* GetContain(void);
FOOD_COUNT* GetFoodCount(void);
void SetContain(D3DXVECTOR3 pos, char CONTAIN_NAME[128], CONTAIN_STATE state);
void TSContain(D3DXVECTOR3 pos, CONTAIN_STATE state, CONTAIN_COOKING cook, ITEMTYPE type);
void CollisionContain(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 size);
int GetSelectContain();
int GetContainDistance();
float VertexMAXChange(float vtx, float max);
float VertexMINChange(float vtx, float min);
void PlayerDistanceContain(void);
void LetsCooking(void);
void Calculation(ITEMTYPE);
void UninitCalculation();
bool UseFood(ITEMTYPE type, unsigned int dish);

#endif