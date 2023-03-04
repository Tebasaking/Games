//=========================================
//
//	render.h
//	Author:�y���m��
//
//=========================================
#ifndef _RENDER_H_		//���̃}�N����`������ĂȂ�������
#define _RENDER_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

//=========================================
//�N���X�錾
//=========================================
class CRender
{
public:
	CRender();			//�R���X�g���N�^
	~CRender();			//�f�X�g���N�^

	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();
	void DrawFPS();
	void SetFog(bool bFlag, D3DXCOLOR col);
	LPDIRECT3DDEVICE9 GetDevice() { return m_pD3DDevice; };

	bool GetCheck() { return bCheck; }

private:
	// ���݂�Draw�̊Ǘ�
	bool bCheck;
	// Direct3D�I�u�W�F�N�g
	LPDIRECT3D9 m_pD3D;
	// Device�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	//���_�o�b�t�@�̐ݒ�
	LPDIRECT3DVERTEXBUFFER9 m_vtxBuffPolygon;
	//��]
	D3DXVECTOR3 m_rot = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	bool m_bCheck = false;
	bool m_Wire = false;
	float m_fWidth = 250.0f, fHeight = 250.0f;

	D3DXVECTOR3 m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0);

#ifdef _DEBUG
	// �t�H���g
	LPD3DXFONT m_pFont = nullptr;
#endif // _DEBUG

#ifdef _DEBUG
	// FPS�J�E���^
	int m_nCountFPS;
#endif // _DEBUG
};

#endif