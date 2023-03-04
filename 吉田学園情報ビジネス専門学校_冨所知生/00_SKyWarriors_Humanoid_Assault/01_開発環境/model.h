////=========================================
////
////	3D���f���̃w�b�_�[�t�@�C��
////	Author : �y���m��
////
////=========================================
//#ifndef _MODEL_H_								
//#define _MODEL_H_							
//
//#include "main.h"
//#include "object.h"
//#include "texture.h"
//
//class CModel
//{
//public:
//	CModel();			//�R���X�g���N�^
//	virtual ~CModel();			//�f�X�g���N�^
//
//	// ����������
//	HRESULT Init(const D3DXVECTOR3 &pos);
//	// �X�V����
//	void Update(void);
//	// �`�揈��
//	void Draw();
//	void Draw(D3DXMATRIX mtxParent);
//	// �e�̕`�揈��
//	void DrawShadow(void);
//	// �I������
//	void Uninit(void);
//	// �e�N�X�`���̐ݒ菈��
//	void SetTexture(CTexture::TEXTURE texture) { m_texture = texture; }	// �e�N�X�`���̐ݒ�
//
//	// ���f���̐ݒ�
//	void SetModel(const char* name);
//	void SetPosition(const D3DXVECTOR3& pos);
//	void SetRot(const D3DXVECTOR3& pos);
//	void SetScale(const float Size);
//	void SetQuaternion(const D3DXQUATERNION quaternion);
//	void SetParent(CModel *pModel) { m_pParents = pModel; }
//	D3DXMATRIX GetMtxWorld() { return m_mtx; }
//
	//float NormalizRot(float fRot);
	//float LimitedRot(float fRot, float LimitRot);
//
//	D3DXVECTOR3 GetModelSize();
//	const D3DXVECTOR3& GetPosition() const { return m_pos; };
//	const D3DXVECTOR3& GetRot() const { return m_rot; }
//	const D3DXVECTOR3& GetSize() const { return m_size; }
//	const D3DXQUATERNION& GetQuaternion() const { return m_quaternion; }
//
//	const float& GetScale() const { return m_scale; }
//	CModel *GetParent() { return m_pParents; }								// �e���f���̃Q�b�^�[
//
//private:
//	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// �o�b�t�@
//	CTexture::TEXTURE		m_texture;					// �e�N�X�`���̗񋓌^
//	float m_scale;										// �傫��
//	const char* m_filename;								// ���f���̃t�@�C����
//	CModel *m_pParents;									// �e���f���ւ̃|�C���^
//
//	LPD3DXMESH				m_pMeshModel = NULL;		// ���b�V�����ւ̃|�C���^
//	LPD3DXBUFFER			m_pBuffMatModel = NULL;		// �}�e���A�����ւ̃|�C���^
//	DWORD					m_nNumMatModel = 0;			// �}�e���A�����̐�
//	D3DXVECTOR3				m_pos;						// �ʒu
//	D3DXVECTOR3				m_rot;						// ��]
//	D3DXVECTOR3				m_rotModel;					// ����
//	D3DXVECTOR3				vtxMin;						// �ŏ�
//	D3DXVECTOR3				vtxMax;						// �ő�
//	D3DXVECTOR3				m_size;						// ���f���T�C�Y
//	D3DXMATRIX				m_mtx;						// ���[���h�}�g���b�N�X
//	IDirect3DTexture9		*pTex0 = NULL;				// �e�N�X�`���ۑ��p
//};
//
//#endif