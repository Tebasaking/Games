//=========================================
// 
// 	�}�l�[�W���\�̏���
// 	Author:�y���m���@
// 
//=========================================
#include "application.h"
#include "render.h"
#include "object2D.h"
#include "billboard.h"
#include "player3D.h"
#include "input.h"
#include "texture.h"
#include "camera.h"
#include "camera_player.h"
#include "camera_radar.h"
#include "tutorial_pic.h"
#include "camera_title.h"
#include "light.h"
#include "Object3D.h"
#include "meshfield.h"
#include "sphere.h"
#include "inputkeyboard.h"
#include "mouse.h"
#include "sound.h"
#include "mode.h"
#include "score.h"
#include "game.h"
#include "title.h"
#include "debug_proc.h"
#include "result.h"
#include "camera_title.h"
#include "fade.h"
#include "model3D.h"
#include "texture3D.h"
#include "joypad.h"
#include "time_over.h"
#include "game_over.h"
#include "tutorial.h"

CDebugProc *CApplication::m_pDebug = nullptr;
CRender *CApplication::m_pRender = nullptr;
CPlayer *CApplication::m_pPlayer = nullptr;
CEnemy *CApplication::m_pEnemy = nullptr;
CTexture* CApplication::m_pTexture = nullptr;
CMode* CApplication::m_pMode = nullptr;
CGame* CApplication::m_pGame = nullptr;
CCameraTitle* CApplication::m_pTitle = nullptr;
CTexture3D* CApplication::m_pTexture3D = nullptr;
CSound*	CApplication::m_pSound = nullptr;		//�T�E���h

CCameraRadar* CApplication::m_pRader = nullptr;
CCameraPlayer* CApplication::m_pCamera = nullptr;

CApplication::MODE CApplication::m_NextMode = MODE_MAX;
CApplication::MODE CApplication::m_mode = MODE_MAX;

LPD3DXEFFECT CApplication::m_pEffect = nullptr;

//=========================================
// �R���X�g���N�^
//=========================================
CApplication::CApplication()
{
}

//=========================================
// �f�X�g���N�^
//=========================================
CApplication::~CApplication()
{
}

