//=========================================
//
// �X�R�A����
// Auther�FArita Meigen
//
//=========================================
#ifndef _RANKING_H_		// ���̃}�N����`������ĂȂ�������
#define _RANKING_H_		// ��d�C���N�\���[�h�h�~�̃}�N����`

#include "object2D.h"

class CScore;

#define MAX_RANK		(3)			//�\�����郉���L���O�̍ő吔

//=========================================
// �X�R�A�N���X���`
//=========================================
class CRanking
{
public:
	CRanking();							//�R���X�g���N�^
	virtual ~CRanking();			//�f�X�g���N�^

									//����������
	HRESULT Init();

	//�X�V����
	void Update(void);

	//�`�揈��
	void Draw(void);

	//�I������
	void Uninit(void);

	//�N���G�C�g����
	static CRanking* Create();

	void Save();
	void Load();
	void Ranking();

	//�Z�b�^�[
	static void SetCurrentScore(int Time);
	void SetCor(D3DXCOLOR col);

private:
	D3DXVECTOR3 m_pos;					// ���W
	int			m_nRankUpdate;			//�X�V�����NNo.
	int			m_MAX_DIGITS;
	static int	m_Score;
	CScore*		m_apScore[MAX_RANK];	// �X�R�A�̍ő吔

};

#endif

