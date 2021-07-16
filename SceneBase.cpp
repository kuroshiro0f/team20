#include "SceneBase.h"

//	初期音量
const int VOLUME_PAL = 40;
//	フォントサイズ
const int LOAD_FONT_SIZE = 50;
const int NORMAL_FONT_SIZE = 17;

SceneBase::SceneBase()
	: m_volumePal(VOLUME_PAL)
	, m_loadFontSize(LOAD_FONT_SIZE)
	, m_normalFontSize(NORMAL_FONT_SIZE)
{
}
