//#pragma once
//
//#include "SceneBase.h"
//
//class TestSceneUeyama : public SceneBase
//{
//public:
//	TestSceneUeyama();
//	~TestSceneUeyama();
//
//	SceneBase* Update()override;	//	�X�V
//	void Draw()override;			//	�`��
//	void Sound()override;			//	���y
//	void Load()override;			//	������
//
//private:
//	class Player* m_player;			//	�v���C���[�N���X�ւ̃|�C���^�����o�ϐ�
//	class Target* m_target[10];		//
//	class Camera* m_camera;			//	�J�����N���X�ւ̃|�C���^�����o�ϐ�
//	class Mark* m_mark;				//	�}�[�N�N���X�ւ̃|�C���^�����o�ϐ�
//	class ObstructManager* m_obstructManager;	//
//	int TargetCount = 0;
//	int StartTime = 0;
//	int m_backGraphHandle;			//	�w�i�̃O���t�B�b�N�n���h��
//	int m_finishGraphHandle;		//	�Q�[���I�������̃O���t�B�b�N�n���h��
//	int m_soundHandle;				//	�Q�[����ʁE�T�E���h�n���h��
//	int m_finishSoundHandle;		//	�Q�[����ʁE�I���̌��ʉ��p�T�E���h�n���h��
//	bool m_checkKeyFlag;			//	�L�[�������ꂽ�܂܂��𔻒肷��t���O
//	bool m_finishFlag;				//	�Q�[���I������t���O
//};