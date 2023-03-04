//=========================================
// game.cpp
// Author: �y���m��
//=========================================
#include <algorithm>
#include "application.h"
#include "game.h"
#include "player_manager.h"
#include "playerUI.h"
#include "enemy_manager.h"
#include "sphere.h"
#include "meshfield.h"
#include "score.h"
#include "input.h"
#include "fade.h"
#include "enemy.h"
#include "camera.h"
#include "radar.h"
#include "number.h"
#include "render.h"
#include "time.h"
#include "score.h"
#include "sound.h"
#include "mouse.h"
#include "ranking.h"
#include "missile_alert.h"

bool CGame::m_bFinish = false;
bool CGame::m_bFinish_2 = false;
CMesh* CGame::m_pMesh[3] = {};
CScore* CGame::m_pScore = nullptr;
CPlayerManager* CGame::m_pPlayerManager = nullptr;
CEnemy_Manager* CGame::m_pEnemyManager = nullptr;
CPlayerUI* CGame::m_PlayerUI = nullptr;
CAlert* CGame::m_pAlert = nullptr;

//=========================================
// �R���X�g���N�^
//=========================================
CGame::CGame()
{
}

//=========================================
// �f�X�g���N�^
//=========================================
CGame::~CGame()
{
}

//=========================================
// ������ 
//=========================================
HRESULT CGame::Init(const D3DXVECTOR3 &pos)
{
	//CObject2D *pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), 4);
	//pObject2D->SetScale(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	//
	//pObject2D->SetTexture(CTexture::TEXTURE_TEST);
	
	// �A���[�g�̐���
	m_pAlert = CAlert::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_PlayerUI = new CPlayerUI(4);
	m_PlayerUI->Init(D3DXVECTOR3(0.0f,0.0f,0.0f));

	m_bFinish = false;
	m_bFinish_2 = false;

	CRender *pRender = CApplication::GetRender();
	pRender->SetFog(true, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0001f));

	//�^�C�}�[�̐���
	CTime *pTime = CTime::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 200.0f, 85.0f, 0.0f));

	// �Q�[���̃^�C�����~�b�g��ݒ�(��,�b);
	pTime->SetAlarm(2,0);

	// �X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH - 300.0f, 85.0f, 0.0f),D3DXVECTOR3(40.0f,40.0f,0.0f));

	// �C
	m_pMesh[0] = CMesh::Create(D3DXVECTOR3(0.0f, -350.0f, 0.0f), CMesh::TYPE_SEA);
	m_pMesh[2] = CMesh::Create(D3DXVECTOR3(0.0f, -300.0f, 0.0f), CMesh::TYPE_WAVE);

	// �v���C���[�}�l�[�W���\�̎擾
	m_pPlayerManager = CPlayerManager::Create(D3DXVECTOR3(0.0f, 1000.0f, 5.0f));
	// �G�l�~�[�̃}�l�[�W���[�̎擾
	m_pEnemyManager = CEnemy_Manager::Create();

	// �X�t�B�A
	CSphere *pSphere = CSphere::Create(D3DXVECTOR3(0.0f, -0.0f, 0.0f));

	// ��
	m_pMesh[1] = CMesh::Create(D3DXVECTOR3(0.0f, -400.0f, 0.0f), CMesh::TYPE_GROUND);

	m_pRadar = nullptr;
	m_pRadar = CRadar::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetObjectinfo(), CRadar::RADAR_MAP);

	//�T�E���h����
	CSound::PlaySound(CSound::SOUND_LABEL_BGM000);

	return S_OK;
}

//=========================================
// �I������
//=========================================
void CGame::Uninit()
{
	// �����L���O�Ɍ��݂̃X�R�A��ۑ�����
	CRanking::SetCurrentScore(m_pScore->GetScore());

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		m_pMesh[nCnt] = nullptr;
	}

	if (m_pScore != nullptr)
	{
		// �X�R�A�̏I������
		m_pScore->Uninit();
		m_pScore = nullptr;
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

	// �T�E���h�̏I��
	CSound::StopSound();
}

//=========================================
// �X�V����
//=========================================
void CGame::Update()
{
	CInput *pKeyboard = CInput::GetKey();

	// �v���C���[�}�l�[�W���\�̍X�V����
	m_pPlayerManager->Update();

	// �G�l�~�[�}�l�[�W���\�̍X�V����
	m_pEnemyManager->Update();

	// �v���C���[UI�̍X�V����
	m_PlayerUI->Update();

	if (m_bFinish)
	{
		// �Q�[�����I�������U���g��ʂ�
		//���[�h�̐ݒ�
		CFade::SetFade(CApplication::MODE_TIME_OVER);
	}
	else if (m_bFinish_2)
	{
		// �Q�[�����I�������U���g��ʂ�
		//���[�h�̐ݒ�
		CFade::SetFade(CApplication::MODE_GAME_OVER);
	}

	// ���[�h�ύX
	//if (pKeyboard->Trigger(DIK_RETURN) || pKeyboard->Trigger(JOYPAD_A))
	//{
	//	//���[�h�̐ݒ�
	//	CFade::SetFade(CApplication::MODE_GAME_OVER);
	//}
}

//=========================================
// �G�l�~�[���폜����
//=========================================
void CGame::DeleteEnemy(CEnemy* pEnemy)
{
}

//=========================================
// �Q�[���Z�b�g
//=========================================
void CGame::EnemyManage()
{
}

//=========================================
// �X�R�A�̉��Z����
//=========================================
void CGame::Add(int Score)
{
	m_pScore->Add(Score);
}