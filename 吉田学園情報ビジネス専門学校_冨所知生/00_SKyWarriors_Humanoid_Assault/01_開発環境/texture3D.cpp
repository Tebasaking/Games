//=============================================================================
//
// �e�N�X�`���ݒ菈��(texture.cpp)
// Author : �������l
// �T�v : �e�N�X�`���ݒ���s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "texture3D.h"
#include "render.h" 
#include "application.h"

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CTexture3D::CTexture3D()
{
	m_pTexture = nullptr;		// �e�N�X�`�����
	m_nMaxTexture = 0;			// �e�N�X�`���̍ő吔
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CTexture3D::~CTexture3D()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : �\��t����e�N�X�`�������i�[����
//=============================================================================
void CTexture3D::Init(void)
{// �����_���[�̃Q�b�g
	CRender *pRender = CApplication::GetRender();

	// �t�@�C���̓ǂݍ���
	LoadFile();

	for (int nCnt = 0; nCnt < m_nMaxTexture; nCnt++)
	{//�|���S���ɓ\��t����e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pRender->GetDevice(),
			&m_pTexture[nCnt].aFileName[0],
			&m_pTexture[nCnt].pTexture);
	}
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̉��
//=============================================================================
void CTexture3D::Uninit(void)
{
	for (int nCnt = 0; nCnt < m_nMaxTexture; nCnt++)
	{//�e�N�X�`���̔j��	  
		if (m_pTexture[nCnt].pTexture != nullptr)
		{
			m_pTexture[nCnt].pTexture->Release();

			m_pTexture[nCnt].pTexture = nullptr;
		}
	}

	if (m_pTexture != nullptr)
	{
		delete[] m_pTexture;
		m_pTexture = nullptr;
	}
}

//=============================================================================
// �e�N�X�`���|�C���^�̃Q�b�^�[	
// Author : �������l
// �T�v : �e�N�X�`���̃Q�b�^�[
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture3D::GetTexture(const int nNumTex)
{
	LPDIRECT3DTEXTURE9 pTexture = nullptr;

	if (nNumTex != -1)
	{// �^�C�v���ݒ肳��Ă�
		pTexture = m_pTexture[nNumTex].pTexture;
	}

	return pTexture;
}

//=============================================================================
// �t�@�C���̓ǂݍ���
// Author : �������l
// �T�v : �t�@�C������ǂݍ��ރe�N�X�`�����Ɩ��O��ǂݍ���
//=============================================================================
void CTexture3D::LoadFile()
{
	// �ϐ��錾
	char aStr[128];
	int nCntTex = 0;

	// �t�@�C���̓ǂݍ���
	FILE *pFile = fopen("data/FILE/texture.txt", "r");

	if (pFile != nullptr)
	{
		while (fscanf(pFile, "%s", &aStr[0]) != EOF)
		{// "EOF"��ǂݍ��ނ܂� 
			if (strncmp(&aStr[0], "#", 1) == 0)
			{// ���ǂݍ���
				fgets(&aStr[0], sizeof(aStr), pFile);
			}

			if (strstr(&aStr[0], "MAX_TEXTURE") != NULL)
			{
				fscanf(pFile, "%s", &aStr[0]);
				fscanf(pFile, "%d", &m_nMaxTexture);
				m_pTexture = new TEXTURE[m_nMaxTexture];
				assert(m_pTexture != nullptr);
				memset(&m_pTexture[0], 0, sizeof(TEXTURE));
			}

			if (strstr(&aStr[0], "TEXTURE_FILENAME") != NULL)
			{
				fscanf(pFile, "%s", &aStr[0]);
				fscanf(pFile, "%s", &m_pTexture[nCntTex].aFileName[0]);
				nCntTex++;
			}
		}
	}
	else
	{
		assert(false);
	}
}
