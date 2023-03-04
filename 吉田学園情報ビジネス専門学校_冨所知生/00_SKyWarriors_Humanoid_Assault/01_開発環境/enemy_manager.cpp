//=========================================
//
//	�G�l�~�[���Ǘ����鏈��
//	Author:�y���m��
//
//=========================================
#include <algorithm>
#include <assert.h>
#include <string.h>
#include "player3D.h"
#include "enemy_manager.h"
#include "application.h"
#include "sound.h"
#include "inputkeyboard.h"
#include "fade.h"
#include "enemy.h"
#include "debug_proc.h"

//=========================================
// �R���X�g���N�^
//=========================================
CEnemy_Manager::CEnemy_Manager()
{
	m_NowWave = 0;
}

//=========================================
// �f�X�g���N�^
//=========================================
CEnemy_Manager::~CEnemy_Manager()
{
}

//========================================
// �I�u�W�F�N�g�̏���������
//=========================================
HRESULT CEnemy_Manager::Init()
{
	// �t�@�C���̓ǂݍ���
	LoadFile();

	return S_OK;
}

//=========================================
// �I�u�W�F�N�g�̍X�V����
//=========================================
void CEnemy_Manager::Update()
{
	EnemyCreate(m_NowWave);
}

//=========================================
// �I�u�W�F�N�g�̏I������
//=========================================
void CEnemy_Manager::Uninit()
{
}

//=========================================
// �I�u�W�F�N�g�̕`�揈��
//=========================================
void CEnemy_Manager::Draw()
{
}

//=========================================
// �I�u�W�F�N�g�̃N���G�C�g
//=========================================
CEnemy_Manager* CEnemy_Manager::Create()
{
	CEnemy_Manager* pEnemy = nullptr;

	pEnemy = new CEnemy_Manager;

	if (pEnemy != nullptr)
	{
		pEnemy->Init();
	}

	return pEnemy;
}

//=========================================
// �t�@�C����ǂݍ��ޏ���
//=========================================
void CEnemy_Manager::LoadFile()
{
	// �ϐ��錾
	char aStr[128];
	char aEqual[128] = {};		// ���ǂݍ��ݗp�ϐ�
	int nCntTex = 0;
	int WaveNumber = 0;

	// �t�@�C���̓ǂݍ���
	FILE *pFile = fopen("data/FILE/enemy_manage.txt", "r");

	if (pFile != nullptr)
	{
		while (fscanf(pFile, "%s", &aStr[0]) != EOF)
		{// "EOF"��ǂݍ��ނ܂� 
			if (strncmp(&aStr[0], "#", 1) == 0)
			{// ���ǂݍ���
				fgets(&aStr[0], sizeof(aStr), pFile);
			}

			if (strstr(&aStr[0], "MAX_WAVE_ENEMY") != NULL)
			{// �E�F�[�u��
				fscanf(pFile, "%s", &aStr[0]);
				fscanf(pFile, "%d", &m_MaxWave);

				m_Wave.resize(m_MaxWave);
			}

			if (strcmp(&aStr[0], "WAVE_SET") == 0)
			{	
				while ((strncmp(&aStr[0], "LOAD_END",8) != 0))
				{
					int nCntEnemySpawn = 0;

					fscanf(pFile, "%s", &aStr[0]);

 					if (strcmp(&aStr[0], "WAVE_NUMBER") == 0)
					{// �E�F�[�u�̔ԍ�
						fscanf(pFile, "%s", &aEqual[0]);
						fscanf(pFile, "%d", &WaveNumber);
					}

					if (strcmp(&aStr[0], "ENEMY_AMOUNT") == 0)
					{// �o��������G�l�~�[�̐�
						fscanf(pFile, "%s", &aEqual[0]);
						fscanf(pFile, "%d", &nCntEnemySpawn);
						
						// �G�l�~�[�̐���ʓr�ۑ�����
						m_Wave[WaveNumber].m_Amount = nCntEnemySpawn;
						// �G�l�~�[�f�[�^���G�l�~�[�̐����m�ۂ���
						m_Wave[WaveNumber].m_EnemyData.resize(nCntEnemySpawn);
					}

					for (int nCnt = 0; nCnt < nCntEnemySpawn; nCnt++)
					{
						fscanf(pFile, "%s", &aStr[0]);

						D3DXVECTOR3 pos = {};
						int type = 0;
						int time = 0;

						if (strncmp(&aStr[0], "-", 1) == 0)
						{// ���ǂݍ���
							fgets(&aStr[0], sizeof(aStr), pFile);
						}
						if (strncmp(&aStr[0], "#", 1) == 0)
						{// ���ǂݍ���
							fgets(&aStr[0], sizeof(aStr), pFile);
						}

						if (strcmp(&aStr[0], "ENEMY_POS") == 0)
						{// �o��������G�l�~�[�̐�
							fscanf(pFile, "%s", &aEqual[0]);
							fscanf(pFile, "%f %f %f", &pos.x,&pos.y,&pos.z);
							fscanf(pFile, "%s", &aStr[0]);
						}
						if (strcmp(&aStr[0], "ENEMY_TYPE") == 0)
						{// �o��������G�l�~�[�̐�
							fscanf(pFile, "%s", &aEqual[0]);
							fscanf(pFile, "%d", &type);
							fscanf(pFile, "%s", &aStr[0]);
						}
						if (strcmp(&aStr[0], "ENEMY_TIME") == 0)
						{// �o��������G�l�~�[�̐�
							fscanf(pFile, "%s", &aEqual[0]);
							fscanf(pFile, "%d", &time);
						}

						// �E�F�[�u�ɃG�l�~�[�̏���ۑ�����
						m_Wave[WaveNumber].m_EnemyData[nCnt].pos = pos;
						m_Wave[WaveNumber].m_EnemyData[nCnt].type = type;
						m_Wave[WaveNumber].m_EnemyData[nCnt].time = time;
					}
				}
			}
		}
	}
	else
	{
		assert(false);
	}
}

