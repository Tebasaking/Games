//=========================================
//
//	�G�l�~�[�̏���
//	Author:�y���m��
//
//=========================================
#include "enemy.h"
#include "application.h"
#include "input.h"
#include "inputkeyboard.h"
#include "texture.h"
#include "game.h"
#include "model.h"
#include "model3D.h"
#include "target.h"
#include "debug_proc.h"
#include "meshfield.h"
#include "radar.h"
#include "bullet3D.h"
#include "enemy_manager.h"
#include "explosion.h"
#include "effect.h"
#include "player3D.h"
#include "serihu.h"
#include "player_manager.h"

//=========================================
//�O���[�o���ϐ�
//=========================================
int nEnemyNumber = 0;

//=========================================
//�R���X�g���N�^
//=========================================
CEnemy::CEnemy()
{
	SetObjectType(OBJECT_ENEMY);
	m_state = ENEMY_IDOL;
	SetHP(10);
	m_type = ENEMY_MAX;
}

//=========================================
//�f�X�g���N�^
//=========================================
CEnemy::~CEnemy()
{
}

//=========================================
//�I�u�W�F�N�g�̏���������
//=========================================
HRESULT CEnemy::Init(const D3DXVECTOR3 &pos)
{
	m_PlayerPos = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);

	m_apModel[0] = new CModel3D;

	m_apModel[0]->SetModelID(3);
	m_apModel[0]->Init();
	m_apModel[0]->SetPos(pos);
	m_state = ENEMY_WARNNING;

	m_pos = pos;

	//�g�嗦�̐ݒ�
	m_apModel[0]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	// ���W�̐ݒ�
	SetPosition(pos);

	// �Â����W�̐ݒ�
	SetPosOld(m_pos);
	
	// �T�C�Y�̐ݒ�
	m_size = m_apModel[0]->GetMaterial()[0].size;

	//�傫���̐ݒ�
	SetSize(m_size);

	m_scale = 1.0f;

	// ���[�V�����̏���������
	CMotionModel3D::Init(pos);

	m_Target = nullptr;

	//�^�[�Q�b�g(�G�̋����\��)�̐ݒ�
	m_Target = CTarget::Create(D3DXVECTOR3(0.0f, -0.0f, 0.0f),this);

	m_Target->SetObject(this);

	m_Radar = nullptr;

	// �G�l�~�[�����[�_�[��ɕ\��������
	m_Radar = CRadar::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetObjectinfo(),CRadar::RADAR_ENEMY);

	return S_OK;
}

