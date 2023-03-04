//=========================================
//
//	meshfield.h
//	Author : 冨所知生
//
//=========================================
#ifndef _MESH_H_								
#define _MESH_H_							

#define MESH_SIZE (10.0f)
#define MESH_X_BLOCK (10)
#define MESH_Z_BLOCK (10)

//=========================================
//プロトタイプ宣言
//=========================================
void InitMesh(void);
void UninitMesh(void);
void UpdateMesh(void);
void DrawMesh(void);

#endif