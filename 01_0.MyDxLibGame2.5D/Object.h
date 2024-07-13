#pragma once
#include"DxLib.h"
struct HitBlock
{
	VECTOR UpLeft;
	VECTOR UpRight;
	VECTOR DownRight;
	VECTOR DownLeft;
	
};
class Object
{
public:
	/*Object();
	~Object();*/

	virtual void Update()abstract;			// 更新.
	virtual void Draw()abstract;			// 描画.
	// モデルハンドルの取得.
	int GetModelHandle() const { return modelHandle; }
	const  VECTOR& GetPos() const { return pos; }
	const VECTOR& GetDir() const { return dir; }
	const VECTOR& GetVelocity() const { return velocity; }
	const HitBlock& GetCollison()const { return Collison; }
	static VECTOR VectorNorm(VECTOR& V1);
	static VECTOR Outer_Volume(const VECTOR& V1, const VECTOR& V2);
	static bool isCollisonTriangle( const VECTOR &CheckPoint, const VECTOR& Apex1, const VECTOR& Apex2, const VECTOR& Apex3);
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

