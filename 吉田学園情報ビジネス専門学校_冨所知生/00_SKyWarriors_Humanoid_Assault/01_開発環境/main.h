//=========================================
//
//	main.h
//	Author:�y���m��
//
//=========================================
#ifndef _MAIN_H_		//���̃}�N����`������ĂȂ�������
#define _MAIN_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <assert.h>
#include <tchar.h> // _T
#include <d3dx9.h>


#ifdef _DEBUG
#define CHECK_MEM_LEAK
#endif // _DEBUG:

////���i�g�p�֎~
//#ifdef CHECK_MEM_LEAK
//#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
//#endif // CHECK_MEM_LEAK


//�O���錾
class CRender;
class CObject;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// ���_�f�[�^
struct VERTEX_2D
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
};

struct VERTEX_3D
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR	col;	//���_�J���[
	D3DXVECTOR2 tex;	//texture���W
};

// �X�N���[���̕�
const int SCREEN_WIDTH = 1280;
// �X�N���[���̍���
const int SCREEN_HEIGHT = 720;

// ���_�t�H�[�}�b�g
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);		//���W�E�@���E�J���[

#endif