#include "TestTitleSceneUeyama.h"
#include "DxLib.h"
#include "GameScene_easy.h"
#include "GameScene_normal.h"
#include "GameScene_hard.h"
#include "TestSceneUeyama.h"

// �ő哧�ߗ�
const int MAX_TRANSP_VAL = 255;
// ���ߗʕω��p�x�N�g��
const int TRANSP_MODERATION = -1;

const int FIRST_TRANS_VAL = 100;

// �S��Փx
const int ALL_DIFFICULT = 3;

const int SCREEN_SIZE_W = 1920;
const int SCREEN_SIZE_H = 1080;

const int VOLUME_PAL_SUP = 130;

//	�t�F�[�h�C���̑��x
const int FADE_IN_SPEED = 3;
//	�t�F�[�h�A�E�g�̑��x
const int FADE_OUT_SPEED = 3;


TestTitleSceneUeyama::TestTitleSceneUeyama()
	:m_state(TITLE_TRANS_STATE::FIRST_ENTER)
	, m_cursolNum(0)
	, m_fadeInFinishFlag(false)
	, m_fadeOutFlag(false)
	, m_fadeOutFinishFlag(false)
{
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		m_checkKeyFlag = TRUE;
	}
	// ���ߗʕϐ���122�ɐݒ�
	m_transpVal = MAX_TRANSP_VAL;
	m_fadeTransVal = FIRST_TRANS_VAL;
	// �����ߗʕϐ����P�ɐݒ�
	m_permeationAmount = 1;
}

TestTitleSceneUeyama::~TestTitleSceneUeyama()
{
	StopSoundMem(m_soundHandle);
	DeleteSoundMem(m_soundHandle);
	DeleteSoundMem(m_click_sound_handle);		//	ENTER�Ői�ނƂ��̃T�E���h�����������
	DeleteGraph(m_backGraphHandle);
	DeleteGraph(m_logoGraphHandle);
	DeleteGraph(m_guidanceGraphHandle);
}

/// <summary>
/// �X�V����
/// </summary>
/// <returns> �V�[���̃|�C���^ </returns>
SceneBase* TestTitleSceneUeyama::Update(float _deltaTime)
{

	// �X�e�[�g�����g���Ƃɏ�����ύX
	switch (m_state)
	{
	case TITLE_TRANS_STATE::FIRST_ENTER:

		// ���L�[���͏d���΍�̃t���O
		// ENTER�L�[����w�𗣂�����A����ENTER�̓��͂�L����
		if (!CheckHitKey(KEY_INPUT_RETURN))
		{
			m_checkKeyFlag = false;
		}

		// ENTER�Ŏ��̃X�e�[�g��
		if (CheckHitKey(KEY_INPUT_RETURN) && m_checkKeyFlag == false)
		{
			// ���L�[���͏d���΍�̃t���O
			m_checkKeyFlag = true;
			ChangeVolumeSoundMem(m_volumePal + VOLUME_PAL_SUP, m_click_sound_handle);
			PlaySoundMem(m_click_sound_handle, DX_PLAYTYPE_NORMAL);

			m_state = TITLE_TRANS_STATE::SECOND_CHOICE;
		}

		break;

	case TITLE_TRANS_STATE::SECOND_CHOICE:

		// ���L�[���͏d���΍�̃t���O
		// ENTER�L�[����w�𗣂�����A����ENTER�̓��͂�L����
		if (!CheckHitKey(KEY_INPUT_RETURN) && !CheckHitKey(KEY_INPUT_UP) && !CheckHitKey(KEY_INPUT_DOWN))
		{
			m_checkKeyFlag = false;
		}

		// ��Փx�I��
		if (CheckHitKey(KEY_INPUT_UP) && !m_checkKeyFlag)
		{
			// ���L�[���͏d���΍�̃t���O
			m_checkKeyFlag = true;

			// �J�[�\������ (0:�C�[�W�[�A1:�m�[�}���A2:�n�[�h)
			if (m_cursolNum == 1 || m_cursolNum == 2)
			{
				m_cursolNum--;
			}
			else if (m_cursolNum == 0)
			{
				m_cursolNum = 2;
			}
		}
		else if (CheckHitKey(KEY_INPUT_DOWN) && !m_checkKeyFlag)
		{
			// ���L�[���͏d���΍�̃t���O
			m_checkKeyFlag = true;

			// �J�[�\������ (0:�C�[�W�[�A1:�m�[�}���A2:�n�[�h)
			if (m_cursolNum == 1 || m_cursolNum == 0)
			{
				m_cursolNum++;
			}
			else if (m_cursolNum == 2)
			{
				m_cursolNum = 0;
			}
		}

		// ENTER�őI��������Փx�̃V�[����
		if (CheckHitKey(KEY_INPUT_RETURN) && !m_checkKeyFlag)
		{
			ChangeVolumeSoundMem(m_volumePal + VOLUME_PAL_SUP, m_click_sound_handle);
			PlaySoundMem(m_click_sound_handle, DX_PLAYTYPE_NORMAL);
			m_fadeOutFlag = true;
		}

		if (m_cursolNum == 0 && m_fadeOutFinishFlag)
		{
			// �C�[�W�[���[�h�V�[���̃C���X�^���X��Ԃ�
			return new GameSceneEasy();
		}

		if (m_cursolNum == 1 && m_fadeOutFinishFlag)
		{
			// �m�[�}�����[�h�̃C���X�^���X��Ԃ�
			return new GameSceneNormal();
		}

		if (m_cursolNum == 2 && m_fadeOutFinishFlag)
		{
			// �n�[�h���[�h�̃C���X�^���X��Ԃ�
			return new GameSceneHard();
		}

		break;

	default:

		break;
	}



	return this;
}

