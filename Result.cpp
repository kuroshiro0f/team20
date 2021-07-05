#include "Result.h"
#include "Title.h"

const int LOGO_X = 0;
const int LOGO_Y = 0;
const int GUIDANCE_X = 0;
const int GUIDANCE_Y = 0;

Result::Result()
{
	m_logoGraphHandle = LoadGraph("data/img/Result_logo.png");			//	�O���t�B�b�N�n���h���Ƀ��U���g��ʂ̃��S�C���[�W���Z�b�g
	m_guidanceGraphHandle = LoadGraph("data/img/Result_guidance.png");	//	�O���t�B�b�N�n���h���Ƀ��U���g��ʂ̃K�C�h�C���[�W���Z�b�g
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		m_checkKeyFlag = TRUE;
	}
}

Result::~Result()
{
}

SceneBase* Result::Update()
{
	if (!CheckHitKey(KEY_INPUT_RETURN))
	{
		m_checkKeyFlag = FALSE;
	}
	if (CheckHitKey(KEY_INPUT_RETURN) && m_checkKeyFlag == FALSE)
	{
		return new Title;
	}
	return this;
}

void Result::Draw()
{
	DrawGraph(LOGO_X, LOGO_Y, m_logoGraphHandle, TRUE);					//	���U���g��ʂ̃��S��\��
	DrawGraph(GUIDANCE_X, GUIDANCE_Y, m_guidanceGraphHandle, TRUE);		//	���U���g��ʂ̃��S��\��
	/*DrawString(0, 0, "���U���g", GetColor(255, 255, 255));*/
}

void Result::Load()
{
}


