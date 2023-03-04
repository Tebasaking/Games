//=========================================
//
// ファイル読み込み処理
// Auther：冨所知生
//
//=========================================
#include<stdio.h>
#include "main.h"
#include "file.h"
#include "model.h"
#include "player.h"
#include "titlemodel.h"

//=========================================
// マクロ定義
//=========================================
#define LOAD_FILE_NAME_000		"model.txt"
#define LOAD_FILE_NAME_001		"motion.txt"
#define LOAD_FILE_NAME_002		"cooking.txt"
#define LOAD_FILE_NAME_003		"title.txt"

//=========================================
// グローバル変数
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
// ファイルの読み込み処理
//=========================================
void InitFile(void)
{
	// ファイルポインタの宣言
	FILE * pFile;

	char aFile[128] = FILE_STAGE;
	strcat(aFile, LOAD_FILE_NAME_000);
	nCntParts = 0;
	nCntModel = 0;

	//ファイルを開く
	pFile = fopen(aFile, "r");

	if (pFile != NULL)
	{//ファイルが開いた場合
		while (1)
		{
			fscanf(pFile, "%s", &g_aString);
			if (strcmp(&g_aString[0], "START") == 0)
			{// 文字列が一致した場合
				break;
			}
		}

		fscanf(pFile, "%s", &g_aString[0]);
		if (strcmp(&g_aString[0], "SCRIPT") == 0)
		{// 文字列が一致した場合
			while (1)
			{// 文字列の初期化と読み込み
				g_aString[0] = {};

					fscanf(pFile, "%s", &g_aString[0]);

					if (strcmp(&g_aString[0], "MODEL_FILENAME") == 0)
					{// 文字列が一致した場合
						fscanf(pFile, "%s", &g_modelFile);
					}
					else if (strcmp(&g_aString[0], "MODELSET") == 0)
					{// 文字列が一致した場合
						while (1)
						{
							// 文字列の初期化と読み込み
							g_aString[0] = {};
							fscanf(pFile, "%s", &g_aString[0]);

							if (strcmp(&g_aString[0], "TYPE") == 0)
							{
								fscanf(pFile, "%d", &nType);
							}

							if (strcmp(&g_aString[0], "POS") == 0)
							{// 文字列が一致した場合
								fscanf(pFile, "%f", &g_modelpos.x);
								fscanf(pFile, "%f", &g_modelpos.y);
								fscanf(pFile, "%f", &g_modelpos.z);
							}

							if (strcmp(&g_aString[0], "rot") == 0)
							{// 文字列が一致した場合
								fscanf(pFile, "%f", &g_modelpos.x);
								fscanf(pFile, "%f", &g_modelpos.y);
								fscanf(pFile, "%f", &g_modelpos.z);
							}

							if (strcmp(&g_aString[0], "END_MODELSET") == 0)
							{// 文字列が一致した場合
							 // モデルの設置
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
				{// 文字列が一致した場合
					break;
				}
			}
		}
		//ファイルを閉じる
		fclose(pFile);
	}

	else
	{//ファイルが開けない場合
	}
}
//=========================================
// motion.txtの読み込み
//=========================================
void MotionFile(void)
{
	// ファイルポインタの宣言
	FILE * pFile;

	char aFile[128] = FILE_STAGE;
	strcat(aFile, LOAD_FILE_NAME_001);

	//ファイルを開く
	pFile = fopen(aFile, "r");

	if (pFile != NULL)
	{//ファイルが開いた場合
		while (1)
		{
			fscanf(pFile, "%s", &g_aString);
			if (strcmp(&g_aString[0], "#") == 0)
			{
				fgets(&g_aString[0], sizeof(g_aString), pFile);
			}

			if (strcmp(&g_aString[0], "START") == 0)
			{// 文字列が一致した場合
				break;
			}
		}

		fscanf(pFile, "%s", &g_aString[0]);
		if (strcmp(&g_aString[0], "CHARACTERSET") == 0)
		{// 文字列が一致した場合
			while (1)
			{// 文字列の初期化と読み込み
				g_aString[0] = {};

				fscanf(pFile, "%s", &g_aString[0]);

				if (strcmp(&g_aString[0], "LOOP") == 0)
				{// 文字列が一致した場合
					fscanf(pFile, "%s", &g_modelFile);
				}

				else if (strcmp(&g_aString[0], "KEYSET") == 0)
				{// 文字列が一致した場合
					while (1)
					{
						// 文字列の初期化と読み込み
						g_aString[0] = {};
						fscanf(pFile, "%s", &g_aString[0]);

						if (strcmp(&g_aString[0], "ANIM_NUMBER") == 0)
						{//文字列が一致した場合
							fscanf(pFile, "%d", &ANIM_NUMBER);
						}

						if (strcmp(&g_aString[0], "NUM_PARTS") == 0)
						{//文字列が一致した場合
							fscanf(pFile, "%f", &PARTS_NUMBER);
						}

						if (strcmp(&g_aString[0], "FRAME") == 0)
						{// 文字列が一致した場合
							fscanf(pFile, "%f", &FRAME);
						}

						if (strcmp(&g_aString[0], "POS") == 0)
						{// 文字列が一致した場合
							fscanf(pFile, "%f", &g_motionpos.x);
							fscanf(pFile, "%f", &g_motionpos.y);
							fscanf(pFile, "%f", &g_motionpos.z);
						}

						if (strcmp(&g_aString[0], "rot") == 0)
						{// 文字列が一致した場合
							fscanf(pFile, "%f", &g_motionrot.x);
							fscanf(pFile, "%f", &g_motionrot.y);
							fscanf(pFile, "%f", &g_motionrot.z);
						}

						if (strcmp(&g_aString[0], "NUM_KEY") == 0)
						{//文字列が一致した場合
							fscanf(pFile, "%f", &NUM_KEY);
						}

						if (strcmp(&g_aString[0], "END_KEYSET") == 0)
						{// 文字列が一致した場合
						 // アニメーションの起動
							LoadAnimation(ANIM_NUMBER, NUM_KEY ,PARTS_NUMBER ,true , 2 , FRAME , g_motionpos, g_motionrot);
							break;
						}
					}
				}

			else if (strcmp(&g_aString[0], "END_CHARACTER") == 0)
			{// 文字列が一致した場合
				nKey = 0;
				break;
			}
		}
	}
		//ファイルを閉じる
		fclose(pFile);
	}

	else
	{//ファイルが開けない場合
	}
}

//=========================================
// 料理の完成時のファイル入出力
//=========================================
void CookingFile()
{
	// ファイルポインタの宣言
	FILE * pFile;

	char aFile[128] = FILE_STAGE;
	strcat(aFile, LOAD_FILE_NAME_002);

	//ファイルを開く
	pFile = fopen(aFile, "r");

	if (pFile != NULL)
	{//ファイルが開いた場合
		while (1)
		{
			fscanf(pFile, "%s", &g_aString);
			if (strcmp(&g_aString[0], "type") == 0)
			{// 文字列が一致した場合
				break;
			}
		}
	}
}

//=========================================
// ファイルの読み込み処理
//=========================================
void TitleFile(void)
{
	// ファイルポインタの宣言
	FILE * pFile;

	char aFile[128] = FILE_STAGE;
	strcat(aFile, LOAD_FILE_NAME_003);
	nCntParts = 0;
	nCntModel = 0;

	//ファイルを開く
	pFile = fopen(aFile, "r");

	if (pFile != NULL)
	{//ファイルが開いた場合
		while (1)
		{
			fscanf(pFile, "%s", &g_aString);
			if (strcmp(&g_aString[0], "START") == 0)
			{// 文字列が一致した場合
				break;
			}
		}

		fscanf(pFile, "%s", &g_aString[0]);
		if (strcmp(&g_aString[0], "SCRIPT") == 0)
		{// 文字列が一致した場合
			while (1)
			{// 文字列の初期化と読み込み
				g_aString[0] = {};

				fscanf(pFile, "%s", &g_aString[0]);

				if (strcmp(&g_aString[0], "MODEL_FILENAME") == 0)
				{// 文字列が一致した場合
					fscanf(pFile, "%s", &g_modelFile);
				}
				else if (strcmp(&g_aString[0], "MODELSET") == 0)
				{// 文字列が一致した場合
					while (1)
					{
						// 文字列の初期化と読み込み
						g_aString[0] = {};
						fscanf(pFile, "%s", &g_aString[0]);

						if (strcmp(&g_aString[0], "POS") == 0)
						{// 文字列が一致した場合
							fscanf(pFile, "%f", &g_modelpos.x);
							fscanf(pFile, "%f", &g_modelpos.y);
							fscanf(pFile, "%f", &g_modelpos.z);
						}

						if (strcmp(&g_aString[0], "rot") == 0)
						{// 文字列が一致した場合
							fscanf(pFile, "%f", &g_modelpos.x);
							fscanf(pFile, "%f", &g_modelpos.y);
							fscanf(pFile, "%f", &g_modelpos.z);
						}

						if (strcmp(&g_aString[0], "END_MODELSET") == 0)
						{// 文字列が一致した場合
						 // モデルの設置
							SetTitleModel(g_modelpos, g_modelFile, nCntModel, nType);
							nCntModel++;
							break;
						}
					}
				}
				else if (strcmp(&g_aString[0], "END_SCRIPT") == 0)
				{// 文字列が一致した場合
					break;
				}
			}
		}
		//ファイルを閉じる
		fclose(pFile);
	}

	else
	{//ファイルが開けない場合
	}
}