//=========================================
//
//	polygon.h
//	Author : 冨所知生
//
//=========================================
#ifndef _POLYGON_H_								
#define _POLYGON_H_							

#define POLYGON_SIZE (10.0f)

//=========================================
//プロトタイプ宣言
//=========================================
void InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);
void *GetPolygon(void);

#endif