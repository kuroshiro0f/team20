//-----------------------------------------------------------------------+
// エフェクトクラス                         
//                                                      2019 Yutaro Ono.
//-----------------------------------------------------------------------+

// インクルードファイル
#include "Effect.h"

// コンストラクタ
PlayEffect::PlayEffect(const char* sourceEffectHandle)
	:m_effectHandle(-1)
	,m_playPos(VGet(0, 0, 0))
	,m_playingEffect(-1)
{
	// モデルのロード
	m_effectHandle = LoadEffekseerEffect(sourceEffectHandle,1.5f);
	if (m_effectHandle == -1)
	{
		printfDx("エフェクト読み込み失敗");
	}

}

// コンストラクタ2 (スケール指定)
PlayEffect::PlayEffect(const char* sourceEffectHandle, float _scale)
	:m_effectHandle(-1)
	, m_playPos(VGet(0, 0, 0))
	, m_playingEffect(-1)
{
	// モデルのロード
	m_effectHandle = LoadEffekseerEffect(sourceEffectHandle, _scale);
	if (m_effectHandle == -1)
	{
		printfDx("エフェクト読み込み失敗");
	}

}

// デストラクタ
PlayEffect::~PlayEffect()
{
	// 処理なし
}


// 解放処理
void PlayEffect::Delete()
{
	if (GetNowPlaying() == 0)
	{
		StopEffect();
	}

	DeleteEffekseerEffect(m_effectHandle);
}

// エフェクトの再生を止める
void PlayEffect::StopEffect()
{
	StopEffekseer3DEffect(m_playingEffect);
	m_playingEffect = IsEffekseer3DEffectPlaying(m_playingEffect);
}

/// <summary>
/// 再生中かを調べる
/// </summary>
/// <returns> 再生中：0, それ以外：1 </returns>
const int PlayEffect::GetNowPlaying()
{
	return IsEffekseer3DEffectPlaying(m_playingEffect);
}

/// <summary>
/// 再生中のエフェクトの座標を変える
/// </summary>
/// <param name="_size"></param>
void PlayEffect::SetPlayingEffectPos(const VECTOR& _playPos)
{
	SetPosPlayingEffekseer3DEffect(m_playingEffect, _playPos.x, _playPos.y, _playPos.z);
}

/// <summary>
/// 再生中エフェクトの回転
/// </summary>
/// <param name="_dirVec"></param>
void PlayEffect::SetPlayingEffectRotation(const VECTOR& _dirVec)
{
	SetRotationPlayingEffekseer3DEffect(m_playingEffect, _dirVec.x, _dirVec.y, _dirVec.z);
}

// Effekseer3Dの描画
void PlayEffect::PlayEffekseer(const VECTOR in_playPos)
{
	// printfDx(" (X座標 : %f, Y座標 : %f, Z座標 : %f ", in_playPos.x, in_playPos.y, in_playPos.z);

	// printfDx("エフェクト再生");

	// エフェクトの座標を更新
	m_playPos = in_playPos;

	// エフェクトの描画
	m_playingEffect = PlayEffekseer3DEffect(m_effectHandle);

	// エフェクトを再生する座標を指定
	SetPosPlayingEffekseer3DEffect(m_playingEffect, m_playPos.x, m_playPos.y, m_playPos.z);
}

// Effekseer3Dのサイズを指定した再生
void PlayEffect::ChangeSizePlayEffekseer(const VECTOR in_playPos, const VECTOR in_size)
{
	// エフェクトの座標更新
	m_playPos = in_playPos;

	// エフェクトの描画
	m_playingEffect = PlayEffekseer3DEffect(m_effectHandle);

	// エフェクトのサイズを設定
	SetScalePlayingEffekseer3DEffect(m_playingEffect, in_size.x, in_size.y, in_size.z);

	// エフェクトを再生する座標を指定
	SetPosPlayingEffekseer3DEffect(m_playingEffect, m_playPos.x, m_playPos.y, m_playPos.z);

}

void PlayEffect::PlayEffekseer2D(const VECTOR in_playPos)
{
	// エフェクトの座標を更新
	m_playPos = in_playPos;

	// エフェクトの描画
	m_playingEffect = PlayEffekseer2DEffect(m_effectHandle);

	// エフェクトを再生する座標を指定
	SetPosPlayingEffekseer2DEffect(m_playingEffect, m_playPos.x, m_playPos.y, m_playPos.z);

}
