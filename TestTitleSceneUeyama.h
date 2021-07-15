#pragma once
#include "SceneBase.h"


class TestTitleSceneUeyama : public SceneBase
{
public:

	enum class TITLE_TRANS_STATE
	{
		FIRST_ENTER = 0,
		SECOND_CHOICE
	};

	TestTitleSceneUeyama();					//	�R���X�g���N�^
	~TestTitleSceneUeyama();					//	�f�X�g���N�^

	SceneBase* Update(float _deltaTime) override;
	void Draw() override;
	void Sound() override;
	void Load() override;

	void UpdateTransparent();

	//	�f���^�^�C���̃Z�b�^�[
	void SetDeltaTime(float _deltaTime) { m_deltaTime = _deltaTime; }

	//	�f���^�^�C���̃Q�b�^�[
	float GetDeltaTime() { return m_deltaTime; }

private:
	TITLE_TRANS_STATE m_state;

	unsigned int m_cursolNum;    // ��Փx�I�����̃J�[�\���ԍ�

	int m_backGraphHandle;				//	�^�C�g����ʁE�w�i�̃O���t�B�b�N�n���h��
	int m_logoGraphHandle;				//	�^�C�g����ʁE���S�̃O���t�B�b�N�n���h��
	int m_guidanceGraphHandle;			//	�^�C�g����ʁE�K�C�h�̃O���t�B�b�N�n���h��
	int m_soundHandle;					//	�^�C�g����ʁE�T�E���h�n���h��
	int m_click_sound_handle;			//  ENTER�Ői�ނƂ��̃T�E���h�n���h��
										// ���t���[�����ߗ�
	int m_permeationAmount;
	// ���ߗ�
	int m_transpVal;
	int m_fadeTransVal;				//	�t�F�[�h�A�E�g���̓��ߗ�
	float m_deltaTime;				//	�f���^�^�C��

	bool m_checkKeyFlag;				//	�L�[�������ꂽ�܂܂��𔻒肷��t���O
	bool m_fadeInFinishFlag;		//	�t�F�[�h�C���̏I������t���O
	bool m_fadeOutFlag;				//	�t�F�[�h�A�E�g�J�n�p�̃t���O
	bool m_fadeOutFinishFlag;		//	�t�F�[�h�A�E�g�̏I������t���O
};