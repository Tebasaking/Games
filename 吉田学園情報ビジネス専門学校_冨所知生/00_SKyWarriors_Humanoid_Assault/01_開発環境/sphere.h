//=========================================
//
//	object2D.h
//	Author:�y���m��
//
//=========================================
#ifndef _SPHERE_H_		//���̃}�N����`������ĂȂ�������
#define _SPHERE_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "object.h"
#include "texture.h"

#define SPHERE_SIZE (20000.0f)
#define SPHERE_X_BLOCK (20)
#define SPHERE_Z_BLOCK (20)
#define SPHERE_VERTEX_NUM ((SPHERE_X_BLOCK + 1) * (SPHERE_Z_BLOCK + 1))
#define SPHERE_INDEX_NUM  (((SPHERE_X_BLOCK + 1) * 2) * ( SPHERE_Z_BLOCK  *(SPHERE_Z_BLOCK - 1)) * SPHERE_Z_BLOCK * 2)
#define SPHERE_PRIMITIVE_NUM (SPHERE_X_BLOCK * SPHERE_Z_BLOCK * 2 + 4 * (SPHERE_Z_BLOCK  - 1))

class CSphere :public CObject
{
public:
	CSphere();			//�R���X�g���N�^
	virtual ~CSphere();			//�f�X�g���N�^

	//����������
	HRESULT Init(const D3DXVECTOR3 &pos) override;
	//�X�V����
	void Update(void) override;
	//�`�揈��
	void Draw(void) override;
	//�I������
	void Uninit(void) override;
	//�N���G�C�g����
	static CSphere* Create(const D3DXVECTOR3 &pos);
	//�e�N�X�`���̐ݒ菈��
	void SetTexture(CTexture::TEXTURE texture);	// �e�N�X�`���̐ݒ�

	void SetPosition(const D3DXVECTOR3& pos);
	void SetAnim(const float Num, const int Pattern);
	void SetSize(const float Size);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//�o�b�t�@
	LPDIRECT3DINDEXBUFFER9  m_pIdxVtxBuff;	//���b�V���t�B�[���h�o�b�t�@
	D3DXMATRIX				m_mtxWorld;		// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;						// ���W
	CTexture::TEXTURE m_texture;			// �e�N�X�`���̗񋓌^
	D3DXVECTOR3 m_size;						// �g�嗦
	float m_scale;							// �傫��
	D3DXVECTOR3 m_rot;
	int m_LineVtx = (SPHERE_X_BLOCK + 1);
};

#endif