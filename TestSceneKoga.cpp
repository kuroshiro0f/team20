//#include "TestSceneKoga.h"
//#include "Result.h"
//#include "Mark.h"
//#include "Target.h"
//#include "Player.h"
//#include "ObstructManager.h"
//#include "Hitchecker.h"
//#include "UI.h"
//#include "Camera.h"
//
//#include "DxLib.h"
//#include "Effect.h"
//#include "TestScene_fujihara.h"
//
//static int enemyNum = 10;
//static int GIRL_Y = 0;
//static int LADY_Y = 0;
//static int GIRL_MIN_Y = -75;
//static int LADY_MIN_Y = -75;
//
//// �^�[�Q�b�g�����ł���Ԋu (�b�P��)
//static const int TARGET_SHOT_INTERVAL = 3;
//
//TestSceneKoga::TestSceneKoga()
//	:m_player(nullptr)
//	, m_camera(nullptr)
//	, m_mark(nullptr)
//	, m_effect(nullptr)
//	, m_targetCount(0)
//	, m_startTime(0)
//	, m_iceThrowFlag(false)
//	, m_iceHitFlagBuffer(false)
//	, m_girl_Y(GIRL_Y)
//	, m_lady_Y(LADY_Y)
//	, m_girlUpFlag(true)
//	//�@�m�F�p
//	, m_hitCount(0)
//	, m_hitFlag(false)
//{
//	// ���̃V�[���ֈڍs���邩�ǂ���
//	m_finishFlag = FALSE;
//	// �G�l�~�[�E�X�R�AUI������
//	for (int i = 0; i < enemyNum; i++)
//	{
//		m_target[i] = nullptr;
//		m_score_ui[i] = nullptr;
//		m_hit_ui[i] = nullptr;
//	}
//	m_target[enemyNum] = nullptr;
//
//	// �J�n���̃^�C�����擾
//	m_startTime = GetNowCount() / 1000;
//}
//
//TestSceneKoga::~TestSceneKoga()
//{
//	delete m_player;	//	�v���C���[�̃|�C���^�����o�ϐ�������
//	delete m_camera;	//	�J�����̃|�C���^�����o�ϐ�������
//	delete m_mark;		//	�}�[�N�̃|�C���^�����o�ϐ�������
//	StopSoundMem(m_finishSoundHandle);
//	DeleteGraph(m_backGraphHandle);
//	DeleteGraph(m_finishGraphHandle);
//	DeleteGraph(m_manualGraphHandle);
//	DeleteGraph(m_girlGraphHandle);
//	DeleteGraph(m_ladyGraphHandle);
//	DeleteSoundMem(m_soundHandle);
//	DeleteSoundMem(m_finishSoundHandle);
//	for (int i = 0; i < enemyNum; i++)
//	{
//		delete m_target[i];
//		delete m_score_ui[i];		//  �X�R�AUI�ւ̃|�C���^�����o�ϐ�
//		delete m_hit_ui[i];			//	�q�b�g����UI�ւ̃|�C���^�����o�ϐ�
//	}
//	delete m_target[enemyNum];
//
//	m_effect->Delete();
//	delete m_effect;
//}
//
//SceneBase* TestSceneKoga::Update()
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
//	if (m_targetCount == 0)
//	{
//		m_target[m_targetCount]->SetSetTime(m_startTime);
//	}
//
//
//	// �G�l�~�[�ˏo�Ǘ�
//	if (GetNowCount() / 1000 - m_startTime > TARGET_SHOT_INTERVAL)
//	{
//		m_startTime = GetNowCount() / 1000;
//		if (m_target[m_targetCount]->GetIceState() == NO_SHOT)
//		{
//			m_target[m_targetCount]->SetIceState(NOW_SHOT);
//			PlaySoundMem(m_iceSoundHandle, DX_PLAYTYPE_BACK);
//			ChangeVolumeSoundMem(m_volumePal+20, m_iceSoundHandle);
//		}
//		if (m_target[m_targetCount]->GetIceState() == END_SHOT)
//		{
//			m_target[m_targetCount + 1]->SetSetTime(m_startTime);
//			m_targetCount++;
//		}
//	}
//
//	// ���݂̔ԍ��ɉ����ăG�l�~�[�̍X�V
//	m_target[m_targetCount]->Update();
//	m_target[m_targetCount]->SetTargetCount(m_targetCount);
//	m_iceHitFlagBuffer = HitChecker::Check(*m_player, *m_target[m_targetCount]);
//	m_target[m_targetCount]->Reaction(m_hit_ui[m_targetCount], m_iceHitFlagBuffer);
//
//	m_player->Update();
//
//	m_camera->Update(*m_player);
//
//
//	// UI�̒��ؖ��𓮂���
//	if (m_girlUpFlag)
//	{
//		m_girl_Y--;
//		if (m_girl_Y < GIRL_MIN_Y)
//		{
//			m_girl_Y = GIRL_MIN_Y;
//			m_girlUpFlag = false;
//		}
//	}
//	else if (!m_girlUpFlag)
//	{
//		m_girl_Y++;
//		if (m_girl_Y > 0)
//		{
//			m_girl_Y = 0;
//			m_girlUpFlag = true;
//		}
//	}
//
//
//
//	if (m_targetCount == enemyNum)	//	�G���^�[�������ꂽ��
//	{
//		m_finishFlag = TRUE;
//	}
//	if (m_finishFlag == TRUE)
//	{
//		// scoreUI�̃X�R�A��Result��score�ϐ��ɃZ�b�g
//
//		WaitTimer(3000);
//		return new Result(m_score_ui[m_targetCount]->GetScore());				//	���U���g�V�[���ɐ؂�ւ���
//	}
//	return this;						//	�Q�[���V�[����\����������
//}
//
//void TestSceneKoga::Draw()
//{
//	// �w�i
//	DrawGraph(0, 0, m_backGraphHandle, TRUE);
//	// ��������n
//	DrawGraph(0, 0, m_manualGraphHandle, TRUE);							//	���������\��
//	DrawGraph(0, m_girl_Y, m_girlGraphHandle, TRUE);
//	DrawGraph(0, m_lady_Y, m_ladyGraphHandle, TRUE);//	�^�C�g����ʂ̔w�i��\��
//	// �ڈ�ƂȂ��
//	m_mark->Mark_Draw();
//	// �^�[�Q�b�g(�A�C�X)
//	for (int i = 0; i <= m_targetCount; i++)
//	{
//		m_target[i]->Draw();
//	}
//
//	// �v���[���[
//	m_player->Draw();
//
//	// �I����
//	if (m_target[enemyNum - 1]->GetIceState() == Target_State::END_SHOT)
//	{
//		DrawGraph(0, 0, m_finishGraphHandle, TRUE);							//	�Ō�̃G�l�~�[���ˏo����I�������"�Q�[���I��"�̕\��
//	}
//	for (int i = 0; i < enemyNum; ++i)
//	{
//		m_score_ui[i]->Draw();
//	}
//	for (int i = 0; i < enemyNum; ++i)
//	{
//		m_hit_ui[i]->Draw();
//	}
//
//	// �G�t�F�N�g�̍Đ�
//	if (!(m_effect->GetNowPlaying() == 0) && m_target[m_targetCount]->GetHitIce())
//	{
//		m_effect->PlayEffekseer(VGet(0, 20, 0));
//		m_target[m_targetCount]->SetHitIce(false);
//	}
//
//	/*m_obstructManager->Draw();*/
//	/*DrawString(0, 0, "�Q�[����ʂł�", GetColor(255, 255, 255));*/
//}
//
//void TestSceneKoga::Sound()
//{
//	if (m_target[enemyNum - 1]->GetIceState() == Target_State::END_SHOT)
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
//void TestSceneKoga::Load()
//{
//	m_finishGraphHandle = LoadGraph("data/img/gameEnd.png");		//	�O���t�B�b�N�n���h���ɃQ�[���I�������̃C���[�W���Z�b�g
//	m_backGraphHandle = LoadGraph("data/img/gameBack.png");			//	�O���t�B�b�N�n���h���ɃQ�[����ʂ̃C���[�W���Z�b
//	m_soundHandle = LoadSoundMem("data/sound/gameBgm.ogg");			//	�T�E���h�n���h���ɃQ�[����ʂ�BGM���Z�b�g
//	m_finishSoundHandle = LoadSoundMem("data/sound/gameEnd.wav");	//	�T�E���h�n���h���ɃQ�[���I�����̌��ʉ����Z�b�g
//	m_girlGraphHandle = LoadGraph("data/img/chinaGirl.png");
//	m_ladyGraphHandle = LoadGraph("data/img/chinaLady.png");
//	m_manualGraphHandle = LoadGraph("data/img/manual.png");			//	�O���t�B�b�N�n���h���ɑ�������̃C���[�W���Z�b�g
//	int scoreHandle = LoadGraph("data/model/score_ui/score(1).png");
//	m_iceSoundHandle = LoadSoundMem("data/sound/throwIce.mp3");		//	�T�E���h�n���h���ɃA�C�X���ˎ��̌��ʉ����Z�b�g
//	m_hitSoundHandle = LoadSoundMem("data/sound/hitIce.mp3");		//	�T�E���h�n���h���Ƀq�b�g���̌��ʉ����Z�b�g
//	m_missSoundHandle = LoadSoundMem("data/sound/missIce.mp3");		//	�T�E���h�n���h���Ƀ~�X���̌��ʉ����Z�b�g
//	m_player = new Player;			//	�v���C���[�N���X�̃C���X�^���X�𐶐�
//	m_camera = new Camera;			//	�J�����N���X�̃C���X�^���X�𐶐�
//	m_mark = new Mark;				//	�}�[�N�N���X�̃C���X�^���X�𐶐�
//	for (int i = 0; i < (enemyNum + 1); i++)
//	{
//		m_target[i] = new Target;
//		m_target[i]->SetInterval(TARGET_SHOT_INTERVAL);
//		m_target[i]->SetThrowSound(m_iceSoundHandle);
//		m_target[i]->SetHitSound(m_hitSoundHandle);
//		m_target[i]->SetMissSound(m_missSoundHandle);
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
//
//}
//
//void TestSceneKoga::DebugKey()
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
