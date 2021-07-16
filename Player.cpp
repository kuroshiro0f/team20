//-----------------------------------------------------------------------------
// @brief  プレイヤークラス.
// 2016 Takeru Yui All Rights Reserved.
//-----------------------------------------------------------------------------
#include "Player.h"
#include "ObstructBase.h"
#include "Effect.h"

// 静的定数.
const float Player::ACCEL				= 500.0f;		// 通常の加速.

//
int Player::m_sHandle;

//const float Player::ACCEL = 0.03f;		// 通常の加速.
const float Player::MAX_SPEED			= 0.8f;			// 最高速度.
const float Player::DEFAULT_DECEL		= -0.01f;		// なにもしない時の減速.
const float Player::BREAK_DECEL			= -0.05f;		// ブレーキ時の減速.
const float Player::GRIP_DECEL			= -0.025f;		// グリップの減速.
const float Player::GRIP_POWER			= 0.1f;			// グリップ力.
const float Player::COLIDE_DECEL_FAC	= 0.4f;			// 障害物にぶつかったときの減速率.

//	音量
const int VOLUME_PAL = 100;

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
Player::Player()
	: modelHandle(-1)
	 , hitRadius(7.5f)
	,m_playerOrbitEfk(nullptr)
{
	// サウンドの読み込み
	m_sHandle = LoadSoundMem("data/sound/sara_shrow.wav");

	// ３Ｄモデルの読み込み
	modelHandle = MV1LoadModel("data/model/sara/sara.pmx");

	// エフェクト読み込み
	m_playerOrbitEfk = new PlayEffect("data/effects/PlayerLine.efk");
	m_efkDir = VGet(0.0f, DX_PI_F, 0.0f);
	m_playerOrbitEfk->SetPlayingEffectRotation(m_efkDir);

	// posはVector型なので、VGetで原点にセット
	pos = VGet(0, 10, -100);
	// ３Dモデルのポジション設定
	MV1SetPosition(modelHandle, pos);
	// 移動する力を（すべての座標）ゼロにする
	velocity = VGet(0, 0, 0);
	// 
	dir = VGet(0, 0, 1);
	// キーを押されていない状態にする
	KeyPush = false;
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
Player::~Player()
{
	// モデルのアンロード.
	MV1DeleteModel(modelHandle);
	// サウンドのアンロード
	DeleteSoundMem(m_sHandle);
	// エフェクトのアンロード
	m_playerOrbitEfk->Delete();
	delete m_playerOrbitEfk;
}

//-----------------------------------------------------------------------------
// @brief  更新.
//-----------------------------------------------------------------------------
void Player::Update(float _deltaTime)
{
	// キー入力取得
	int Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// 加速処理.
	VECTOR accelVec = VGet(0, 0, 0);

	// キーが押されておらず、かつキーが押されたら
	if (CheckHitKey(KEY_INPUT_SPACE)&& !KeyPush)
	{
		PlaySoundMem(m_sHandle, DX_PLAYTYPE_BACK);
		ChangeVolumeSoundMem(VOLUME_PAL, m_sHandle);
		KeyPush = true;
	}

	if (KeyPush)
	{
		accelVec = VScale(dir, ACCEL);
	}

	// z座標が415を超えたら所定の位置に戻る
	if (VSize(pos) > VSize(VGet(0, 0, 415)))
	{
		// キーが押されていない状態にする
		KeyPush = false;
		// posを原点にセット
		pos = VGet(0, 10, -100);
		// 移動する力を（すべての方向）ゼロにする
		velocity = VGet(0, 0, 0);
	}

	// 止まっている場合は減速しない.
	if (VSize(velocity) > 0)
	{
		// 右か左を押していたらグリップによる減速.
		if (Key & PAD_INPUT_RIGHT || Key & PAD_INPUT_LEFT)
		{
			accelVec = VAdd(accelVec, VScale(dir, GRIP_DECEL));
		}
		// 何も押さなければ減速.
		if (Key == 0&&KeyPush==false)
		{
			accelVec = VScale(dir, DEFAULT_DECEL);
		}
	}

	// ベロシティ加速計算.
	velocity = VAdd(velocity, accelVec);

	// 反対方向に進む状態になっていたら止める.
	if (VDot(velocity, dir) < 0)
	{
		velocity = VGet(0, 0, 0);
	}

	// 上下方向にいかないようにベロシティを整える.
	velocity = VGet(velocity.x * _deltaTime, 0, velocity.z * _deltaTime);

	// ポジションを更新.
	pos = VAdd(pos, velocity);

	// 力をかけ終わったベロシティの方向にディレクションを調整.
	/*if (VSize(velocity) != 0)
	{
		dir = VNorm(velocity);
	}*/
	//printfDx("%f %f %f\n", dir.x, dir.y, dir.z);

	// ３Dモデルのポジション設定
	MV1SetPosition(modelHandle, pos);

	// 向きに合わせて回転.
	//MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	
	// モデルに向いてほしい方向に回転.
	/*MATRIX tmpMat = MV1GetMatrix(modelHandle);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	tmpMat = MMult(tmpMat, rotYMat);
	MV1SetRotationMatrix(modelHandle, tmpMat);*/
}

//-----------------------------------------------------------------------------
// @brief  描画.
//-----------------------------------------------------------------------------
void Player::Draw()
{
	// 3Dモデルのスケールを拡大
	MV1SetScale(modelHandle, VGet(3.0f, 3.0f, 3.0f));
	// ３Ｄモデルの描画
	MV1DrawModel(modelHandle);

	if (!KeyPush)
	{
		m_playerOrbitEfk->StopEffect();
	}
	// プレイヤーの軌道エフェクト
	if (KeyPush)
	{
		if (m_playerOrbitEfk->GetNowPlaying() != 0)
		{
			m_playerOrbitEfk->PlayEffekseer(pos);
			m_playerOrbitEfk->SetPlayingEffectRotation(m_efkDir);
		}

		// エフェクト再生中はプレイヤーの座標を追尾
		m_playerOrbitEfk->SetPlayingEffectPos(pos);	
	}


	// デバッグあたり判定.
	// DrawSphere3D(pos, hitRadius, 5, 0x00ffff, 0x00ffff, false);
}

//-----------------------------------------------------------------------------
// @brief  衝突処理.
//-----------------------------------------------------------------------------
void Player::OnHitObstruct(ObstructBase& obstruct)
{
	//// 自分自身の位置を障害物のあたり判定分ずらす.
	//// Z軸とX軸の二次元座標として位置ずらしを行う.
	//VECTOR yZeroPlayer = VGet(pos.x, 0, pos.z);
	//VECTOR yZeroObstruct = VGet(obstruct.GetPos().x, 0, obstruct.GetPos().z);

	//VECTOR obsToPlayer = VSub(yZeroPlayer, yZeroObstruct);

	//// ぶつかったときに離す距離。ちょうどだとfloat誤差で重なり続けるので少し間をあける.
	//float awayRange = (hitRadius + obstruct.GetHitRadius() + 0.01f);

	//VECTOR awayVec = VScale(VNorm(obsToPlayer), awayRange);
	//pos = VAdd(yZeroObstruct, awayVec);

	//// ぶつかったら減速する.
	//velocity = VScale(velocity, COLIDE_DECEL_FAC);
}