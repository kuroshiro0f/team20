#include "TestSceneKoga.h"
#include "Result.h"
#include "Mark.h"
#include "Target.h"
#include "Player.h"
#include "ObstructManager.h"
#include "Hitchecker.h"
#include "Camera.h"

#include "DxLib.h"

TestSceneKoga::TestSceneKoga()
	:m_player(nullptr)
	, m_camera(nullptr)
	, m_mark(nullptr)
	, m_obstructManager(nullptr)
	, m_targetCount(0)
	, m_startTime(0)
	, m_iceThrowFlag(false)
{
	for (int i = 0; i < 10; i++)
	{
		m_target[i] = nullptr;
	}
	m_startTime = GetNowCount() / 1000;
}
TestSceneKoga::~TestSceneKoga()
{
	delete m_player;	//	�v���C���[�̃|�C���^�����o�ϐ�������
	delete m_camera;	//	�J�����̃|�C���^�����o�ϐ�������
	delete m_mark;		//	�}�[�N�̃|�C���^�����o�ϐ�������
	for (int i = 0; i < 10; i++)
	{
		delete m_target[i];	//	�^�[�Q�b�g�̃|�C���^�����o�ϐ�������
	}
	//m_obstructManager->DestroyObstructs();
	//delete m_obstructManager;
}

SceneBase* TestSceneKoga::Update()
{
	m_mark->Mark_Update();
	if (GetNowCount()/1000 - m_startTime > 1 )
	{
		m_startTime = GetNowCount() / 1000;
		m_target[m_targetCount]->SetIsShot(true);
		m_targetCount++;
	}
	
	if (m_iceThrowFlag)
	{
		DrawString(1800, 980, "����", GetColor(255, 255, 255));
	}
	else
	{
		DrawString(1800, 980, "������", GetColor(255, 255, 255));
	}

	for (int i = 0; i < m_targetCount; i++)
	{
		m_target[i]->Update();
	}
	
	
	m_player->Update();
	//m_obstructManager->Update();
	m_camera->Update(*m_player);
	for (int i = 0; i < m_targetCount; i++)
	{
		HitChecker::Check(*m_player, *m_target[i]);
	}
	if (m_targetCount > 10)	//	�A�C�X��10��΂��I�������
	{
		WaitTimer(300);
		return new Result;				//	���U���g�V�[���ɐ؂�ւ���
	}
	return this;						//	�Q�[���V�[����\����������
}
void TestSceneKoga::Draw()
{
	m_mark->Mark_Draw();
	for (int i = 0; i < m_targetCount; i++)
	{
		m_target[i]->Draw();
	}
	m_player->Draw();
	//m_obstructManager->Draw();
	DrawString(0, 0, "�Q�[����ʂł�", GetColor(255, 255, 255));

}
void TestSceneKoga::Load()
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
