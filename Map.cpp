// 2023 Takeru MapChipNumYui All Rights Reserved.
#include<vector>
#include"Object.h"
#include "Map.h"
#include "DxLib.h"
#include "WorldSprite.h"

const float Map::ChipSize = 0.725f;
const int Map::ChipPiMapChipNumXelSize = 32;
#define MAMapChipNumX_LINE_LENGTH 1024
#define MAMapChipNumX_FIELDS 10
/// <summarMapChipNumY>
/// コンストラクタ
/// </summarMapChipNumY>
Map::Map()
	: sprite{ (nullptr) }
{
	
}

/// <summarMapChipNumY>
/// デストラクタ
/// </summarMapChipNumY>
Map::~Map()
{
	for (int i = 0; i < MapChipNumY; i++)
	{
		if (sprite[i] != nullptr)
		{

			delete sprite;


		}
	}
}
/// <summarMapChipNumY>
/// mapデータをCSVファイルから持ってくる
/// </summarMapChipNumY>
void Map::DownLoad()
{

	OriginMap = NULL;
	MapChipNumX = 0;
	MapChipNumY = 0;
	///FILEのポインタ(ファイルのさしている位置を出す）
	FILE* fp;
	errno_t err;

	///ファイルを開く
	
	err = fopen_s(&fp, "./MapTiles/2.5.csv", "rt");
    //読み込みエラー
	if (err)
	{
		printf("ファイルを開けません");

	}

	///最初の行を読み
	char buff[MAMapChipNumX_LINE_LENGTH];
	fgets(buff, MAMapChipNumX_LINE_LENGTH, fp);
	///カンマを数える
	char c;
	c = fgetc(fp);

	while (c != '\n' && c != EOF)
	{
   // 読み取った文字がカンマなら1つカウント増やす
    c = fgetc(fp);
		    
	if (c == ',')
	{
	        MapChipNumX++;
	 }
     }

	///カンマの数を1行の大きさとする
	int bufferLen = MapChipNumX * 6 + 1;
	///1行のデータとしての大きさを出す
	char* buf = new char[bufferLen];
	char* ptmp = buf;
	///ファイルポインタを先頭に戻す
	fseek(fp, 0, SEEK_SET);
	
	///1行分の大きさを利用して列を出す
	bool firstRow = true;
	while (fgets(buf, bufferLen - 1, fp) != NULL)
	{
		MapChipNumY++;
	}
	///出た大きさを動的確保する
	OriginMap = new int* [MapChipNumY];
	//WorldSptiteのポインタをいれる配列の先頭ポインタMapChipNumY個
	sprite = new WorldSprite ** [MapChipNumY];
	
	for ( int iMapChipNumY = 0; iMapChipNumY < MapChipNumY; iMapChipNumY++)
	{
		OriginMap[iMapChipNumY] = new int[MapChipNumX];
		///sprite[iMapChipNumY]にWorldSptiteのポインタをいれるをMapChipNumX個
		sprite[iMapChipNumY] = new WorldSprite*[MapChipNumX];
	}
	///ファイルポインタを先頭に戻す
	fseek(fp, 0, SEEK_SET);

	///ファイルのデータを移す
	char* readPoint;
	char* firstPoint;
	for (int iMapChipNumY = 0; iMapChipNumY < MapChipNumY; iMapChipNumY++)
	{
		// 1行取り込み
		fgets(buf, bufferLen - 1, fp);
		readPoint = firstPoint = buf;
		for (int iMapChipNumX = 0; iMapChipNumX < MapChipNumX; iMapChipNumX++)
		{
			//カンマまでreadPointの位置を進める
			while (',' != *readPoint && '\n' != *readPoint)
			{
				readPoint++;
			}
			// カンマをNULL文字に置き換え
			*readPoint = '\0';
			//この時点でfirstPoint - readPoint間で文字列が完成するので数値に変換
			OriginMap[iMapChipNumY][iMapChipNumX] = atoi(firstPoint);
			//次のデータ読み取り位置まで進める
			readPoint++;
			firstPoint = readPoint;
		}
	}
	///ファイルを閉じる
	fclose(fp);
	// バッファ開放
	delete[] buf;



}

