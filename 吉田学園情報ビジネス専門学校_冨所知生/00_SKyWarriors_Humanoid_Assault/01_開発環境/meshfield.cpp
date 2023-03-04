//=========================================
//
//	�r���{�[�h�̏���
//	Author:�y���m��
//
//=========================================
#include "application.h"
#include "meshfield.h"
#include "texture.h"
#include "calculation.h"

//=========================================
//�R���X�g���N�^
//=========================================
CMesh::CMesh(int nPriority)
{
	SetObjectType(OBJECT_MESH);
	m_pVtxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_MeshSize = 0;
}

//=========================================
//�f�X�g���N�^
//=========================================
CMesh::~CMesh()
{

}

//=========================================
//�I�u�W�F�N�g�̏���������
//=========================================
HRESULT CMesh::Init(const D3DXVECTOR3 &pos)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();

	// �^�C�v�ɑΉ������e�N�X�`���̐ݒ�
	switch (m_type)
	{
	case TYPE_SEA:
		m_texture = CTexture::TEXTURE_WAVE;
		SetMeshSize(100000.0f);
		SetBlock(2.0f, 2.0f);
		break;

	case TYPE_WAVE:
		m_texture = CTexture::TEXTURE_SEA;
		SetMeshSize(3000.0f);
		SetBlock(10.0f, 10.0f);
		break;

	case TYPE_GROUND:
		m_texture = CTexture::TEXTURE_GROUND;
		SetMeshSize(1000.0f);
		SetBlock(20.0f, 20.0f);
		break;
	}

	// �u���b�N��
	int MESH_X_BLOCK = m_BlockX;
	int MESH_Z_BLOCK = m_BlockZ;

	MESH_VERTEX_NUM = ((MESH_X_BLOCK + 1) * (MESH_Z_BLOCK + 1));
	MESH_INDEX_NUM = (((MESH_X_BLOCK + 1) * 2) * (MESH_Z_BLOCK  *(MESH_Z_BLOCK - 1)) * MESH_Z_BLOCK * 2);
	MESH_PRIMITIVE_NUM = (MESH_X_BLOCK * MESH_Z_BLOCK * 2 + 4 * (MESH_Z_BLOCK - 1));

	// ���_���̕�m_fVtxHeight���擾
	m_fVtxHeight.resize(MESH_VERTEX_NUM);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESH_VERTEX_NUM,	//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,													//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESH_INDEX_NUM,			//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,													//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pIdxVtxBuff,
		NULL);

	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_pos = pos;

	switch (m_type)
	{
	case TYPE_SEA:
		for (int nCntZ = 0; nCntZ <= MESH_Z_BLOCK; nCntZ++)
		{
			for (int nCntX = 0; nCntX <= MESH_X_BLOCK; nCntX++)
			{
				//���_���W�̐ݒ�i���[���h���W�ł͂Ȃ����[�J�����W���w�肷��j
				pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].pos = D3DXVECTOR3
				(-(m_MeshSize * MESH_X_BLOCK) / 2 + nCntX * m_MeshSize,					// x
					sinf(nCntX * D3DX_PI * 0.25f) * 10.0f,								// y
					(m_MeshSize * MESH_Z_BLOCK) / 2 - nCntZ * m_MeshSize);				// z

				//�e���_�̖@���̐ݒ�
				pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				//���_�J���[�̐ݒ�
				pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//�e�N�X�`���̐ݒ�
				pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].tex = D3DXVECTOR2((float)nCntX, (float)nCntZ);
			}
		}
		break;

	case TYPE_WAVE:
		for (int nCntZ = 0; nCntZ <= MESH_Z_BLOCK; nCntZ++)
		{
			for (int nCntX = 0; nCntX <= MESH_X_BLOCK; nCntX++)
			{
				//���_���W�̐ݒ�i���[���h���W�ł͂Ȃ����[�J�����W���w�肷��j
				pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].pos = D3DXVECTOR3
				(-(m_MeshSize * MESH_X_BLOCK) / 2 + nCntX * m_MeshSize,					// x
					sinf(nCntX * nCntZ) * 100.0f ,										// y
					(m_MeshSize * MESH_Z_BLOCK) / 2 - nCntZ * m_MeshSize);				// z

				// ���_�̍���
				m_fVtxHeight[nCntX + (MESH_X_BLOCK + 1) * nCntZ] = pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].pos.y;

				//�e���_�̖@���̐ݒ�
				pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				//���_�J���[�̐ݒ�
				pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f);

				//�e�N�X�`���̐ݒ�
				pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].tex = D3DXVECTOR2((float)nCntX, (float)nCntZ);
			}
		}
		break;

	case TYPE_GROUND:

		// ���A���̏u�Ԃ���srand��0�ŌŒ肷��B
		srand(0);

		for (int nCntZ = 0; nCntZ <= MESH_Z_BLOCK; nCntZ++)
		{
			for (int nCntX = 0; nCntX <= MESH_X_BLOCK; nCntX++)
			{
				//���_���W�̐ݒ�i���[���h���W�ł͂Ȃ����[�J�����W���w�肷��j
				pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].pos = D3DXVECTOR3
				(-(m_MeshSize * MESH_X_BLOCK) / 2 + nCntX * m_MeshSize,					// x
					sinf(nCntX * D3DX_PI * 0.25f) * 5.0f * (rand() % 100 + 1),			// y
					(m_MeshSize * MESH_Z_BLOCK) / 2 - nCntZ * m_MeshSize);				// z

				//�e���_�̖@���̐ݒ�
				pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				//���_�J���[�̐ݒ�
				pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//�e�N�X�`���̐ݒ�
				pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].tex = D3DXVECTOR2((float)nCntX, (float)nCntZ);
			}
		}
		break;
	}

	// ���_���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIdx;
	m_pIdxVtxBuff->Lock(0, 0, (void**)&pIdx, 0);

	int nLineVtx = (m_BlockX + 1);

	//�c�̒��_�̐�
	for (int nCntZ = 0; nCntZ < MESH_Z_BLOCK; nCntZ++)
	{
		//�C���f�b�N�X
		int nLineTop = nCntZ * (nLineVtx * 2 + 2);

		//���̒��_�̐�
		for (int nCntX = 0; nCntX < nLineVtx; nCntX++)
		{//��̒i�̏���
			pIdx[(nCntX * 2 + 1) + nLineTop] = (WORD)(nCntX + nLineVtx * nCntZ);

			//���̒i�̏���
			pIdx[nCntX * 2 + nLineTop] = (WORD)(pIdx[(nCntX * 2 + 1) + nLineTop] + nLineVtx);
		}

		//�k�ރ|���S����O��Ɠ���ɂ��鏈��
		if (nCntZ < MESH_Z_BLOCK)
		{
			pIdx[(nLineVtx * 2) + nLineTop] = (WORD)(MESH_X_BLOCK + (nLineVtx)* nCntZ);
			pIdx[(nLineVtx * 2) + nLineTop + 1] = (WORD)(2 * (nLineVtx)+(nLineVtx)* nCntZ);
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxVtxBuff->Unlock();

	return S_OK;
}

//=========================================
//�I�u�W�F�N�g�̍X�V����
//=========================================
void CMesh::Update()
{
	NorCreate();

	int MESH_X_BLOCK = m_BlockX;
	int MESH_Z_BLOCK = m_BlockZ;

	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	static float aaa = 0.0f;

	aaa += 0.1f;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_type == TYPE_WAVE)
	{
		for (int nCntZ = 0; nCntZ <= MESH_Z_BLOCK; nCntZ++)
		{
			for (int nCntX = 0; nCntX <= MESH_X_BLOCK; nCntX++)
			{
				float fAddWave = 5.0f * D3DX_PI / 180.0f;

				m_fVtxHeight[nCntX + (MESH_X_BLOCK + 1) * nCntZ] += sinf(fAddWave);

				//���_���W�̐ݒ�i���[���h���W�ł͂Ȃ����[�J�����W���w�肷��j
				pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].pos.y = sinf(m_fVtxHeight[nCntX + (MESH_X_BLOCK + 1) * nCntZ]) * 30.0f;

				//�e�N�X�`���̐ݒ�
				pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].tex.y += 0.01f;

				//���_�J���[�̐ݒ�
				pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			}
		}
	}

	if (m_type == TYPE_GROUND || m_type == TYPE_SEA)
	{
		for (int nCntZ = 0; nCntZ <= MESH_Z_BLOCK; nCntZ++)
		{
			for (int nCntX = 0; nCntX <= MESH_X_BLOCK; nCntX++)
			{
				if (pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].pos.y >= 200.0f)
				{
					//���_�J���[�̐ݒ�
					pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
				}
			}
		}
	}

	// ���_���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=========================================
