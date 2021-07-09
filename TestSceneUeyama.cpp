#include "TestSceneUeyama.h"
#include "Result.h"
#include "Mark.h"
#include "Target.h"
#include "Player.h"
#include "ObstructManager.h"
#include "Hitchecker.h"
#include "UI.h"
#include "Camera.h"

#include "DxLib.h"
#include "Effect.h"
#include "TestScene_fujihara.h"

static int enemyNum = 10;	//	�G�l�~�[�̐�
static int GIRL_Y = 0;
static int LADY_Y = 0;
static int GIRL_MIN_Y = -75;
static int LADY_MIN_Y = -75;

TestSceneUeyama::TestSceneUeyama()
	:m_player(nullptr)
	, m_camera(nullptr)
	, m_mark(nullptr)
	, m_targetCount(0)
	, m_startTime(0)
	, m_iceThrowFlag(false)
	, m_girl_Y(GIRL_Y)
	, m_lady_Y(LADY_Y)
	, m_girlUpFlag(true)
	, m_ladyUpFlag(true)
	//�@�m�F�p
	, m_hitCount(0)
	, m_hitFlag(false)
{
	// ���̃V�[���ֈڍs���邩�ǂ���
	m_finishFlag = FALSE;
	// �G�l�~�[�E�X�R�AUI������
	for (int i = 0; i < enemyNum; i++)
	{
		m_target[i] = nullptr;
		m_score_ui[i] = nullptr;
		m_hit_ui[i] = nullptr;
	}
	m_target[enemyNum] = nullptr;

	// �J�n���̃^�C�����擾
	m_startTime = GetNowCount() / 1000;
}

TestSceneUeyama::~TestSceneUeyama()
{
	//	�������
	delete m_player;	
	delete m_camera;	
	delete m_mark;		
	StopSoundMem(m_finishSoundHandle);		
	DeleteGraph(m_backGraphHandle);			
	DeleteGraph(m_finishGraphHandle);
	DeleteSoundMem(m_soundHandle);
	DeleteSoundMem(m_finishSoundHandle);
	for (int i = 0; i < enemyNum; i++)
	{
		delete m_target[i];
		delete m_score_ui[i];		
		delete m_hit_ui[i];			
	}
	delete m_target[enemyNum];
}

SceneBase* TestSceneUeyama::Update()
{

	// �f�o�b�O�r���h�̂݃f�o�b�O�֐����Ăяo��
#ifdef _DEBUG
	DebugKey();
#endif

	// ���̍X�V
	m_mark->Mark_Update();

	if (m_targetCount == 0)
	{
		m_target[m_targetCount]->SetSetTime(m_startTime);
	}


	// �G�l�~�[�ˏo�Ǘ�
	if (GetNowCount() / 1000 - m_startTime > 5)
	{
		m_startTime = GetNowCount() / 1000;
		if (m_target[m_targetCount]->GetIceState() == NO_SHOT)
		{
			m_target[m_targetCount]->SetIceState(NOW_SHOT);
		}
		if (m_target[m_targetCount]->GetIceState() == END_SHOT)
		{
			m_target[m_targetCount + 1]->SetSetTime(m_startTime);
			m_targetCount++;
		}
	}

	// ���݂̔ԍ��ɉ����ăG�l�~�[�̍X�V
	//for (int i = 0; i < m_targetCount; i++)
	//{
	m_target[m_targetCount]->Update();
	m_target[m_targetCount]->SetTargetCount(m_targetCount);
	m_target[m_targetCount]->Reaction(HitChecker::Check(*m_player, *m_target[m_targetCount]));

	//}
	m_player->Update();

	m_camera->Update(*m_player);

	// �����蔻��ɂ��X�R�A�̍X�V����
	//if (HitChecker::Check(*m_player, *m_target[m_targetCount - 1]))
	//{
	//	m_hit_ui[m_targetCount - 1]->ScoreUpdate(m_hit_ui[m_targetCount - 1], true);
	//}
	//if (m_target[enemyNum - 1]->GetIceState() == Target_State::END_SHOT)
	//{
	//	m_hit_ui[m_targetCount - 1]->ScoreUpdate(m_hit_ui[m_targetCount - 1], false);
	//}

	if (m_girlUpFlag)
	{
		m_girl_Y--;
		if (m_girl_Y < GIRL_MIN_Y)
		{
			m_girl_Y = GIRL_MIN_Y;
			m_girlUpFlag = false;
		}
	}
	else if(!m_girlUpFlag)
	{
		m_girl_Y++;
		if (m_girl_Y > 0)
		{
			m_girl_Y = 0;
			m_girlUpFlag = true;
		}
	}



	if (m_targetCount == enemyNum)	//	�G���^�[�������ꂽ��
	{
		m_finishFlag = TRUE;
	}
	if (m_finishFlag == TRUE)
	{
		//	���U���g�V�[���Ɉڍs
		return new Result(m_score_ui[m_targetCount]->GetScore());
	}
	//	�Q�[���V�[����\����������
	return this;
}

