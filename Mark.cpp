#include "Mark.h"

const int MARK_X = 0;
const int MARK_Y = 0;
const int MARK_Z = 0;

Mark::Mark()
	: m_modelHandle(-1)
{
	m_modelHandle = MV1LoadModel("data/model/mark/table.pmx");		//	3D���f���̓ǂݍ���

	m_pos = VGet(MARK_X, MARK_Y, MARK_Z);		//	�ڈ�̈ʒu
}

Mark::~Mark()
{
	MV1DeleteModel(m_modelHandle);		//	���f���̃A�����[�h
}

void Mark::Mark_Update()
{



	MV1SetPosition(m_modelHandle, m_pos);
}

void Mark::Mark_Draw()
{
	MV1DrawModel(m_modelHandle);

	//DrawSphere3D(m_pos, 100.0f, 5, 0x00ffff, 0x00ffff, false);		//	�f�o�b�O�p�ɋ��̂�\��
}
