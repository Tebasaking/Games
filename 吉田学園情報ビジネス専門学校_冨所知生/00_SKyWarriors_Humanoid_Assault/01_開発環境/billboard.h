//=========================================
//
//	object2D.h
//	Author:�y���m��
//
//=========================================
#ifndef _BILLBOARD_H_		//���̃}�N����`������ĂȂ�������
#define _BILLBOARD_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "object.h"
#include "texture.h"

class CBillboard :public CObject
{
public:
	explicit CBillboard(int nPriority = CObject::LAYER_FOUR);	//�R���X�g���N�^
	virtual ~CBillboard();			//�f�X�g���N�^

	//����������
	HRESULT Init(const D3DXVECTOR3 &pos) override;
	//�X�V����
	void Update(void) override;
	//�`�揈��
	void Draw(void) override;
	//�I������
	void Uninit(void) override;
	//�N���G�C�g����
	static CBillboard* Create(const D3DXVECTOR3 &pos);
	//�e�N�X�`���̐ݒ菈��
	void SetTexture(CTexture::TEXTURE texture);	// �e�N�X�`���̐ݒ�

	void SetPosition(const D3DXVECTOR3& pos);
	void SetAnim(const float NumX, const int PatternX, const int NumY, const int PatternY);
	void SetSize(const D3DXVECTOR3 Size);
	void SetColor(const D3DXCOLOR &col);

	void SetZFunc(const _D3DCMPFUNC zFunc) { m_zFunc = zFunc; }						// Z�e�X�g�̗D��x�̃Z�b�^�[
	void SetAlphaValue(const int nAlphaValue) { m_nAlphaValue = nAlphaValue; }		// �A���t�@�e�X�g�̓��ߗ��̃Z�b�^�[
	void SetBill(bool bBill) { m_bBill = bBill; }

	D3DCOLOR GetColor() { return m_col; }
	D3DXVECTOR3 GetSize() { return m_scale; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//�o�b�t�@
	D3DXMATRIX				m_mtxWorld;		// ���[���h�}�g���b�N�X
	D3DXVECTOR3				m_pos;			//���W
	CTexture::TEXTURE		m_texture;		// �e�N�X�`���̗񋓌^
	D3DXVECTOR3				m_size;			// �傫��
	D3DXVECTOR3				m_scale;		// �g�嗦
	_D3DCMPFUNC				m_zFunc;		// Z�e�X�g�̐ݒ�
	D3DXCOLOR m_col;						// �F

	bool					m_bBill;		// billboard��ON/OFF
	int						m_nAlphaValue;	// ���e�X�g�̓��ߗ�
};

#endif