//***************************************************************************
//
// vZ(calculation.cpp)
// AutherFú±l
//
//***************************************************************************

//***************************************************************************
// CN[h
//***************************************************************************
#include "main.h"
#include "calculation.h"

//===========================================================================
// [hÀWÖÌLXg
// Author : ú±l
// Tv : pos,rotÌsñvZðs¢A[JÀWð[hÀWÉÏ··é
//===========================================================================
D3DXVECTOR3	WorldCastVtx(D3DXVECTOR3 vtx, D3DXVECTOR3 FormerPos, D3DXVECTOR3 FormerRot)
{
	// Ïé¾
	D3DXMATRIX		mtxWorldVtx;				// [h}gbNX
	D3DXMATRIX		mtxRot, mtxTrans;			// vZp}gbNX

	// [h}gbNXÌú»
	// sñú»Ö(æêøÌ[sñ]ð[PÊsñ]Éú»)
	D3DXMatrixIdentity(&mtxWorldVtx);

	// Êuð½f
	// sñÚ®Ö (æêøÉX,Y,ZûüÌÚ®sñðì¬)
	D3DXMatrixTranslation(&mtxTrans, vtx.x, vtx.y, vtx.z);
	D3DXMatrixMultiply(&mtxWorldVtx, &mtxWorldVtx, &mtxTrans);		// sñ|¯ZÖ

	// ü«Ì½f
	// sññ]Ö (æêøÉ[[(y)sb`(x)[(z)]ûüÌñ]sñðì¬)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, FormerRot.y, FormerRot.x, FormerRot.z);

	// sñ|¯ZÖ (æñø * æOøðæêøÉi[)
	D3DXMatrixMultiply(&mtxWorldVtx, &mtxWorldVtx, &mtxRot);

	// Êuð½f
	// sñÚ®Ö (æêøÉX,Y,ZûüÌÚ®sñðì¬)
	D3DXMatrixTranslation(&mtxTrans, FormerPos.x, FormerPos.y, FormerPos.z);
	D3DXMatrixMultiply(&mtxWorldVtx, &mtxWorldVtx, &mtxTrans);		// sñ|¯ZÖ

	return D3DXVECTOR3(mtxWorldVtx._41, mtxWorldVtx._42, mtxWorldVtx._43);
}

D3DXVECTOR3 WorldCastVtx(D3DXVECTOR3 vtx, D3DXVECTOR3 FormerPos, D3DXQUATERNION FormeQuaternion)
{
	// Ïé¾
	D3DXMATRIX		mtxWorldVtx;				// [h}gbNX
	D3DXMATRIX		mtxRot, mtxTrans;			// vZp}gbNX

	// [h}gbNXÌú»
	// sñú»Ö(æêøÌ[sñ]ð[PÊsñ]Éú»)
	D3DXMatrixIdentity(&mtxWorldVtx);

	// Êuð½f
	// sñÚ®Ö (æêøÉX,Y,ZûüÌÚ®sñðì¬)
	D3DXMatrixTranslation(&mtxTrans, vtx.x, vtx.y, vtx.z);
	D3DXMatrixMultiply(&mtxWorldVtx, &mtxWorldVtx, &mtxTrans);		// sñ|¯ZÖ

	// NH[^jIÌgpµ½p¨ÌÝè
	D3DXMatrixRotationQuaternion(&mtxRot, &FormeQuaternion);		// NI[^jIÉæésññ]

	// sñ|¯ZÖ (æñø * æOøðæêøÉi[)
	D3DXMatrixMultiply(&mtxWorldVtx, &mtxWorldVtx, &mtxRot);

	// Êuð½f
	// sñÚ®Ö (æêøÉX,Y,ZûüÌÚ®sñðì¬)
	D3DXMatrixTranslation(&mtxTrans, FormerPos.x, FormerPos.y, FormerPos.z);
	D3DXMatrixMultiply(&mtxWorldVtx, &mtxWorldVtx, &mtxTrans);		// sñ|¯ZÖ

	return D3DXVECTOR3(mtxWorldVtx._41, mtxWorldVtx._42, mtxWorldVtx._43);
}

//=============================================================================
// pxÌ³K»
// Author : ú±l
// Tv : pxª~ü¦Ì2{ð´¦½Æ«ÉÍÍàÉß·
//=============================================================================
float RotNormalization(float fRot)
{
	if (fRot >= D3DX_PI)
	{// Ú®ûüÌ³K»
		fRot -= D3DX_PI * 2;
	}
	else if (fRot <= -D3DX_PI)
	{// Ú®ûüÌ³K»
		fRot += D3DX_PI * 2;
	}

	return fRot;
}
