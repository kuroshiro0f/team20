#include "Target.h"
#include "ObstructBase.h"

// �ÓI�萔.


//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
Target::Target()
	: modelHandle(-1)
	, hitRadius(5.0f)
	, score(false)
	, timenow(0)
{
	// �R�c���f���̓ǂݍ���
	modelHandle = MV1LoadModel("data/model/target/icecream/SVH-icecream/icecream.pmx");

	// pos��Vector�^�Ȃ̂ŁAVGet�Ō��_�ɃZ�b�g
	pos = VGet(0, 0, 0);
	// �ړ�����͂��i���ׂĂ̍��W�j�[���ɂ���
	velocity = VGet(0, 0, 0);
	// 
	dir = VGet(0, 0, 1);
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
void Target::Update()
{


	// �㉺�����ɂ����Ȃ��悤�Ƀx���V�e�B�𐮂���.
	velocity = VGet(velocity.x, 0, velocity.z);

	// �|�W�V�������X�V.
	pos = VAdd(pos, velocity);

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
	// �R�c���f���̕`��
	MV1DrawModel(modelHandle);

	// �f�o�b�O�����蔻��.
	DrawSphere3D(pos, hitRadius, 5, 0x00ffff, 0x00ffff, false);
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