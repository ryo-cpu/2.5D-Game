#pragma once
#include"DxLib.h"
struct HitBlock
{
	VECTOR UpLeft;
	VECTOR DownRight;
	
};
class Object
{
public:
	Object();
	~Object();

	virtual void Update()abstract;			// 更新.
	virtual void Draw()abstract;			// 描画.
	// モデルハンドルの取得.
	int GetModelHandle() const { return modelHandle; }
	const VECTOR& GetPos() const { return pos; }
	const VECTOR& GetDir() const { return dir; }
	const VECTOR& GetVelcity() const { return velocity; }
	const HitBlock& GetCollison()const { return Collison; }
protected:
	int		modelHandle;	// モデルハンドル.
	VECTOR	pos;			// ポジション.
	VECTOR	velocity;		// 移動力.
	VECTOR	dir;			// 回転方向.
	HitBlock Collison;      //当たり判定ブロック
	int width;
	int height;
	int Depth;

	
};

