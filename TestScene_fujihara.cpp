////#include "TestScene_fujihara.h"
////#include "Result.h"
////#include "Mark.h"
////#include "Target.h"
////#include "Player.h"
////#include "ObstructManager.h"
////#include "Hitchecker.h"
////#include "UI.h"
////#include "Camera.h"
////
////#include "DxLib.h"
////
////// �m�F�p�ϐ�
////int hitCount = NULL;
////bool hitFrag = false;
////
////static int enemyNum = 10;
////
////TestScene_fujihara::TestScene_fujihara()
////	:m_player(nullptr)
////	, m_camera(nullptr)
////	, m_mark(nullptr)
////	, m_targetCount(0)
////	, m_startTime(0)
////	, m_iceThrowFlag(false)
////{
////	 ���̃V�[���ֈڍs���邩�ǂ���
////	m_finishFlag = FALSE;
////	 �G�l�~�[�E�X�R�AUI������
////	for (int i = 0; i < enemyNum + 1; i++)
////	{
////		m_target[i] = nullptr;
////		/*m_score_ui[i] = nullptr;
////		m_hit_ui[i] = nullptr;*/
////	}
////	for (int i = 0; i < enemyNum; i++)
////	{
////		m_target[i] = nullptr;
////		m_score_ui[i] = nullptr;
////		m_hit_ui[i] = nullptr;
////	}
////	m_startTime = GetNowCount() / 1000;
////}
////
////TestScene_fujihara::~TestScene_fujihara()
////{
////	delete m_player;	//	�v���C���[�̃|�C���^�����o�ϐ�������
////	delete m_camera;	//	�J�����̃|�C���^�����o�ϐ�������
////	delete m_mark;		//	�}�[�N�̃|�C���^�����o�ϐ�������
////	StopSoundMem(m_finishSoundHandle);
////	DeleteGraph(m_backGraphHandle);
////	DeleteGraph(m_finishGraphHandle);
////	DeleteSoundMem(m_soundHandle);
////	DeleteSoundMem(m_finishSoundHandle);
////	for (int i = 0; i < enemyNum; i++)
////	{
////		delete m_target[i];
////		delete m_score_ui[i];		//  �X�R�AUI�ւ̃|�C���^�����o�ϐ�
////		delete m_hit_ui[i];			//	�q�b�g����UI�ւ̃|�C���^�����o�ϐ�
////	}
////
////}
////
////SceneBase* TestScene_fujihara::Update()
////{
////
////	 �f�o�b�O�r���h�̂݃f�o�b�O�֐����Ăяo��
////#ifdef _DEBUG
////	DebugKey();
////#endif
////
////	 ���̍X�V
////	m_mark->Mark_Update();
////
////	 �G�l�~�[�ˏo�Ǘ�
////	if (GetNowCount() / 1000 - m_startTime > 1)
////	{
////		m_startTime = GetNowCount() / 1000;
////		m_target[m_targetCount]->SetIceState(Target_State::NOW_SHOT);
////		m_targetCount++;
////
////	}
////
////	 ���݂̔ԍ��ɉ����ăG�l�~�[�̍X�V
////	for (int i = 0; i < m_targetCount; i++)
////	{
////		m_target[i]->Update();
////	}
////	m_player->Update();
////
////	m_camera->Update(*m_player);
////
////	 �����蔻��ɂ��X�R�A�̍X�V����
////	if (HitChecker::Check(*m_player, *m_target[m_targetCount-1]))
////	{
////		m_hit_ui[m_targetCount-1]->ScoreUpdate(m_hit_ui[m_targetCount-1], true);
////	}
////	if (m_target[enemyNum - 1]->GetIceState() == Target_State::END_SHOT)
////	{
////		m_hit_ui[m_targetCount-1]->ScoreUpdate(m_hit_ui[m_targetCount-1], false);
////	}
////	
////	HitChecker::Check(*m_player, *m_target[m_targetCount]);
////
////	if (m_targetCount > enemyNum)	//	�G���^�[�������ꂽ��
////	{
////		m_finishFlag = TRUE;
////	}
////	if (m_finishFlag == TRUE)
////	{
////		WaitTimer(3000);
////		return new Result(m_score_ui[m_targetCount]->GetScore());				//	���U���g�V�[���ɐ؂�ւ���
////	}
////	return this;						//	�Q�[���V�[����\����������
////}
////
////void TestScene_fujihara::Draw()
////{
////	DrawGraph(0, 0, m_backGraphHandle, TRUE);							//	�^�C�g����ʂ̔w�i��\��
////	m_mark->Mark_Draw();
////	for (int i = 0; i < m_targetCount; i++)
////	{
////		m_target[i]->Draw();
////	}
////	m_player->Draw();
////	if (m_finishFlag == TRUE)
////	{
////		DrawGraph(0, 0, m_finishGraphHandle, TRUE);							//	�^�C�g����ʂ̔w�i��\��
////	}
////	for (int i = 0; i < enemyNum; ++i)
////	{
////		m_score_ui[i]->Draw();
////	}
////	for (int i = 0; i < enemyNum; ++i)
////	{
////		m_hit_ui[i]->Draw();
////	}
////	/*m_obstructManager->Draw();*/
////	/*DrawString(0, 0, "�Q�[����ʂł�", GetColor(255, 255, 255));*/
////}
////
////void TestScene_fujihara::Sound()
////{
////	if (m_finishFlag == TRUE)
////	{
////		StopSoundMem(m_soundHandle);
////		PlaySoundMem(m_finishSoundHandle, DX_PLAYTYPE_BACK, FALSE);
////		ChangeVolumeSoundMem(m_volumePal, m_finishSoundHandle);
////	}
////	if (m_finishFlag == FALSE)
////	{
////		PlaySoundMem(m_soundHandle, DX_PLAYTYPE_BACK, FALSE);
////		ChangeVolumeSoundMem(m_volumePal, m_soundHandle);
////	}
////}
////
////void TestScene_fujihara::Load()
////{
////	m_finishGraphHandle = LoadGraph("data/img/gameEnd.png");		//	�O���t�B�b�N�n���h���ɃQ�[���I�������̃C���[�W���Z�b�g
////	m_backGraphHandle = LoadGraph("data/img/gameBack.png");			//	�O���t�B�b�N�n���h���ɃQ�[����ʂ̃C���[�W���Z�b
////	m_soundHandle = LoadSoundMem("data/sound/gameBgm.ogg");			//	�T�E���h�n���h���ɃQ�[����ʂ�BGM���Z�b�g
////	m_finishSoundHandle = LoadSoundMem("data/sound/gameEnd.wav");		//	�T�E���h�n���h���ɃQ�[���I�����̌��ʉ����Z�b�g
////	int scoreHandle = LoadGraph("data/model/score_ui/score(1).png");
////	m_player = new Player;			//	�v���C���[�N���X�̃C���X�^���X�𐶐�
////	m_camera = new Camera;			//	�J�����N���X�̃C���X�^���X�𐶐�
////	m_mark = new Mark;				//	�}�[�N�N���X�̃C���X�^���X�𐶐�
////	for (int i = 0; i < enemyNum + 1; i++)
////	{
////		m_target[i] = new Target;
////	}
////	for (int i = 0; i < 2; ++i)
////	{
////		for (int j = 0; j < 5; ++j)
////		{
////			m_score_ui[j + (i * 5)] = new UI(j, i, scoreHandle);
////			m_hit_ui[j + (i * 5)] = new UI(j, i, -1);
////		}
////	}
////	 UI�N���X��private�����o�ϐ��ɉ摜�n���h�������[�h
////	m_score_ui[0]->Load();
////
////}
////
////void TestScene_fujihara::DebugKey()
////{
////	 �m�F�p
////	if (CheckHitKey(KEY_INPUT_A))
////	{
////		if (hitCount < enemyNum)
////		{
////			hitFrag = true;
////			m_hit_ui[hitCount]->ScoreUpdate(m_hit_ui[hitCount], hitFrag);
////			hitCount++;
////		}
////	}
////	if (CheckHitKey(KEY_INPUT_B))
////	{
////		if (hitCount < enemyNum)
////		{
////			hitFrag = false;
////			m_hit_ui[hitCount]->ScoreUpdate(m_hit_ui[hitCount], hitFrag);
////			hitCount++;
////		}
////	}
////	if (m_iceThrowFlag)
////	{
////		DrawString(1800, 980, "����", GetColor(255, 255, 255));
////	}
////	else
////	{
////		DrawString(1800, 980, "������", GetColor(255, 255, 255));
////	}
////	if (CheckHitKey(KEY_INPUT_RETURN))
////	{
////		m_checkKeyFlag = TRUE;
////	}
////	if (CheckHitKey(KEY_INPUT_RETURN) && m_checkKeyFlag == FALSE)	//	�G���^�[�������ꂽ��
////	{
////		m_finishFlag = TRUE;
////	}
////}
////
