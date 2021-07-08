//-----------------------------------------------------------------------------
// @brief  メイン処理.
// 2016 Takeru Yui All Rights Reserved.
//-----------------------------------------------------------------------------

#pragma once

class Target;
class Player;
class TestSceneKoga;

class HitChecker
{
public:
	static bool Check(Player& player, Target& Target);
};