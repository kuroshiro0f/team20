#include "Target.h"
#include "ObstructBase.h"
#include "TestSceneKoga.h"
#include "Hitchecker.h"
#include "Effect.h"
#include "UI.h"
#include <cmath>

// �ÓI�萔.
const int Target::m_target_X = 400;
//const int Target::m_target_X = 0;
const int Target::m_target_Y = 10;
const int Target::m_target_Z = 0;

const int Target::m_font_X = 1340;
const int Target::m_font_Y = 160;
const int Target::m_font_size = 50;
const int Target::m_font_thick = -1;

static const double pi = 3.141592653589793;

// ����
const int VOLUME_PAL = 100;

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
Target::Target()
	: modelHandle(-1)
	, hitRadius(7.5f)
	, timenow(0)
	, m_targetCount(0)
	, m_plusX(0)
	, m_setTime(0) 
	,m_shotInterval(5)
	, m_iceState(NO_SHOT)
	, m_hitFlag(false)
	, m_throwIceSoundHandle(-1)
	, m_hitIceSoundHandle(-1)
	, m_iceType(0)
{
	// �R�c���f���̓ǂݍ���
	modelHandle = MV1LoadModel("data/model/target/icecream/SVH-icecream/icecream.pmx");
	m_FontHandle = CreateFontToHandle(NULL, m_font_size, m_font_thick, DX_FONTTYPE_NORMAL);

	m_target_accel = 0.1f;

	// pos��Vector�^�Ȃ̂ŁAVGet�Ō��_�ɃZ�b�g
	pos = VGet(m_target_X, m_target_Y, m_target_Z);
	// �ړ�����͂��i���ׂĂ̍��W�j�[���ɂ���
	velocity = VGet(0, 0, 0);
	// 
	dir = VGet(-1, 0, 0);
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
Target::~Target()
{
	// ���f���̃A�����[�h.
	MV1DeleteModel(modelHandle);
}

//-----------------------------------------------------------------------------
// @brief  �X�V.
//-----------------------------------------------------------------------------
void Target::Update(float _deltaTime)
{
	if (m_iceState==END_SHOT)
	{
		return;
	}
	 accelVec = VGet(0, 0, 0);
	//	�A�C�X�ˏo�t���O��true�ɂȂ�����
	if (m_iceState == NOW_SHOT)
	{
		accelVec = VScale(dir, m_target_accel);
	}
	
	// �x���V�e�B�����v�Z.
	velocity = VAdd(velocity, accelVec);

	// �㉺�����ɂ����Ȃ��悤�Ƀx���V�e�B�𐮂���.
	velocity = VGet(velocity.x * _deltaTime, 0, velocity.z * _deltaTime);

	// �|�W�V�������X�V.
	pos = VAdd(pos, velocity);

	switch (m_iceType)
	{
	case 0:
		break;
	case 1:
		pos.z = cos(pos.x / 20.0f) * (pos.x / 5);
		break;
	case 2:
		pos.y = sin(pos.x / 20.0f) * (pos.x / 5);
		pos.z = cos(pos.x / 20.0f) * (pos.x / 5);
		break;
	}
	//pos.y = sin(pos.x / 20.0f) * (pos.x / 5);
	//pos.z = cos(pos.x / 20.0f) * (pos.x / 5);

	// �͂������I������x���V�e�B�̕����Ƀf�B���N�V�����𒲐�.
	if (VSize(velocity) != 0)
	{
		dir = VNorm(velocity);
	}
	//printfDx("%f %f %f\n", dir.x, dir.y, dir.z);

	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(modelHandle, pos);

	// �����ɍ��킹�ĉ�].
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	// ���f���Ɍ����Ăق��������ɉ�].
	MATRIX tmpMat = MV1GetMatrix(modelHandle);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	tmpMat = MMult(tmpMat, rotYMat);
	MV1SetRotationMatrix(modelHandle, tmpMat);
}

//-----------------------------------------------------------------------------
// @brief  �`��.
//-----------------------------------------------------------------------------
void Target::Draw()
{
	// �����f���ł͏���������̂ŕ`��{����ݒ�
	MV1SetScale(modelHandle, VGet(3.0f, 3.0f, 3.0f));
	if (m_iceState != NO_SHOT)
	{
		// �R�c���f���̕`��
		MV1DrawModel(modelHandle);
	}
	
	if (m_iceState == NO_SHOT)
	{
		int timebuffer = GetNowCount() / 1000;
		
		DrawCircleAA(m_font_X, m_font_Y,((m_shotInterval + 1) - (timebuffer - m_setTime))*30
			,32, GetColor(255, 255, 255),FALSE);
	}

	// �f�o�b�O�����蔻��.
	//DrawSphere3D(pos, hitRadius, 5, 0x00ffff, 0x00ffff, false);
}

//-----------------------------------------------------------------------------
// @brief  ���A�N�V����.
//-----------------------------------------------------------------------------
void Target::Reaction(UI* _ui, bool _hitFlag)
{
	switch (_hitFlag)
	{
	case true:
		m_plusX = 20 + m_targetCount * 10;
		pos = VGet(m_plusX, 100, -200);
		m_hitFlag = true;

		ScoreUpdateUI(*_ui, _hitFlag);

		PlaySoundMem(m_hitIceSoundHandle, DX_PLAYTYPE_BACK);
		ChangeVolumeSoundMem(VOLUME_PAL, m_hitIceSoundHandle);

		// �RD���f���̃|�W�V�����ݒ�
		MV1SetPosition(modelHandle, pos);
		m_iceState = END_SHOT;
		break;
	case false:
		if (pos.x < -500 || pos.x > 500 && m_iceState == NOW_SHOT)
		{
			pos = VGet(200, 100, 200);

			ScoreUpdateUI(*_ui, _hitFlag);

			PlaySoundMem(m_missIceSoundHandle, DX_PLAYTYPE_BACK);
			ChangeVolumeSoundMem(VOLUME_PAL, m_missIceSoundHandle);

			// �RD���f���̃|�W�V�����ݒ�
			MV1SetPosition(modelHandle, pos);
			m_iceState = END_SHOT;
		}
		break;
	}
}

void Target::ScoreUpdateUI(UI& _ui,bool _hitFlag)
{
	_ui.ScoreUpdate(_hitFlag);
}

//-----------------------------------------------------------------------------
// @brief  �Փˏ���.
//-----------------------------------------------------------------------------
//void Target::OnHitObstruct(ObstructBase& obstruct)
//{
//	// �������g�̈ʒu����Q���̂����蔻�蕪���炷.
//	// Z����X���̓񎟌����W�Ƃ��Ĉʒu���炵���s��.
//	VECTOR yZeroTarget = VGet(pos.x, 0, pos.z);
//	VECTOR yZeroObstruct = VGet(obstruct.GetPos().x, 0, obstruct.GetPos().z);
//
//	VECTOR obsToTarget = VSub(yZeroTarget, yZeroObstruct);
//
//	// �Ԃ������Ƃ��ɗ��������B���傤�ǂ���float�덷�ŏd�Ȃ葱����̂ŏ����Ԃ�������.
//	float awayRange = (hitRadius + obstruct.GetHitRadius() + 0.01f);
//
//	VECTOR awayVec = VScale(VNorm(obsToTarget), awayRange);
//	pos = VAdd(yZeroObstruct, awayVec);
//
//	// �Ԃ������猸������.
//	velocity = VScale(velocity, COLIDE_DECEL_FAC);
//}