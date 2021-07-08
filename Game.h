#ifndef _GAME_H_
#define _GAME_H_

#include "SceneBase.h"

#include "DxLib.h"

class Game : public SceneBase
{
public:
	Game();				//	�R���X�g���N�^
	~Game();			//	�f�X�g���N�^

	SceneBase* Update()override;	//	�X�V
	void Draw()override;			//	�`��
	void Sound()override;			//	���y
	void Load()override;			//	������
	void DebugKey();

	int GetTargetCount() { return m_targetCount; }

private:
	class Player* m_player;			//	�v���C���[�N���X�ւ̃|�C���^�����o�ϐ�
	class Target* m_target[10];			//
	class Camera* m_camera;			//	�J�����N���X�ւ̃|�C���^�����o�ϐ�
	class Mark* m_mark;				//	�}�[�N�N���X�ւ̃|�C���^�����o�ϐ�
	class UI* m_score_ui[10];		//  UI�N���X�ւ̃|�C���^�����o�ϐ�
	class UI* m_hit_ui[10];			//	�q�b�g����UI�N���X�ւ̃|�C���^�����o�ϐ�
	int m_targetCount;				//	�A�C�X�̔�΂�����
	int m_startTime;				//	�Q�[���̊J�n����
	int m_backGraphHandle;			//	�w�i�̃O���t�B�b�N�n���h��
	int m_finishGraphHandle;		//	�Q�[���I�������̃O���t�B�b�N�n���h��
	int m_soundHandle;				//	�Q�[����ʁE�T�E���h�n���h��
	int m_finishSoundHandle;		//	�Q�[����ʁE�I���̌��ʉ��p�T�E���h�n���h��
	bool m_checkKeyFlag;			//	�L�[�������ꂽ�܂܂��𔻒肷��t���O
	bool m_finishFlag;				//	�Q�[���I������t���O
	bool m_iceThrowFlag;			//	�A�C�X�ˏo�t���O
};

#endif // _GAME_H_
