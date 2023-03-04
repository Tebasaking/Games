//=========================================
//
// �^�C�}�[����
// Auther�F�y���m��
//
//=========================================
#ifndef _TIME_H_		// ���̃}�N����`������ĂȂ�������
#define _TIME_H_		// ��d�C���N�\���[�h�h�~�̃}�N����`

#include "object2D.h"
#include "number.h"

//=========================================
// �X�R�A�N���X���`
//=========================================
class CTime :public CObject2D
{
private:
	static const int MAX_DIGITS = 8;

public:
	CTime();							//�R���X�g���N�^
	virtual ~CTime() override;			//�f�X�g���N�^

	// ����������
	HRESULT Init(const D3DXVECTOR3& pos) override;
	// �X�V����
	void Update(void) override;
	// �`�揈��
	void Draw(void) override;
	// �I������
	void Uninit(void) override;
	// �N���G�C�g����
	static CTime* Create(const D3DXVECTOR3 &pos);

	// �X�R�A�̐ݒ�
	void Set();
	void Add(int nValue);
	void Sub(int nValue);

	// �A���[��(�I������)�̐ݒ�
	void SetAlarm(int minutes, int seconds);

	static int GetTime() { return m_Time; }
	static int GetSec() { return m_Seconds; }
	static int GetMin() { return m_Minutes; }

private:
	D3DXVECTOR3 m_pos;					// ���W
	CNumber	  *m_pNumber[MAX_DIGITS];	// �i���o�[1
	int		   m_Alarm;					// �ݒ肳�ꂽ�ڕW����
	static int m_Time;					// �n�܂��Ă���̎���
	static int m_Seconds;				// ���݂̎���(�b)
	static int m_Minutes;				// ���݂̎���(��)
	DWORD m_StartGameTime;				// �Q�[�����n�܂�������
};

#endif