//=========================================
//�I�u�W�F�N�g�̍X�V����
//=========================================
void CEnemy::Update()
{
	auto FloatRandom = [](float fMax, float fMin)
	{
		return ((rand() / (float)RAND_MAX) * (fMax - fMin)) + fMin;
	};

	// �Â����W�̐ݒ�
	SetPosOld(m_pos);

	D3DXVECTOR3 PlayerPos;
	D3DXVECTOR3 PlayerRot;

	// �O���E���h�̎擾
	CMesh *pGround = CGame::GetGround();

	// ���S����
	Death();

	// ���W�̎擾
	m_pos = GetPosition();

	CObject *object = nullptr;
	CObject *PlayerObj = nullptr;

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		object = CObject::GetObjectTop(nCnt);

		//�v���C���[�̍��W���擾
		while (object)
		{
			if (object != nullptr)
			{
				EObjType ObjType = object->GetObjectType();

				if (ObjType == OBJECT_PLAYER)
				{
					m_PlayerPos = object->GetPosition();
					PlayerRot = object->GetRot();
					PlayerObj = object;
					break;
				}
			}
			object = object->GetObjectNext();
		}
	}

	Search();

	D3DXVECTOR3 rot = GetRot();

	//if (SearchEye(PlayerPos, m_pos, D3DX_PI * 0.5f, 100.0f, rot.y))
	//{
	//	m_state = ENEMY_WARNNING;
	//}

	float EnemySpeed = 5.0f;

	//=========================================
	// �G�l�~�[�̌��݂̏��
	//=========================================
	//=========================================
	// ��퓬��Ԃ̓G�̍s������
	//=========================================
	if (m_state == ENEMY_CAUTION)
	{
		rot.y += 0.01f;

		if (m_type == ENEMY_FLY)
		{
			// �ړ���
			m_move = D3DXVECTOR3(sinf(rot.y) * EnemySpeed,
				-(rot.x * EnemySpeed),
				cosf(rot.y) * EnemySpeed);

			m_CntWar++;
		}
		if (m_CntWar >= 120 + (int)FloatRandom(1200,100))
		{
			m_CntWar = 0;
			m_state = ENEMY_WARNNING;
		}
	}

	if (m_state == ENEMY_IDOL)
	{
		rot.y += 0.01f;

		if (m_type == ENEMY_FLY)
		{
			// �ړ���
			m_move = D3DXVECTOR3(sinf(rot.y) * EnemySpeed,
				-(rot.x * EnemySpeed),
				cosf(rot.y) * EnemySpeed);
		}

		if (m_type == ENEMY_GROUND)
		{
			D3DXVECTOR3 CollisionCheck = m_pos;

			if (!pGround->Collision(&CollisionCheck))
			{
				m_move = D3DXVECTOR3(sinf(rot.y) * EnemySpeed,
					-10.0f,
					cosf(rot.y) * EnemySpeed);
			}
			else
			{
				m_move = D3DXVECTOR3(sinf(rot.y) * EnemySpeed,
					-0.0f,
					cosf(rot.y) * EnemySpeed);
			}
		}
	}

	//=========================================
	// �퓬��Ԃ̃G�l�~�[�̍s������
	//=========================================
	if (m_state == ENEMY_WARNNING && m_type != ENEMY_TUTORIAL)
	{
		//���̎擾
		D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 posTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		
		Pos = GetPosition();
		posTarget = PlayerPos;

		D3DXVECTOR3 EnemyVec = m_PlayerPos - GetPosition();

		// �x�N�g�����Z�o
		D3DXVECTOR3 MoveVec = {};

		D3DXVec3Normalize(&MoveVec, &m_move);
		D3DXVec3Normalize(&EnemyVec, &EnemyVec);

		// �i�s�����x�N�g������o�������ݒn���猩���G�l�~�[�ւ̊p�x
		float AdvanceRot = acos((MoveVec.x * EnemyVec.x) + (MoveVec.y * EnemyVec.y) + (MoveVec.z * EnemyVec.z));

		float AdvanceRotVec = AdvanceRot * (180 * D3DX_PI);

		D3DXVECTOR3 Vec = EnemyVec / AdvanceRotVec;

		// 1�t���[���ɓ����p�x��ݒ肷��
		float OneRadian = (1 * (180 / D3DX_PI));

		D3DXVec3Normalize(&Vec, &Vec);

		D3DXVECTOR3 A = Vec;

		D3DXVECTOR3 AB = Vec *  OneRadian;
		D3DXVec3Normalize(&AB, &AB);

		//m_m_move = AB * m_MissileSpeed;

		m_move = AB * EnemySpeed;

		// �p�x�̐ݒ�
		D3DXVECTOR3 rotDest = AtanRot(m_pos + m_move, m_pos);
		rotDest.x -= D3DX_PI * 0.5f;
		rotDest.z += D3DX_PI;

		D3DXVECTOR3 rotResult = rotDest - rot;
		
		rotResult = NormalizeRotXYZ(rotResult);
		
		// ��]�̉��Z
		rot += rotResult * 0.01f;

		rot = NormalizeRotXYZ(rot);

		m_AttackCount++;

		// ��s�@�����ړ�������
		if (m_type == ENEMY_FLY)
		{
			m_move = D3DXVECTOR3(sinf(rot.y) * EnemySpeed,
				-(rot.x * EnemySpeed),
				cosf(rot.y) * EnemySpeed);
		}
		else if (m_type == ENEMY_GROUND)
		{
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}

		if (AdvanceRot <= D3DX_PI * 0.25f)
		{
			// �A�^�b�N�J�E���g��300~400�ȏ�̎�
			if (PlayerObj != nullptr && m_AttackCount >= 300 + FloatRandom(200,0))
			{
				// �v���C���[�ɑ΂��ă~�T�C���𔭎˂���
				Bullet(PlayerObj);

				if (m_type == ENEMY_FLY)
				{
					// �G�l�~�[�̏�Ԃ�ҋ@��Ԃɂ���
					m_state = ENEMY_CAUTION;
				}
			}
		}
	}

	// �ړ��ʂ����Z����
	m_pos += m_move;

	if (pGround != nullptr)
	{
		if (m_type == ENEMY_FLY)
		{
			D3DXVECTOR3 GroundPos = m_pos;
			GroundPos.y -= 100.0f;

			// ���̓����蔻��
			if (pGround->Collision(&GroundPos) && m_state == ENEMY_DEATH)
			{
				CExplosion::Create(m_pos, m_quaternion);

				// �G�l�~�[�̑���
				((CGame*)CApplication::GetModeObject())->DeleteEnemy(this);

				CApplication::GetGame()->GetEM()->Death(this);

				// ������
				CEnemy::Uninit();
			}

			m_pos.y = GroundPos.y + 100.0f;
		}
		else if (m_type == ENEMY_GROUND)
		{
			D3DXVECTOR3 GroundPos = m_pos;
			GroundPos.y -= 100.0f;

			// ���̓����蔻��
			if (pGround->Collision(&GroundPos))
			{
				m_pos.y = GroundPos.y;
			}
		}
	}

	//���S��Ԃ̔���
	if (m_state == ENEMY_DEATH)
	{
		// �p�x�̐ݒ�
		D3DXVECTOR3 rotDest = D3DXVECTOR3(D3DX_PI * 0.5f, rot.y, rot.z);
		D3DXVECTOR3 rotResult = rotDest - rot;

		rotResult = NormalizeRotXYZ(rotResult);

		// ��]�̉��Z
		rot += rotResult * 0.01f;

		float EnemySpeed = 5.0f;

		m_move = D3DXVECTOR3(sinf(rot.y) * EnemySpeed,
			-(rot.x * EnemySpeed),
			cosf(rot.y) * EnemySpeed);

		// �v���C���[�̌������߂�
		D3DXVECTOR3 BackPos = MtxPosRot(D3DXVECTOR3(0.0f, 0.0f, -50.0f), rot, m_pos);

		auto FloatRandom = [](float fMax, float fMin)
		{
			return ((rand() / (float)RAND_MAX) * (fMax - fMin)) + fMin;
		};

		for (int i = 0; i < 10; i++)
		{
			D3DXVECTOR3 pos = GetPosition();

			pos.x += FloatRandom(2.5f, -2.5f);
			pos.y += FloatRandom(2.5f, -2.5f);
			pos.z += FloatRandom(2.5f, -2.5f);

			CEffect *pEffect = CEffect::Create(D3DXVECTOR3(pos.x + FloatRandom(1.0f, -1.0f), pos.y, pos.z + FloatRandom(1.0f, -1.0f)), 0, 0, CTexture::TEXTURE_PARTIClE);
			pEffect->SetSize(D3DXVECTOR3(15.0f, 15.0f, 0.0f));
			pEffect->SetMoveVec(D3DXVECTOR3(0.0f, FloatRandom(1.5f, -1.5f), FloatRandom(10.5f, -10.5f)));
			pEffect->SetLife(25);
			pEffect->SetRenderMode(CEffect::MODE_ADD);

			pEffect->SetColor(D3DXCOLOR(1.0f, FloatRandom(0.5f, 0.0f), 0.1f, 1.0f));

			pEffect->SetTex(CTexture::TEXTURE_PARTIClE);
			pEffect->SetQuaternion(m_quaternion);
		}
	}

	// ���W�̐ݒ�
	SetPosition(m_pos);

	// �G�l�~�[�̓����蔻��
	EnemyCollision();

	if (m_apModel[0] != nullptr)
	{
		// �G�l�~�[�̉�]�̐ݒ�
		m_apModel[0]->SetRot(rot);
	}

	// ��]�̐ݒ�
	SetRotation(rot);

	if (m_Radar != nullptr)
	{
		m_Radar->SetRotation(D3DXVECTOR3(0.0f,-GetRot().y,0.0f));
	}

	// ���[�V�����̍X�V����
	CMotionModel3D::Update();

	// �J�����̎��_
	//CDebugProc::Print("�G�l�~�[�̃X�N���[�����W : (%.3f , %.3f , %.3f )\n", m_pos.x, m_pos.y, m_pos.z);
}

