#include "Result.h"
#include "TestTitleSceneUeyama.h"

const int LOGO_X = 0;
const int LOGO_Y = 0;
const int GUIDANCE_X = 0;
const int GUIDANCE_Y = 0;
const int RESULT_NUM = 3;
const int NICE_P = 5;
const int PF_P = 10;
const int VOLUME_PAL_SUP = 90;

// �ő哧�ߗ�
const int defaultTrans = 255;
// ���ߗʕω��p�x�N�g��
const int transModeration = -1;

//	�t�F�[�h�C���̑��x
const int FADE_IN_SPEED = 3;
//	�t�F�[�h�A�E�g�̑��x
const int FADE_OUT_SPEED = 3;

Result::Result(const int& _score)
	:m_score(_score)
	, m_fadeInFinishFlag(false)
	, m_fadeOutFlag(false)
	, m_fadeOutFinishFlag(false)
{
	// ���ߗʕϐ���255�ɐݒ�
	transParent = defaultTrans;
	// �����ߗʕϐ����P�ɐݒ�
	permeationAmount = 1;

	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		m_checkKeyFlag = TRUE;
	}
}

Result::~Result()
{
	DeleteGraph(m_logoGraphHandle);
	DeleteGraph(m_scoreGraphHandle);
	for (int i = 0; i < 11; i++)
	{
		DeleteGraph(m_numGraphHandle[i]);
	}
	DeleteGraph(m_evaluationGraphHandle[m_evaluation]);
	DeleteGraph(m_guidanceGraphHandle);
	/*StopSoundMem(m_bgmSoundHandle);
	DeleteSoundMem(m_bgmSoundHandle);*/
	DeleteSoundMem(m_scoreSoundHandle);
	DeleteSoundMem(m_numSoundHandle);
	DeleteSoundMem(m_evaluationSoundHandle[m_evaluation]);
	DeleteSoundMem(m_click_sound_handle);					//	ENTER�Ői�ނƂ��̃T�E���h�����������

}

SceneBase* Result::Update(float _deltaTime)
{
	if (CheckHitKey(KEY_INPUT_UP))
	{
		m_volumePal++;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		m_volumePal--;
	}
	/*m_scoreStr(std::to_string(m_score));*/
	if (m_checkResultFlag <= RESULT_NUM)
	{
		WaitTimer(1000);
		m_checkResultFlag++;
	}
	if (!CheckHitKey(KEY_INPUT_RETURN))
	{
		m_checkKeyFlag = FALSE;
	}

	// ���ߗʂ�255���傫���Ȃ�����
	if (transParent >= defaultTrans)
	{
		// ���ߗʂ�121�ɐݒ�
		transParent = defaultTrans - 1;
		// �����ߗʂ�-1�ɂ���
		permeationAmount *= transModeration;
	}
	// ���ߗʂ�0��菬�������
	else if (0 >= transParent)
	{
		// ���ߗʂ��P�ɐݒ�
		transParent = 1;
		// �����ߗʂ�1�ɂ���
		permeationAmount *= transModeration;
	}
	// �����ߗʂ𓧉ߗʂɉ��Z����
	transParent += (permeationAmount * 3);

	if (CheckHitKey(KEY_INPUT_RETURN) && m_checkKeyFlag == FALSE)
	{
		ChangeVolumeSoundMem(m_volumePal + VOLUME_PAL_SUP, m_click_sound_handle);
		PlaySoundMem(m_click_sound_handle, DX_PLAYTYPE_NORMAL);		//	�����Đ����I���܂őҋ@
		return new TestTitleSceneUeyama;
	}
	return this;
}

void Result::Draw()
{
	if (!m_fadeInFinishFlag)
	{
		// �t�F�[�h�C������
		for (int i = 0; i < 255; i += FADE_IN_SPEED)
		{
			// �`��P�x���Z�b�g
			SetDrawBright(i, i, i);
			DrawGraph(0, 0, m_logoGraphHandle, TRUE);
			ScreenFlip();
		}
		m_fadeInFinishFlag = true;
	}
	DrawGraph(LOGO_X, LOGO_Y, m_logoGraphHandle, TRUE);					//	���U���g��ʂ̃��S��\��

	// ���߂��ĕ`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, transParent);
	DrawGraph(GUIDANCE_X, GUIDANCE_Y, m_guidanceGraphHandle, TRUE);		//	���U���g��ʂ̃��S��\��
	// ���߂����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (m_checkResultFlag >= 1)
	{
		DrawGraph(0, 0, m_scoreGraphHandle, TRUE);						//	���U���g��ʂ̃��S��\��
	}
	if (m_checkResultFlag >= 2)
	{
		if (m_score != 0)
		{
			for (int i = m_score - 1; i >= 0; --i)
			{
				DrawGraph(0, 0, m_numGraphHandle[i], TRUE);				//	���U���g��ʂ̃��S��\��
			}
		}
	}
	if (m_checkResultFlag >= 3)
	{
		DrawGraph(0, 0, m_evaluationGraphHandle[m_evaluation], TRUE);				//	���U���g��ʂ̃��S��\��
	}
	// �t�F�[�h�A�E�g����
	if (m_fadeOutFlag)
	{
		for (int i = 0; i < 255; i += FADE_OUT_SPEED)
		{
			// �`��P�x���Z�b�g
			SetDrawBright(255 - i, 255 - i, 255 - i);

			// �O���t�B�b�N��`��
			DrawGraph(0, 0, m_logoGraphHandle, FALSE);
			ScreenFlip();
		}
		m_fadeOutFinishFlag = true;
	}
}

