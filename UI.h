#pragma once
#include "DxLib.h"

// �X�R�A��UI�N���X
class UI final
{
public:
	// �R���X�g���N�^
	UI(const int& _x, const int& _y, const int& _graph_handle);
	// �f�X�g���N�^
	~UI();
	// ���[�h
	void UI::Load();
	// �X�V
	// �����ɃG�l�~�[����score�ƃ^�[�Q�b�g�J�E���g�������Ă���
	void UI::ScoreUpdate(bool _hitOrMiss);
	// �`��
	void UI::Draw();
	// getter
	int GetScore() { return m_score; }

private:
	// ��������摜�n���h��
	static int m_help_graphHandle;
	// �X�R�A�摜�n���h��
	static int  m_score_graphHandle;
	// �����������̉摜�n���h��
	static int m_hit_graphHandle;
	// �O�ꂽ���̉摜�n���h��
	static int m_miss_graphHandle;

	// �X�R�A�ۑ��p�ϐ�
	static int m_score;

	// �X�R�A�̍��W
	int m_posX;
	int m_posY;
	// �n���h���i�[�ϐ�
	int m_handle;
};