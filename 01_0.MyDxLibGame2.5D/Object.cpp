#include<math.h>
#include "Object.h"
// �ÓI�萔
// ���x�i1=1m�A60fps�Œ�Ƃ��āA����10km�j
// 10000m �� ���� �� �� �� �b �� �t���[��


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

bool Object::isCollisonTriangle(const VECTOR& CheckPoint, const VECTOR& Apex1, const VECTOR& Apex2, const VECTOR& Apex3)
{
    //check����e���_�ւ̃x�N�g��
    VECTOR Check_to_1 = VSub(CheckPoint,Apex1);
    VECTOR Check_to_2 = VSub(CheckPoint, Apex2);
    VECTOR Check_to_3 = VSub(CheckPoint, Apex3);
    //�O�ς��o��
    VECTOR OuterVolume_1 = Outer_Volume(Check_to_1, Check_to_2);
    VECTOR OuterVolume_2 = Outer_Volume(Check_to_2, Check_to_3);
    VECTOR OuterVolume_3 = Outer_Volume(Check_to_3, Check_to_1);
    ///�P�ʃx�N�g����
    OuterVolume_1 = VectorNorm(OuterVolume_1);
    OuterVolume_2 = VectorNorm(OuterVolume_2);
    OuterVolume_3 = VectorNorm(OuterVolume_3);

    VECTOR  OuterVolume_Scale3 = VScale(OuterVolume_1, 3);
    ///�����������Ȃ�O�ςR�𑫂������̂ƊO�ς��O�ς̐������������̂Ɠ����ɂȂ�̂Ŋm�F����
    if (OuterVolume_1.x + OuterVolume_2.x + OuterVolume_3.x == OuterVolume_Scale3.x
     && OuterVolume_1.y + OuterVolume_2.y + OuterVolume_3.y == OuterVolume_Scale3.y
     && OuterVolume_1.z + OuterVolume_2.z + OuterVolume_3.z == OuterVolume_Scale3.z)
    {
      ///�����������Ȃ�3�p�`�̓����Ƀ|�C���g�����邩��TRUE��Ԃ�
        return true;
    }
    ///�������Ⴄ�ƃ|�C���g��3�p�`�O�ɂ���̂�FALSE��Ԃ�
    return false;
}
