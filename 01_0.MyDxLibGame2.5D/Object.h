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
	

	///�g������
	static VECTOR VectorNorm(VECTOR& V1);
	static VECTOR Outer_Volume(const VECTOR& V1, const VECTOR& V2);
	static VECTOR VMultiplication(const VECTOR& V1, const VECTOR& V2);
	static VECTOR PositiveProjectionVector(const VECTOR& Ground, const VECTOR& V1);
	static bool isCollisonTriangle( const VECTOR &CheckPoint, const VECTOR& Apex1, const VECTOR& Apex2, const VECTOR& Apex3);
    static VECTOR Push_Back_Vector(VECTOR&ChekPoint, const VECTOR& Apex1, const VECTOR& Apex2, const VECTOR& Apex3);
	static bool isEqual_VECTOR(const VECTOR& V1, const VECTOR& V2);
	/// <summary>
	/// �w��̎��ŉ�]������
	/// </summary>
	/// <param name="V1">�ω�������VECTOR</param>
	/// <param name="Axis">���ƂȂ�VERCTOR</param>
	/// <param name="Power">��]�����߂�s��</param>
	/// <returns></returns>
	static VECTOR RotFreeAxis(VECTOR& V1,const  VECTOR& Axis,const MATRIX& Power);
	
	/// <summary>
	/// HitBlock����pos���t�Z����
	/// </summary>
	void FixPos();
	/// <summary>
	/// pos����HitBlock���t�Z����
	/// </summary>
	void FixHitBlock();
protected:
	int		modelHandle;	// ���f���n���h��.
	VECTOR	pos;			// �|�W�V����.
	VECTOR	velocity;		// �ړ���.
	VECTOR	dir;			// �ړ�����.
	VECTOR  slope;          //object�̌X��
	HitBlock Collison;      //�����蔻��u���b�N
	float width;
	float height;
	float Depth;
	static const float Scale;
	
};

