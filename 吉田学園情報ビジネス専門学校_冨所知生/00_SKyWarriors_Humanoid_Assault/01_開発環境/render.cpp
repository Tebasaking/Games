//=========================================
//
//	�����_�[(�|���S���̐���)����
//	Author:�y���m��
//
//=========================================
#include <stdio.h>
#include "render.h"
#include "object.h"
#include "camera.h"
#include "application.h"
#include "debug_proc.h"
#include "input.h"
#include "inputkeyboard.h"
#include "model3D.h"

#define POLIGON_MAX (2)

//=========================================
//�R���X�g���N�^
//=========================================
CRender::CRender()
{

}

//=========================================
//�f�X�g���N�^
//=========================================
CRender::~CRender()
{

}

//=========================================
//�����_�[�̏���������
//=========================================
HRESULT CRender::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	bCheck = false;
	m_Wire = false;

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == nullptr)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;										// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;							// �J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;							// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;										// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��

	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if ((FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))) &&
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))) &&
		// ��L�̐ݒ肪���s������
		// �`��ƒ��_������CPU�ōs�Ȃ�
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))))
	{
		// �������s
		return E_FAIL;
	}

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// �J�����O�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// �A���t�@�u�����h�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// �A���t�@�u�����h�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// �A���t�@�u�����h�̐ݒ�

	// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���̑傫����ς��Ă��Y��ɓ\��
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���̑傫����ς��Ă��Y��ɓ\��
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`�����J��Ԃ��ē\��
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`�����J��Ԃ��ē\��

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �|���S���ƃe�N�X�`���̃A���t�@�l��������B
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �|���S���ƃe�N�X�`���̃A���t�@�l��������B�e�N�X�`���w��
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �|���S���ƃe�N�X�`���̃A���t�@�l��������B�|���S���w��

//#ifdef _DEBUG
//	// �f�o�b�O���\���p�t�H���g�̐���
//	D3DXCreateFont(m_pD3DDevice, 36, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
//		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_pFont);
//#endif

	return S_OK;
}

//=========================================
//�����_�[�̍X�V����
//=========================================
void CRender::Update()
{
	//�X�V����
	CObject::UpdateAll();

	CInput *pKeyboard = CInput::GetKey();
	//���C���[�t���[��
	//if (pKeyboard->Trigger(DIK_F1))
	//{
	//	m_Wire = !m_Wire;
	//	m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, m_Wire ? D3DFILL_WIREFRAME : D3DFILL_FORCE_DWORD);
	//}
}

//=========================================
//�����_�[�̏I������
//=========================================
void CRender::Uninit()
{
#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
#endif // _DEBUG

	// �f�o�C�X�̔j��
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}

//=========================================
//�����_�[�̕`�揈��
//=========================================
void CRender::Draw()
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
#ifdef _DEBUG
		// FPS�\��
		CDebugProc::Draw();
#endif // _DEBUG

		switch (CApplication::GetMode())
		{
		case CApplication::MODE_TITLE:
		{// �^�C�g�����[�h
			// �`�揈��
			CObject::DrawAll(CObject::TITLE_MODE);
			break;
		}

		case CApplication::MODE_GAME:
		{
			//�`�揈��
			CObject::DrawAll(CObject::RADAR_MODE);
			//�`�揈��
			CObject::DrawAll(CObject::NORMAL_MODE);
			break;
		}

		case CApplication::MODE_RESULT:
		{
			// �`�揈��
			CObject::DrawAll(CObject::TITLE_MODE);
			break;
		}
		case CApplication::MODE_GAME_OVER:
		{
			// �`�揈��
			CObject::DrawAll(CObject::TITLE_MODE);
			break;
		}
		case CApplication::MODE_TIME_OVER:
		{
			// �`�揈��
			CObject::DrawAll(CObject::TITLE_MODE);
			break;
		}
		case CApplication::MODE_TUTORIAL_PIC:
		{
			// �`�揈��
			CObject::DrawAll(CObject::TITLE_MODE);
			break;
		}
		case CApplication::MODE_TUTORIAL:
		{
			// �`�揈��
			CObject::DrawAll(CObject::NORMAL_MODE);
			break;
		}

		}

		// Direct3D�ɂ��`��̏I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// �t�H�O�ݒ菈��
//=============================================================================
void CRender::SetFog(bool bFlag, D3DXCOLOR col)
{
	// �t�H�O�̗L���ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, bFlag);

	// �t�H�O�J���[�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, col);

	// �t�H�O���[�h ������(�͈͎w�� : D3DFOG_LINEAR, ���x�w�� : D3DFOG_EXP)
	m_pD3DDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);

	// �͈͎w��(��LINEAR���Ɏw��)
	float fFogStartPos = 100;
	float fFogEndPos = 23000;

	m_pD3DDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&fFogStartPos));
	m_pD3DDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&fFogEndPos));

	// ���x�w��(��EXP���Ɏw��)
	float fFogDensity = 0.00001f;

	m_pD3DDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&fFogDensity));
}

#ifdef _DEBUG
//=============================================================================
// FPS�\��
//=============================================================================
void CRender::DrawFPS()
{
	//RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	//TCHAR str[256];

	//D3DXVECTOR3 TPos = CTarget::GetTargetPos();

	////wsprintf(str, _T("�G�l�~�[�̃X�N���[�����W : (%.0f , %f , %f )\n"), TPos.x, TPos.y, TPos.z);

	//// �J�����̎��_
	//sprintf(&str[0], "  �G�l�~�[�̃X�N���[�����W : (%.0f , %f , %f )\n", TPos.x, TPos.y, TPos.z);

	//// �e�L�X�g�`��
	//m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
}
#endif // _DEBUG
