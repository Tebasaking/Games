//**************************************************************************************************
//
// �J��������(camera.h)
// Auther�F�������l
// Author : ���c�C�l
// Author : �y���m��
// �T�v : �J�����̐ݒ菈��
//
//**************************************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>
#include <DirectXMath.h>

#include "camera_radar.h"
#include "application.h"
#include "render.h"
#include "input.h"
#include "mouse.h"
#include "inputkeyboard.h"
#include "move.h"
#include "calculation.h"
#include "player_manager.h"
#include "debug_proc.h"
#include "game.h"
#include "meshfield.h"
#include "object.h"
#include "joypad.h"
#include "camera_player.h"
#include "player3D.h"
#include "sound.h"
#include "utility.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************
const float CCameraRadar::CAMERA_NEAR = 30.0f;		// �j�A
const float CCameraRadar::CAMERA_FUR = 100000000.0f;	// �t�@�[

//=============================================================================
// �R���X�g���N�^
// Author	: �������l
// �T�v		: �C���X�^���X�������ɍs������
//=============================================================================
CCameraRadar::CCameraRadar() :
	m_nCntFly(0),
	m_fRotMove(0.0f)										// �ړ�����
{
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CCameraRadar::~CCameraRadar()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�ƒ����_�̊Ԃ̋������Z�o����
//=============================================================================
HRESULT CCameraRadar::Init(D3DXVECTOR3 pos)
{
	m_posV = D3DXVECTOR3(0.0f, 15000.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_quaternion = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_viewport.MinZ = 0.0f;
	m_viewport.MaxZ = 1.0f;
	m_viewType = TYPE_PARALLEL;
	SetViewType(m_viewType);

	// ���_�ƒ����_�̋���
	D3DXVECTOR3 posDiss = m_posR - m_posV;
	m_fDistance = sqrtf((posDiss.y * posDiss.y) + (posDiss.x * posDiss.x) + (posDiss.z * posDiss.z));

	m_mode = TYPE_FREE;

	m_nCntMoveSound = 10000;

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �I��
//=============================================================================
void CCameraRadar::Uninit(void)
{
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V
//=============================================================================
void CCameraRadar::Update(void)
{
	// �v���C���[�̈ʒu���擾���āAX �� Y �̍��W�����킹��B
	CPlayer3D *pPlayer = CPlayerManager::GetPlayer();

	if (pPlayer != nullptr)
	{
		D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();

		m_posV = D3DXVECTOR3(PlayerPos.x, GetPosV().y, PlayerPos.z);
		m_posR = D3DXVECTOR3(PlayerPos.x, GetPosR().y, PlayerPos.z);
	}

	//	CMouse *pMouse = CApplication::GetMouse();

	// ��]���s���B
	Rotate();

	//// �f�o�b�O�p
	//CDebugProc::Print("=========== camera_radar ===========\n");
	//CDebugProc::Print("�J�����̍��W : (%.1f,%.1f,%.1f) \n", m_posV.x, m_posV.y, m_posV.z);
	//CDebugProc::Print("�J�����̍��WR : (%.1f,%.1f,%.1f) \n", m_posR.x, m_posR.y, m_posR.z);
	//CDebugProc::Print("�J�����̉�] : (%.2f,%.2f,%.2f) \n", GetRot().x, GetRot().y, GetRot().z);
	//CDebugProc::Print("====================================\n");
}

//=============================================================================
// ��]�̌v�Z
// Author : �������l
// Author : YudaKaito
// �T�v : 
//=============================================================================
void CCameraRadar::Rotate()
{
	// X���̉�]
	CPlayer3D *pPlayer = CPlayerManager::GetPlayer();

	// �v���C���[�̃N�H�[�^�j�I���̎擾
	D3DXQUATERNION qua = CApplication::GetCamera()->GetQuaternion();
	D3DXQuaternionNormalize(&qua, &qua);

	D3DXMATRIX WorldMatrix;

	// �v���C���[�̐i�s�����x�N�g��(0,0,1)�����݂̃N�H�[�^�j�I�����x�N�g���ɕϊ����ĂQ�̃x�N�g���̊p�x�����߂�
	D3DXVECTOR3 Vec1 = D3DXVECTOR3(0, 0, 1);
	// �N�H�[�^�j�I������]�s��ɕϊ�
	D3DXMatrixRotationQuaternion(&WorldMatrix, &qua);

	D3DXVECTOR3 Vec2;
	D3DXVec3TransformCoord(&Vec2, &Vec1, &WorldMatrix);

	//CDebugProc::Print("Vec2 : (%.1f,%.1f,%.1f) \n", Vec2.x, Vec2.y, Vec2.z);
	//CDebugProc::Print("%.1f \n", atan2f(Vec2.x, Vec2.z));
	SetRot(D3DXVECTOR3(0.0f, 0.0f, atan2f(Vec2.x, Vec2.z)));


	//// ���όv�Z
	//float dot = Vec1.x * Vec2.x + Vec1.z * Vec2.z;
	//
	//dot = acos(dot);

	//// �O�όv�Z
	//float Cross = Vec2Cross(&Vec1, &Vec2);

	//if (Cross <= 0)
	//{
	//	dot *= -1;
	//}

	//SetRot(D3DXVECTOR3(GetRot().x, GetRot().y, dot));
}

//=========================================
// �}�E�X�̈ړ�
// Author : �������l
// Author : YudaKaito
//=========================================
void CCameraRadar::MouseMove(void)
{
}

//=========================================
// �W���C�p�b�h�̈ړ�
// Author : �y���m��
// �T�v : �W���C�p�b�h�g�p���̃J�����̐���
//=========================================
void CCameraRadar::JoyPadMove(void)
{

}

//=========================================
// �}�E�X�𗘗p�����J�����̐���
// Author : �y���m��
//=========================================
bool CCameraRadar::Limit_Used_Mouse()
{
	//CMouse *pMouse = CApplication::GetMouse();
	//D3DXVECTOR3 axis = {};

	//// �N���b�N�̏���ۊ�
	//bool hasRightClick = pMouse->GetPress(CMouse::MOUSE_KEY_RIGHT);

	//if (hasRightClick)
	//{
	//	if (m_rotMove.x > 0.0f)
	//	{
	//		m_MouseMove++;
	//	}
	//	else if (m_rotMove.x < 0.0f)
	//	{
	//		m_MouseMove--;
	//	}

	//	// �������̏���A������̏��
	//	if (m_MouseMove >= 5.0f || m_MouseMove <= -10.0f)
	//	{
	//		return true;
	//	}
	//}

	return false;
}

//=========================================
// �N�H�[�^�j�I�������W�A���ɕϊ����鏈��
//=========================================
double CCameraRadar::quaternion_to_radian(double qw, double qx, double qy, double qz)
{
	// Calculate quaternion magnitude
	double q_norm = std::sqrt(qw*qw + qx*qx + qy*qy + qz*qz);

	// Calculate rotation angle in radians
	double theta = 2.0*std::acos(qw / q_norm);

	// Calculate rotation axis
	double axis_x = qx / q_norm;
	double axis_y = qy / q_norm;
	double axis_z = qz / q_norm;

	// Calculate rotation matrix
	double R[3][3] = { { std::cos(theta / 2.0), -axis_x*std::sin(theta / 2.0), -axis_y*std::sin(theta / 2.0) },
	{ axis_x*std::sin(theta / 2.0), std::cos(theta / 2.0), -axis_z*std::sin(theta / 2.0) },
	{ axis_y*std::sin(theta / 2.0), axis_z*std::sin(theta / 2.0), std::cos(theta / 2.0) } };

	// Calculate radians
	double radian = std::acos((R[0][0] + R[1][1] + R[2][2] - 1.0) / 2.0);

	return radian;
}

//=========================================
// ���W�A�����N�H�[�^�j�I���ɕϊ�
//=========================================
D3DXQUATERNION CCameraRadar::radian_to_quaternion(double radian)
{
	D3DXQUATERNION qua;

	// Calculate quaternion elements
	qua.w = std::cos(radian * 0.5f);
	qua.x = 0.0;
	qua.y = std::sin(radian * 0.5f);
	qua.z = std::sin(radian * 0.5f);

	// Normalize quaternion
	double q_norm = std::sqrt(qua.w*qua.w + qua.x * qua.x + qua.y * qua.y + qua.z * qua.z);
	qua.w /= q_norm;
	qua.x /= q_norm;
	qua.y /= q_norm;
	qua.z /= q_norm;

	return qua;
}

//=========================================
// �N�H�[�^�j�I�������W�A���ɕϊ����鏈��
//=========================================
D3DXVECTOR3 CCameraRadar::QuaternionToPolar(double w, double x, double y, double z)
{
	D3DXVECTOR3 radian;

	float r = std::sqrt(w*w + x*x + y*y + z*z); // ���a���v�Z
	radian.x = std::acos(w / r); // ��1�̊p�x���v�Z
	radian.y = std::atan2(y, x); // ��2�̊p�x���v�Z
	radian.z = std::atan2(z, std::sqrt(w*w + x*x + y*y)); // ��3�̊p�x���v�Z

	return radian;
}

//=========================================
// �I�C���[�p���N�H�[�^�j�I���ɕϊ�����
//=========================================
D3DXQUATERNION CCameraRadar::fromEuler(float yaw, float pitch, float roll)
{
	// �e���̉�]���N�H�[�^�j�I���ɕϊ�����
	D3DXQUATERNION qYaw;
	D3DXQuaternionRotationYawPitchRoll(&qYaw, yaw, 0, 0);

	D3DXQUATERNION qPitch;
	D3DXQuaternionRotationYawPitchRoll(&qPitch, 0, pitch, 0);

	D3DXQUATERNION qRoll;
	D3DXQuaternionRotationYawPitchRoll(&qRoll, 0, 0, roll);

	// �e�N�H�[�^�j�I�������ԂɊ|�����킹��
	D3DXQUATERNION qRotation;
	D3DXQuaternionMultiply(&qRotation, &qYaw, &qPitch);
	D3DXQuaternionMultiply(&qRotation, &qRotation, &qRoll);

	// ���ʂ𐳋K������
	D3DXQuaternionNormalize(&qRotation, &qRotation);

	return qRotation;
}

//=========================================
// �N�H�[�^�j�I������]�s��ɕϊ�����
//=========================================
D3DXVECTOR3 CCameraRadar::DirectionVectorFromQuaternion(const D3DXQUATERNION& qRotation)
{
	// �N�H�[�^�j�I������]�s��ɕϊ�����
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationQuaternion(&rotationMatrix, &qRotation);

	// �����x�N�g�������o��
	D3DXVECTOR3 direction(0, 0, 1);
	D3DXVec3TransformNormal(&direction, &direction, &rotationMatrix);

	return direction;
}