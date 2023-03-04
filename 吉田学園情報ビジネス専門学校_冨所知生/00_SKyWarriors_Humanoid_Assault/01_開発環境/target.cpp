//=========================================
//
//	�^�[�Q�b�g�̏���
//	Author:�y���m��
//
//=========================================
#include "target.h"
#include "application.h"
#include "debug_proc.h"

D3DXVECTOR3 CTarget::m_TargetPos = {};
//=========================================
//�R���X�g���N�^
//=========================================
CTarget::CTarget()
{

}

//=========================================
//�f�X�g���N�^
//=========================================
CTarget::~CTarget()
{

}

//=========================================
//�I�u�W�F�N�g�̏���������
//=========================================
HRESULT CTarget::Init(const D3DXVECTOR3 &pos)
{
	//����������
	CObject2D::Init(pos);

	// �e�N�X�`���̐ݒ�
	CObject2D::SetTexture(CTexture::TEXTURE_TARGET);

	//�T�C�Y�̐ݒ�
	CObject2D::SetScale(D3DXVECTOR3(0.0f,0.0f,0.0f));

	// �^�C�v�ݒ�
	SetObjectType(OBJECT_TARGET);

	return S_OK;
}

//=========================================
//�I�u�W�F�N�g�̍X�V����
//=========================================
void CTarget::Update()
{
	D3DXVECTOR3 EnemyPos;			// �G�l�~�[�̕ϊ��O���W
	D3DXVECTOR3 PlayerPos;			// �v���C���[�̍��W

	//�v���C���[�̍��W���擾
	if (pObject != nullptr)
	{
		// �ڕW�̍��W���X�N���[�����W�ɕϊ�����
		EnemyPos = pObject->GetPosition();
		m_TargetPos = CApplication::WorldToScreen(EnemyPos);
	}

	if (m_TargetPos.x >= 0.0f && m_TargetPos.x <= SCREEN_WIDTH &&
		m_TargetPos.y >= 0.0f && m_TargetPos.y <= SCREEN_HEIGHT &&
		m_TargetPos.z >= 0.0f)
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

					if (ObjType == OBJECT_PLAYER)
					{
						PlayerPos = object->GetPosition();

						if (PlayerPos.x > 0.0f || PlayerPos.x < 0.0f)
						{
							int nCnt = 0;
						}
						break;
					}
				}
				object = object->GetObjectNext();
			}
		}

		//�v���C���[�ƃG�l�~�[�̋���
		D3DXVECTOR3 PtoE_Diss = PlayerPos - EnemyPos;
		float PtoE_Distance = sqrtf((PtoE_Diss.y * PtoE_Diss.y) + (PtoE_Diss.x * PtoE_Diss.x) + (PtoE_Diss.z * PtoE_Diss.z));

		//�������}�C�i�X��������v���X�ɂ��鏈��
		//������̂����Ńv���C���[�̌��ɃG�l�~�[���s�����������^�[�Q�b�g���傫���Ȃ�ׂ��Ȃ񂾂��Ǐ������Ȃ�
		if (PtoE_Distance <= 0)
		{
			PtoE_Distance *= -1;
		}

		float Conversion = ((1.0f / PtoE_Distance));

		//�����ɉ����ăT�C�Y�����߂�
		m_Size = 10000.0f * (Conversion);

		//�ő�T�C�Y
		if (m_Size >= 200.0f)
		{
			m_Size = 200.0f;
		}
		//�ŏ��T�C�Y
		else if (m_Size <= 10.0f)
		{
			m_Size = 10.0f;
		}

		D3DXVECTOR3 pos = GetPosition();

		//�T�C�Y�̐ݒ�
		CObject2D::SetScale(D3DXVECTOR3(m_Size,m_Size,0.0f));

		// �X�N���[�����W�ɐݒ肷��
		SetPosition(m_TargetPos);
	}
	else
	{
		m_Size = 0;

		//�T�C�Y�̐ݒ�
		CObject2D::SetScale(D3DXVECTOR3(0.0f,0.0f,0.0f));
	}

	//// �I�u�W�F�N�g�����S���Ă�����
	//if (pObject == nullptr)
	//{
	//	Uninit();
	//}

	//EObjType obj = GetObjectType();
	//CTarget *pTagert = this;

	// �J�����̎��_
	//CDebugProc::Print("�^�[�Q�b�g�̃T�C�Y %f \n", m_Size);
}

//=========================================
//�I�u�W�F�N�g�̏I������
//=========================================
void CTarget::Uninit()
{
	// �I������
	CObject2D::Uninit();
}

//=========================================
//�I�u�W�F�N�g�̕`�揈��
//=========================================
void CTarget::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();

	// Z�e�X�g���g�p����
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);

	// ���e�X�g���g�p����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// ���e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	{
		// 2D�I�u�W�F�N�g�̕`�揈��
		CObject2D::Draw();
	}

	// Z�e�X�g�̏I��
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// ���e�X�g�̏I��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=========================================
//�I�u�W�F�N�g�̃N���G�C�g
//=========================================
CTarget* CTarget::Create(const D3DXVECTOR3 &pos, CObject *object)
{
	int nNumCreate = m_nNumAll;

	CTarget* pCTarget = nullptr;

	pCTarget = new CTarget;

	if (pCTarget != nullptr)
	{
		pCTarget->Init(pos);
	}
	
	// �^�[�Q�b�g��ݒ肷��I�u�W�F�N�g���擾
	pCTarget->SetObject(object);

	return pCTarget;
}