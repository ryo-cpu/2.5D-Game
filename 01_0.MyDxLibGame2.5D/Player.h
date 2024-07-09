// 2023 Takeru Yui All Rights Reserved.
#pragma once

#include "DxLib.h"
class Enemy;
/// <summary>
/// プレイヤークラス
/// </summary>
class Player final
{
public:
	Player();				// コンストラクタ.
	~Player();				// デストラクタ.

	void Update();			// 更新.
	void Draw();			// 描画.
	void DrawCollision();
	bool isCollision(Enemy*enemy);
	// モデルハンドルの取得.
	int GetModelHandle() const { return modelHandle; }

	const VECTOR& GetPos() const { return pos; }
	const VECTOR& GetDir() const { return dir; }

private:
	int		modelHandle;	// モデルハンドル.
	VECTOR	pos;			// ポジション.
	VECTOR	velocity;		// 移動力.
	VECTOR	dir;			// 回転方向.
	int width;
	int height;
	int Depth;

	// 静的定数.
	static const float Speed;
	static const float Scale;
};
