#include<math.h>
#include "Object.h"
// �ÓI�萔
// ���x�i1=1m�A60fps�Œ�Ƃ��āA����10km�j
// 10000m �� ���� �� �� �� �b �� �t���[��
const float Object::Scale = 0.002f;

VECTOR Object::VectorNorm(VECTOR& V1)
{
    float size = sqrtf(V1.x * V1.x + V1.y * V1.y + V1.z * V1.z);
    if (V1.x != 0 && V1.y != 0 && V1.z != 0)
    {
        V1 = VNorm(V1);
    }
    else if (V1.x != 0)
    {
        V1.x = V1.x / size;
    }
    else  if (V1.y != 0)
    {

        V1.y = V1.y / size;
    }
    else if (V1.z != 0)
     {
               
        V1.z = V1.z / size;
     }
  
    return V1;
    
}

VECTOR Object::Outer_Volume(const VECTOR& V1, const VECTOR& V2)
{
    VECTOR OuterVolume;
    OuterVolume.x = V1.y * V2.z - V1.z * V2.y;
    OuterVolume.y = V1.z * V2.x - V1.x * V2.z;
    OuterVolume.z = V1.x * V2.y - V1.y * V2.x;

    return OuterVolume;
}

VECTOR Object::VMultiplication(const VECTOR& V1, const VECTOR& V2)
{
    VECTOR ans;
    ans.x = V1.x * V2.x;
    ans.y = V1.y* V2.y;
    ans.z = V1.z * V2.z;

    return ans;
}

VECTOR Object::PositiveProjectionVector(const VECTOR& Ground, const VECTOR& V1)
{

    float GroundLength =VSize(Ground);

  

    return VScale(Ground, VDot(Ground, V1) / (GroundLength * GroundLength));
}

bool Object::isCollisonTriangle(const VECTOR& CheckPoint, const VECTOR& Apex1, const VECTOR& Apex2, const VECTOR& Apex3)
{
    //check����e���_�ւ̃x�N�g��
    VECTOR Check_to_1 = VSub(Apex1,CheckPoint);
    VECTOR Check_to_2 = VSub(Apex2, CheckPoint);
    VECTOR Check_to_3 = VSub(Apex3,CheckPoint);
    //�O�ς��o��
    VECTOR OuterVolume_1 = Outer_Volume(Check_to_1, Check_to_2);
    VECTOR OuterVolume_2 = Outer_Volume(Check_to_2, Check_to_3);
    VECTOR OuterVolume_3 = Outer_Volume(Check_to_3, Check_to_1);
    
    VECTOR OuterVolume_Multiplication = VMultiplication(VMultiplication(OuterVolume_1, OuterVolume_2), OuterVolume_3);
    ///3�̊O�ς����������̂ƂQ�̊O�ς̕������������m���߂�
    ///2�̊O�ς��m���߂邱�Ƃłǂ̃p�^�[���ł������Ⴂ�����o�ł���
    
    ///�����Ⴂ���m���߂�ɂ�3�̊O�ς����������̂ƂQ�̊O�ς����������̂��{�|�ł킩��
    VECTOR Check1 = VMultiplication(OuterVolume_Multiplication, OuterVolume_1);
    VECTOR Check2=VMultiplication(OuterVolume_Multiplication, OuterVolume_2);

        
    if (Check1.x>=0&&Check1.y>=0&&Check1.z>=0&& Check2.x >=0 && Check2.y >=0 && Check2.z>=0)
    {
      ///�����������Ȃ�3�p�`�̓����Ƀ|�C���g�����邩��TRUE��Ԃ�
        return true;
    }
    ///�������Ⴄ�ƃ|�C���g��3�p�`�O�ɂ���̂�FALSE��Ԃ�
    return false;
}

void Object::SetPos(const VECTOR& Pos)
{
    pos = Pos;
}

void Object::SetHitBlock(const HitBlock& HitBlock)
{
    Collison = HitBlock;
}

