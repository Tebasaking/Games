#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//マクロ定義
#define MAX_PARTICLE				(1024)				//パーティクルの最大数

//構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;					//位置
	D3DXVECTOR3 move;					//移動量
	D3DXCOLOR col;						//色
	D3DXMATRIX  mtxWorld;				//ワールドマトリックス
	int nType;							//種類
	int nLife;							//寿命
	float fRadius;						//半径
	bool bUse;							//使用しているかどうか
}Particle;

//パーティクルが3Dか2Dか
typedef enum
{
	PARTICLE_3D,
	PARTICLE_2D
}PARTICLESTATE;

//プロトタイプ宣言
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, int nType);
Particle* GetParticle();

#endif // _PARTICLE_H_