#include "SceneMgr.h"
#include "Title.h"
#include "Result.h"
#include "Game.h"
#include "TestSceneUeyama.h"

#include "DxLib.h"

SceneMgr::SceneMgr()
{
	m_scene = nullptr;		//	�����o�ϐ��̏�����
}

SceneMgr::~SceneMgr()
{
	delete m_scene;			//	�����o�ϐ��̏���
}

void SceneMgr::Update()
{
	SceneBase* tmpScene = m_scene->Update();		//	���݂̃V�[����ۑ�(public�̊֐��E�ϐ����Ăяo���Ƃ��̓A���[���Z�q(->)�@�v����)
	if (tmpScene != m_scene)						//	�V�[�����؂�ւ������
	{
		delete m_scene;								//	���O�̃V�[��������
		m_scene = tmpScene;							//	�V�[�����X�V����
		m_scene->Load();							//	�V�[���̏�����
	}
}

void SceneMgr::Draw()
{
	m_scene->Draw();		//	�V�[����`��
}

void SceneMgr::SetScene(SceneBase* _Scene)
{
	if (m_scene != nullptr)	//	m_Scene����ł͂Ȃ��ꍇ
	{
		delete m_scene;		//	m_Scene������
	}
	m_scene = _Scene;		//	�V�[���̍X�V
	m_scene->Load();		//	�V�[���̏�����
}