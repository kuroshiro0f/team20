#include "SceneMgr.h"
#include "Title.h"
#include "Result.h"
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

void SceneMgr::Update(float _deltaTime)
{
	SceneBase* tmpScene = m_scene->Update(_deltaTime);		//	���݂̃V�[����ۑ�(public�̊֐��E�ϐ����Ăяo���Ƃ��̓A���[���Z�q(->)�@�v����)
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

void SceneMgr::Sound()
{
	m_scene->Sound();		//	BGM�𗬂�
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
