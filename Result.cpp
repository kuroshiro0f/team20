#include "Result.h"
#include "Title.h"

const int LOGO_X = 0;
const int LOGO_Y = 0;
const int GUIDANCE_X = 0;
const int GUIDANCE_Y = 0;
const int RESULT_NUM = 3;
const int NICE_P = 5;
const int PF_P = 10;

// �ő哧�ߗ�
const int defaultTrans = 255;
// ���ߗʕω��p�x�N�g��
const int transModeration = -1;

Result::Result(const int &_score)
	:m_score(_score)
{
	m_click_sound_handle = LoadSoundMem("data/sound/EnterToSound.wav");	//	ENTER�Ői�ލۂ̃T�E���h�����[�h

	if (m_score < NICE_P)
	{
		m_evaluation = 0;
		m_evaluationGraphHandle[m_evaluation] = LoadGraph("data/img/NEVERGIVEUP.png");		//	�O���t�B�b�N�n���h���Ƀ��U���g��ʂ̃C���[�W���Z�b�g
		m_evaluationSoundHandle[m_evaluation] = LoadSoundMem("data/sound/NGU.mp3");			//	�T�E���h�n���h���Ƀ��U���g��ʂ̌��ʉ����Z�b�g
	}
	if (m_score >= NICE_P && m_score < PF_P)
	{
		m_evaluation = 1;
		m_evaluationGraphHandle[m_evaluation] = LoadGraph("data/img/NICE.png");				//	�O���t�B�b�N�n���h���Ƀ��U���g��ʂ̃C���[�W���Z�b�g
		m_evaluationSoundHandle[m_evaluation] = LoadSoundMem("data/sound/NICE.mp3");		//	�T�E���h�n���h���Ƀ��U���g��ʂ̌��ʉ����Z�b�g
	}
	if (m_score == PF_P)
	{
		m_evaluation = 2;
		m_evaluationGraphHandle[m_evaluation] = LoadGraph("data/img/PERFECT.png");			//	�O���t�B�b�N�n���h���Ƀ��U���g��ʂ̃C���[�W���Z�b�g
		m_evaluationSoundHandle[m_evaluation] = LoadSoundMem("data/sound/PF.mp3");			//	�T�E���h�n���h���Ƀ��U���g��ʂ̌��ʉ����Z�b�g
	}
	/*m_scoreStr(std::to_string(m_score));*/
	m_logoGraphHandle = LoadGraph("data/img/Result_logo.png");				//	�O���t�B�b�N�n���h���Ƀ��U���g��ʂ̃C���[�W���Z�b�g
	m_scoreGraphHandle = LoadGraph("data/img/Result_score.png");			//	�O���t�B�b�N�n���h���Ƀ��U���g��ʂ̃C���[�W���Z�b�g
	m_guidanceGraphHandle = LoadGraph("data/img/Result_guidance.png");		//	�O���t�B�b�N�n���h���Ƀ��U���g��ʂ̃C���[�W���Z�b�g
	m_numGraphHandle[0] = LoadGraph("data/img/0.png");
	m_numGraphHandle[1] = LoadGraph("data/img/1.png");
	m_numGraphHandle[2] = LoadGraph("data/img/2.png");
	m_numGraphHandle[3] = LoadGraph("data/img/3.png");
	m_numGraphHandle[4] = LoadGraph("data/img/4.png");
	m_numGraphHandle[5] = LoadGraph("data/img/5.png");
	m_numGraphHandle[6] = LoadGraph("data/img/6.png");
	m_numGraphHandle[7] = LoadGraph("data/img/7.png");
	m_numGraphHandle[8] = LoadGraph("data/img/8.png");
	m_numGraphHandle[9] = LoadGraph("data/img/9.png");
	m_numGraphHandle[10] = LoadGraph("data/img/10.png");
	//m_bgmSoundHandle = LoadSoundMem("");									//	�T�E���h�n���h���Ƀ��U���g��ʂ�BGM���Z�b�g
	m_scoreSoundHandle = LoadSoundMem("data/sound/score.mp3");				//	�T�E���h�n���h���Ƀ��U���g��ʂ̌��ʉ����Z�b�g
	m_numSoundHandle = LoadSoundMem("data/sound/num.mp3");					//	�T�E���h�n���h���Ƀ��U���g��ʂ̌��ʉ����Z�b�g

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

SceneBase* Result::Update()
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
		transParent = defaultTrans-1;
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
	transParent += permeationAmount;

	if (CheckHitKey(KEY_INPUT_RETURN) && m_checkKeyFlag == FALSE)
	{
		PlaySoundMem(m_click_sound_handle, DX_PLAYTYPE_NORMAL);		//	�����Đ����I���܂őҋ@
		return new Title;
	}
	return this;
}

void Result::Draw()
{
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
		DrawGraph(0, 0, m_numGraphHandle[m_score], TRUE);				//	���U���g��ʂ̃��S��\��
	}
	if (m_checkResultFlag >= 3)
	{
		DrawGraph(0, 0, m_evaluationGraphHandle[0], TRUE);				//	���U���g��ʂ̃��S��\��
	}
	/*DrawString(0, 0, "���U���g", GetColor(255, 255, 255));*/
}

void Result::Sound()
{
	switch(m_checkResultFlag)
	{
	case 1:
		PlaySoundMem(m_scoreSoundHandle, DX_PLAYTYPE_BACK, TRUE);
		ChangeVolumeSoundMem(m_volumePal, m_scoreSoundHandle);
		break;
	case 2:
		PlaySoundMem(m_numSoundHandle, DX_PLAYTYPE_BACK, TRUE);
		ChangeVolumeSoundMem(m_volumePal, m_numSoundHandle);
		break;
	case 3:
		PlaySoundMem(m_evaluationSoundHandle[m_evaluation], DX_PLAYTYPE_BACK, TRUE);
		ChangeVolumeSoundMem(m_volumePal, m_evaluationSoundHandle[m_evaluation]);
		break;
	}
	/*PlaySoundMem(m_bgmSoundHandle, DX_PLAYTYPE_LOOP, TRUE);
	ChangeVolumeSoundMem(m_volumePal, m_bgmSoundHandle);*/
}

void Result::Load()
{
}


