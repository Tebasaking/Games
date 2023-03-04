//=============================================================================
//
// 3D���f���N���X(model3D.h)
// Author : �y���m��
// �T�v : 3D���f���������s��
//
//=============================================================================
#ifndef _MODEL3D_H_			// ���̃}�N����`������ĂȂ�������
#define _MODEL3D_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"
#include <vector>

#define MAX_MATERIAL_TEXTURE_NUM (10)

class CModel3D
{
public:
	//=========================================
	// ���f���̃}�e���A�����
	//=========================================
	struct MODEL_MATERIAL
	{
		LPD3DXMESH		pMesh;				// ���b�V�����ւ̃|�C���^
		LPD3DXBUFFER	pBuffer;			// �}�e���A�����ւ̃|�C���^
		DWORD			nNumMat;			// �}�e���A�����̐�
		D3DXVECTOR3		size;				// ���f���̑傫��
		std::vector<int> pNumTex;			// �e�N�X�`���^�C�v
		char			aFileName[0xff];	// X�t�@�C���̃p�X
		LPDIRECT3DTEXTURE9 pTexture[MAX_MATERIAL_TEXTURE_NUM];		// �e�N�X�`��
	};

	//=========================================
	// �ÓI�����o�֐�
	//=========================================
	static CModel3D *Create();													// 3D���f���̐���
	static void InitModel();													// ���f���̏�����
	static void UninitModel();													// ���f���̏I��
	static void LoadModel(const char *pFileName);								// ���f���̓ǂݍ���
	static std::vector<MODEL_MATERIAL> GetMaterial() { return m_material; }		// �}�e���A�����̎擾
	static int GetMaxModel() { return m_nMaxModel; }							// ���f����

	//=========================================
	// �R���X�g���N�^�ƃf�X�g���N�^
	//=========================================
	explicit CModel3D();
	~CModel3D();

	//=========================================
	// �����o�֐�
	//=========================================
	HRESULT Init();														// ������
	void Uninit();														// �I��
	void Update();														// �X�V
	void Draw();														// �`��

	void Draw(D3DXMATRIX mtxParent);									// �`��(�I�[�o�[���[�h)
	void DrawMaterial();												// �}�e���A���`��
	void SetPos(const D3DXVECTOR3 &pos);								// �ʒu�̃Z�b�^�[
	void SetRot(const D3DXVECTOR3 &rot);								// �����̃Z�b�^�[
	void SetSize(const D3DXVECTOR3 &size);								// �傫���̃Z�b�^�[
	void SetMtxWorld(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }	// ���[���h�}�g���b�N�X�̐ݒ�
	void SetParent(CModel3D *pParent) { m_pParent = pParent; }			// �e���f���̃Z�b�^�[
	void SetModelID(const int nModelID) { m_nModelID = nModelID; }		// ���f��ID
	void SetColor(const D3DXCOLOR color);								// �J���[�̐ݒ�
	void SetColor(bool bColor) { m_bColor = bColor; }					// �J���[�̐ݒ�(�I�[�o�[���[�h)
	void SetShadow(bool bShadow) { m_bShadow = bShadow; }				// �e�̎g�p�󋵂̐ݒ�
	void SetLighting(bool bLighting) { m_bLighting = bLighting; }		// ���C�g���g�p�󋵂̐ݒ�

	float NormalizeRot(float fRot);
	float LimitedRot(float fRot, float LimitRot);

	// �N�H�[�^�j�I���̐ݒ�
	void SetQuaternion(const D3DXQUATERNION quaternion) { m_quaternion = quaternion; }

	D3DXVECTOR3 GetPos() { return m_pos; }									// �ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetRot() { return m_rot; }									// �����̃Q�b�^�[
	D3DXVECTOR3 GetSize() { return m_size; }								// �傫���̃Q�b�^�[
	MODEL_MATERIAL GetMyMaterial() { return m_material[m_nModelID]; }		// �}�e���A�����̎擾
	D3DXMATRIX GetMtxWorld() { return m_mtxWorld; }							// ���[���h�}�g���b�N�X�̎擾
	CModel3D *GetParent() { return m_pParent; }								// �e���f���̃Q�b�^�[
	D3DXQUATERNION& GetQuaternion() { return m_quaternion; }

private:
	//=========================================
	// �����o�֐�
	//=========================================
	void Shadow();		// �e�̕`��

	//=========================================
	// �ÓI�����o�ϐ�
	//=========================================
	static std::vector<MODEL_MATERIAL> m_material;		// �}�e���A�����
	static int				m_nMaxModel;		// ���f����

	//=========================================
	// �����o�ϐ�
	//=========================================
	CModel3D			*m_pParent;			// �e���f���̏��
	D3DXMATRIX			m_mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3			m_pos;				// �ʒu
	D3DXVECTOR3			m_rot;				// ����
	D3DXVECTOR3			m_size;				// �傫��
	D3DXCOLOR			m_color;			// �J���[
	int					m_nModelID;			// ���f��ID
	bool				m_bColor;			// �J���[���g�p����
	bool				m_bShadow;			// �e�̎g�p��
	bool				m_bLighting;		// ���C�g�̎g�p��
	D3DXQUATERNION		m_quaternion;		//�N�H�[�^�j�I��
	LPD3DXEFFECT		pEffect;			// �V�F�[�_�[
	IDirect3DTexture9	*pTex0 = NULL;		// �e�N�X�`���ۑ��p

	//=========================================
	//�n���h���ꗗ
	//=========================================
	D3DXHANDLE			m_hmWVP;					// ���[���h�`�ˉe�s��
	D3DXHANDLE			m_hmWIT;					// ���[�J�� - ���[���h�ϊ��s��
	D3DXHANDLE			m_hvLightDir;				// ���C�g�̕���
	D3DXHANDLE			m_hvCol;					// ���_�F
	D3DXHANDLE			m_hvEyePos;					// ���_�̈ʒu
	D3DXHANDLE			m_hTechnique;				// �e�N�j�b�N
	D3DXHANDLE			m_hTexture;					// �e�N�X�`��
};

#endif