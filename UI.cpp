#include "UI.h"

// �X�S�N�J�^�C�A�C�X�̉摜�T�C�Y
const int score_pixel = 320;
// �摜�̏k������傫��
const double score_shrink = 0.4f;
// RotaGraph���g���̂Ő^�񒆂���̃X�S�N�J�^�C�A�C�X�̉摜�T�C�Y
const int score_graph_size = score_pixel*score_shrink;

// �n���h��������ϐ��̎��̂����
int UI::m_help_graphHandle;
int UI::m_score_graphHandle;
int UI::m_hit_graphHandle;
int UI::m_miss_graphHandle;
int UI::m_score;

// ScoreUI�R���X�g���N�^
UI::UI(const int& _x, const int& _y, const int& _graph_handle)
{
	// x,y���W�ɉ摜�̈ʒu���W���i�[����
	m_posX = (_x * score_graph_size) + 100;
	m_posY = (_y * score_graph_size) + 100;
	// �g���摜���i�[����
	m_handle = _graph_handle;
	// score���O�ɂ���
	m_score = 0;
}

// ScoreUI�f�X�g���N�^
UI::~UI()
{

}

void UI::Load()
{
	// ��������摜�̓ǂݍ���
	m_help_graphHandle = LoadGraph("data/model/score_ui/");
	// �X�R�A�摜�̓ǂݍ���
	m_score_graphHandle = LoadGraph("data/model/score_ui/hit.png");
	// HIT�摜�̓ǂݍ���
	m_hit_graphHandle = LoadGraph("data/model/score_ui/hit.png");
	// MISS�摜�̓ǂݍ���
	m_miss_graphHandle = LoadGraph("data/model/score_ui/miss.png");
}

// �X�V
// �����ɃG�l�~�[����score��targetCount�������Ă���
void UI::ScoreUpdate(bool _hitOrMiss)
{
	m_handle = -1;
	if (m_handle == -1)
	{
		// �����蔻���ǂ�Ł~���Z���̔���H
			// �������Ă����
		if (_hitOrMiss)
		{
			// �`��p�n���h����hit�̃n���h�����i�[
			m_handle = m_hit_graphHandle;
			// �X�R�A������Z����
			m_score++;
		}
		// �������Ă��Ȃ����
		else
		{
			// �`��p�n���h����miss�̃n���h�����i�[
			m_handle = m_miss_graphHandle;
		}
	}
}

// �`��(�������̒l�ŌĂяo���摜��ς���)
void UI::Draw()
{
	//DrawGraph(m_posX, m_posY, m_handle, TRUE);
 	DrawRotaGraph(m_posX, m_posY, score_shrink, 0, m_handle, TRUE, FALSE);
}