VECTOR Object::Push_Back_Vector(VECTOR& ChekPoint, const VECTOR& Apex1, const VECTOR& Apex2, const VECTOR& Apex3)
{
    //pos����e���_�ւ̃x�N�g��
    VECTOR Check_to_1 = VSub(Apex1,ChekPoint);
    VECTOR Check_to_2 = VSub(Apex2,ChekPoint);
    VECTOR Check_to_3 = VSub(Apex3,ChekPoint);

    ///�������ɂ͕Ԃ��Ȃ��̂łO�ɂ���
    Check_to_1.z = 0;
    Check_to_2.z = 0;
    Check_to_3.z = 0;

    //����傫���O�p�`�ւ̃x�N�g���ɂ���@�����Ԃ�����Ȃ�����
    //float�^�̐��̍ŏ��l
    Check_to_1 = VAdd(Check_to_1, VScale(Object::VectorNorm(Check_to_1), 0.0000001));
    Check_to_2 = VAdd(Check_to_2, VScale(Object::VectorNorm(Check_to_2), 0.0000001));
    Check_to_3 = VAdd(Check_to_3, VScale(Object::VectorNorm(Check_to_3), 0.0000001));


    //�ӂ̃x�N�g�������߂�
    VECTOR Around_1_2 = VSub(Apex2, Apex1);
    VECTOR Around_1_3 = VSub(Apex3, Apex1);
    VECTOR Around_3_2 = VSub(Apex2, Apex3);

    //�ӂ���pos�ւ̐����������ʒu�����߂�
    VECTOR Pos_Intersect_Around1_2 = PositiveProjectionVector(Around_1_2, Check_to_1);
    VECTOR Pos_Intersect_Around1_3 = PositiveProjectionVector(Around_1_3, Check_to_1);
    VECTOR Pos_Intersect_Around3_2 = PositiveProjectionVector(Around_3_2, Check_to_3);

    //�ӂ���pos�ւ̐����̌�_�ւ̃x�N�g�������߂�
    VECTOR  Pos_to_Around1_2 = VSub(Pos_Intersect_Around1_2,ChekPoint);
    VECTOR  Pos_to_Around1_3 = VSub(Pos_Intersect_Around1_3,ChekPoint);
    VECTOR  Pos_to_Around3_2 = VSub(Pos_Intersect_Around3_2,ChekPoint);


    ///�ŏ��l�̃x�N�g����Ԃ�
    if (VSize(Pos_to_Around1_2) <= VSize(Pos_to_Around1_3))
    {
        if (VSize(Pos_to_Around1_2) <= VSize(Pos_to_Around3_2))
        {
            return Pos_to_Around1_2;
        }
        else
        {
            return  Pos_to_Around3_2;
        }
    }
    else
    {
        if (VSize(Pos_to_Around1_3) <= VSize(Pos_to_Around3_2))
        {
            return Pos_to_Around1_3;
        }
        else
        {
            return  Pos_to_Around3_2;
        }
    }
}

bool Object::isEqual_VECTOR(const VECTOR& V1, const VECTOR& V2)
{
    if (V1.x == V2.x)
    {
        if (V1.y == V2.y)
        {
            if (V1.z == V2.z)
            {
                return true;
            }
        }

    }
    return false;
}

void Object::Initialization_HitBlock()
{
    Collison.DownLeft.x = pos.x +width/2;
    Collison.DownLeft.y = pos.y - height/2;
    Collison.DownLeft.z = pos.z;

    Collison.UpLeft.x = pos.x + width/2;
    Collison.UpLeft.y = pos.y + height/2;
    Collison.UpLeft.z = pos.z; 

    Collison.DownRight.x = pos.x - width/2;
    Collison.DownRight.y = pos.y - height/2;
    Collison.DownRight.z = pos.z;

    Collison.UpRight.x = pos.x - width/2;
    Collison.UpRight.y = pos.y + height/2;
    Collison.UpRight.z = pos.z;
  

}

void Object::SetDir(const VECTOR& Dir)
{
    dir = Dir;
}

void Object::SetSlope(const VECTOR& Slope)
{
    slope = Slope;
}

VECTOR Object::RotFreeAxis(VECTOR& V1,const VECTOR& Axis,const MATRIX& Power)
{
    ///Axis�����_�Ƃ���x�N�g������ʏ�̃x�N�g����
    MATRIX Axis_to_Origin = MGetAxis1(VGet(1, 0, 0), VGet(0, 1, 0), VGet(0, 0, 1), Axis);
    ///�ʏ�̃x�N�g������Axis�����_�Ƃ���x�N�g����
    MATRIX Origin_to_Axis = MGetAxis2(VGet(1, 0, 0), VGet(0, 1, 0), VGet(0, 0, 1), Axis);
    //////Axis�����_�Ƃ���x�N�g������ʏ�̃x�N�g����
    V1 = VTransform(V1, Origin_to_Axis);
    ///Power��������
    V1 = VTransform(V1, Power);
    ///�ʏ�̃x�N�g������Axis�����_�Ƃ���x�N�g����
    V1 = VTransform(V1, Axis_to_Origin);

    return V1;

}



void Object::FixPos()
{
 
    //UpLeft��Collison�̑Ίp�����𑫂�
    pos = VAdd( Collison.UpLeft, VScale(VSub(Collison.DownRight, Collison.UpLeft),0.5f));
  

}

void Object::FixHitBlock()
{
    Collison.DownLeft = VAdd(Collison.DownLeft, velocity);
    Collison.DownRight = VAdd(Collison.DownRight, velocity);
    Collison.UpLeft = VAdd(Collison.UpLeft, velocity);
    Collison.UpRight = VAdd(Collison.UpRight, velocity);

}
