//=========================================
//
//	�^�C�g���̃I�u�W�F�N�g�̏���
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
#include "title_model.h"
#include "effect.h"
#include "object.h"

//=========================================
//�R���X�g���N�^
//=========================================
CTitleModel::CTitleModel(int nPriority) : CMotionModel3D(LAYER_FIVE)
{
	SetObjectType(OBJECT_ENEMY);
	SetHP(10);
	m_type = ENEMY_MAX;
}

//=========================================
//�f�X�g���N�^
//=========================================
CTitleModel::~CTitleModel()
{
}

//=========================================
//�I�u�W�F�N�g�̏���������
//=========================================
HRESULT CTitleModel::Init(const D3DXVECTOR3 &pos)
{
	m_PlayerPos = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);

	m_apModel[0] = new CModel3D;

	m_apModel[0]->SetModelID(3);
	m_apModel[0]->Init();
	m_apModel[0]->SetPos(pos);

	m_pos = pos;

	//�g�嗦�̐ݒ�
	m_apModel[0]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	// ���W�̐ݒ�
	SetPosition(pos);

	// �Â����W�̐ݒ�
	SetPosOld(m_pos);

	m_scale = 1.0f;

	// ���[�V�����̏���������
	CMotionModel3D::Init(pos);

	if (m_type == ENEMY_GROUND)
	{
		//�傫���̐ݒ�
		SetSize(D3DXVECTOR3(2.0f,2.0f,2.0f));
	}
	else if (m_type == ENEMY_FLY)
	{
		//�傫���̐ݒ�
		SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	}

	return S_OK;
}

//=========================================
//�I�u�W�F�N�g�̍X�V����
//=========================================
void CTitleModel::Update()
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

	// ���W�̎擾
	m_pos = GetPosition();

	// �I�u�W�F�N�g�̎擾
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		CObject *object = CObject::GetObjectTop(nCnt);

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
					break;
				}
			}
			object = object->GetObjectNext();
		}
	}

	D3DXVECTOR3 rot = GetRot();

	//if (SearchEye(PlayerPos, m_pos, D3DX_PI * 0.5f, 100.0f, rot.y))
	//{
	//	m_state = ENEMY_WARNNING;
	//}

	float EnemySpeed = 5.0f;

	// �ړ��ʗp
	D3DXVECTOR3 move = move = D3DXVECTOR3(sinf(rot.y) * EnemySpeed,
		-(rot.x * EnemySpeed),
		cosf(rot.y) * EnemySpeed);

	{
		if (m_type == ENEMY_FLY)
		{
		
			rot.y += 0.01f;

			// �ړ���
			move = D3DXVECTOR3(sinf(rot.y) * EnemySpeed,
				-(rot.x * EnemySpeed),
				cosf(rot.y) * EnemySpeed);

			// �v���C���[�̌������߂�
			D3DXVECTOR3 BackPos = MtxPos(D3DXVECTOR3(0.0f, 0.0f, -25.0f), m_quaternion, m_pos);

			for (int i = 0; i < 10; i++)
			{
				D3DXVECTOR3 pos = BackPos;

				pos.x += FloatRandom(5.5f, -5.5f);
				pos.y += FloatRandom(5.5f, -5.5f);
				pos.z += FloatRandom(5.5f, -5.5f);

				CEffect *pEffect = CEffect::Create(D3DXVECTOR3(pos.x + FloatRandom(1.0f, -1.0f), pos.y, pos.z + FloatRandom(1.0f, -1.0f)), 0, 0, CTexture::TEXTURE_PARTIClE);
				pEffect->SetSize(D3DXVECTOR3(8.0f, 8.0f, 0.0f));
				pEffect->SetMoveVec(D3DXVECTOR3(0.0f, FloatRandom(1.5f, -1.5f), FloatRandom(1.5f, -1.5f)));
				pEffect->SetLife(15);
				pEffect->SetRenderMode(CEffect::MODE_ADD);

				pEffect->SetColor(D3DXCOLOR(1.0f, FloatRandom(0.5f, 0.0f), 0.1f, 1.0f));

				pEffect->SetTex(CTexture::TEXTURE_PARTIClE);
				pEffect->SetQuaternion(m_quaternion);
				
				// �ړ��ʂ����Z����
				m_pos += move;
			}

		}

		if (m_type == ENEMY_GROUND)
		{
			move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			rot.z = -D3DX_PI * 0.25f;
		}
	}

	// ���W�̐ݒ�
	SetPosition(m_pos);

	// �G�l�~�[�̉�]�̐ݒ�
	m_apModel[0]->SetRot(rot);

	// ��]�̐ݒ�
	SetRotation(rot);

	// ���[�V�����̍X�V����
	CMotionModel3D::Update();

	// �J�����̎��_
	//CDebugProc::Print("�G�l�~�[�̃X�N���[�����W : (%.3f , %.3f , %.3f )\n", m_pos.x, m_pos.y, m_pos.z);
}

//=========================================
//�I�u�W�F�N�g�̏I������
//=========================================
void CTitleModel::Uninit()
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
void CTitleModel::Draw()
{
	if (this == nullptr)
	{
		return;
	}

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
	m_apModel[0]->Draw();

	// ���[�V�����̕`�揈��
	CMotionModel3D::Draw();

	SetMtxWorld(m_WorldMtx);
}

//=========================================
//�I�u�W�F�N�g�̃N���G�C�g
//=========================================
CTitleModel* CTitleModel::Create(const D3DXVECTOR3 &pos, const ModelType &type)
{
	CTitleModel* pModel = nullptr;

	pModel = new CTitleModel;

	if (pModel != nullptr)
	{
		pModel->SetType(type);
		pModel->SetPosition(pos);
		pModel->Init(pos);
	}

	return pModel;
}

//=========================================
// �^�C�v�ƃ��[�V�����̐ݒ�
//=========================================
void CTitleModel::SetType(ModelType type)
{
	// �^�C�v�̐ݒ�
	m_type = type;

	switch (m_type)
	{
	case ENEMY_FLY:
		SetMotion("data/MOTION/fly_motion.txt");
		break;

	case ENEMY_GROUND:
		SetMotion("data/MOTION/fly_motion.txt");
		break;
	}
}