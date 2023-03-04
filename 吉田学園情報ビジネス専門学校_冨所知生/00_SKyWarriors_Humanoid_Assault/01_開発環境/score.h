//=========================================
//
// �X�R�A����
// Auther�F�y���m��
//
//=========================================
#ifndef _SCORE_H_		// ���̃}�N����`������ĂȂ�������
#define _SCORE_H_		// ��d�C���N�\���[�h�h�~�̃}�N����`

#include "object2D.h"
#include "number.h"

//=========================================
// �X�R�A�N���X���`
//=========================================
class CScore :public CObject2D
{
private:
	static const int MAX_DIGITS = 6;
public:
	explicit CScore();							//�R���X�g���N�^
	virtual ~CScore() override;			//�f�X�g���N�^

	//����������
	HRESULT Init(const D3DXVECTOR3 &pos) override;

	//�X�V����
	void Update(void) override;

	//�`�揈��
	void Draw(void) override;

	//�I������
	void Uninit(void) override;

	//�N���G�C�g����
	static CScore* Create(const D3DXVECTOR3 &pos, D3DXVECTOR3 Numsize);
	int GetScore() { return m_Score; }

	//�X�R�A�̐ݒ�
	void Set();
	void SetCor(D3DXCOLOR col);

	// �X�R�A�̉��Z����
	void Add(int Score) { m_Score += Score; }
	void ScoreSet(int Score) { m_Score = Score; }
	void ScoreSizeSet(D3DXVECTOR3 size);
	void Load();
	//void Ranking();

private:
	D3DXVECTOR3 m_pos;					// ���W
	CNumber*	m_pNumber[MAX_DIGITS];	// �i���o�[1
	D3DXVECTOR3 m_NumSize;				// �i���o�[�̃T�C�Y
	int			m_Score;				// �X�R�A
	int			m_nRankUpdate;			// �X�V�����NNo.
	int			m_nTimerRanking;		// �����L���O��ʕ\���^�C�}�[
	float		m_fPtnrank;				// �v���C���[�_��
	int			m_nCntrank;				// �_�ł̃J�E���g�p

};

#endif