void TestSceneUeyama::Draw()
{
	DrawGraph(0, 0, m_backGraphHandle, TRUE);							//	�Q�[����ʂ̔w�i��\��
	DrawGraph(0, 0, m_manualGraphHandle, TRUE);							//	���������\��
	DrawGraph(0, m_girl_Y, m_girlGraphHandle, TRUE);					
	DrawGraph(0,m_lady_Y, m_ladyGraphHandle,TRUE);
	m_mark->Mark_Draw();
	for (int i = 0; i <= m_targetCount; i++)
	{
		m_target[i]->Draw();
	}
	m_player->Draw();
	if (m_target[enemyNum - 1]->GetIceState() == Target_State::END_SHOT)
	{
		DrawGraph(0, 0, m_finishGraphHandle, TRUE);							//	�Ō�̃G�l�~�[���ˏo����I�������"�Q�[���I��"�̕\��
	}
	for (int i = 0; i < enemyNum; ++i)
	{
		m_score_ui[i]->Draw();
	}
	for (int i = 0; i < enemyNum; ++i)
	{
		m_hit_ui[i]->Draw();
	}
	/*m_obstructManager->Draw();*/
	/*DrawString(0, 0, "�Q�[����ʂł�", GetColor(255, 255, 255));*/
}

void TestSceneUeyama::Sound()
{
	//	10�ڂ̃A�C�X���ˏo����I�������Q�[���I�����̌��ʉ��𗬂�
	if (m_target[enemyNum - 1]->GetIceState() == Target_State::END_SHOT)
	{
		StopSoundMem(m_soundHandle);
		PlaySoundMem(m_finishSoundHandle, DX_PLAYTYPE_BACK, FALSE);
		ChangeVolumeSoundMem(m_volumePal, m_finishSoundHandle);
	}
	//	�Q�[���I���܂�BGM�𗬂�
	if (m_finishFlag == FALSE)
	{
		PlaySoundMem(m_soundHandle, DX_PLAYTYPE_BACK, FALSE);
		ChangeVolumeSoundMem(m_volumePal, m_soundHandle);
	}
}

void TestSceneUeyama::Load()
{
	m_finishGraphHandle = LoadGraph("data/img/gameEnd.png");		//	�O���t�B�b�N�n���h���ɃQ�[���I�������̃C���[�W���Z�b�g
	m_backGraphHandle = LoadGraph("data/img/gameBack.png");			//	�O���t�B�b�N�n���h���ɃQ�[����ʂ̃C���[�W���Z�b�g
	m_girlGraphHandle = LoadGraph("data/img/chinaGirl.png");
	m_ladyGraphHandle = LoadGraph("data/img/chinaLady.png");
	m_manualGraphHandle = LoadGraph("data/img/manual.png");			//	�O���t�B�b�N�n���h���ɑ�������̃C���[�W���Z�b�g
	m_soundHandle = LoadSoundMem("data/sound/gameBgm.ogg");			//	�T�E���h�n���h���ɃQ�[����ʂ�BGM���Z�b�g
	m_finishSoundHandle = LoadSoundMem("data/sound/gameEnd.wav");		//	�T�E���h�n���h���ɃQ�[���I�����̌��ʉ����Z�b�g
	int scoreHandle = LoadGraph("data/model/score_ui/score(1).png");
	m_player = new Player;			//	�v���C���[�N���X�̃C���X�^���X�𐶐�
	m_camera = new Camera;			//	�J�����N���X�̃C���X�^���X�𐶐�
	m_mark = new Mark;				//	�}�[�N�N���X�̃C���X�^���X�𐶐�
	for (int i = 0; i < enemyNum; i++)
	{
		m_target[i] = new Target;
	}
	m_target[enemyNum] = new Target();

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

}

void TestSceneUeyama::DebugKey()
{
	// �m�F�p
	if (CheckHitKey(KEY_INPUT_A))
	{
		if (m_hitCount < enemyNum)
		{
			m_hitFlag = true;
			//m_hit_ui[m_hitCount]->ScoreUpdate(m_hit_ui[m_hitCount], m_hitFlag);
			m_hitCount++;
		}
	}
	if (CheckHitKey(KEY_INPUT_B))
	{
		if (m_hitCount < enemyNum)
		{
			m_hitFlag = false;
			//m_hit_ui[m_hitCount]->ScoreUpdate(m_hit_ui[m_hitCount], m_hitFlag);
			m_hitCount++;
		}
	}
	if (m_iceThrowFlag)
	{
		DrawString(1800, 980, "����", GetColor(255, 255, 255));
	}
	else
	{
		DrawString(1800, 980, "������", GetColor(255, 255, 255));
	}
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		m_checkKeyFlag = TRUE;
	}
	if (CheckHitKey(KEY_INPUT_RETURN) && m_checkKeyFlag == FALSE)	//	�G���^�[�������ꂽ��
	{
		m_finishFlag = TRUE;
	}
}
