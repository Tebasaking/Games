//**************************************************************************************************
//
// vZ(calculation.h)
// AutherFϊ±l
//
//**************************************************************************************************
#ifndef _CALCULATION_H_			// ±Μ}Nθ`ͺ³κΔΘ©Α½η
#define _CALCULATION_H_			// ρdCN[hh~Μ}Nθ`

//***************************************************************
// vg^CvιΎ
//***************************************************************
// §δΦ
D3DXVECTOR3	WorldCastVtx(D3DXVECTOR3 vtx, D3DXVECTOR3 FormerPos, D3DXVECTOR3 FormerRot);				// [hΐWΙLXg
D3DXVECTOR3	WorldCastVtx(D3DXVECTOR3 vtx, D3DXVECTOR3 FormerPos, D3DXQUATERNION FormeQuaternion);		// [hΐWΙLXg
float RotNormalization(float fRot);																		// pxΜ³K»

#endif
