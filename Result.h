#ifndef _RESULT_H_
#define _RESULT_H_

#include "SceneBase.h"
#include "UI.h"

#include "DxLib.h"

class Result : public SceneBase
{
public:
	Result(const int& _score);			//	�R���X�g���N�^
	~Result();			//�@�f�X�g���N�^

	SceneBase* Update(float _deltaTime)override;	//	�X�V
	void Draw()override;			//	�`��
	void Sound()override;			//	���y
	void Load()override;			//	������

private:
	int m_score;						//	�X�R�A�i�[�ϐ�
	int m_evaluation;
	int m_logoGraphHandle;				//	���S�̃O���t�B�b�N�n���h��
	int m_guidanceGraphHandle;			//	�K�C�h�̃O���t�B�b�N�n���h��
	int m_scoreGraphHandle;				//	�X�R�A�̃O���t�B�b�N�n���h��
	int m_numGraphHandle[11];			//
	int m_evaluationGraphHandle[3];		//	�]���̃O���t�B�b�N�n���h��
	// �����ߗ�
	int permeationAmount;
	// ���ߗ�
	int transParent;
	int m_click_sound_handle;			//	ENTER�Ői�ނƂ��̃T�E���h�n���h��
	int m_bgmSoundHandle;				//	BGM�̃T�E���h�n���h��
	int m_scoreSoundHandle;				//	�X�R�A�̃T�E���h�n���h��
	int m_numSoundHandle;				//	���\���̃T�E���h�n���h��
	int m_evaluationSoundHandle[3];		//	�]���̃T�E���h�n���h��
	int m_checkResultFlag = 0;				//	��ʊǗ��p�t���O
	bool m_checkKeyFlag;				//	�L�[�������ꂽ�܂܂��𔻒肷��t���O
	bool m_fadeInFinishFlag;			//	�t�F�[�h�C���̏I������t���O
	bool m_fadeOutFlag;					//	�t�F�[�h�A�E�g�J�n�p�̃t���O
	bool m_fadeOutFinishFlag;			//	�t�F�[�h�A�E�g�̏I������t���O
};

#endif // _RESULT_H_