/// <summarMapChipNumY>
/// ロード
/// </summarMapChipNumY>
void Map::Load()
{
	MapData = OriginMap;
	// とりあえずマップロード
	int chipGraph = LoadGraph("MapTiles/Assets/Map2.5d.png");
	
	

	// マップチップを表示するためのクラスWorldSpriteに
	// 元画像のハンドル、１チップあたりのサイズ、表示するマップチップ番号を渡す
	for (int i = 0; i <  MapChipNumY; i++)
	{
		for (int j = 0; j <MapChipNumX; j++)
		{


			sprite[i][j] = new WorldSprite();
			sprite[i][j]->Initialize(chipGraph, ChipPiMapChipNumXelSize, MapData[i][j]);
		
			// マップチップの位置と大きさを設定
			VECTOR chipHalfOffset = VGet(-Map::ChipSize * 0.5f, -Map::ChipSize * 0.5f, 0);					// マップチップの半分サイズ左下にずらすオフセット
			VECTOR chipPos = VAdd(VGet((j+ 1)*ChipSize,( MapChipNumY - i)* ChipSize, 0), chipHalfOffset);	// 真ん中ピボットなのでマッチップ半分サイズずらす+地面なので一つ下に
			sprite[i][j]->SetTransform(chipPos, Map::ChipSize);
			///画像の頂点を設定
			sprite[i][j]->SetApex(chipPos, MapData[i][j],Map::ChipSize);
		}
	}
}

/// <summarMapChipNumY>
/// 更新
/// </summarMapChipNumY>
void Map::Update()
{
	// 処理なし
}

void Map::Draw(const VECTOR& Ppos)
{
	for (int i = 0; i < MapChipNumY; i++)
	{
		for (int j = 0; j < MapChipNumX; j++)
		{
			VECTOR Mpos = sprite[i][j]->GetPos();
			if (Mpos.x<Ppos.x + 12 && Mpos.x>Ppos.x - 12)
			{
				sprite[i][j]->Draw();
				const VECTOR* Apex = sprite[i][j]->GetApex();
				DrawTriangle3D(Apex[0], Apex[1], Apex[2], GetColor(255, 0, 0), TRUE);
			}
		}
		// ゆくゆくはカメラを持ってきて、カメラ範囲以外表示しないように

	}
}

/// <summarMapChipNumY>
/// 描画
/// </summarMapChipNumY>
void Map::Draw()
{
	for (int i = 0; i <  MapChipNumY; i++)
	{
		for (int j = 0; j < MapChipNumX; j++)
		{
			sprite[i][j]->Draw();
			const VECTOR* Apex=sprite[i][j]->GetApex();
			DrawTriangle3D(Apex[0], Apex[1], Apex[2],GetColor(255,0,0),TRUE);
		}
		// ゆくゆくはカメラを持ってきて、カメラ範囲以外表示しないように
		
	}
}