void TestTitleSceneUeyama::Draw()
{
	if (!m_fadeInFinishFlag)
	{
		// �t�F�[�h�C������
		for (int i = 0; i < 255; i += FADE_IN_SPEED)
		{
			// �`��P�x���Z�b�g
			SetDrawBright(i, i, i);

			// �O���t�B�b�N��`��
			DrawGraph(0, 0, m_backGraphHandle, TRUE);
			DrawGraph(0, 0, m_logoGraphHandle, TRUE);
			ScreenFlip();
		}
		m_fadeInFinishFlag = true;
	}
	// ���ߗʍX�V
	UpdateTransparent();

	// �o�b�N�O���E���h
	DrawGraph(0, 0, m_backGraphHandle, TRUE);

	// �I�����ɃJ�[�\�������₷���悤�ɔw�i���Â�����
	if (m_state == TITLE_TRANS_STATE::SECOND_CHOICE)
	{
		// ���߂��ĕ`��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 190);
		DrawBox(0, 0, SCREEN_SIZE_W, SCREEN_SIZE_H, GetColor(0, 0, 0), TRUE);
		// ���߂����ɖ߂�
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	// �^�C�g�����S
	DrawGraph(0, 0, m_logoGraphHandle, TRUE);

	// �X�e�[�g�����g���Ƃɏ�����ύX
	switch (m_state)
	{
	case TITLE_TRANS_STATE::FIRST_ENTER:

		// ���߂��ĕ`��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_transpVal);
		DrawGraph(0, 0, m_guidanceGraphHandle, TRUE);		//	PUSH ENTER
		// ���߂����ɖ߂�
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		break;

	case TITLE_TRANS_STATE::SECOND_CHOICE:

		//--------------------------------------------------//
		// ��Փx�I���J�[�\��
		//-------------------------------------------------//
		// ���߂��ĕ`��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_transpVal);
		// �J�[�\����DrawBox�ŕ`��
		DrawBox(SCREEN_SIZE_W / 2 - GetFontSize() * 4 * 3,
			SCREEN_SIZE_H / 2 + m_cursolNum * 80 - 8,
			SCREEN_SIZE_W / 2 + GetFontSize() * 4 * 3,
			SCREEN_SIZE_H / 2 + m_cursolNum * 80 + 72,
			GetColor(255, 155, 50), TRUE);
		// ���߂����ɖ߂�
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// ��Փx�\��
		for (int i = 0; i < ALL_DIFFICULT; i++)
		{
			if (i == 0)
			{
				DrawExtendFormatString(SCREEN_SIZE_W / 2 - GetFontSize() * 4 * 2, SCREEN_SIZE_H / 2 + (i * 80), 4.0, 4.0, GetColor(255, 255, 255), "�C�[�W�[");
			}

			if (i == 1)
			{
				DrawExtendFormatString(SCREEN_SIZE_W / 2 - GetFontSize() * 4 * 2, SCREEN_SIZE_H / 2 + (i * 80), 4.0, 4.0, GetColor(255, 255, 255), "�m�[�}��");
			}

			if (i == 2)
			{
				DrawExtendFormatString(SCREEN_SIZE_W / 2 - GetFontSize() * 4 * 1.5, SCREEN_SIZE_H / 2 + (i * 80), 4.0, 4.0, GetColor(255, 255, 255), "�n�[�h");
			}
		}

		// �t�F�[�h�A�E�g����
		if (m_fadeOutFlag)
		{
			for (int i = 0; i < 255; i += FADE_OUT_SPEED)
			{
				// �`��P�x���Z�b�g
				SetDrawBright(255 - i, 255 - i, 255 - i);

				// �O���t�B�b�N��`��
				DrawGraph(0, 0, m_backGraphHandle, FALSE);
				ScreenFlip();
			}
			m_fadeOutFinishFlag = true;
			
		}
		break;

	default:

		break;
	}

}

/// <summary>
/// �T�E���h�̍Đ�����
/// </summary>
void TestTitleSceneUeyama::Sound()
{
	PlaySoundMem(m_soundHandle, DX_PLAYTYPE_BACK, FALSE);
	ChangeVolumeSoundMem(m_volumePal, m_soundHandle);
}

/// <summary>
/// �ǂݍ��ݏ���
/// </summary>
void TestTitleSceneUeyama::Load()
{
	m_backGraphHandle = LoadGraph("data/img/Title_back.png");			//	�O���t�B�b�N�n���h���Ƀ^�C�g����ʂ̃C���[�W���Z�b�g
	m_logoGraphHandle = LoadGraph("data/img/Title_logo.png");			//	�O���t�B�b�N�n���h���Ƀ^�C�g����ʂ̃C���[�W���Z�b�g
	m_guidanceGraphHandle = LoadGraph("data/img/Title_guidance.png");	//	�O���t�B�b�N�n���h���Ƀ^�C�g����ʂ̃C���[�W���Z�b�g
	m_soundHandle = LoadSoundMem("data/sound/titleBgm.ogg");
	m_click_sound_handle = LoadSoundMem("data/sound/EnterToSound.wav");	//	ENTER�Ői�ލۂ̃T�E���h�����[�h
}

/// <summary>
/// �_�ŃG�t�F�N�g�ɗp���铧�ߗʂ̍X�V����
/// </summary>
void TestTitleSceneUeyama::UpdateTransparent()
{
	// ���ߗʂ�122���傫���Ȃ�����
	if (m_transpVal >= MAX_TRANSP_VAL)
	{
		// ���ߗʂ�255�ɐݒ�
		m_transpVal = MAX_TRANSP_VAL - 1;
		// �����ߗʂ�-1�ɂ���
		m_permeationAmount *= TRANSP_MODERATION;
	}
	// ���ߗʂ�0��菬�������
	else if (MAX_TRANSP_VAL / 2 >= m_transpVal)
	{
		// ���ߗʂ�ݒ�
		m_transpVal = MAX_TRANSP_VAL / 2 + 1;
		// �����ߗʂ�1�ɂ���
		m_permeationAmount *= TRANSP_MODERATION;
	}
	// �����ߗʂ𓧉ߗʂɉ��Z����
	m_transpVal += m_permeationAmount;
}
