//#pragma once
//#include "SceneBase.h"
//
//
//class TestTitleScene : public SceneBase
//{
//public:
//
//	enum class TITLE_TRANS_STATE
//	{
//		FIRST_ENTER = 0,
//		SECOND_CHOICE
//	};
//
//	TestTitleScene();
//	~TestTitleScene();
//
//	SceneBase* Update() override;
//	void Draw() override;
//	void Sound() override;
//	void Load() override;
//
//	void UpdateTransparent();
//
//private:
//
//	TITLE_TRANS_STATE m_state;
//
//	unsigned int m_cursolNum;    // ��Փx�I�����̃J�[�\���ԍ�
//
//	int m_backGraphHandle;				//	�^�C�g����ʁE�w�i�̃O���t�B�b�N�n���h��
//	int m_logoGraphHandle;				//	�^�C�g����ʁE���S�̃O���t�B�b�N�n���h��
//	int m_guidanceGraphHandle;			//	�^�C�g����ʁE�K�C�h�̃O���t�B�b�N�n���h��
//	int m_soundHandle;					//	�^�C�g����ʁE�T�E���h�n���h��
//	int m_click_sound_handle;			//  ENTER�Ői�ނƂ��̃T�E���h�n���h��
//										// ���t���[�����ߗ�
//	int m_permeationAmount;
//	// ���ߗ�
//	int m_transpVal;
//
//	bool m_checkKeyFlag;				//	�L�[�������ꂽ�܂܂��𔻒肷��t���O
//};