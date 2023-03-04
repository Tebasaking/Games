//=========================================
//
//	�r���{�[�h�̏���
//	Author:�y���m��
//
//=========================================
#include "billboard.h"
#include "application.h"
#include "texture.h"

#define POLYGON_SIZE (400.0f)

//=========================================
//�R���X�g���N�^
//=========================================
CBillboard::CBillboard(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetObjectType(OBJECT_EFFECT);
	m_texture = CTexture::TEXTURE_NONE;
	m_zFunc = D3DCMP_LESS;							// Z�e�X�g�̗D��x
	m_nAlphaValue = 0;								// �A���t�@�e�X�g�̓��ߗ�
	m_bBill = true;
}

//=========================================
//�f�X�g���N�^
//=========================================
CBillboard::~CBillboard()
{

}

//=========================================
//�I�u�W�F�N�g�̏���������
//=========================================
HRESULT CBillboard::Init(const D3DXVECTOR3 &pos)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer
	(sizeof(VERTEX_3D) * 4,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,		// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	m_texture = CTexture::TEXTURE_FIRE;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_pos = pos;

	//�e���_�̖@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f,0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f,0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f,0.0f);

	//tex�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���A�����b�N����
	m_pVtxBuff->Unlock();

	SetSize(D3DXVECTOR3(10.0f,10.0f,0.0f));

	Draw();

	return S_OK;
}

//=========================================
//�I�u�W�F�N�g�̍X�V����
//=========================================
void CBillboard::Update()
{
	//SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
}

//=========================================
//�I�u�W�F�N�g�̏I������
//=========================================
void CBillboard::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	CObject::Release();
}

//=========================================
//�I�u�W�F�N�g�̕`�揈��
//=========================================
void CBillboard::Draw()
{
	//	m_texture = CTexture::TEXTURE_NONE;

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();
	CTexture* pTexture = CApplication::GetTexture();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetTexture(m_texture));

	// �J�����O�̐ݒ�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	// Z�e�X�g���g�p����
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZFUNC, m_zFunc);

	// ���e�X�g���g�p����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// ���e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, m_nAlphaValue);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���C�g�𖳌�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxView;

	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��������[�s��]��[�P�ʍs��]�ɏ�����)
	D3DXMatrixIdentity(&m_mtxWorld);

	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	if (m_bBill)
	{
		// �J�����t�s���ݒ�
		D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);
		m_mtxWorld._41 = 0.0f;
		m_mtxWorld._42 = 0.0f;
		m_mtxWorld._43 = 0.0f;
	}
	else
	{
		// �����̔��f
		D3DXVECTOR3 rot = GetRot();

		// �����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, D3DX_PI * 0.5f, rot.z);			// �s���]�֐�
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);						// �s��|���Z�֐� 
	}

	// �ʒu�𔽉f
	// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);		// �s��|���Z�֐�
	
	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �r���{�[�h�`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// �J�����O�̐ݒ�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	// ���C�g��L��	
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���e�X�g�̏I��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, nullptr);

	SetMtxWorld(m_mtxWorld);

	// ���ɖ߂�
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
}

//=========================================
//�I�u�W�F�N�g�̃N���G�C�g
//=========================================
CBillboard* CBillboard::Create(const D3DXVECTOR3 &pos)
{
	int nNumCreate = m_nNumAll;

	CBillboard* pCBillboard = nullptr;

	pCBillboard = new CBillboard(LAYER_FIVE);

	if (pCBillboard != nullptr)
	{
		pCBillboard->Init(pos);
	}

	return pCBillboard;
}

//=========================================
//���W�̐ݒ菈��
//=========================================
void CBillboard::SetPosition(const D3DXVECTOR3& pos)
{
	m_pos = pos;
}

//=========================================
// �e�N�X�`���̐ݒ�
//=========================================
void CBillboard::SetTexture(CTexture::TEXTURE texture)
{
	m_texture = texture;
}

//=========================================
//�T�C�Y�̐ݒ�
//=========================================
void CBillboard::SetSize(const D3DXVECTOR3 size)
{
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	m_scale = size;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_scale.x, m_scale.y * 0.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_scale.x, m_scale.y * 0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_scale.x,-m_scale.y * 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_scale.x,-m_scale.y * 0.5f, 0.0f);

	// ���_���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=========================================
//�T�C�Y�̐ݒ�
//=========================================
void CBillboard::SetColor(const D3DXCOLOR &col)
{
	if (m_pVtxBuff == nullptr)
	{
		return;
	}

	// �F�̐ݒ�
	m_col = col;

	// ���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̍X�V
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// ���_���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=========================================
//�e�N�X�`���̐ݒ�
//=========================================
void CBillboard::SetAnim(const float NumX, const int PatternX, const int NumY, const int PatternY)
{
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	float PatternSizeX = 1.0f / PatternX;
	float PatternSizeY = 1.0f / PatternY;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//tex�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(NumX * PatternSizeX, NumY * PatternSizeY);
	pVtx[1].tex = D3DXVECTOR2(NumX * PatternSizeX + PatternSizeX, NumY * PatternSizeY);
	pVtx[2].tex = D3DXVECTOR2(NumX * PatternSizeX, NumY * PatternSizeY + PatternSizeY);
	pVtx[3].tex = D3DXVECTOR2(NumX * PatternSizeX + PatternSizeX, NumY * PatternSizeY + PatternSizeY);

	// ���_���A�����b�N����
	m_pVtxBuff->Unlock();
}