//�I�u�W�F�N�g�̏I������
//=========================================
void CMesh::Uninit()
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
void CMesh::Draw()
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

	// ���b�V���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESH_VERTEX_NUM, 0, MESH_PRIMITIVE_NUM);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, nullptr);
}

//=========================================
//�I�u�W�F�N�g�̃N���G�C�g
//=========================================
CMesh* CMesh::Create(const D3DXVECTOR3 &pos, MeshType type)
{
	int nNumCreate = m_nNumAll;

	CMesh* pCMesh = nullptr;

	pCMesh = new CMesh;

	if (pCMesh != nullptr)
	{
		pCMesh->SetType(type);
		pCMesh->Init(pos);
	}

	return pCMesh;
}

//=========================================
//���W�̐ݒ菈��
//=========================================
void CMesh::SetPosition(const D3DXVECTOR3& pos)
{
	m_pos = pos;
}

//=========================================
// �e�N�X�`���̐ݒ�
//=========================================
void CMesh::SetTexture(CTexture::TEXTURE texture)
{
	m_texture = texture;
}

//=========================================
//�T�C�Y�̐ݒ�
//=========================================
void CMesh::SetSize(const float size)
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
void CMesh::SetAnim(const float Num, const int Pattern)
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

//=========================================
//�I�u�W�F�N�g�̔��菈��
//=========================================
bool CMesh::Collision(D3DXVECTOR3 *pos)
{
	// �����蔻��
	bool bCollison = false;

	if (pos->y <= 200.0f)
	{
		CApplication::MODE pMode = CApplication::GetMode();

		if (CApplication::GetMode() == CApplication::MODE_GAME && m_pVtxBuff != nullptr)
		{
			// ���_���̎擾
			VERTEX_3D *pVtx = NULL;

			// ���_�o�b�t�@�����b�N
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			// �C���f�b�N�X�o�b�t�@�����b�N
			WORD *pIdx;
			m_pIdxVtxBuff->Lock(0, 0, (void**)&pIdx, 0);

			// �^�[�Q�b�g���̐錾
			D3DXVECTOR3 posTarget = *pos;

			for (int nCntPolygon = 0; nCntPolygon < MESH_PRIMITIVE_NUM; nCntPolygon++)
			{
				// �ϐ��錾
				D3DXVECTOR3 V1 = pVtx[pIdx[nCntPolygon]].pos;
				D3DXVECTOR3 V2 = pVtx[pIdx[nCntPolygon + 1]].pos;
				D3DXVECTOR3 V3 = pVtx[pIdx[nCntPolygon + 2]].pos;

				V1 = WorldCastVtx(V1, m_pos, m_rot);
				V2 = WorldCastVtx(V2, m_pos, m_rot);
				V3 = WorldCastVtx(V3, m_pos, m_rot);

				if (V1 == V2
					|| V1 == V3
					|| V2 == V3)
				{// �k�ރ|���S���̏ꍇ
					continue;
				}

				// �|���S���̕Ӄx�N�g��
				D3DXVECTOR3 P1 = V2 - V1;
				D3DXVECTOR3 P2 = V3 - V2;
				D3DXVECTOR3 P3 = V1 - V3;

				// ���_�ƃ^�[�Q�b�g�̃x�N�g��
				D3DXVECTOR3 VecA = posTarget - V1;
				D3DXVECTOR3 VecB = posTarget - V2;
				D3DXVECTOR3 VecC = posTarget - V3;

				// ��r���Z�p�̕ϐ��̒�`�Ƒ��
				float fA = (P1.x * VecA.z) - (P1.z * VecA.x);
				float fB = (P2.x * VecB.z) - (P2.z * VecB.x);
				float fC = (P3.x * VecC.z) - (P3.z * VecC.x);

				if ((0.0f < fA && 0.0f < fB && 0.0f < fC)
					|| (0.0f > fA && 0.0f > fB && 0.0f > fC))
				{// ����̐ݒ�
					// �ʖ@���x�N�g��
					D3DXVECTOR3 norVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					// �ʖ@���x�N�g��
					D3DXVec3Cross(&norVec, &P1, &P2);

					//���K��
					D3DXVec3Normalize(&norVec, &norVec);

					// �ʒu�̐ݒ�
					float fCloss = V1.y - ((posTarget.x - V1.x) * norVec.x + (posTarget.z - V1.z) * norVec.z) / norVec.y;

					if (fCloss >= pos->y)
					{
						bCollison = true;
						pos->y = fCloss;
					}

					float randcolr = (rand() % 10) * 1.0f;
					float randcolg = (rand() % 10) * 1.0f;
					float randcolb = (rand() % 10) * 1.0f;
					pVtx[pIdx[nCntPolygon]].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					pVtx[pIdx[nCntPolygon + 1]].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
					pVtx[pIdx[nCntPolygon + 2]].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
					break;
				}
			}

			// �C���f�b�N�X�o�b�t�@�̃A�����b�N
			m_pIdxVtxBuff->Unlock();

			// ���_�o�b�t�@�̃A�����b�N
			m_pVtxBuff->Unlock();

		}
	}

	return bCollison;
}

