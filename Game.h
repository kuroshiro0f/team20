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
	void Load()override;			//	������

private:
	class Player* m_player;			//	�v���C���[�N���X�ւ̃|�C���^�����o�ϐ�
	class Target* m_target[10];			//
	class Camera* m_camera;			//	�J�����N���X�ւ̃|�C���^�����o�ϐ�
	class Mark* m_mark;				//	�}�[�N�N���X�ւ̃|�C���^�����o�ϐ�
	class ObstructManager* m_obstructManager;	//
	int TargetCount = 0;
	int StartTime = 0;
};

#endif // _GAME_H_
