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

	virtual void Update()abstract;			// �X�V.
	virtual void Draw()abstract;			// �`��.
	// ���f���n���h���̎擾.
	int GetModelHandle() const { return modelHandle; }
	const VECTOR& GetPos() const { return pos; }
	const VECTOR& GetDir() const { return dir; }
	const VECTOR& GetVelcity() const { return velocity; }
	const HitBlock& GetCollison()const { return Collison; }
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

