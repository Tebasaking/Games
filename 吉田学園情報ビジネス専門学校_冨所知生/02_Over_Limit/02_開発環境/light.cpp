//=========================================
//
//	���C�g�̐ݒu�Ɛ��䏈��
//	Author : �y���m��
//
//=========================================
#include "main.h"
#include "light.h"

//�}�N���ϐ�
#define MAX_LIGHT (5)

//�O���[�o���ϐ��錾
D3DLIGHT9 g_light[MAX_LIGHT];		//���C�g����

//=========================================
//���C�g�̏���������
////=========================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir[MAX_LIGHT];				//���C�g�̕����x�N�g��

	//���C�g�̍\���̂��N���A����
	ZeroMemory(&g_light[0], sizeof(g_light));

	//���C�g�̕�����ݒ�
	vecDir[0] = D3DXVECTOR3(0.2f, 0.5f, 0.4f);

	//���C�g�̕�����ݒ�
	vecDir[1] = D3DXVECTOR3(-1.0f, 0.0f, 0.2f);

	//���C�g�̕�����ݒ�
	vecDir[2] = D3DXVECTOR3(0.1f, -0.5f, -0.4f);

	//���C�g�̕�����ݒ�
	vecDir[3] = D3DXVECTOR3(0.1f, 0.9f, -0.4f);

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//���K������(�傫��1�̃x�N�g���ɂ���)
		D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);
		
		//���C�g�̎�ނ�ݒ�
		g_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;		//���s����

		//���C�g�̊g�U����ݒ�
		g_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_light[nCntLight].Direction = vecDir[nCntLight];

		//���C�g��ݒ肷�遫nCnt�Ԗڂ�Light��ݒ肷��
		pDevice->SetLight(nCntLight, &g_light[nCntLight]);

		//���C�g��L�������遫nCnt�Ԗڂ�Light��ݒ肷��
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//=========================================
//���C�g�̔j��
//=========================================
void UninitLight(void)
{

}

//=========================================
//���C�g�̍X�V
//=========================================
void UpdateLight(void)
{

}