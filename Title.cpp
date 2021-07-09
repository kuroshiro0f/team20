#include "Title.h"
#include "Game.h"
#include "TestSceneUeyama.h"
#include "TestSceneKoga.h"

#include "DxLib.h"

const int LOGO_X = 0;			//	���S��X���W
const int LOGO_Y = 0;			//	���S��Y���W
const int GUIDANCE_X = 0;		//	�K�C�h��X���W
const int GUIDANCE_Y = 0;		//	�K�C�h��Y���W

// �ő哧�ߗ�
const int defaultTrans = 255;
// ���ߗʕω��p�x�N�g��
const int transModeration = -1;

Title::Title()
{
	m_backGraphHandle = LoadGraph("data/img/Title_back.png");			//	�O���t�B�b�N�n���h���Ƀ^�C�g����ʂ̃C���[�W���Z�b�g
	m_logoGraphHandle = LoadGraph("data/img/Title_logo.png");			//	�O���t�B�b�N�n���h���Ƀ^�C�g����ʂ̃C���[�W���Z�b�g
	m_guidanceGraphHandle = LoadGraph("data/img/Title_guidance.png");	//	�O���t�B�b�N�n���h���Ƀ^�C�g����ʂ̃C���[�W���Z�b�g
	m_soundHandle = LoadSoundMem("data/sound/titleBgm.ogg");			//	�T�E���h�n���h���Ƀ^�C�g����ʂ�BGM���Z�b�g
	m_click_sound_handle = LoadSoundMem("data/sound/EnterToSound.wav");	//	ENTER�Ői�ލۂ̃T�E���h�����[�h
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		m_checkKeyFlag = TRUE;
	}
	// ���ߗʕϐ���255�ɐݒ�
	transParent = defaultTrans;
	// �����ߗʕϐ����P�ɐݒ�
	permeationAmount = 1;
}

Title::~Title()
{
	StopSoundMem(m_soundHandle);
	DeleteSoundMem(m_soundHandle);
	DeleteSoundMem(m_click_sound_handle);		//	ENTER�Ői�ނƂ��̃T�E���h�����������
	DeleteGraph(m_backGraphHandle);
	DeleteGraph(m_logoGraphHandle);
	DeleteGraph(m_guidanceGraphHandle);
}

SceneBase* Title::Update()
{
	// ���ߗʂ�122���傫���Ȃ�����
	if (transParent >= defaultTrans)
	{
		// ���ߗʂ�255�ɐݒ�
		transParent=defaultTrans-1;
		// �����ߗʂ�-1�ɂ���
		permeationAmount*= transModeration;
	}
	// ���ߗʂ�0��菬�������
	else if (defaultTrans/2 >= transParent )
	{
		// ���ߗʂ�ݒ�
		transParent = defaultTrans/2+1;
		// �����ߗʂ�1�ɂ���
		permeationAmount*= transModeration;
	}
	// �����ߗʂ𓧉ߗʂɉ��Z����
	transParent += permeationAmount;

	if (!CheckHitKey(KEY_INPUT_RETURN))
	{
		m_checkKeyFlag = FALSE;
	}
	
	if (CheckHitKey(KEY_INPUT_RETURN) && m_checkKeyFlag == FALSE)
	{
		PlaySoundMem(m_click_sound_handle, DX_PLAYTYPE_NORMAL);
		return new TestSceneUeyama;
	}
	return this;
}

void Title::Draw()
{
	DrawGraph(0, 0, m_backGraphHandle, TRUE);							//	�^�C�g����ʂ̔w�i��\��
	DrawGraph(LOGO_X, LOGO_Y, m_logoGraphHandle, TRUE);					//	�^�C�g����ʂ̃��S��\��

	// ���߂��ĕ`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, transParent);
	DrawGraph(GUIDANCE_X, GUIDANCE_Y, m_guidanceGraphHandle, TRUE);		//	�^�C�g����ʂ̃K�C�h��\��
	// ���߂����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Title::Sound()
{
	PlaySoundMem(m_soundHandle, DX_PLAYTYPE_BACK,FALSE);
	ChangeVolumeSoundMem(m_volumePal, m_soundHandle);
}

void Title::Load()
{
	//	���W�ƃO���t�B�b�N�n���h����������UI�N���X�̃C���X�^���X�𐶐�
}
