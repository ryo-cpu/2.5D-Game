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

	virtual void Update()abstract;			// �X�V.
	virtual void Draw()abstract;			// �`��.
	// ���f���n���h���̎擾.
	int GetModelHandle() const { return modelHandle; }
	const  VECTOR& GetPos() const { return pos; }
	const VECTOR& GetDir() const { return dir; }
	const VECTOR& GetVelocity() const { return velocity; }
	const HitBlock& GetCollison()const { return Collison; }
	static VECTOR VectorNorm(VECTOR& V1);
	static VECTOR Outer_Volume(const VECTOR& V1, const VECTOR& V2);
	static VECTOR VMultiplication(const VECTOR& V1, const VECTOR& V2);
	static VECTOR PositiveProjectionVector(const VECTOR& Ground, const VECTOR& V1);
	static bool isCollisonTriangle( const VECTOR &CheckPoint, const VECTOR& Apex1, const VECTOR& Apex2, const VECTOR& Apex3);
	void SetPos(const VECTOR &Pos);
	void SetHitBlock(const HitBlock& HitBlock);
<<<<<<< HEAD
	VECTOR Push_BackPos(const VECTOR& Apex1, const VECTOR& Apex2, const VECTOR& Apex3);
=======
>>>>>>> e5d3c409a3bdf42c940d2ca826fbce199c2c1994
	/// <summary>
	/// HitBlock����pos���t�Z����
	/// </summary>
	void FixPos();
	void FixHitBlock();
protected:
	int		modelHandle;	// ���f���n���h��.
	VECTOR	pos;			// �|�W�V����.
	VECTOR	velocity;		// �ړ���.
	VECTOR	dir;			// ��]����.
	HitBlock Collison;      //�����蔻��u���b�N
	int width;
	int height;
	int Depth;

	
};

