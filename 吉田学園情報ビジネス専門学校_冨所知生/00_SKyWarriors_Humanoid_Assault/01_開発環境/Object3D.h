////=========================================
////
////	3D���f���̃w�b�_�[�t�@�C��
////	Author : �y���m��
////
////=========================================
//#ifndef _OBJECT3D_H_								
//#define _OBJECT3D_H_							
//
//#include "main.h"
//#include "object.h"
//#include "texture.h"
//
//class CObject3D :public CObject
//{
//public:
//	CObject3D();			//�R���X�g���N�^
//	virtual ~CObject3D();			//�f�X�g���N�^
//
//	// ����������
//	HRESULT Init(const D3DXVECTOR3 &pos) override;
//	// �X�V����
//	void Update(void) override;
//	// �`�揈��
//	void Draw(void) override;
//	// �e�̕`�揈��
//	void DrawShadow(void);
//	// �I������
//	void Uninit(void) override;
//	// �N���G�C�g����
//	static CObject3D* Create(const D3DXVECTOR3 &pos);
//	// �e�N�X�`���̐ݒ菈��
//	void SetTexture(CTexture::TEXTURE texture);	// �e�N�X�`���̐ݒ�
//	
//	// ���f���̐ݒ�
//	void SetModel(const char* name);
//	void SetPosition(const D3DXVECTOR3& pos);
//	void SetRot(const D3DXVECTOR3& pos);
//	void SetSize(const float Size);
//	void SetQuaternion(const D3DXQUATERNION quaternion);
//	float NormalizRot(float fRot);
//	float LimitedRot(float fRot, float LimitRot);
//	
//	const D3DXVECTOR3& GetPosition() const override { return m_pos; };
//	const D3DXVECTOR3& GetRot() const override { return m_rot; }
//	const float& GetSize() const override { return m_size; }
//	const D3DXQUATERNION& GetQuaternion() const { return m_quaternion; }
//
//private:
//	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// �o�b�t�@
//	CTexture::TEXTURE m_texture;						// �e�N�X�`���̗񋓌^
//	float m_size;										// �傫��
//
//	LPD3DXMESH				m_pMeshModel = NULL;		// ���b�V�����ւ̃|�C���^
//	LPD3DXBUFFER			m_pBuffMatModel = NULL;		// �}�e���A�����ւ̃|�C���^
//	DWORD					m_nNumMatModel = 0;			// �}�e���A�����̐�
//	D3DXVECTOR3				m_pos;						// �ʒu
//	D3DXVECTOR3				m_rot;						// ��]
//	D3DXVECTOR3				m_rotModel;					// ����
//	D3DXMATRIX				m_mtxWorldModel;			// ���[���h�}�g���b�N�X
//	LPD3DXEFFECT			pEffect;					// �V�F�[�_�[
//	IDirect3DTexture9		*pTex0 = NULL;				// �e�N�X�`���ۑ��p
//
//	D3DXQUATERNION			m_quaternion;				//�N�H�[�^�j�I��
//};
//
//#endif