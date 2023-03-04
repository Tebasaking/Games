//=========================================
//
//	player.h
//	Author : �y���m��
//
//=========================================
#ifndef _PLAYER_H_								
#define _PLAYER_H_							

#define MAX_PLAYER (1)
#define MAX_PARTS (2)
#define PLAYER_MOVE (1.0f)
#define MAX_KEY	(2)
#define MAX_KEY_SET (3)
#define MAX_ANIMATION (3)

//�v���C���[�̏��
typedef enum
{
	PLAYER_NORMAL,
	PLAYER_HAVE,
	PLAYER_CUTTING,
	PLAYER_MAX
}PLAYERSTATE;

//�v���C���[�̃p�[�c�̍\����
typedef struct
{
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;
	DWORD nNumMat;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 move;			//�v���C���[�̈ړ���
	D3DXVECTOR3 rot;
	D3DXVECTOR3 posOrigin;		//���̈ʒu
	D3DXVECTOR3 rotOrigin;		//���̊p�x
	D3DXVECTOR3 posDest;		//�ړI�̈ʒu
	D3DXVECTOR3 rotDest;		//�ړI�̌���
	D3DXVECTOR3 vtxMin;			//�v���C���[�̍ŏ��l
	D3DXVECTOR3 vtxMax;			//�v���C���[�̍ő�l
	D3DXVECTOR3 MovePos;		//���[�V�����̂Ƃ���Pos
	D3DXVECTOR3 fFrame;			//�t���[�����ŃA�j���[�V���������������l���i�[����
	int nIdxModelParent;		//�e���f���̃C���f�b�N�X
	int nType;					//�p�[�c�̃^�C�v
}ModelParts;

//�v���C���[�̍\����
typedef struct
{
	ModelParts aModel[MAX_PARTS];		//���f���̃p�[�c�̐�
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 posOld;					//���X�����ʒu
	D3DXVECTOR3 rot;					//����
	D3DXVECTOR3 move;					//�ړ�
	D3DXVECTOR3 rotDestPlayer;			//�ړI�̍��W
	D3DXVECTOR3 vtxMinPlayer;			//�v���C���[�̍ŏ��l
	D3DXVECTOR3 vtxMaxPlayer;			//�v���C���[�̍ő�l
	D3DXVECTOR3 size;					//�v���C���[�̃T�C�Y
	D3DXMATRIX  mtxWorldPlayer;			//���[���h�}�g���b�N�X
	LPD3DXMESH pMeshPlayer;				//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMatPlayer;		//�}�e���A�����ւ̃|�C���^
	DWORD nNumMatPlayer;				//�}�e���A�����̐�
	PLAYERSTATE state;					//�v���C���[�̃X�e�[�g
	bool  bUse;							//�g�p���Ă��邩���Ă��Ȃ���
	float ShadowSize;					//���f���Ɖe�̋��������߂�
	int  Shadow;						//���f���̉��ɂ���e
	int  Number;						//�ǂ̃p�[�c�𓮂�����
	char PLAYER_NAME[128];				//�t�@�C���̖��O
}PLAYER;

//�L�[���Ƃ̍\����
typedef struct
{
	D3DXVECTOR3 pos;					//���W
	D3DXVECTOR3 rot;					//��]
}Key;

//�L�[�̈�A�̗�����Ǘ�����\����
typedef struct
{
	float nFRAME;						//���݂̃t���[����
	Key aKey[MAX_KEY];					//�L�[�̍\���̂̔z��
}KeySet;

//�A�j���[�V�����̈�A�̗�����Ǘ�����\����
typedef struct
{
	bool bLOOP;							//���[�v�����邩���Ȃ���
	int	 nNUM_KEY;						//�L�[�̌�
	KeySet aKeySet[MAX_KEY_SET];		//�L�[�̈�A�̍\���̂̔z��
}MotionSet;

//=========================================
//�v���g�^�C�v�錾
//=========================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER* GetPlayer(void);
void SetPlayer(D3DXVECTOR3 pos);
void SetParts(D3DXVECTOR3 pos, char PLAYER_NAME[128],int nCnt);
void LoadAnimation(int AnimNumber, int KeyNumber, int Number, bool bLoop, int NUM_KEY, int FRAME, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void MotionPlayer(int nCntMotionSet);
void Cutting(void);
MotionSet *GetMotionSet(void);

#endif