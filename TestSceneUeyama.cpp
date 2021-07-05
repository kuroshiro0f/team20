#include "TestSceneUeyama.h"
#include "Result.h"
#include "Mark.h"
#include "Target.h"
#include "Player.h"
#include "ObstructManager.h"
#include "Hitchecker.h"
#include "Camera.h"

#include "DxLib.h"

TestSceneUeyama::TestSceneUeyama()
	:m_player(nullptr)
	, m_camera(nullptr)
	, m_mark(nullptr)
	, m_obstructManager(nullptr)
{
	m_backGraphHandle = LoadGraph("data/img/gameBack.png");			//	�O���t�B�b�N�n���h���Ƀ^�C�g����ʂ̃C���[�W���Z�b�g
	for (int i = 0; i < 10; i++)
	{
		m_target[i] = nullptr;
	}
	StartTime = GetNowCount();
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		m_checkKeyFlag = TRUE;
	}
}

TestSceneUeyama::~TestSceneUeyama()
{
	delete m_player;	//	�v���C���[�̃|�C���^�����o�ϐ�������
	delete m_camera;	//	�J�����̃|�C���^�����o�ϐ�������
	delete m_mark;		//	�}�[�N�̃|�C���^�����o�ϐ�������
	for (int i = 0; i < 10; i++)
	{
		delete m_target[i];
	}
	//m_obstructManager->DestroyObstructs();
	/*delete m_obstructManager;*/
}

SceneBase* TestSceneUeyama::Update()
{
	m_mark->Mark_Update();
	m_target[TargetCount]->Update();
	m_player->Update();
	/*m_obstructManager->Update();*/
	m_camera->Update(*m_player);
	/*HitChecker::Check(*m_player, *m_obstructManager);*/
	if (!CheckHitKey(KEY_INPUT_RETURN))
	{
		m_checkKeyFlag = FALSE;
	}
	if (CheckHitKey(KEY_INPUT_RETURN) && m_checkKeyFlag == FALSE)	//	�G���^�[�������ꂽ��
	{
		WaitTimer(300);
		return new Result;				//	���U���g�V�[���ɐ؂�ւ���
	}
	return this;						//	�Q�[���V�[����\����������
}

void TestSceneUeyama::Draw()
{
	DrawGraph(0, 0, m_backGraphHandle, TRUE);							//	�^�C�g����ʂ̔w�i��\��
	m_mark->Mark_Draw();
	m_target[TargetCount]->Draw();
	m_player->Draw();
	/*m_obstructManager->Draw();*/
	DrawString(0, 0, "�Q�[����ʂł�", GetColor(255, 255, 255));
}


void TestSceneUeyama::Load()
{
	m_player = new Player;			//	�v���C���[�N���X�̃C���X�^���X�𐶐�
	m_camera = new Camera;			//	�J�����N���X�̃C���X�^���X�𐶐�
	m_mark = new Mark;				//	�}�[�N�N���X�̃C���X�^���X�𐶐�
	for (int i = 0; i < 10; i++)
	{
		m_target[i] = new Target;
	}
	/*m_obstructManager = new ObstructManager;
	m_obstructManager->CreateObstructs();*/
}
