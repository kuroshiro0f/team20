#include "Game.h"
#include "Result.h"
#include "Mark.h"
#include "Target.h"
#include "Player.h"
#include "ObstructManager.h"
#include "Hitchecker.h"
#include "Camera.h"

#include "DxLib.h"

Game::Game()
	:m_player(nullptr)
	,m_camera(nullptr)
	,m_mark(nullptr)
	,m_obstructManager(nullptr)
{
	for (int i = 0; i < 10; i++)
	{
		m_target[i] = nullptr;
	}
	StartTime = GetNowCount();
}

Game::~Game()
{
	delete m_player;	//	�v���C���[�̃|�C���^�����o�ϐ�������
	delete m_camera;	//	�J�����̃|�C���^�����o�ϐ�������
	delete m_mark;		//	�}�[�N�̃|�C���^�����o�ϐ�������
	for (int i = 0; i < 10; i++)
	{
		delete m_target[i];
	}
	//m_obstructManager->DestroyObstructs();
	//delete m_obstructManager;
}

SceneBase* Game::Update()
{
	m_mark->Mark_Update();
	m_target[TargetCount]->Update();
	m_player->Update();
	//m_obstructManager->Update();
	m_camera->Update(*m_player);
	//HitChecker::Check(*m_player, *m_obstructManager);
	if (CheckHitKey(KEY_INPUT_RETURN))	//	�G���^�[�������ꂽ��
	{
		return new Result;				//	���U���g�V�[���ɐ؂�ւ���
	}
	return this;						//	�Q�[���V�[����\����������
}

void Game::Draw()
{
	m_mark->Mark_Draw();
	m_target[TargetCount]->Draw();
	m_player->Draw();
	//m_obstructManager->Draw();
}

void Game::Load()
{
	m_player = new Player;			//	�v���C���[�N���X�̃C���X�^���X�𐶐�
	m_camera = new Camera;			//	�J�����N���X�̃C���X�^���X�𐶐�
	m_mark = new Mark;				//	�}�[�N�N���X�̃C���X�^���X�𐶐�
	for (int i = 0; i < 10; i++)
	{
		m_target[i] = new Target;
	}
	//m_obstructManager = new ObstructManager;
	//m_obstructManager->CreateObstructs();
}