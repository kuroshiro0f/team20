#ifndef _MARK_H_
#define _MARK_H_

#include"DxLib.h"

class Mark
{
public:
	Mark();					//	�R���X�g���N�^
	~Mark();				//	�f�X�g���N�^

	void Mark_Update();		//	�X�V
	void Mark_Draw();		//	�`��

	//	���f���n���h���̎擾
	int GetModelHandle()
	{
		return m_modelHandle;
	}



private:
	int m_modelHandle;		//	���f���n���h��
	VECTOR m_pos;				//	�|�W�V����
};

#endif // _MARK_H_