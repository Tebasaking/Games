//=========================================
//
// �t�@�C���ǂݍ��ݏ���
// Auther�F�y���m��
//
//=========================================
#include<stdio.h>
#include "main.h"
#include "file.h"
#include "model.h"
#include "player.h"
#include "titlemodel.h"

//=========================================
// �}�N����`
//=========================================
#define LOAD_FILE_NAME_000		"model.txt"
#define LOAD_FILE_NAME_001		"motion.txt"
#define LOAD_FILE_NAME_002		"cooking.txt"
#define LOAD_FILE_NAME_003		"title.txt"

//=========================================
// �O���[�o���ϐ�
//=========================================
static D3DXVECTOR3		g_modelpos;
static D3DXVECTOR3		g_motionpos;
static D3DXVECTOR3		g_motionrot;
static float			FRAME;
static float			NUM_KEY;
static float			PARTS_NUMBER;
static int				ANIM_NUMBER;
static char				g_motionFile[128];
static char				g_modelFile[128];
static char				g_aString[128];
static int				nCntParts;
static int				nCntAnim;
static int				nCntModel;
static int				nKey;
static int				nType;

//=========================================
// �t�@�C���̓ǂݍ��ݏ���
//=========================================
void InitFile(void)
{
	// �t�@�C���|�C���^�̐錾
	FILE * pFile;

	char aFile[128] = FILE_STAGE;
	strcat(aFile, LOAD_FILE_NAME_000);
	nCntParts = 0;
	nCntModel = 0;

	//�t�@�C�����J��
	pFile = fopen(aFile, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		while (1)
		{
			fscanf(pFile, "%s", &g_aString);
			if (strcmp(&g_aString[0], "START") == 0)
			{// �����񂪈�v�����ꍇ
				break;
			}
		}

		fscanf(pFile, "%s", &g_aString[0]);
		if (strcmp(&g_aString[0], "SCRIPT") == 0)
		{// �����񂪈�v�����ꍇ
			while (1)
			{// ������̏������Ɠǂݍ���
				g_aString[0] = {};

					fscanf(pFile, "%s", &g_aString[0]);

					if (strcmp(&g_aString[0], "MODEL_FILENAME") == 0)
					{// �����񂪈�v�����ꍇ
						fscanf(pFile, "%s", &g_modelFile);
					}
					else if (strcmp(&g_aString[0], "MODELSET") == 0)
					{// �����񂪈�v�����ꍇ
						while (1)
						{
							// ������̏������Ɠǂݍ���
							g_aString[0] = {};
							fscanf(pFile, "%s", &g_aString[0]);

							if (strcmp(&g_aString[0], "TYPE") == 0)
							{
								fscanf(pFile, "%d", &nType);
							}

							if (strcmp(&g_aString[0], "POS") == 0)
							{// �����񂪈�v�����ꍇ
								fscanf(pFile, "%f", &g_modelpos.x);
								fscanf(pFile, "%f", &g_modelpos.y);
								fscanf(pFile, "%f", &g_modelpos.z);
							}

							if (strcmp(&g_aString[0], "rot") == 0)
							{// �����񂪈�v�����ꍇ
								fscanf(pFile, "%f", &g_modelpos.x);
								fscanf(pFile, "%f", &g_modelpos.y);
								fscanf(pFile, "%f", &g_modelpos.z);
							}

							if (strcmp(&g_aString[0], "END_MODELSET") == 0)
							{// �����񂪈�v�����ꍇ
							 // ���f���̐ݒu
								SetModel(g_modelpos, g_modelFile, nCntModel, nType);
								nCntModel++;
								break;
							}

							else if (strcmp(&g_aString[0], "END_PLAYERSET") == 0)
							{
								SetPlayer(g_modelpos);
								break;
							}

							else if (strcmp(&g_aString[0], "END_PARTSSET") == 0)
							{
								SetParts(g_modelpos, g_modelFile, nCntParts);
								nCntParts++;
								break;
							}
						}
					}
				else if (strcmp(&g_aString[0], "END_SCRIPT") == 0)
				{// �����񂪈�v�����ꍇ
					break;
				}
			}
		}
		//�t�@�C�������
		fclose(pFile);
	}

	else
	{//�t�@�C�����J���Ȃ��ꍇ
	}
}
//=========================================
// motion.txt�̓ǂݍ���
//=========================================
void MotionFile(void)
{
	// �t�@�C���|�C���^�̐錾
	FILE * pFile;

	char aFile[128] = FILE_STAGE;
	strcat(aFile, LOAD_FILE_NAME_001);

	//�t�@�C�����J��
	pFile = fopen(aFile, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		while (1)
		{
			fscanf(pFile, "%s", &g_aString);
			if (strcmp(&g_aString[0], "#") == 0)
			{
				fgets(&g_aString[0], sizeof(g_aString), pFile);
			}

			if (strcmp(&g_aString[0], "START") == 0)
			{// �����񂪈�v�����ꍇ
				break;
			}
		}

		fscanf(pFile, "%s", &g_aString[0]);
		if (strcmp(&g_aString[0], "CHARACTERSET") == 0)
		{// �����񂪈�v�����ꍇ
			while (1)
			{// ������̏������Ɠǂݍ���
				g_aString[0] = {};

				fscanf(pFile, "%s", &g_aString[0]);

				if (strcmp(&g_aString[0], "LOOP") == 0)
				{// �����񂪈�v�����ꍇ
					fscanf(pFile, "%s", &g_modelFile);
				}

				else if (strcmp(&g_aString[0], "KEYSET") == 0)
				{// �����񂪈�v�����ꍇ
					while (1)
					{
						// ������̏������Ɠǂݍ���
						g_aString[0] = {};
						fscanf(pFile, "%s", &g_aString[0]);

						if (strcmp(&g_aString[0], "ANIM_NUMBER") == 0)
						{//�����񂪈�v�����ꍇ
							fscanf(pFile, "%d", &ANIM_NUMBER);
						}

						if (strcmp(&g_aString[0], "NUM_PARTS") == 0)
						{//�����񂪈�v�����ꍇ
							fscanf(pFile, "%f", &PARTS_NUMBER);
						}

						if (strcmp(&g_aString[0], "FRAME") == 0)
						{// �����񂪈�v�����ꍇ
							fscanf(pFile, "%f", &FRAME);
						}

						if (strcmp(&g_aString[0], "POS") == 0)
						{// �����񂪈�v�����ꍇ
							fscanf(pFile, "%f", &g_motionpos.x);
							fscanf(pFile, "%f", &g_motionpos.y);
							fscanf(pFile, "%f", &g_motionpos.z);
						}

						if (strcmp(&g_aString[0], "rot") == 0)
						{// �����񂪈�v�����ꍇ
							fscanf(pFile, "%f", &g_motionrot.x);
							fscanf(pFile, "%f", &g_motionrot.y);
							fscanf(pFile, "%f", &g_motionrot.z);
						}

						if (strcmp(&g_aString[0], "NUM_KEY") == 0)
						{//�����񂪈�v�����ꍇ
							fscanf(pFile, "%f", &NUM_KEY);
						}

						if (strcmp(&g_aString[0], "END_KEYSET") == 0)
						{// �����񂪈�v�����ꍇ
						 // �A�j���[�V�����̋N��
							LoadAnimation(ANIM_NUMBER, NUM_KEY ,PARTS_NUMBER ,true , 2 , FRAME , g_motionpos, g_motionrot);
							break;
						}
					}
				}

			else if (strcmp(&g_aString[0], "END_CHARACTER") == 0)
			{// �����񂪈�v�����ꍇ
				nKey = 0;
				break;
			}
		}
	}
		//�t�@�C�������
		fclose(pFile);
	}

	else
	{//�t�@�C�����J���Ȃ��ꍇ
	}
}

