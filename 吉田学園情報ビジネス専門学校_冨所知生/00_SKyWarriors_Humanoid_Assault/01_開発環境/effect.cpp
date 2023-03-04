//=========================================
//
//	3D�G�t�F�N�g�̏���(3D [�r���{�[�h])
//	Author:�y���m��
//
//=========================================
#include "explosion.h"
#include "application.h"
#include "texture.h"
#include "calculation.h"
#include "explosion.h"
#include "missile_locus.h"
#include "sound.h"
#include "effect.h"

//=========================================
//�R���X�g���N�^
//=========================================
CEffect::CEffect()
{
	SetObjectType(OBJECT_EFFECT);
	nAnimCount = 0;
	nAnimNum = 0;
}

//=========================================
//�f�X�g���N�^
//=========================================
CEffect::~CEffect()
{

}

//=========================================
//�I�u�W�F�N�g�̏���������
//=========================================
HRESULT CEffect::Init(const D3DXVECTOR3 &pos)
{
	CBillboard::Init(pos);

	// ���W
	m_pos = pos;

	m_RandAlfa = (float)(rand() % 10 + 1) * 0.01f;

	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// Z�o�b�t�@�̐ݒ�
	SetZFunc(D3DCMP_ALWAYS);

	// ���e�X�g�̓��ߗ��̐ݒ�
	SetAlphaValue(50);
	
	//�T�C�Y�̐ݒ�
	CBillboard::SetSize(D3DXVECTOR3(40.0f,40.0f,0.0f));

	// �e�N�X�`���̐ݒ�
	CBillboard::SetTexture(m_tex);

	return S_OK;
}

//=========================================
//�I�u�W�F�N�g�̍X�V����
//=========================================
void CEffect::Update()
{
	// �ʒu�̎擾
	//D3DXVECTOR3 pos = GetPosition();
	D3DXCOLOR col = GetColor();

	//// �F�������_���ŉ����Ă���
	//m_col = GetColor();
	col.a -= 0.01f;

	SetColor(col);

	D3DXVECTOR3 size = GetSize();
	size.x += -0.75f;
	size.y += -0.75f;
	size.z += -0.75f;
	SetSize(size);

	// �ʒu�̍X�V
	//SetPosition(pos);

	// ���C�t�̌���
	DecreaseLife();

	if (col.a <= 0.0f || m_nLife == 0 || size.x <= 0.0f)
	{
		Uninit();
	}
}

//=========================================
//�I�u�W�F�N�g�̏I������
//=========================================
void CEffect::Uninit()
{
	CBillboard::Uninit();
}

//=========================================
//�I�u�W�F�N�g�̕`�揈��
//=========================================
void CEffect::Draw()
{
	// �����_�[�̎擾
	CRender *pRender = CApplication::GetRender();
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	switch (m_renderMode)
	{
	case CEffect::MODE_NORMAL:
		break;

	case CEffect::MODE_ADD:
		// ���u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;

	case CEffect::MODE_SUB:
		// ���u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;

	default:
		break;
	}

	CBillboard::Draw();

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
}

//=========================================
//�I�u�W�F�N�g�̃N���G�C�g
//=========================================
CEffect* CEffect::Create(const D3DXVECTOR3 &pos, int ANIM_SPEED, int ANIM_MAX, CTexture::TEXTURE tex)
{
	int nNumCreate = m_nNumAll;

	CEffect* pEffect = nullptr;

	pEffect = new CEffect;

	if (pEffect != nullptr)
	{
		pEffect->m_tex = tex;
		pEffect->SetTexture(tex);
		pEffect->Init(pos);
		pEffect->m_ANIM_MAX = ANIM_MAX;
		pEffect->m_ANIM_SPEED = ANIM_SPEED;
	}

	return pEffect;
}

//=============================================================================
// ���C�t�̌�������
// Author : �������l
// �T�v : 2D�`����s��
//=============================================================================
void CEffect::DecreaseLife()
{
	if (m_nLife > 0)
	{
		D3DXVECTOR3 size = GetSize();
		D3DXCOLOR color = GetColor();

		// ���C�t�̌���
		m_nLife--;
		SetSize(size - m_subSize);
		SetColor(D3DXCOLOR(color.r, color.g, color.b, color.a - m_fSubAlpha));

		if (m_nLife <= 0)
		{
			m_nLife = 0;
		}
	}
}
