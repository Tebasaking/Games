//=========================================
//
//	model.h
//	Author : �y���m��
//
//=========================================
#ifndef _TITLEMODEL_H_								
#define _TITLEMODEL_H_							

#define MAX_TITLEMODEL (12)
#define KITCHEN_SIZE (10)
#define DISH_SIZE	(8)
#define MAX_TITLE_TEXTURE (30)

typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 rot;					//����
	D3DXCOLOR	col;					//���f���̐F
	D3DXVECTOR3 move;					//�ړ�
	D3DXVECTOR3 rotDestTitleModel;		//�ړI�̍��W
	D3DXVECTOR3 vtxMinTitleModel;		//���f���̍ŏ��l
	D3DXVECTOR3 vtxMaxTitleModel;		//���f���̍ő�l
	D3DXMATRIX  mtxWorldTitleModel;		//���[���h�}�g���b�N�X
	LPD3DXMESH pMeshTitleModel;			//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMatTitleModel;	//�}�e���A�����ւ̃|�C���^
	LPDIRECT3DTEXTURE9	pTexture[MAX_TITLE_TEXTURE];	// �e�N�X�`���ւ̃|�C���^
	DWORD nNumMatTitleModel;			//�}�e���A�����̐�
	int   Type;							//���f���̃^�C�v
	int	  Shadow;						//���f���̉��ɂ���e
	int	  CookCount;					//�������Ă��鎞��
	float ShadowSize;					//���f���Ɖe�̋��������߂�
	bool  bUse;							//�g�p���Ă��邩���Ă��Ȃ���
	bool  bIsLanding;					//��ɃA�C�e�����Ȃ���
	bool  cook;							//���������ǂ���
	char MODEL_NAME[128];				//�t�@�C���̖��O
}TITLEMODEL;

//=========================================
//�v���g�^�C�v�錾
//=========================================
void InitTitleModel(void);
void UninitTitleModel(void);
void UpdateTitleModel(void);
void DrawTitleModel(void);
void Cutting(void);
TITLEMODEL* GetTitleModel(void);
void SetTitleModel(D3DXVECTOR3 pos, char MODEL_NAME[128], int nCnt, int nType);
float VertexMAXChange(float vtx, float max);
float VertexMINChange(float vtx, float min);
int GetSelectObject();
int GetObjectDistance();

#endif