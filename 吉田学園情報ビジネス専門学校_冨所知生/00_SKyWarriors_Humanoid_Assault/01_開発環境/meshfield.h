//=========================================
//
//	object2D.h
//	Author:�y���m��
//
//=========================================
#ifndef _MESH_FIELD_H_		//���̃}�N����`������ĂȂ�������
#define _MESH_FIELD_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"
#include "object.h"
#include "texture.h"
#include "Object3D.h"
#include <vector>

#define MESH_SIZE (100.0f)

class CMesh :public CObject
{
public:

	enum MeshType
	{
		TYPE_SEA = 0,
		TYPE_WAVE,
		TYPE_GROUND,
	};

	explicit CMesh(int nPriority = LAYER_ONE);	//�R���X�g���N�^
	virtual ~CMesh();			//�f�X�g���N�^

	//����������
	HRESULT Init(const D3DXVECTOR3 &pos) override;
	//�X�V����
	void Update(void) override;
	//�`�揈��
	void Draw(void) override;
	//�I������
	void Uninit(void) override;
	//�N���G�C�g����
	static CMesh* Create(const D3DXVECTOR3 &pos, MeshType type);
	//�e�N�X�`���̐ݒ菈��
	void SetTexture(CTexture::TEXTURE texture);	// �e�N�X�`���̐ݒ�
	// �^�C�v�̎擾����
	MeshType GetType() { return m_type; }
	
	void SetMeshSize(float size) { m_MeshSize = size; }
	void SetPosition(const D3DXVECTOR3& pos);
	void SetAnim(const float Num, const int Pattern);
	void SetSize(const float Size);

	void NorCreate();								// ���b�V���t�B�[���h�̖@���쐬
	bool Collision(D3DXVECTOR3 *pos);				// ���菈��

	// ���b�V���^�C�v�̐ݒ�
	void SetType(MeshType type) { m_type = type; }
	// �u���b�N���ݒ�
	void SetBlock(float XBlock, float ZBlock) { m_BlockX = XBlock; m_BlockZ = ZBlock; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//�o�b�t�@
	LPDIRECT3DINDEXBUFFER9  m_pIdxVtxBuff;	//���b�V���t�B�[���h�o�b�t�@
	D3DXMATRIX				m_mtxWorld;		// ���[���h�}�g���b�N�X
	D3DXVECTOR3				m_pos;			// ���W
	CTexture::TEXTURE m_texture;			// �e�N�X�`���̗񋓌^
	D3DXVECTOR3 m_size;						// �傫��

	float m_scale;							// �g�嗦
	float m_polygon;						// �|���S����
	float m_fAddWave;						// �g��ǉ�����
	float m_fAmplitude;						// �U�ꕝ�̐ݒ�
	float m_MeshSize;						// ���b�V���̃T�C�Y
	float m_BlockX;							// X�u���b�N��
	float m_BlockZ;							// Y�u���b�N��
	bool  m_bWave;							// �E�F�[�u
	
	float MESH_VERTEX_NUM;
	float MESH_INDEX_NUM;
	float MESH_PRIMITIVE_NUM;

	D3DXVECTOR3 m_rot;
	MeshType	m_type;						// ���b�V���̃^�C�v

	// ���_�̍���
	std::vector<float> m_fVtxHeight;
};

#endif