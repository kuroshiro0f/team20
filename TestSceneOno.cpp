//#include "TestSceneOno.h"
//#include "Result.h"
//#include "Mark.h"
//#include "Target.h"
//#include "Player.h"
//#include "ObstructManager.h"
//#include "Hitchecker.h"
//#include "UI.h"
//#include "Camera.h"
//#include "Effect.h"
//
//#include "DxLib.h"
//
//
//static int enemyNum = 10;
//
//TestSceneOno::TestSceneOno()
//	:m_player(nullptr)
//	, m_camera(nullptr)
//	, m_mark(nullptr)
//	,m_effect(nullptr)
//	,m_playerOrbitEfk(nullptr)
//	, m_targetCount(0)
//	, m_startTime(0)
//	, m_iceThrowFlag(false)
//	,m_hitCount(0)
//	,m_hitFlag(false)
//{
//	// ���̃V�[���ֈڍs���邩�ǂ���
//	m_finishFlag = FALSE;
//	// �G�l�~�[�E�X�R�AUI������
//	for (int i = 0; i < enemyNum; i++)
//	{
//		m_score_ui[i] = nullptr;
//		m_hit_ui[i] = nullptr;
//	}
//
//	// �^�[�Q�b�g�̈�̊m��
//	m_targets.resize(enemyNum + 1);
//
//	m_startTime = GetNowCount() / 1000;
//}
//
//TestSceneOno::~TestSceneOno()
//{
//	delete m_player;	//	�v���C���[�̃|�C���^�����o�ϐ�������
//	delete m_camera;	//	�J�����̃|�C���^�����o�ϐ�������
//	delete m_mark;		//	�}�[�N�̃|�C���^�����o�ϐ�������
//	StopSoundMem(m_finishSoundHandle);
//	DeleteGraph(m_backGraphHandle);
//	DeleteGraph(m_finishGraphHandle);
//	DeleteSoundMem(m_soundHandle);
//	DeleteSoundMem(m_finishSoundHandle);
//	for (int i = 0; i < enemyNum; i++)
//	{
//		delete m_score_ui[i];		//  �X�R�AUI�ւ̃|�C���^�����o�ϐ�
//		delete m_hit_ui[i];			//	�q�b�g����UI�ւ̃|�C���^�����o�ϐ�
//	}
//
//	// �S�^�[�Q�b�g�̊m��
//	while (!m_targets.empty())
//	{
//		delete m_targets.back();
//		m_targets.pop_back();
//	}
//
//	m_effect->Delete();
//	delete m_effect;
//	m_playerOrbitEfk->Delete();
//	delete m_playerOrbitEfk;
//}
//
//SceneBase* TestSceneOno::Update()
//{
//
//	// �f�o�b�O�r���h�̂݃f�o�b�O�֐����Ăяo��
//#ifdef _DEBUG
//	DebugKey();
//#endif
//
//	// ���̍X�V
//	m_mark->Mark_Update();
//
//	// �G�l�~�[�ˏo�Ǘ�
//	if (GetNowCount() / 1000 - m_startTime > 1)
//	{
//		m_startTime = GetNowCount() / 1000;
//		m_targets[m_targetCount]->SetIceState(Target_State::NOW_SHOT);
//		m_targetCount++;
//	}
//
//	// ���݂̔ԍ��ɉ����ăG�l�~�[�̍X�V
//	for (int i = 0; i < m_targetCount; i++)
//	{
//		m_targets[i]->Update();
//	}
//	m_player->Update();
//
//	m_camera->Update(*m_player);
//	for (int i = 0; i < m_targetCount; i++)
//	{
//		HitChecker::Check(*m_player, *m_targets[i]);
//	}
//	if (m_targetCount > enemyNum)	//	�G���^�[�������ꂽ��
//	{
//		m_finishFlag = TRUE;
//	}
//	if (m_finishFlag == TRUE)
//	{
//		WaitTimer(3000);
//		return new Result(m_score_ui[m_targetCount]->GetScore());				//	���U���g�V�[���ɐ؂�ւ���
//	}
//	return this;						//	�Q�[���V�[����\����������
//}
//
//void TestSceneOno::Draw()
//{
//	DrawGraph(0, 0, m_backGraphHandle, TRUE);							//	�^�C�g����ʂ̔w�i��\��
//	m_mark->Mark_Draw();
//	for (int i = 0; i < m_targetCount; i++)
//	{
//		m_targets[i]->Draw();
//	}
//	m_player->Draw();
//	if (m_finishFlag == TRUE)
//	{
//		DrawGraph(0, 0, m_finishGraphHandle, TRUE);							//	�^�C�g����ʂ̔w�i��\��
//	}
//	for (int i = 0; i < enemyNum; ++i)
//	{
//		m_score_ui[i]->Draw();
//	}
//	for (int i = 0; i < m_hitCount; ++i)
//	{
//		m_hit_ui[i]->Draw();
//	}
//
//	// �G�t�F�N�g�̍Đ�
//	if (!(m_effect->GetNowPlaying() == 0))
//	{
//		m_effect->PlayEffekseer(VGet(0, 20, 0));
//	}
//
//	// �v���C���[�̋O���G�t�F�N�g
//	if (m_playerOrbitEfk->GetNowPlaying() != 0)
//	{
//		m_playerOrbitEfk->PlayEffekseer(m_player->GetPos());
//		VECTOR efkDir = VGet(0.0f, DX_PI_F, 0.0f);
//		m_playerOrbitEfk->SetPlayingEffectRotation(efkDir);
//	}
//	else
//	{
//		// �G�t�F�N�g�Đ����̓v���C���[�̍��W��ǔ�
//		m_playerOrbitEfk->SetPlayingEffectPos(m_player->GetPos());
//	}
//	
//}
//
//void TestSceneOno::Sound()
//{
//	if (m_finishFlag == TRUE)
//	{
//		StopSoundMem(m_soundHandle);
//		PlaySoundMem(m_finishSoundHandle, DX_PLAYTYPE_BACK, FALSE);
//		ChangeVolumeSoundMem(m_volumePal, m_finishSoundHandle);
//	}
//	if (m_finishFlag == FALSE)
//	{
//		PlaySoundMem(m_soundHandle, DX_PLAYTYPE_BACK, FALSE);
//		ChangeVolumeSoundMem(m_volumePal, m_soundHandle);
//	}
//}
//
//void TestSceneOno::Load()
//{
//	m_finishGraphHandle = LoadGraph("data/img/gameEnd.png");		//	�O���t�B�b�N�n���h���ɃQ�[���I�������̃C���[�W���Z�b�g
//	m_backGraphHandle = LoadGraph("data/img/gameBack.png");			//	�O���t�B�b�N�n���h���ɃQ�[����ʂ̃C���[�W���Z�b
//	m_soundHandle = LoadSoundMem("data/sound/gameBgm.ogg");			//	�T�E���h�n���h���ɃQ�[����ʂ�BGM���Z�b�g
//	m_finishSoundHandle = LoadSoundMem("data/sound/gameEnd.wav");		//	�T�E���h�n���h���ɃQ�[���I�����̌��ʉ����Z�b�g
//	int scoreHandle = LoadGraph("data/model/score_ui/score(1).png");
//	m_player = new Player;			//	�v���C���[�N���X�̃C���X�^���X�𐶐�
//	m_camera = new Camera;			//	�J�����N���X�̃C���X�^���X�𐶐�
//	m_mark = new Mark;				//	�}�[�N�N���X�̃C���X�^���X�𐶐�
//
//	// �^�[�Q�b�g�̐���
//	for (int i = 0; i < m_targets.size(); i++)
//	{
//		m_targets[i] = new Target();
//	}
//
//	for (int i = 0; i < 2; ++i)
//	{
//		for (int j = 0; j < 5; ++j)
//		{
//			m_score_ui[j + (i * 5)] = new UI(j, i, scoreHandle);
//			m_hit_ui[j + (i * 5)] = new UI(j, i, -1);
//		}
//	}
//	// UI�N���X��private�����o�ϐ��ɉ摜�n���h�������[�h
//	m_score_ui[0]->Load();
//
//	m_effect = new PlayEffect("data/effects/FeatherBomb.efk");
//	m_playerOrbitEfk = new PlayEffect("data/effects/PlayerLine.efk");
//
//}
//
//void TestSceneOno::DebugKey()
//{
//	// �m�F�p
//	if (CheckHitKey(KEY_INPUT_A))
//	{
//		if (m_hitCount < enemyNum)
//		{
//			m_hitFlag = true;
//			//m_hit_ui[m_hitCount]->ScoreUpdate(m_hit_ui[m_hitCount], m_hitFlag);
//			m_hitCount++;
//		}
//	}
//	if (CheckHitKey(KEY_INPUT_B))
//	{
//		if (m_hitCount < enemyNum)
//		{
//			m_hitFlag = false;
//			//m_hit_ui[m_hitCount]->ScoreUpdate(m_hit_ui[m_hitCount], m_hitFlag);
//			m_hitCount++;
//		}
//	}
//	if (m_iceThrowFlag)
//	{
//		DrawString(1800, 980, "����", GetColor(255, 255, 255));
//	}
//	else
//	{
//		DrawString(1800, 980, "������", GetColor(255, 255, 255));
//	}
//	if (CheckHitKey(KEY_INPUT_RETURN))
//	{
//		m_checkKeyFlag = TRUE;
//	}
//	if (CheckHitKey(KEY_INPUT_RETURN) && m_checkKeyFlag == FALSE)	//	�G���^�[�������ꂽ��
//	{
//		m_finishFlag = TRUE;
//	}
//}