//=========================================
// �G�l�~�[�𐶐����鏈��
//=========================================
void CEnemy_Manager::EnemyCreate(int Wave)
{
	int ENEMY_AMOUNT = m_Wave[Wave].m_Amount;

	for (int nCnt = 0; nCnt < ENEMY_AMOUNT; nCnt++)
	{// �E�F�[�u�̃^�C�}�[���G�l�~�[�̃^�C�}�[�ƈ�v�������A��v�����G�l�~�[�𐶐�����
		if (m_Wave[Wave].m_Timer == m_Wave[Wave].m_EnemyData[nCnt].time * 60)
		{
			D3DXVECTOR3 pos = m_Wave[Wave].m_EnemyData[nCnt].pos;
			int	type = m_Wave[Wave].m_EnemyData[nCnt].type;

			// �E�F�[�u�ɃG�l�~�[�̏���ۑ�����
			m_Wave[Wave].m_EnemyList.push_back(CEnemy::Create(pos, (CEnemy::EnemyType)type, Wave));
		}
	}

	m_Wave[Wave].m_Timer++;
	
	// �J�����̎��_
	//CDebugProc::Print("�G�l�~�[�J�E���g %d \n", m_Wave[Wave].m_Timer);
}

//=========================================
// �G�l�~�[���S�ł��������肷��
//=========================================
void CEnemy_Manager::Extinction()
{
	// ���݂̃E�F�[�u���̃G�l�~�[���X�g�̃T�C�Y��0��菬�����Ȃ�
	if (m_NowWave != m_MaxWave)
	{
		if (m_Wave[m_NowWave].m_EnemyList.size() <= 0)
		{// �E�F�[�u����i�߂�
			m_NowWave++;

			if (m_NowWave != m_MaxWave)
			{
				EnemyCreate(m_NowWave);
			}
		}
	}

	if (m_NowWave == m_MaxWave)
	{
		//���[�h�̐ݒ�
		CFade::SetFade(CApplication::MODE_RESULT);
	}
}

//=========================================
// �G�l�~�[�̎��S����
//=========================================
void CEnemy_Manager::Death(CEnemy* pEnemy)
{
	// pEnemy�������Ă���E�F�[�u���̎擾
	int nWave = pEnemy->GetWave();

	// ���X�g����pEnemy���폜����
	auto itEnd = std::remove(std::begin(m_Wave[nWave].m_EnemyList), std::end(m_Wave[nWave].m_EnemyList), pEnemy);

	// �{���̈Ӗ��ŗv�f����菜��
	m_Wave[nWave].m_EnemyList.erase(itEnd, std::cend(m_Wave[nWave].m_EnemyList));
}