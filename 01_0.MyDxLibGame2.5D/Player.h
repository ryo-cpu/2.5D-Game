// 2023 Takeru Yui All Rights Reserved.
#pragma once

#include "DxLib.h"
#include"Object.h"f
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
};