void Map::HitCalc(Object& object)
{
	
	HitBlock Collison = object.GetCollison();
	bool isChengeBlock = false;
	///一点ずつ当たってるか調べる
	HITRESULT_LINE DownHitSensor;
	HITRESULT_LINE UpHitSensor;
	HITRESULT_LINE RightHitSensor;
	HITRESULT_LINE LeftHitSensor;

	for (int Y = 0; MapChipNumY >Y; Y++)
	{

		for (int X = 0; MapChipNumX > X; X++)
		{
			if (MapData[Y][X] != -1)
			{
				///sprite[MapChipNumX][MapChipNumY]の頂点を取得
				const VECTOR* Apex = sprite[Y][X]->GetApex();
				



				//下線
				DownHitSensor= HitCheck_Line_Triangle(Collison.DownLeft, Collison.DownRight, Apex[0], Apex[1], Apex[2]);
				if (DownHitSensor.HitFlag)
				{
					VECTOR Push_BackPower;
					VECTOR R_Push_BackPower;
					VECTOR L_Push_BackPower;
					
					bool TouchRight= Object::isCollisonTriangle(Collison.DownRight, Apex[0], Apex[1], Apex[2]);
					bool TouchLeft= Object::isCollisonTriangle(Collison.DownLeft, Apex[0], Apex[1], Apex[2]);

					Push_BackPower = Object::Push_Back_Vector(DownHitSensor.Position, Apex[0], Apex[1], Apex[2]);
					R_Push_BackPower = Object::Push_Back_Vector(Collison.DownRight, Apex[0], Apex[1], Apex[2]);
					L_Push_BackPower = Object::Push_Back_Vector(Collison.DownLeft, Apex[0], Apex[1], Apex[2]);

				
					
					//辺の長さを比
					float OLL = VSize( VSub(Collison.DownRight, Collison.DownLeft));
					float L_S = VSize( VSub(Collison.DownLeft, DownHitSensor.Position));
					float R_S = VSize(VSub(Collison.DownRight, DownHitSensor.Position));

					float Magnifivation_From_OLL_to_L = L_S / OLL;
					float Magnifivation_From_OLL_to_R = R_S / OLL;

					if (VSize(VSub(Collison.DownRight,DownHitSensor.Position))==0)
					{
						Collison.DownRight = VAdd(Collison.DownRight, R_Push_BackPower);
						Collison.UpRight = VAdd(Collison.UpRight, R_Push_BackPower);
						Collison.DownLeft = VAdd(Collison.DownLeft, R_Push_BackPower);
						Collison.UpLeft = VAdd(Collison.UpLeft, R_Push_BackPower);
					}
					else if (VSize(VSub(Collison.DownLeft, DownHitSensor.Position)) == 0)
					{
						Collison.DownRight = VAdd(Collison.DownRight, L_Push_BackPower);
1;						Collison.UpRight = VAdd(Collison.UpRight, L_Push_BackPower);
						Collison.DownLeft = VAdd(Collison.DownLeft, L_Push_BackPower);
						Collison.UpLeft = VAdd(Collison.UpLeft, L_Push_BackPower);
					}
					else if (TouchRight && !TouchLeft)
					{
						Collison.DownRight = VAdd(Collison.DownRight, R_Push_BackPower);
						Collison.UpRight = VAdd(Collison.UpRight,R_Push_BackPower);
						Collison.DownLeft = VAdd(Collison.DownLeft, VScale(R_Push_BackPower, Magnifivation_From_OLL_to_L*-1));
						Collison.UpLeft = VAdd(Collison.UpLeft, VScale(R_Push_BackPower, Magnifivation_From_OLL_to_L*-1));

					}
					else if (!TouchRight && TouchLeft)
					{
						Collison.DownLeft = VAdd(Collison.DownRight, L_Push_BackPower);
						Collison.UpLeft = VAdd(Collison.UpRight, L_Push_BackPower);
						Collison.DownRight = VAdd(Collison.DownLeft, VScale(R_Push_BackPower, Magnifivation_From_OLL_to_R*-1));
						Collison.UpRight = VAdd(Collison.UpLeft, VScale(R_Push_BackPower, Magnifivation_From_OLL_to_R*-1));
					}

					else if(TouchRight && TouchLeft)
					{
						Collison.DownLeft = VAdd(Collison.DownRight, L_Push_BackPower);
						Collison.UpLeft = VAdd(Collison.UpRight, L_Push_BackPower);
						Collison.DownRight = VAdd(Collison.DownRight, R_Push_BackPower);
						Collison.UpRight = VAdd(Collison.UpRight, R_Push_BackPower);
						
					}
					else
					{
						///Push_BackPowerを比でかけたものにかける
						Collison.DownLeft = VSub(Collison.DownLeft, Push_BackPower);
						Collison.UpLeft = VSub(Collison.UpLeft, Push_BackPower);
						Collison.DownRight = VSub(Collison.DownRight, Push_BackPower);
						Collison.UpRight = VSub(Collison.UpRight, Push_BackPower);
					}
					isChengeBlock = true;
				
					break;
					
				}
				
					//上線
					UpHitSensor = HitCheck_Line_Triangle(Collison.UpLeft, Collison.UpRight, Apex[0], Apex[1], Apex[2]);
					if (UpHitSensor.HitFlag)
					{
						VECTOR Push_BackPower;
						Push_BackPower = Object::Push_Back_Vector(UpHitSensor.Position, Apex[0], Apex[1], Apex[2]);




						Collison.DownLeft = VSub(Collison.DownLeft, Push_BackPower);
						Collison.UpLeft = VSub(Collison.UpLeft, Push_BackPower);
						Collison.DownRight = VSub(Collison.DownRight, Push_BackPower);
						Collison.UpRight = VSub(Collison.UpRight, Push_BackPower);
						break;
					}
					///左辺

					LeftHitSensor = HitCheck_Line_Triangle(Collison.UpLeft, Collison.DownLeft, Apex[0], Apex[1], Apex[2]);
					if (LeftHitSensor.HitFlag)
					{
						VECTOR Push_BackPower;
						Push_BackPower = Object::Push_Back_Vector(LeftHitSensor.Position, Apex[0], Apex[1], Apex[2]);




						Collison.DownLeft = VSub(Collison.DownLeft, Push_BackPower);
						Collison.UpLeft = VSub(Collison.UpLeft, Push_BackPower);
						Collison.DownRight = VSub(Collison.DownRight, Push_BackPower);
						Collison.UpRight = VSub(Collison.UpRight, Push_BackPower);
						break;

					}

					///右辺

					RightHitSensor = HitCheck_Line_Triangle(Collison.UpRight, Collison.DownRight, Apex[0], Apex[1], Apex[2]);
					if (RightHitSensor.HitFlag)
					{
						VECTOR Push_BackPower;
						Push_BackPower = Object::Push_Back_Vector(RightHitSensor.Position, Apex[0], Apex[1], Apex[2]);





						Collison.DownLeft = VSub(Collison.DownLeft, Push_BackPower);
						Collison.UpLeft = VSub(Collison.UpLeft,Push_BackPower);
						Collison.DownRight = VSub(Collison.DownRight, Push_BackPower);
						Collison.UpRight = VSub(Collison.UpRight, Push_BackPower);

						break;
					}
				
				
				

			}

		}


	}
	
	///下辺を表すベクトル LR
	VECTOR LR = VSub(Collison.DownRight,Collison.DownLeft);
	if (isChengeBlock)
	{
		///下の辺の高低差を求める
		
		
		/////LR と　Collison.DownRight　の内積／二つのSizeをかけたもの　でCosの値を求める
		float Cos_LR = VDot(LR, Collison.DownLeft) / (VSize(LR) * VSize(Collison.DownLeft));
		/////ACosで角度を求める
		float rag =acosf(Cos_LR);
		/////誤差をなくすため小数点代2以下を切り捨て
		////小数点第一を1の位に持ってくる
		rag = rag * 100;
		/////小数点以下を切り上げて
		rag = ceilf(rag+1);
		/////元の桁に戻す
	   rag = rag / 100;
		/////出た値をslope(傾き）に代入する
		object.SetSlope(VGet(0, -1.f, rag/2));
		////傾きを元に戻す
	
	///傾ける値から回転力を追加する
		///右下
		Collison.DownRight = VAdd(Collison.DownLeft, VGet(object.GetWidth(), 0, 0));
		Collison.DownRight = Object::RotFreeAxis(Collison.DownRight, Collison.DownLeft, MGetRotZ(rag / 2));
        ////右上
		Collison.UpRight = VAdd(Collison.DownRight, VGet(0, object.GetHeight(), 0));
		Collison.UpRight = Object::RotFreeAxis(Collison.UpRight,Collison.DownRight,MGetRotZ(rag/2));
		////左上
		Collison.UpLeft = VAdd(Collison.DownLeft, VGet(0, object.GetHeight(), 0));
		Collison.UpLeft = Object::RotFreeAxis(Collison.UpLeft, Collison.DownLeft, MGetRotZ(rag / 2));

		


		
	}
	

	
	///修正された物がめり込んでないか調べる
	/// ///めり込んでないか調べるためもう一周
	for (int Y = 0; MapChipNumY < Y; Y++)
	{

		for (int X = 0; X > MapChipNumX; X++)
		{


			if (MapData[Y][X] != -1)
			{
				///sprite[MapChipNumX][MapChipNumY]の頂点を取得
				const VECTOR* Apex = sprite[MapChipNumY][MapChipNumX]->GetApex();
				///線の判定
				DownHitSensor = HitCheck_Line_Triangle(Collison.DownRight, Collison.DownLeft, Apex[0], Apex[1], Apex[2]);
				RightHitSensor = HitCheck_Line_Triangle(Collison.UpRight, Collison.DownRight, Apex[0], Apex[1], Apex[2]);
				UpHitSensor = HitCheck_Line_Triangle(Collison.UpLeft, Collison.UpRight, Apex[0], Apex[1], Apex[2]);
				LeftHitSensor = HitCheck_Line_Triangle(Collison.UpLeft, Collison.DownLeft, Apex[0], Apex[1], Apex[2]);
				///めり込んでないか調べる
				if (DownHitSensor.HitFlag || UpHitSensor.HitFlag || RightHitSensor.HitFlag || LeftHitSensor.HitFlag)
				{
					///押し返しを元に戻して
					Collison = object.GetCollison();
					///動く前に戻す
					Collison.DownLeft = VSub(Collison.DownLeft, object.GetVelocity());
					Collison.UpLeft = VSub(Collison.UpLeft, object.GetVelocity());
					Collison.DownRight = VSub(Collison.DownRight, object.GetVelocity());
					Collison.UpRight = VSub(Collison.UpRight, object.GetVelocity());
					isChengeBlock = false;
					break;



				}


			}

		}


	}
	///オブジェクトの方に代入
	object.SetHitBlock(Collison);
	///posを修正
	object.FixPos();

}



