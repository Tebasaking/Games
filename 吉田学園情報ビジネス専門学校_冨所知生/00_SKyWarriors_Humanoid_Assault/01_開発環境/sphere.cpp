//=========================================
//
//	�r���{�[�h�̏���
//	Author:�y���m��
//
//=========================================
#include "application.h"
#include "sphere.h"
#include "texture.h"

//=========================================
//�R���X�g���N�^
//=========================================
CSphere::CSphere()
{
	m_pVtxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 1000.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// �e�N�X�`���̐ݒ�
	CSphere::SetTexture(CTexture::TEXTURE_SKY);
}

//=========================================
//�f�X�g���N�^
//=========================================
CSphere::~CSphere()
{

}

//=========================================
//�I�u�W�F�N�g�̏���������
//=========================================
HRESULT CSphere::Init(const D3DXVECTOR3 &pos)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * SPHERE_VERTEX_NUM,	//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,													//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * SPHERE_INDEX_NUM,			//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,													//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pIdxVtxBuff,
		NULL);

	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_pos = pos;
	float RotZ = 0.0f;
	float Radius = 0.0f;

	for (int nCntZ = 0; nCntZ <= SPHERE_Z_BLOCK; nCntZ++)
	{
		RotZ = (D3DX_PI / SPHERE_Z_BLOCK * 0.55f) * nCntZ;
		Radius = sinf(RotZ) * SPHERE_SIZE;

		for (int nCntX = 0; nCntX <= SPHERE_X_BLOCK; nCntX++)
		{
			//���_���W�̐ݒ�i���[���h���W�ł͂Ȃ����[�J�����W���w�肷��j
			pVtx[nCntX + (SPHERE_X_BLOCK + 1) * nCntZ].pos = D3DXVECTOR3
			(sinf(nCntX * ((D3DX_PI * 2.0f) / SPHERE_X_BLOCK)) * Radius,				//x
				cosf(RotZ) * SPHERE_SIZE,									//y
				-cosf(nCntX  * ((D3DX_PI * 2.0f) / SPHERE_X_BLOCK)) * Radius);			//z

			//�e���_�̖@���̐ݒ�
			pVtx[nCntX + (SPHERE_X_BLOCK + 1) * nCntZ].nor = pVtx[nCntX + (SPHERE_X_BLOCK + 1) * nCntZ].pos;

			//�@���̐��K��
			D3DXVec3Normalize(&pVtx[nCntX + (SPHERE_X_BLOCK + 1) * nCntZ].nor, &pVtx[nCntX + (SPHERE_X_BLOCK + 1) * nCntZ].nor);

			//���_�J���[�̐ݒ�
			pVtx[nCntX + (SPHERE_X_BLOCK + 1) * nCntZ].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`���̐ݒ�
			pVtx[(nCntX + (SPHERE_X_BLOCK + 1) * nCntZ)].tex = D3DXVECTOR2((float)1.0f / SPHERE_X_BLOCK * nCntX, (float)1.0f / SPHERE_Z_BLOCK * nCntZ);
		}
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIdx;
	m_pIdxVtxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//�c�̒��_�̐�
	for (int nCntZ = 0; nCntZ < SPHERE_Z_BLOCK; nCntZ++)
	{
		//�C���f�b�N�X
		int nLineTop = nCntZ * (m_LineVtx * 2 + 2);

		//���̒��_�̐�
		for (int nCntX = 0; nCntX < m_LineVtx; nCntX++)
		{//��̒i�̏���
			pIdx[(nCntX * 2 + 1) + nLineTop] = (WORD)(nCntX + m_LineVtx * nCntZ);

			//���̒i�̏���
			pIdx[nCntX * 2 + nLineTop] = (WORD)(pIdx[(nCntX * 2 + 1) + nLineTop] + m_LineVtx);
		}

		//�k�ރ|���S����O��Ɠ���ɂ��鏈��
		if (nCntZ < SPHERE_Z_BLOCK)
		{
			pIdx[(m_LineVtx * 2) + nLineTop] = (WORD)(SPHERE_X_BLOCK + (m_LineVtx)* nCntZ);
			pIdx[(m_LineVtx * 2) + nLineTop + 1] = (WORD)(2 * (m_LineVtx)+(m_LineVtx)* nCntZ);
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxVtxBuff->Unlock();

	return S_OK;
}

//=========================================
//�I�u�W�F�N�g�̍X�V����
//=========================================
void CSphere::Update()
{

}

//=========================================
//�I�u�W�F�N�g�̏I������
//=========================================
void CSphere::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	if (m_pIdxVtxBuff != nullptr)
	{
		m_pIdxVtxBuff->Release();
		m_pIdxVtxBuff = nullptr;
	}

	CObject::Release();
}

//=========================================
//�I�u�W�F�N�g�̕`�揈��
//=========================================
void CSphere::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();
	CTexture* pTexture = CApplication::GetTexture();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetTexture(m_texture));

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetTexture(m_texture));

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// �J�����O�̐ݒ�

																		// ���C�g�𖳌�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX	mtxRot, mtxTrans, mtxView;

	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��������[�s��]��[�P�ʍs��]�ɏ�����)
	D3DXMatrixIdentity(&m_mtxWorld);

	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// �����̔��f
	// �s���]�֐� (��������[���[(y)�s�b�`(x)���[��(z)]�����̉�]�s����쐬)
	D3DXMatrixRotationZ(&mtxRot, -m_rot.z);

	// �s��|���Z�֐� (������ * ��O������������Ɋi�[)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);		// �s��|���Z�֐�

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxVtxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ���b�V���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, SPHERE_VERTEX_NUM, 0, SPHERE_PRIMITIVE_NUM);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// �J�����O�̐ݒ�
																		// ���C�g��L��	
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, nullptr);
}

//=========================================
//�I�u�W�F�N�g�̃N���G�C�g
//=========================================
CSphere* CSphere::Create(const D3DXVECTOR3 &pos)
{
	int nNumCreate = m_nNumAll;

	CSphere* pCSphere = nullptr;

	pCSphere = new CSphere;

	if (pCSphere != nullptr)
	{
		pCSphere->Init(pos);
	}

	return pCSphere;
}

//=========================================
//���W�̐ݒ菈��
//=========================================
void CSphere::SetPosition(const D3DXVECTOR3& pos)
{
	m_pos = pos;
}

//=========================================
// �e�N�X�`���̐ݒ�
//=========================================
void CSphere::SetTexture(CTexture::TEXTURE texture)
{
	m_texture = texture;
}

//=========================================
//�T�C�Y�̐ݒ�
//=========================================
void CSphere::SetSize(const float size)
{
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	m_scale = size;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-size, size, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(size, size, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-size, -size, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(size, -size, 0.0f);

	// ���_���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=========================================
//�e�N�X�`���̐ݒ�
//=========================================
void CSphere::SetAnim(const float Num, const int Pattern)
{
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	float PatternSize = 1.0f / Pattern;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//tex�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(Num * PatternSize, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(Num * PatternSize + PatternSize, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(Num * PatternSize, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(Num * PatternSize + PatternSize, 1.0f);

	// ���_���A�����b�N����
	m_pVtxBuff->Unlock();
}