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
	const VECTOR& GetSlope()const { return slope; }
	const HitBlock& GetCollison()const { return Collison; }
	const float& GetWidth()const { return width*Scale;}
	const float& GetHeight()const { return height; }
	const float& GetDepth()const { return Depth; }
	void SetHitBlock(const HitBlock& HitBlock);
	void SetPos(const VECTOR& Pos);
	void Initialization_HitBlock();
	void SetDir(const VECTOR& Dir);
	void SetSlope(const VECTOR& Slope);
	float GetScale()const { return Scale; }
	

	///使う道具
	static VECTOR VectorNorm(VECTOR& V1);
	static VECTOR Outer_Volume(const VECTOR& V1, const VECTOR& V2);
	static VECTOR VMultiplication(const VECTOR& V1, const VECTOR& V2);
	static VECTOR PositiveProjectionVector(const VECTOR& Ground, const VECTOR& V1);
	static bool isCollisonTriangle( const VECTOR &CheckPoint, const VECTOR& Apex1, const VECTOR& Apex2, const VECTOR& Apex3);
    static VECTOR Push_Back_Vector(VECTOR&ChekPoint, const VECTOR& Apex1, const VECTOR& Apex2, const VECTOR& Apex3);
	static bool isEqual_VECTOR(const VECTOR& V1, const VECTOR& V2);
	/// <summary>
	/// 指定の軸で回転させる
	/// </summary>
	/// <param name="V1">変化させるVECTOR</param>
	/// <param name="Axis">軸となるVERCTOR</param>
	/// <param name="Power">回転を決める行列</param>
	/// <returns></returns>
	static VECTOR RotFreeAxis(VECTOR& V1,const  VECTOR& Axis,const MATRIX& Power);
	
	/// <summary>
	/// HitBlockからposを逆算する
	/// </summary>
	void FixPos();
	/// <summary>
	/// posからHitBlockを逆算する
	/// </summary>
	void FixHitBlock();
protected:
	int		modelHandle;	// モデルハンドル.
	VECTOR	pos;			// ポジション.
	VECTOR	velocity;		// 移動力.
	VECTOR	dir;			// 移動方向.
	VECTOR  slope;          //objectの傾き
	HitBlock Collison;      //当たり判定ブロック
	float width;
	float height;
	float Depth;
	static const float Scale;
	
};

