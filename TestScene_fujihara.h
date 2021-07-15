#pragma once

#include "SceneBase.h"
#include "DxLib.h"

class TestScene_fujihara :public SceneBase
{
public:

	enum class GAME_SCENE_STATE
	{
		COUNTDOWN,
		GAME
	};

	TestScene_fujihara();				//	�R���X�g���N�^
	~TestScene_fujihara();			//	�f�X�g���N�^

	SceneBase* Update()override;	//	�X�V
	void Draw()override;			//	�`��
	void Sound()override;			//	���y
	void Load()override;			//	������
	void DebugKey();

	int GetTargetCount() { return m_targetCount; }

private:
	class Player* m_player;			//	�v���C���[�N���X�ւ̃|�C���^�����o�ϐ�
	class Target* m_target[11];			//
	class Camera* m_camera;			//	�J�����N���X�ւ̃|�C���^�����o�ϐ�
	class Mark* m_mark;				//	�}�[�N�N���X�ւ̃|�C���^�����o�ϐ�
	class UI* m_score_ui[10];		//  UI�N���X�ւ̃|�C���^�����o�ϐ�
	class UI* m_hit_ui[10];			//	�q�b�g����UI�N���X�ւ̃|�C���^�����o�ϐ�
	class PlayEffect* m_effect;     //  �G�t�F�N�g�v���[���[
	GAME_SCENE_STATE m_state;
	int m_targetCount;				//	�A�C�X�̔�΂�����
	int m_startTime;				//	�Q�[���̊J�n����
	int m_girl_Y;					//	���̎q�̉摜��y���W
	int m_lady_Y;					//
	int m_backGraphHandle;			//	�w�i�̃O���t�B�b�N�n���h��
	int m_finishGraphHandle;		//	�Q�[���I�������̃O���t�B�b�N�n���h��
	int m_soundHandle;				//	�Q�[����ʁE�T�E���h�n���h��
	int m_finishSoundHandle;		//	�Q�[����ʁE�I���̌��ʉ��p�T�E���h�n���h��
	int m_iceSoundHandle;			//	�A�C�X�̔��ˉ��p�T�E���h�n���h��
	int m_hitSoundHandle;			//	�A�C�X�ƎM�̏Փˉ��p�T�E���h�n���h��
	int m_missSoundHandle;			//	�A�C�X�ƎM���Փˎ��s�������̌����p�T�E���h�n���h��
	int m_manualGraphHandle;		//	��������̃O���t�B�b�N�n���h��
	int m_girlGraphHandle;			//  ���̎q�̉摜�n���h��
	int m_girl_missReaction_GraphHandle;	//  �~�X�������̏��̎q�ɒǉ�����摜�n���h��
	int m_girl_hitReaction_GraphHandle;		//  �����������̏��̎q�ɒǉ�����摜�n���h��
	int m_ladyGraphHandle;
	bool m_checkKeyFlag;			//	�L�[�������ꂽ�܂܂��𔻒肷��t���O
	bool m_finishFlag;				//	�Q�[���I������t���O
	bool m_iceThrowFlag;			//	�A�C�X�ˏo�t���O
	bool m_iceHitFlagBuffer;
	bool m_girlUpFlag;				//  ���̎q�̉摜���㏸�����邩�ǂ���

	bool m_girl_hitReactionFlag;	//  ���̎q��hit�������̃��A�N�V���������邩�ǂ���
	bool m_girl_missReactionFlag;	//  ���̎q��miss�������̃A�N�V���������邩�ǂ���
	bool m_girl_ReactionFlag;		//  ���̎q�Ƀ��A�N�V���������邩�ǂ���

	//// �m�F�p�ϐ�
	int m_hitCount;
	bool m_hitFlag;
};