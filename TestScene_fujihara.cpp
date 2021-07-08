#include "TestScene_fujihara.h"
#include "Result.h"
#include "Mark.h"
#include "Target.h"
#include "Player.h"
#include "ObstructManager.h"
#include "Hitchecker.h"
#include "UI.h"
#include "Camera.h"

#include "DxLib.h"

//// �m�F�p�ϐ�
int hitCount = NULL;
bool hitFrag = false;

static int enemyNum = 10;

TestScene_fujihara::TestScene_fujihara()
	:m_player(nullptr)
	, m_camera(nullptr)
	, m_mark(nullptr)
	, m_target(nullptr)
	, m_obstructManager(nullptr)
{
	for (int i = 0; i < enemyNum; ++i)
	{
		m_score_ui[i] = nullptr;
		m_hit_ui[i] = nullptr;
	}
}

TestScene_fujihara::~TestScene_fujihara()
{
	delete m_player;	//	�v���C���[�̃|�C���^�����o�ϐ�������
	delete m_camera;	//	�J�����̃|�C���^�����o�ϐ�������
	delete m_mark;		//	�}�[�N�̃|�C���^�����o�ϐ�������
	delete m_target;
	m_obstructManager->DestroyObstructs();
	delete m_obstructManager;
	for (int i = 0; i < enemyNum; ++i)
	{
		delete m_score_ui[i];		//  �X�R�AUI�ւ̃|�C���^�����o�ϐ�
		delete m_hit_ui[i];			//	�q�b�g����UI�ւ̃|�C���^�����o�ϐ�
	}
}

SceneBase* TestScene_fujihara::Update()
{
	// �m�F�p
	if (CheckHitKey(KEY_INPUT_A))
	{
		if (hitCount < enemyNum)
		{
			hitFrag = true;
			m_hit_ui[hitCount]->ScoreUpdate(m_hit_ui[hitCount], hitFrag);
			hitCount++;
		}
	}
	if (CheckHitKey(KEY_INPUT_B))
	{
		if (hitCount < enemyNum)
		{
			hitFrag = false;
			m_hit_ui[hitCount]->ScoreUpdate(m_hit_ui[hitCount], hitFrag);
			hitCount++;
		}
	}


	m_mark->Mark_Update();
	m_target->Update();
	m_player->Update();
	m_obstructManager->Update();
	m_camera->Update(*m_player);
	HitChecker::Check(*m_player, *m_obstructManager);
	if (CheckHitKey(KEY_INPUT_RETURN))	//	�G���^�[�������ꂽ��
	{
		WaitTimer(300);
		return new Result;				//	���U���g�V�[���ɐ؂�ւ���
	}
	return this;						//	�Q�[���V�[����\����������
}

void TestScene_fujihara::Draw()
{
	m_mark->Mark_Draw();
	m_target->Draw();
	m_player->Draw();
	//m_obstructManager->Draw();
	for (int i = 0; i < enemyNum; ++i)
	{
		m_score_ui[i]->Draw();
	}
	for (int i = 0; i < hitCount; ++i)
	{
		m_hit_ui[i]->Draw();
	}


	DrawString(0, 0, "�Q�[����ʂł�", GetColor(255, 255, 255));
}

void TestScene_fujihara::Load()
{
	int scoreHandle = LoadGraph("data/model/score_ui/score(1).png");
	m_player = new Player;			//	�v���C���[�N���X�̃C���X�^���X�𐶐�
	m_camera = new Camera;			//	�J�����N���X�̃C���X�^���X�𐶐�
	m_mark = new Mark;				//	�}�[�N�N���X�̃C���X�^���X�𐶐�
	m_target = new Target;			//	�I�N���X�̃C���X�^���X�𐶐�
	// �X�R�A�\���̃N���X���Q�O�C���X�^���X����
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			m_score_ui[j + (i * 5)] = new UI(j, i, scoreHandle);
			m_hit_ui[j + (i * 5)] = new UI(j, i, -1);
		}
	}
	// UI�N���X��private�����o�ϐ��ɉ摜�n���h�������[�h
	m_score_ui[0]->Load();
	m_obstructManager = new ObstructManager;	//	
	m_obstructManager->CreateObstructs();
}