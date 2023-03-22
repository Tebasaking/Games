//==================================================
//
// title.cpp
// Author: �y���m��
//
//==================================================
#include "application.h"
#include "tutorial.h"
#include "player3D.h"
#include "enemy.h"
#include "fade.h"
#include "texture.h"
#include "meshfield.h"
#include "sphere.h"
#include "camera.h"
#include "title_model.h"
#include "input.h"
#include "missile_alert.h"
#include "player_manager.h"
#include "playerUI.h"
#include "enemy_manager.h"
#include "time.h"
#include "score.h"

CMesh* CTutorial::m_pMesh[3] = {};
CScore* CTutorial::m_pScore = nullptr;
CPlayerManager* CTutorial::m_pPlayerManager = nullptr;
CEnemy_Manager* CTutorial::m_pEnemyManager = nullptr;
CPlayerUI* CTutorial::m_PlayerUI = nullptr;
CAlert* CTutorial::m_pAlert = nullptr;

//==================================================
// �R���X�g���N�^
//==================================================
CTutorial::CTutorial()
{
}

//==================================================
// �f�X�g���N�^
//==================================================
CTutorial::~CTutorial()
{
}

//=========================================
// ������ 
//=========================================
HRESULT CTutorial::Init(const D3DXVECTOR3 &pos)
{
	m_Select = 0;

	pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), 4);

	pObject2D->SetScale(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	CInput *pKeyboard = CInput::GetKey();
	if (pKeyboard->GetAcceptJoyPadCount() != 0)
	{
		pObject2D->SetTexture(CTexture::TEXTURE_TUTORIAL_GAME);
	}
	else
	{
		pObject2D->SetTexture(CTexture::TEXTURE_TUTORIAL_GAME_MOUSE);
	}
	// �A���[�g�̐���
	m_pAlert = CAlert::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_PlayerUI = new CPlayerUI(4);
	m_PlayerUI->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CRender *pRender = CApplication::GetRender();
	pRender->SetFog(true, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0001f));

	// �C
	m_pMesh[0] = CMesh::Create(D3DXVECTOR3(0.0f, -350.0f, 0.0f), CMesh::TYPE_SEA);
	m_pMesh[2] = CMesh::Create(D3DXVECTOR3(0.0f, -300.0f, 0.0f), CMesh::TYPE_WAVE);

	// �v���C���[�}�l�[�W���\�̎擾
	m_pPlayerManager = CPlayerManager::Create(D3DXVECTOR3(0.0f, 1000.0f, 5.0f));
	// �G�l�~�[�̐���
	CEnemy::Create(D3DXVECTOR3(0.0f,1000.0f,-2000.0f),CEnemy::ENEMY_TUTORIAL,0);
	// �G�l�~�[�̐���
	CEnemy::Create(D3DXVECTOR3(0.0f, 1000.0f, 2000.0f), CEnemy::ENEMY_TUTORIAL, 0);

	// �X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH - 300.0f, 85.0f, 0.0f), D3DXVECTOR3(40.0f, 40.0f, 0.0f));

	// �X�t�B�A
	CSphere *pSphere = CSphere::Create(D3DXVECTOR3(0.0f, -0.0f, 0.0f));

	return S_OK;
}

//=========================================
// �X�V����
//=========================================
void CTutorial::Update()
{
	// �v���C���[UI�̍X�V����
	m_PlayerUI->Update();

	CInput *pKeyboard = CInput::GetKey();

	//float X = SCREEN_WIDTH * 0.5f;
	//float Y = SCREEN_HEIGHT * 0.5f;


	if (pKeyboard->Trigger(JOYPAD_START) || pKeyboard->Trigger(DIK_RETURN))
	{
		//���[�h�̐ݒ�
		CFade::SetFade(CApplication::MODE_TITLE);
	}

	//else if (m_Select == 3)
	//{
	//	//���[�h�̐ݒ�
	//	CFade::SetFade(CApplication::MODE_TITLE);

	//	for (int nCnt = 0; nCnt < 3; nCnt++)
	//	{
	//		pObject2D[nCnt]->SetScale(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//	}
	//}
}

//=========================================
// �I������
//=========================================
void CTutorial::Uninit()
{
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		m_pMesh[nCnt] = nullptr;
	}

	if (m_PlayerUI != nullptr)
	{
		m_PlayerUI->Release();
	}

	if (m_pPlayerManager != nullptr)
	{
		m_pPlayerManager->Uninit();
		delete m_pPlayerManager;
		m_pPlayerManager = nullptr;
	}

	if (m_pEnemyManager != nullptr)
	{
		m_pEnemyManager->Uninit();
		delete m_pEnemyManager;
		m_pEnemyManager = nullptr;
	}

	Release();
}