//=========================================
//
//	sphere.h
//	Author : 冨所知生
//
//=========================================
#ifndef _SPHERE_H_								
#define _SPHERE_H_							

#define SPHERE_SIZE (10.0f)
#define SPHERE_X_BLOCK (20)
#define SPHERE_Z_BLOCK (20)

//=========================================
//プロトタイプ宣言
//=========================================
void InitSphere(void);
void UninitSphere(void);
void UpdateSphere(void);
void DrawSphere(void);

#endif