//=========================================
//�I�u�W�F�N�g�̏I������
//=========================================
void CEnemy::Uninit()
{
	// ���f���̉��
	m_apModel[0]->Uninit();
	delete m_apModel[0];
	m_apModel[0] = nullptr;

	// ���[�V�����̏I������
	CMotionModel3D::Uninit();

	// �I�u�W�F�N�g�̉��
	CObject::Release();
}

//=========================================
//�I�u�W�F�N�g�̕`�揈��
//=========================================
void CEnemy::Draw()
{
	// �f�o�C�X�̎擾
	PDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;
	D3DXMATRIX mtxParents;

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXVECTOR3 scale(5.0f, 5.0f, 5.0f);

	// �J�����O�̐ݒ�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_WorldMtx);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);                // �s��ړ��֐�
	D3DXMatrixMultiply(&m_WorldMtx, &m_WorldMtx, &mtxTrans);					// �s��|���Z�֐�

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_WorldMtx);

	// ������
	if (m_apModel[0] != nullptr)
	{
		m_apModel[0]->Draw();
	}

	// ���[�V�����̕`�揈��
	CMotionModel3D::Draw();

	SetMtxWorld(m_WorldMtx);
}

//=========================================
// ���S����
//=========================================
void CEnemy::Death()
{
	if (CApplication::GetMode() != CApplication::MODE_GAME)
	{
		return;
	}

	int nLife = GetHP();

	if (nLife <= 0 && m_state != ENEMY_DEATH)
	{
		CApplication::GetGame()->GetPM()->GetPlayer()->AddBullet();
		CSerihu::Create(CSerihu::SHOUT_DOWN);
		CGame::Add(1000);

		if (m_Target != nullptr)
		{
			// �^�[�Q�b�g�̏I������
			m_Target->Uninit();
			m_Target = nullptr;
		}

		if (m_Radar != nullptr)
		{
			// ���[�_�[�̏I������
			m_Radar->Uninit();
			m_Radar = nullptr;
		}

		m_state = ENEMY_DEATH;
	}
}

