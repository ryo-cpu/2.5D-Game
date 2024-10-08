// 2023 Takeru Yui All Rights Reserved.
#pragma once

#include "DxLib.h"
#include"Object.h"
class Enemy;
/// <summary>
/// プレイヤークラス
/// </summary>
class Player :public Object
{
public:
	Player();				// コンストラクタ.
	~Player();				// デストラクタ.
  void	Update() override;			// 更新.
  void Draw() override;
  static const  float Speed;
  static const float Scale;
};