//=========================================
// �����̊������̃t�@�C�����o��
//=========================================
void CookingFile()
{
	// �t�@�C���|�C���^�̐錾
	FILE * pFile;

	char aFile[128] = FILE_STAGE;
	strcat(aFile, LOAD_FILE_NAME_002);

	//�t�@�C�����J��
	pFile = fopen(aFile, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		while (1)
		{
			fscanf(pFile, "%s", &g_aString);
			if (strcmp(&g_aString[0], "type") == 0)
			{// �����񂪈�v�����ꍇ
				break;
			}
		}
	}
}

//=========================================
// �t�@�C���̓ǂݍ��ݏ���
//=========================================
void TitleFile(void)
{
	// �t�@�C���|�C���^�̐錾
	FILE * pFile;

	char aFile[128] = FILE_STAGE;
	strcat(aFile, LOAD_FILE_NAME_003);
	nCntParts = 0;
	nCntModel = 0;

	//�t�@�C�����J��
	pFile = fopen(aFile, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		while (1)
		{
			fscanf(pFile, "%s", &g_aString);
			if (strcmp(&g_aString[0], "START") == 0)
			{// �����񂪈�v�����ꍇ
				break;
			}
		}

		fscanf(pFile, "%s", &g_aString[0]);
		if (strcmp(&g_aString[0], "SCRIPT") == 0)
		{// �����񂪈�v�����ꍇ
			while (1)
			{// ������̏������Ɠǂݍ���
				g_aString[0] = {};

				fscanf(pFile, "%s", &g_aString[0]);

				if (strcmp(&g_aString[0], "MODEL_FILENAME") == 0)
				{// �����񂪈�v�����ꍇ
					fscanf(pFile, "%s", &g_modelFile);
				}
				else if (strcmp(&g_aString[0], "MODELSET") == 0)
				{// �����񂪈�v�����ꍇ
					while (1)
					{
						// ������̏������Ɠǂݍ���
						g_aString[0] = {};
						fscanf(pFile, "%s", &g_aString[0]);

						if (strcmp(&g_aString[0], "POS") == 0)
						{// �����񂪈�v�����ꍇ
							fscanf(pFile, "%f", &g_modelpos.x);
							fscanf(pFile, "%f", &g_modelpos.y);
							fscanf(pFile, "%f", &g_modelpos.z);
						}

						if (strcmp(&g_aString[0], "rot") == 0)
						{// �����񂪈�v�����ꍇ
							fscanf(pFile, "%f", &g_modelpos.x);
							fscanf(pFile, "%f", &g_modelpos.y);
							fscanf(pFile, "%f", &g_modelpos.z);
						}

						if (strcmp(&g_aString[0], "END_MODELSET") == 0)
						{// �����񂪈�v�����ꍇ
						 // ���f���̐ݒu
							SetTitleModel(g_modelpos, g_modelFile, nCntModel, nType);
							nCntModel++;
							break;
						}
					}
				}
				else if (strcmp(&g_aString[0], "END_SCRIPT") == 0)
				{// �����񂪈�v�����ꍇ
					break;
				}
			}
		}
		//�t�@�C�������
		fclose(pFile);
	}

	else
	{//�t�@�C�����J���Ȃ��ꍇ
	}
}