#include "main.h"
#include "light.h"
#include "inputkeyboard.h"
#include "application.h"

//�O���[�o���ϐ��錾
D3DLIGHT9 g_light;		//���C�g����

//=========================================
//���C�g�̏���������
////=========================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();

	D3DXVECTOR3 vecDir; //���C�g�̕����x�N�g��

	//���C�g�̍\���̂��N���A����
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));

	//���C�g�̎�ނ�ݒ�
	g_light.Type = D3DLIGHT_DIRECTIONAL;		//���s����

	//���C�g�̊g�U����ݒ�
	g_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_light.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

	//���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	//���K������(�傫��1�̃x�N�g���ɂ���)
	D3DXVec3Normalize(&vecDir, &vecDir);

	g_light.Direction = vecDir;

	//���C�g��ݒ肷��
	pDevice->SetLight(0, &g_light);

	//���C�g��L��������
	pDevice->LightEnable(0, TRUE);
}

void UninitLight(void)
{

}

void UpdateLight(void)
{
	//LPDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();

	//CInput *pKeyboard = CInput::GetKey();

	//if (pKeyboard->Press(DIK_LEFT))
	//{
	//	g_light.Direction.x += 0.1f;
	//}
	//if (pKeyboard->GetPress(DIK_RIGHT))
	//{
	//	g_light.Direction.x -= 0.1f;
	//}

	//g_light.Direction.x = NormalizeLight(g_light.Direction.x);

	//if (pKeyboard->Press(DIK_UP))
	//{
	//	g_light.Direction.y -= 0.1f;
	//}
	//if (pKeyboard->Press(DIK_DOWN))
	//{
	//	g_light.Direction.y += 0.1f;
	//}

	//g_light.Direction.y = NormalizeLight(g_light.Direction.y);

	//if (pKeyboard->Press(DIK_F))
	//{
	//	g_light.Direction.z -= 0.1f;
	//}
	//if (pKeyboard->Press(DIK_G))
	//{
	//	g_light.Direction.z += 0.1f;
	//}

	//g_light.Direction.z = NormalizeLight(g_light.Direction.z);

	////���C�g��ݒ肷��
	//pDevice->SetLight(0, &g_light);

}

//=========================================
//���C�g�̐���
//=========================================
float NormalizeLight(float Direction)
{
	if (Direction > 1.0f)
	{
		Direction = 1.0f;
	}
	else if (Direction < -1.0f)
	{
		Direction = -1.0f;
	}

	return Direction;
}