//=========================================
// ���b�V���t�B�[���h�̖@���쐧
//=========================================
void CMesh::NorCreate()
{
	// �ʖ@���x�N�g�����쐬����

	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �C���f�b�N�X�o�b�t�@�����b�N
	WORD *pIdx;
	m_pIdxVtxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntPolygon = 0; nCntPolygon < MESH_PRIMITIVE_NUM; nCntPolygon++)
	{
		if (pIdx[nCntPolygon] == pIdx[nCntPolygon + 1] ||
			pIdx[nCntPolygon + 1] == pIdx[nCntPolygon + 2] ||
			pIdx[nCntPolygon + 2] == pIdx[nCntPolygon])
		{
			continue;
		}

		D3DXVECTOR3 V[3] = {};

		V[0] = pVtx[pIdx[nCntPolygon ]].pos;
		V[1] = pVtx[pIdx[nCntPolygon  + 1]].pos;
		V[2] = pVtx[pIdx[nCntPolygon  + 2]].pos;

		V[0] = WorldCastVtx(V[0], m_pos, m_rot);
		V[1] = WorldCastVtx(V[1], m_pos, m_rot);
		V[2] = WorldCastVtx(V[2], m_pos, m_rot);

		// �|���S���̕Ӄx�N�g��
		D3DXVECTOR3 P[3] = {};

		// �Ӄx�N�g���̎Z�o
		P[0] = V[1] - V[0];
		P[1] = V[2] - V[0];

		// �ʖ@���x�N�g��
		D3DXVECTOR3 Nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if (nCntPolygon % 2 == 0)
		{// �ʖ@���x�N�g��
			D3DXVec3Cross(&Nor, &P[0], &P[1]);
		}
		else
		{// �ʖ@���x�N�g��
			D3DXVec3Cross(&Nor, &P[1], &P[0]);
		}

		//���K��
		D3DXVec3Normalize(&Nor, &Nor);

		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			// �@����ۑ�����
			pVtx[pIdx[nCntPolygon + nCnt]].nor += Nor;

			// �x�N�g���𐳋K������
			D3DXVec3Normalize(&pVtx[pIdx[nCntPolygon + nCnt]].nor, &pVtx[pIdx[nCntPolygon + nCnt]].nor);
		}
	}

	// ���_���A�����b�N����
	m_pVtxBuff->Unlock();
}