void Result::Sound()
{
	switch (m_checkResultFlag)
	{
	case 1:
		PlaySoundMem(m_scoreSoundHandle, DX_PLAYTYPE_BACK, TRUE);
		ChangeVolumeSoundMem(m_volumePal + VOLUME_PAL_SUP, m_scoreSoundHandle);
		break;
	case 2:
		PlaySoundMem(m_numSoundHandle, DX_PLAYTYPE_BACK, TRUE);
		ChangeVolumeSoundMem(m_volumePal + VOLUME_PAL_SUP, m_numSoundHandle);
		break;
	case 3:
		PlaySoundMem(m_evaluationSoundHandle[m_evaluation], DX_PLAYTYPE_BACK, TRUE);
		ChangeVolumeSoundMem(m_volumePal + VOLUME_PAL_SUP, m_evaluationSoundHandle[m_evaluation]);
		break;
	}
	/*PlaySoundMem(m_bgmSoundHandle, DX_PLAYTYPE_LOOP, TRUE);
	ChangeVolumeSoundMem(m_volumePal, m_bgmSoundHandle);*/
}

void Result::Load()
{
	m_click_sound_handle = LoadSoundMem("data/sound/EnterToSound.wav");	//	ENTER�Ői�ލۂ̃T�E���h�����[�h

	if (m_score < NICE_P)
	{
		m_evaluation = 0;
		m_evaluationGraphHandle[m_evaluation] = LoadGraph("data/img/result_02_png/Result _01_neverGiveLogo.png");		//	�O���t�B�b�N�n���h���Ƀ��U���g��ʂ̃C���[�W���Z�b�g
		m_evaluationSoundHandle[m_evaluation] = LoadSoundMem("data/sound/NGU.mp3");			//	�T�E���h�n���h���Ƀ��U���g��ʂ̌��ʉ����Z�b�g
	}
	if (m_score >= NICE_P && m_score < PF_P)
	{
		m_evaluation = 1;
		m_evaluationGraphHandle[m_evaluation] = LoadGraph("data/img/result_02_png/Result _01_niceLogo.png");				//	�O���t�B�b�N�n���h���Ƀ��U���g��ʂ̃C���[�W���Z�b�g
		m_evaluationSoundHandle[m_evaluation] = LoadSoundMem("data/sound/NICE.mp3");		//	�T�E���h�n���h���Ƀ��U���g��ʂ̌��ʉ����Z�b�g
	}
	if (m_score == PF_P)
	{
		m_evaluation = 2;
		m_evaluationGraphHandle[m_evaluation] = LoadGraph("data/img/result_02_png/Result _01_perfectLogo.png");			//	�O���t�B�b�N�n���h���Ƀ��U���g��ʂ̃C���[�W���Z�b�g
		m_evaluationSoundHandle[m_evaluation] = LoadSoundMem("data/sound/PF.mp3");			//	�T�E���h�n���h���Ƀ��U���g��ʂ̌��ʉ����Z�b�g
	}
	/*m_scoreStr(std::to_string(m_score));*/
	m_logoGraphHandle = LoadGraph("data/img/result_02_png/Result _01_backGround.png");				//	�O���t�B�b�N�n���h���Ƀ��U���g��ʂ̃C���[�W���Z�b�g
	// m_scoreGraphHandle = LoadGraph("data/img/Result_score.png");			//	�O���t�B�b�N�n���h���Ƀ��U���g��ʂ̃C���[�W���Z�b�g
	m_guidanceGraphHandle = LoadGraph("data/img/result_02_png/Result_01_EnterLogo.png");		//	�O���t�B�b�N�n���h���Ƀ��U���g��ʂ̃C���[�W���Z�b�g
	m_numGraphHandle[0] = LoadGraph("data/img/result_02_png/Result.png");
	m_numGraphHandle[1] = LoadGraph("data/img/result_02_png/Result_01_ice02.png");
	m_numGraphHandle[2] = LoadGraph("data/img/result_02_png/Result_01_ice03.png");
	m_numGraphHandle[3] = LoadGraph("data/img/result_02_png/Result_01_ice04.png");
	m_numGraphHandle[4] = LoadGraph("data/img/result_02_png/Result_01_ice05.png");
	m_numGraphHandle[5] = LoadGraph("data/img/result_02_png/Result_01_ice06.png");
	m_numGraphHandle[6] = LoadGraph("data/img/result_02_png/Result_01_ice07.png");
	m_numGraphHandle[7] = LoadGraph("data/img/result_02_png/Result_01_ice08.png");
	m_numGraphHandle[8] = LoadGraph("data/img/result_02_png/Result_01_ice09.png");
	m_numGraphHandle[9] = LoadGraph("data/img/result_02_png/Result_01_ice10.png");
	m_numGraphHandle[10] = LoadGraph("data/img/result_02_png/Result_01_ice11.png");
	//m_bgmSoundHandle = LoadSoundMem("");									//	�T�E���h�n���h���Ƀ��U���g��ʂ�BGM���Z�b�g
	m_scoreSoundHandle = LoadSoundMem("data/sound/score.mp3");				//	�T�E���h�n���h���Ƀ��U���g��ʂ̌��ʉ����Z�b�g
	m_numSoundHandle = LoadSoundMem("data/sound/num.mp3");					//	�T�E���h�n���h���Ƀ��U���g��ʂ̌��ʉ����Z�b�g
}