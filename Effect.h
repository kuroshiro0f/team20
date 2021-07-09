//-----------------------------------------------------------------------+
// エフェクトクラス                         
//                                                      2019 Yutaro Ono.
//-----------------------------------------------------------------------+
#pragma once

// インクルードファイル
#include "DxLib.h"
#include "EffekseerForDXLib.h"


class PlayEffect
{

public:

	PlayEffect(const char* sourceEffectHandle);
	PlayEffect(const char* sourceEffectHandle, float _scale);
	~PlayEffect();

	void Delete();

	// Efekseer3Dの単純再生
	void PlayEffekseer(const VECTOR in_playPos);

	// Effekseer3Dのサイズを指定した再生
	void ChangeSizePlayEffekseer(const VECTOR in_playPos, const VECTOR in_size);

	// 2DのEffekseer再生
	void PlayEffekseer2D(const VECTOR in_playPos);

	void StopEffect();

	const int GetNowPlaying();    // エフェクトが再生中かどうか(0:再生中  1:再生されていない)

	// 再生中のエフェクトの座標セッター
	void SetPlayingEffectPos(const VECTOR& _playPos);

	// 再生中エフェクトの回転値セッター
	void SetPlayingEffectRotation(const VECTOR& _dirVec);

	// 再生中のエフェクトの拡大率を変更する
	void SetPlayingEffectScale(const float in_sizeX, const float in_sizeY, const float in_sizeZ) { SetScalePlayingEffekseer3DEffect(m_playingEffect, in_sizeX, in_sizeY, in_sizeZ); }

private:

	VECTOR m_playPos;          // エフェクトの座標

	int m_effectHandle;        // 被ダメージエフェクトのハンドル
	int m_playingEffect;
};