//-----------------------------------------------------------------------+
// �G�t�F�N�g�N���X                         
//                                                      2019 Yutaro Ono.
//-----------------------------------------------------------------------+

// �C���N���[�h�t�@�C��
#include "Effect.h"

// �R���X�g���N�^
PlayEffect::PlayEffect(const char* sourceEffectHandle)
	:m_effectHandle(-1)
	,m_playPos(VGet(0, 0, 0))
	,m_playingEffect(-1)
{
	// ���f���̃��[�h
	m_effectHandle = LoadEffekseerEffect(sourceEffectHandle,1.5f);
	if (m_effectHandle == -1)
	{
		printfDx("�G�t�F�N�g�ǂݍ��ݎ��s");
	}

}

// �R���X�g���N�^2 (�X�P�[���w��)
PlayEffect::PlayEffect(const char* sourceEffectHandle, float _scale)
	:m_effectHandle(-1)
	, m_playPos(VGet(0, 0, 0))
	, m_playingEffect(-1)
{
	// ���f���̃��[�h
	m_effectHandle = LoadEffekseerEffect(sourceEffectHandle, _scale);
	if (m_effectHandle == -1)
	{
		printfDx("�G�t�F�N�g�ǂݍ��ݎ��s");
	}

}

// �f�X�g���N�^
PlayEffect::~PlayEffect()
{
	// �����Ȃ�
}


// �������
void PlayEffect::Delete()
{
	if (GetNowPlaying() == 0)
	{
		StopEffect();
	}

	DeleteEffekseerEffect(m_effectHandle);
}

// �G�t�F�N�g�̍Đ����~�߂�
void PlayEffect::StopEffect()
{
	StopEffekseer3DEffect(m_playingEffect);
	m_playingEffect = IsEffekseer3DEffectPlaying(m_playingEffect);
}

/// <summary>
/// �Đ������𒲂ׂ�
/// </summary>
/// <returns> �Đ����F0, ����ȊO�F1 </returns>
const int PlayEffect::GetNowPlaying()
{
	return IsEffekseer3DEffectPlaying(m_playingEffect);
}

/// <summary>
/// �Đ����̃G�t�F�N�g�̍��W��ς���
/// </summary>
/// <param name="_size"></param>
void PlayEffect::SetPlayingEffectPos(const VECTOR& _playPos)
{
	SetPosPlayingEffekseer3DEffect(m_playingEffect, _playPos.x, _playPos.y, _playPos.z);
}

/// <summary>
/// �Đ����G�t�F�N�g�̉�]
/// </summary>
/// <param name="_dirVec"></param>
void PlayEffect::SetPlayingEffectRotation(const VECTOR& _dirVec)
{
	SetRotationPlayingEffekseer3DEffect(m_playingEffect, _dirVec.x, _dirVec.y, _dirVec.z);
}

// Effekseer3D�̕`��
void PlayEffect::PlayEffekseer(const VECTOR in_playPos)
{
	// printfDx(" (X���W : %f, Y���W : %f, Z���W : %f ", in_playPos.x, in_playPos.y, in_playPos.z);

	// printfDx("�G�t�F�N�g�Đ�");

	// �G�t�F�N�g�̍��W���X�V
	m_playPos = in_playPos;

	// �G�t�F�N�g�̕`��
	m_playingEffect = PlayEffekseer3DEffect(m_effectHandle);

	// �G�t�F�N�g���Đ�������W���w��
	SetPosPlayingEffekseer3DEffect(m_playingEffect, m_playPos.x, m_playPos.y, m_playPos.z);
}

// Effekseer3D�̃T�C�Y���w�肵���Đ�
void PlayEffect::ChangeSizePlayEffekseer(const VECTOR in_playPos, const VECTOR in_size)
{
	// �G�t�F�N�g�̍��W�X�V
	m_playPos = in_playPos;

	// �G�t�F�N�g�̕`��
	m_playingEffect = PlayEffekseer3DEffect(m_effectHandle);

	// �G�t�F�N�g�̃T�C�Y��ݒ�
	SetScalePlayingEffekseer3DEffect(m_playingEffect, in_size.x, in_size.y, in_size.z);

	// �G�t�F�N�g���Đ�������W���w��
	SetPosPlayingEffekseer3DEffect(m_playingEffect, m_playPos.x, m_playPos.y, m_playPos.z);

}

void PlayEffect::PlayEffekseer2D(const VECTOR in_playPos)
{
	// �G�t�F�N�g�̍��W���X�V
	m_playPos = in_playPos;

	// �G�t�F�N�g�̕`��
	m_playingEffect = PlayEffekseer2DEffect(m_effectHandle);

	// �G�t�F�N�g���Đ�������W���w��
	SetPosPlayingEffekseer2DEffect(m_playingEffect, m_playPos.x, m_playPos.y, m_playPos.z);

}
