//=========================================
//
//	object2D.h
//	Author:�y���m��
//
//=========================================
#ifndef _OBJECT2D_H_		//���̃}�N����`������ĂȂ�������
#define _OBJECT2D_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"
#include "object.h"
#include "texture.h"

class CObject2D :public CObject
{
public:
	explicit CObject2D(int nPriority = LAYER_FOUR);
	virtual ~CObject2D();			//�f�X�g���N�^

	//����������
	HRESULT Init(const D3DXVECTOR3 &pos) override;
	//�X�V����
	void Update(void) override;
	//�`�揈��
	void Draw(void) override;
	//�I������
	void Uninit(void) override;
	//�N���G�C�g����
	static CObject2D* Create(const D3DXVECTOR3 &pos,int nPriority);
	//�e�N�X�`���̐ݒ菈��
	void SetTexture(CTexture::TEXTURE texture);	// �e�N�X�`���̐ݒ�

	void VtxUpdate();
	void SetColor(const D3DXCOLOR &col);
	void SetPosition(const D3DXVECTOR3& pos);
	void SetAnim(const int Num,const int Pattern);
	void SetScale(const D3DXVECTOR3 Size);

	D3DXVECTOR3 GetTest(){ return m_pos; };

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//�o�b�t�@
	D3DXVECTOR3 m_pos;						//���W
	CTexture::TEXTURE m_texture;			// �e�N�X�`���̗񋓌^
	D3DXVECTOR3 m_size;						// �傫��
	D3DXVECTOR3	m_scale;					// �g�嗦
	D3DXCOLOR m_col;						// �F
	float m_fLength;						// ����
	float m_fAngle;							// �Ίp��
};

#endif