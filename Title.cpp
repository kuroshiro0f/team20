#include "Title.h"
#include "Game.h"
#include "TestSceneUeyama.h"

#include "DxLib.h"

const int LOGO_X = 0;			//	���S��X���W
const int LOGO_Y = 0;			//	���S��Y���W
const int GUIDANCE_X = 0;		//	�K�C�h��X���W
const int GUIDANCE_Y = 0;		//	�K�C�h��Y���W

Title::Title()
{
	m_backGraphHandle = LoadGraph("data/img/Title_back.png");			//	�O���t�B�b�N�n���h���Ƀ^�C�g����ʂ̃C���[�W���Z�b�g
	m_logoGraphHandle = LoadGraph("data/img/Title_logo.png");			//	�O���t�B�b�N�n���h���Ƀ^�C�g����ʂ̃C���[�W���Z�b�g
	m_guidanceGraphHandle = LoadGraph("data/img/Title_guidance.png");	//	�O���t�B�b�N�n���h���Ƀ^�C�g����ʂ̃C���[�W���Z�b�g
	m_soundHandle = LoadSoundMem("data/sound/titleBgm.ogg");			//	�T�E���h�n���h���Ƀ^�C�g����ʂ�BGM���Z�b�g
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		m_checkKeyFlag = TRUE;
	}
}

Title::~Title()
{
	StopSoundMem(m_soundHandle);
	DeleteSoundMem(m_soundHandle);
	DeleteGraph(m_backGraphHandle);
	DeleteGraph(m_logoGraphHandle);
	DeleteGraph(m_guidanceGraphHandle);
}

SceneBase* Title::Update()
{
	if (!CheckHitKey(KEY_INPUT_RETURN))
	{
		m_checkKeyFlag = FALSE;
	}
	/*if (CheckHitKey(KEY_INPUT_RETURN) && m_checkKeyFlag == FALSE)
	{
		return new Game;
	}*/
	if (CheckHitKey(KEY_INPUT_RETURN) && m_checkKeyFlag == FALSE)
	{
		return new TestSceneUeyama;
	}
	return this;
}

void Title::Draw()
{
	DrawGraph(0, 0, m_backGraphHandle, TRUE);							//	�^�C�g����ʂ̔w�i��\��
	DrawGraph(LOGO_X, LOGO_Y, m_logoGraphHandle, TRUE);					//	�^�C�g����ʂ̃��S��\��
	DrawGraph(GUIDANCE_X, GUIDANCE_Y, m_guidanceGraphHandle, TRUE);		//	�^�C�g����ʂ̃K�C�h��\��
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