//=========================================
//�I�u�W�F�N�g�̃N���G�C�g
//=========================================
CEnemy* CEnemy::Create(const D3DXVECTOR3 &pos, const EnemyType &type,const int &Wave)
{
	CEnemy* pCEnemy = nullptr;

	pCEnemy = new CEnemy;

	if (pCEnemy != nullptr)
	{
		pCEnemy->SetWave(Wave);
		pCEnemy->SetType(type);
		pCEnemy->SetPosition(pos);
		pCEnemy->Init(pos);
		
		// �G�l�~�[�ԍ��̎w��
		pCEnemy->SetNumber(nEnemyNumber);
		// �G�l�~�[�ԍ��̉��Z
		nEnemyNumber++;
	}

	return pCEnemy;
}

//=========================================
// �G�l�~�[�̒e���ˏ���
//=========================================
void CEnemy::Bullet(CObject *obj)
{
	// ��������e�𔭎˂���
	CBullet3D::Create(D3DXVECTOR3(50.0f, 50.0f, 0.0f), m_quaternion, obj, this, 60 , D3DX_PI * 0.1f);
	CBullet3D::Create(D3DXVECTOR3(-50.0f, 50.0f, 0.0f), m_quaternion, obj, this, 60 , D3DX_PI * 0.1f);

	m_AttackCount = 0;
}

//=========================================
// �G�l�~�[���m�̓����蔻��
//=========================================
void CEnemy::EnemyCollision()
{
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		CObject *object = CObject::GetObjectTop(nCnt);

		//�v���C���[�̍��W���擾
		while (object)
		{
			if (object != nullptr)
			{
				EObjType ObjType = object->GetObjectType();

				if (ObjType == OBJECT_ENEMY && object != this)
				{
					SetCollision(Collision(object, true));
				}
			}
			object = object->GetObjectNext();
		}
	}
}

//=========================================
// �^�C�v�ƃ��[�V�����̐ݒ�
//=========================================
void CEnemy::SetType(EnemyType type)
{
	// �^�C�v�̐ݒ�
	m_type = type;

	switch (m_type)
	{
	case ENEMY_FLY:
		SetMotion("data/MOTION/fly_motion.txt");
		break;

	case ENEMY_GROUND:
		SetMotion("data/MOTION/tank.txt");
		break;

	case ENEMY_TUTORIAL:
		SetMotion("data/MOTION/fly_motion.txt");
		break;
	}
}

//=========================================
// �v���C���[�����͈͓̔��ɓ����������肷�鏈��
//=========================================
void CEnemy::Search()
{
	//// ���_�ƒ����_�̋���
	//D3DXVECTOR3 posDiss = m_pos - m_PlayerPos;
	//float fDistance = sqrtf((posDiss.y * posDiss.y) + (posDiss.x * posDiss.x) + (posDiss.z * posDiss.z));

	//if ((fDistance >= -1000.0f && fDistance <= 1000.0f ) && m_state != ENEMY_DEATH)
	//{// �G�l�~�[��G�Ώ�Ԃɂ���
	//	m_state = ENEMY_WARNNING;
	//}
}

//=========================================
// �^�[�Q�b�g��Ԃ����߂�
//=========================================
void CEnemy::TargetSetColor(D3DXCOLOR col)
{
	if(m_Target != nullptr)
	{ 
	m_Target->SetColor(col);
	}
}