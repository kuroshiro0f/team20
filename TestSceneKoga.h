//#pragma once
//
//#include"SceneBase.h"
//
//class TestSceneKoga : public SceneBase
//{
//public:
//	TestSceneKoga();		// �R���X�g���N�^
//	~TestSceneKoga();		// �f�X�g���N�^
//	
//	SceneBase* Update()override;	//	�X�V
//	void Draw()override;			//	�`��
//	void Sound()override;
//	void Load()override;			//	������
//
//	int GetTargetCount() { return m_targetCount; }
//
//private:
//	class Player* m_player;			//	�v���C���[�N���X�ւ̃|�C���^�����o�ϐ�
//	class Target* m_target[10];		//	�^�[�Q�b�g�N���X�ւ̃|�C���^�����o�ϐ�
//	class Camera* m_camera;			//	�J�����N���X�ւ̃|�C���^�����o�ϐ�
//	class Mark* m_mark;				//	�}�[�N�N���X�ւ̃|�C���^�����o�ϐ�
//	class ObstructManager* m_obstructManager;	//
//	int m_targetCount;				//	�A�C�X�̔�΂�����
//	int m_startTime;				//	�Q�[���̊J�n����
//	bool m_iceThrowFlag;			//	�A�C�X�ˏo�t���O
//};