//=========================================
// ����������
//=========================================
HRESULT CApplication::Init(HINSTANCE hInstance,HWND hWnd)
{
	m_pRender = new CRender;
	m_pTexture = new CTexture;
	m_pCamera = new CCameraPlayer;
	m_pRader = new CCameraRadar;
	m_pDebug = new CDebugProc;
	m_pTexture3D = new CTexture3D;
	m_pTitle = new CCameraTitle;

	if (FAILED(m_pRender->Init(hWnd, false)))
	{// ���������������s�����ꍇ
		return -1;
	}

	// TEXTURE(3D)�̓ǂݍ���
	m_pTexture3D->Init();

	// ���C�g�̏���������
	InitLight();

	// Model3D�̓ǂݍ���
	CModel3D::InitModel();

	CInput::Create();

	if (FAILED(CInput::GetKey()->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//----------------------------
	// �T�E���h�̐����Ə�����
	//----------------------------
	m_pSound = new CSound;
	m_pSound->Init(hWnd);

	// �J�����̏������ݒ�
	if (m_pCamera != nullptr)
	{
		m_pCamera->SetObjMode(CObject::NORMAL_MODE);
		m_pCamera->Init(D3DXVECTOR3(0.0f, 1000.0f, -150.0f));
		m_pCamera->SetViewSize(0, 0, SCREEN_WIDTH , SCREEN_HEIGHT);
	}

	if (m_pRader != nullptr)
	{
		// �J�����̏������ݒ�2
		m_pRader->SetObjMode(CObject::RADAR_MODE);
		m_pRader->Init(D3DXVECTOR3(0.0f, 5000.0f, -150.0f));
		//m_pRader->SetViewSize(25.0f, SCREEN_HEIGHT * 0.5f + 5.0f, SCREEN_WIDTH * 0.25f * 0.75f, SCREEN_HEIGHT * 0.5f * 0.75f);
		m_pRader->SetViewSize(25.0f, SCREEN_HEIGHT - 285, SCREEN_WIDTH * 0.25f * 0.75f, SCREEN_HEIGHT * 0.5f * 0.75f);

	}

	// �J�����̏������ݒ�
	if (m_pTitle != nullptr)
	{	// �J�����̏������ݒ�3
		m_pTitle->SetObjMode(CObject::TITLE_MODE);
		m_pTitle->Init(D3DXVECTOR3(0.0f, 0.0f, -150.0f));
		m_pTitle->SetViewSize(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	// �Q�[���X�^�[�g���̏����ݒ�
	// ���[�h�̐ݒ�
	SetNextMode(MODE_TITLE);

	// �f�o�b�N�̏���������
	m_pDebug->Init();

	//���[�h�̐ݒ�
	CFade::Create(m_NextMode);

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetRender()->GetDevice();

	D3DXCreateEffectFromFile(
		pDevice, "Effect.fx", NULL, NULL,
		0, NULL, &m_pEffect, nullptr);

	return S_OK;
}

//=========================================
// �X�V����
//=========================================
void CApplication::Update()
{
	//���͏����̍X�V����
	CInput::GetKey()->Update();

	// ���[�h�̕ύX
	ChangeMode();

	// ���C�g�̍X�V����
	UpdateLight();

	// �J�����̍X�V����
	m_pCamera->Update();

	// �^�C�g���J�����̍X�V����
	m_pTitle->Update();

	// ���[�_�[�̍X�V����
	m_pRader->Update();

	// �����_�[�̍X�V����
	m_pRender->Update();
}

//=========================================
// �`�揈��
//=========================================
void CApplication::Draw()
{
	// �����_�[�̕`�揈��
	m_pRender->Draw();
}

//=========================================
// �I������
//=========================================
void CApplication::Uninit()
{
	//���͏����̏I������
	CInput::GetKey()->Uninit();

	if (m_pRender != nullptr)
	{
		// �����_�[�̏I������
		m_pRender->Uninit();
		delete m_pRender;
		m_pRender = nullptr;
	}

	if (m_pTexture3D != nullptr)
	{
		// �e�N�X�`���̏I������
		m_pTexture3D->Uninit();
		delete m_pTexture3D;
		m_pTexture3D = nullptr;
	}

	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	if (m_pRender != nullptr)
	{
		delete m_pRender;
		m_pRender = nullptr;
	}
	if (m_pTexture != nullptr)
	{
		// �e�N�X�`���̏I������
		m_pTexture->ReleaseAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}
	if (m_pCamera != nullptr)
	{
		// �J�����̏I������
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
	if (m_pRader != nullptr)
	{
		delete m_pRader;
		m_pRader = nullptr;
	}
	if (m_pTitle != nullptr)
	{
		delete m_pTitle;
		m_pTitle = nullptr;
	}
	if (m_pDebug != nullptr)
	{
		// �f�o�b�N�̏I������
		m_pDebug->Uninit();
		delete m_pDebug;
		m_pDebug = nullptr;
	}
	if (m_pRader != nullptr)
	{
		// ���[�_�[�̏I������
		m_pRader->Uninit();
		delete m_pRader;
		m_pRader = nullptr;
	}
	if (m_pTitle != nullptr)
	{
		// �^�C�g���J�����̏I������
		m_pTitle->Uninit();
		delete m_pTitle;
		m_pTitle = nullptr;
	}
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();
		//delete m_pMode;
		//m_pMode = nullptr;
	}

	// �I�u�W�F�N�g�̏I������
	CObject::UninitAll();

	// ���f���̏I������
	CModel3D::UninitModel();

	// ���C�g�̏I������
	UninitLight();
}

//=========================================
// �����_�[�̏��̎擾
//=========================================
CRender *CApplication::GetRender()
{
	return m_pRender;
}

//=========================================
// �v���C���[�̏��̎擾
//=========================================
CPlayer *CApplication::GetPlayer()
{
	return m_pPlayer;
}

//=========================================
// �v���C���[�̏��̎擾
//=========================================
CEnemy *CApplication::GetEnemy()
{
	return m_pEnemy;
}

//=========================================
// �e�N�X�`���̏��̎擾
//=========================================
CTexture* CApplication::GetTexture()
{
	return m_pTexture;
}

//=========================================
// ���[���h���W���X�N���[�����W�ɕϊ�����֐�
//=========================================
D3DXVECTOR3 CApplication::WorldToScreen(D3DXVECTOR3 pos)
{
	// �r���[�s��Ǝˉe�s��̎擾
	D3DXMATRIX mtx;

	D3DXMatrixTranslation(&mtx, pos.x, pos.y, pos.z);

	CCamera *pCamera = GetCamera();

	D3DXMATRIX view = pCamera->GetView();
	D3DXMATRIX proj = pCamera->GetProjection();

	mtx = mtx * view * proj;

	D3DXVECTOR3 pOut(mtx._41, mtx._42, mtx._43);

	// z�Ŋ�����-1��1�͈̔͂Ɏ��߂�
	pOut.x /= pOut.z, pOut.y /= pOut.z/*, pOut.z /= pOut.z*/;

	// �r���[�|�[�g�s��i�X�N���[���s��j�̍쐬
	D3DXMATRIX viewport;
	D3DXMatrixIdentity(&viewport);

	viewport._11 = SCREEN_WIDTH / 2.0f;
	viewport._22 = -SCREEN_HEIGHT / 2.0f;
	viewport._41 = SCREEN_WIDTH / 2.0f;
	viewport._42 = SCREEN_HEIGHT / 2.0f;

	D3DXVec3TransformCoord(&pOut, &pOut, &viewport);

	return pOut;
}

//==================================================
// �Q�[�����[�h�̎��̃��[�h�̐ݒ�
//==================================================
void CApplication::SetNextMode(MODE mode)
{
	m_NextMode = mode;
	m_mode = mode;
}

//=========================================
// �Q�[�����[�h�̕ύX
//=========================================
void CApplication::ChangeMode()
{
	if (m_NextMode == MODE_MAX)
	{
		return;
	}

	// �I�u�W�F�N�g�S�Ă̏I������
	CObject::UninitAll();

	//���[�h�̐ݒ�
	CFade::Create(m_NextMode);

	switch (m_NextMode)
	{
	case MODE_TITLE:
		// �J�����̏���������
		//m_pCamera->Init(D3DXVECTOR3(0.0f, 0.0f, -150.0f));
		m_pTitle->Init(D3DXVECTOR3(0.0f, 0.0f, -150.0f));
		m_pMode = new CTitle;
		break;

	case MODE_GAME:
		// �J�����̏���������
		m_pCamera->Init(D3DXVECTOR3(0.0f, 1000.0f, -150.0f));
		m_pRader->Init(D3DXVECTOR3(0.0f, 5000.0f, -150.0f));
		m_pMode = new CGame;
		break;

	case MODE_RESULT:
		// �J�����̏���������
		m_pCamera->Init(D3DXVECTOR3(0.0f, 1000.0f, -150.0f));
		m_pMode = new CResult;
		break;

	case MODE_TIME_OVER:
		m_pTitle->Init(D3DXVECTOR3(0.0f, 0.0f, -150.0f));
		// �^�C���I�[�o�[�̏���������
		m_pMode = new CTimeOver;
		break;

	case MODE_GAME_OVER:
		m_pTitle->Init(D3DXVECTOR3(0.0f, 0.0f, -150.0f));
		// �Q�[���I�[�o�[�̏���������
		m_pMode = new CGameOver;
		break;

	case MODE_TUTORIAL_PIC:
		m_pTitle->Init(D3DXVECTOR3(0.0f, 0.0f, -150.0f));
		// �`���[�g���A���摜�̏���������
		m_pMode = new CTutorial_Pic;
		break;

	case MODE_TUTORIAL:
		m_pCamera->Init(D3DXVECTOR3(0.0f, 1000.0f, -150.0f));
		// TUTORIAL�̏���������
		m_pMode = new CTutorial;
		break;

	default:
		break;
	}

	// ���̃��[�h�̏�����
	m_NextMode = MODE_MAX;

	if (m_pMode != nullptr)
	{
		m_pMode->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
}

