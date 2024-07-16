#include<math.h>
#include "Object.h"
// 静的定数
// 速度（1=1m、60fps固定として、時速10km）
// 10000m ÷ 時間 ÷ 分 ÷ 秒 ÷ フレーム


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
    ans.x = V1.y* V2.y;
    ans.x = V1.z * V2.z;

    return VECTOR();
}

VECTOR Object::PositiveProjectionVector(const VECTOR& Ground, const VECTOR& V1)
{
    float GroundLength = Ground.x * Ground.x + Ground.y * Ground.y+ Ground.z * Ground.z;
    return VScale(Ground, VDot(Ground, V1) / (GroundLength * GroundLength));
}

bool Object::isCollisonTriangle(const VECTOR& CheckPoint, const VECTOR& Apex1, const VECTOR& Apex2, const VECTOR& Apex3)
{
    //checkから各頂点へのベクトル
    VECTOR Check_to_1 = VSub(CheckPoint,Apex1);
    VECTOR Check_to_2 = VSub(CheckPoint, Apex2);
    VECTOR Check_to_3 = VSub(CheckPoint, Apex3);
    //外積を出す
    VECTOR OuterVolume_1 = Outer_Volume(Check_to_1, Check_to_2);
    VECTOR OuterVolume_2 = Outer_Volume(Check_to_2, Check_to_3);
    VECTOR OuterVolume_3 = Outer_Volume(Check_to_3, Check_to_1);
    
    VECTOR OuterVolume_Multiplication = VMultiplication(VMultiplication(OuterVolume_1, OuterVolume_2), OuterVolume_3);
    ///3つの外積をかけたものと２つの外積の符号が同じか確かめる
    ///2つの外積を確かめることでどのパターンでも符号違いが検出できる
    if (OuterVolume_Multiplication.x<0&&OuterVolume_1.x<0|| OuterVolume_Multiplication.x >= 0 && OuterVolume_1.x >= 0
      && OuterVolume_Multiplication.y < 0 && OuterVolume_1.y < 0 || OuterVolume_Multiplication.y >= 0 && OuterVolume_1.y >= 0
      && OuterVolume_Multiplication.z < 0 && OuterVolume_1.z < 0 || OuterVolume_Multiplication.z >= 0 && OuterVolume_1.z >= 0
        && OuterVolume_Multiplication.x < 0 && OuterVolume_2.x < 0 || OuterVolume_Multiplication.x >= 0 && OuterVolume_2.x >= 0
        && OuterVolume_Multiplication.y < 0 && OuterVolume_2.y < 0 || OuterVolume_Multiplication.y >= 0 && OuterVolume_2.y >= 0
        && OuterVolume_Multiplication.z < 0 && OuterVolume_2.z < 0 || OuterVolume_Multiplication.z >= 0 && OuterVolume_2.z >= 0)
    {
      ///向きが同じなら3角形の内側にポイントがあるからTRUEを返す
        return true;
    }
    ///向きが違うとポイントが3角形外にあるのでFALSEを返す
    return false;
}

void Object::FixPos()
{
  
    pos = VAdd( Collison.UpLeft, VScale(VSub(Collison.UpLeft, Collison.DownRight),0.5f));

}
