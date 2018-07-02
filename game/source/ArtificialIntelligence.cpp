#include "Enemy.h"
#include "Player.h"

#include <vector>


/*
ノード位置
可変長配列
*/
Vector3	NodeLootPoints[] =
{
	//0~10
	{ -26.8f  ,1.0f  ,   236.7f },//0
	{ -35.1f  ,1.0f  ,  1059.2f },//1
	{ -47.2f  ,1.0f  ,  2058.1f },//2
	{ -56.7f  ,1.0f  , 3044.4f },//3
	{ -64.6f  ,1.0f  , 3856.1f },//4
	{ -73.0f  ,1.0f  , 4730.8f },//5
	{ -32.9f  ,1.0f  , 5004.4f },//6
	{ 145.8f  ,1.0f  , 5145.1f },//7
	{ 343.2f  ,1.0f  , 5089.5f },//8
	{ 447.4f  ,1.0f  , 4853.7f },//9
	{ 448.9f  ,1.0f  , 4663.3f },//10
								 //11~20
	{ 446.8f ,1.0f  , 4049.6f },//11
	{ 445.5f ,1.0f  , 3644.6f },//12
	{ 484.1f ,1.0f  , 3459.1f },//13
	{ 654.2f ,1.0f  , 3312.3f },//14
	{ 945.5f, 1.0f  , 3338.2f },//15
	{ 1161.8f ,1.0f , 3481.6f },//16
	{ 1253.8f ,1.0f , 3717.2f },//17
	{ 1245.4f ,1.0f , 4074.7f },//18
	{ 1236.0f ,1.0f , 4751.4f },//19
	{ 1227.2f ,1.0f , 5440.3f },//20
								//21~30
	{ 1218.1f ,1.0f , 6016.1f },//21
	{ 1182.2f ,1.0f , 6308.6f },//22
	{ 1187.1f ,1.0f , 6624.1f },//23
	{ 1276.8f ,1.0f , 6798.5f },//24
	{ 1407.1f ,1.0f , 6903.3f },//25
	{ 1577.5f ,1.0f , 6944.8f },//26
	{ 1769.8f ,1.0f , 6950.1f },//27
	{ 2007.5f ,1.0f , 6912.4f },//28
	{ 2221.3f ,1.0f , 6870.8f },//29
	{ 2378.6f ,1.0f , 6928.5f },//30
								//31~40
	{ 2542.4f ,1.0f , 7092.7f },//31
	{ 3006.6f ,1.0f , 7689.3f },//32
	{ 3458.3f ,1.0f , 8261.4f },//33
	{ 3867.7f ,1.0f , 8780.1f },//34
	{ 4309.4f ,1.0f , 9339.6f },//35
	{ 4593.2f ,1.0f , 9693.5f },//36
	{ 5047.4f ,1.0f , 10231.0f },//37
	{ 5496.3f ,1.0f , 10763.6f },//38
	{ 5696.8f ,1.0f , 11047.3f },//39
	{ 5889.2f ,1.0f , 11175.4f },//40
								 //41~50
	{ 6060.4f ,1.0f , 11180.9f },//41
	{ 6208.6f ,1.0f , 11017.8f },//42
	{ 6244.6f ,1.0f , 10795.9f },//43
	{ 6163.6f ,1.0f , 10578.9f },//44
	{ 6001.0f ,1.0f , 10285.0f },//45
	{ 5683.7f ,1.0f , 9789.22f },//46
	{ 5414.7f ,1.0f , 9369.40f },//47
	{ 5184.6f ,1.0f , 8935.95f },//48
	{ 4889.0f ,1.0f , 8301.28f },//49
	{ 4703.9f ,1.0f , 7873.33f },//50
								 //51~60
	{ 4501.8f ,1.0f , 7405.7f },//51
	{ 3952.4f ,1.0f , 6532.6f },//52
	{ 3092.8f ,1.0f , 5153.2f },//53
	{ 2854.4f ,1.0f , 4726.7f },//54
	{ 2840.8f ,1.0f , 4484.8f },//55
	{ 2994.7f ,1.0f , 4207.7f },//56
	{ 3330.2f ,1.0f , 3897.5f },//57
	{ 3614.6f ,1.0f , 3645.7f },//58
	{ 3781.9f ,1.0f , 3398.0f },//59
	{ 3862.0f ,1.0f , 3092.7f },//60
								//61~70
	{ 3827.4f ,1.0f , 2627.1f },//61
	{ 3692.9f ,1.0f , 2200.0f },//62
	{ 3531.5f ,1.0f , 1854.7f },//63
	{ 3338.2f ,1.0f , 1466.5f },//64
	{ 3126.9f ,1.0f , 1026.8f },//65
	{ 3028.9f ,1.0f ,  708.2f },//66
	{ 2946.3f ,1.0f ,   77.1f },//67
	{ 2916.7f ,1.0f , -645.6f },//68
	{ 2895.5f ,1.0f , -1338.3f },//69
	{ 2851.4f ,1.0f , -1949.7f },//70
								 //71~80
	{ 2665.7f ,1.0f , -2615.0f },//71
	{ 2390.8f ,1.0f , -3075.2f },//72
	{ 1919.1f ,1.0f , -3491.0f },//73
	{ 1562.5f ,1.0f , -3794.0f },//74
	{ 1205.0f ,1.0f , -3863.0f },//75
	{ 728.40f ,1.0f , -3872.4f },//76
	{ 386.40f ,1.0f , -3873.8f },//77
	{ 140.12f ,1.0f , -3798.9f },//78
	{ 41.411f ,1.0f , -3664.9f },//79
	{ 9.1062f ,1.0f , -3379.3f },//80
};

//可変長配列無限にループしやすくなる為の最大取得変数
const int NodeMaxNumber = sizeof NodeLootPoints / sizeof NodeLootPoints[0];


/*

*/		
void Car_A_E::AI_System()
{
	AI_AccelMode();
	AI_NodeSystem();
	AI_HandleingMode();

}

void Car_A_E::AI_NodeSystem()
{
	//VectorListでnode確保
	std::vector<Vector3>node;

	//ノード初期化
	node.resize(NodeMaxNumber);

	//番号合わせ
	for (int i = 0;i < NodeMaxNumber;i++)
	{
		node[i] = NodeLootPoints[i];
	}

	//ノードと現在座標のベクトル
	Vector3 RangeVector;
	RangeVector = node[CatchNodeNumber] - pos;
	
	//向きを座標へ
	Vector3 VectorAngle;
	VectorAngle.x = sinf(angle.y);
	VectorAngle.y = 0.0f;
	VectorAngle.z = cosf(angle.y);
	//合成
	Vector3 FrontPoint = VectorAngle ;

	//外積
	Vector3Cross(cross, FrontPoint,RangeVector);
	//内積
	float dot;
	dot = Vector3Dot(FrontPoint, RangeVector);

	//詳細関係
	float L1 = sqrtf(pow(VectorAngle.x, 2) + pow(VectorAngle.z, 2));
	float L2 = sqrtf(pow(RangeVector.x, 2) + pow(RangeVector.z, 2));

	//視野変数
	float cosValue = dot / (L1*L2);

	//ズレの位置をハンドル回す強さに変える
	float distAngle = 1.0f - cosValue;
	if (distAngle > 0.05f)distAngle = 0.05f;

	//ウェイポイントの設定
	Vector3 NextWaypointVector;
	if (CatchNodeNumber <= NodeMaxNumber)//最大配列以下
	{
		NextWaypointVector = node[CatchNodeNumber + 1] - pos;
	}
	else
	{
		NextWaypointVector = node[0] - pos;//最大の次は0に返す為
	}

	//長さを取得
	float NextWayPointVectorLength = NextWaypointVector.Length();//  次のwaypointと車両の距離
	float WayPointVectorLength = RangeVector.Length();			 //現在のwaypointと車両の距離

	testNode = node[CatchNodeNumber];
	//waypointに範囲を作る　通過した時に未来を見る
	if (Collision::GetInstance()->ColSphere(pos, 30.0f, node[CatchNodeNumber], 50.0f) == true)
	{
		////走行座標から　今目指してるwaypointよりもその次に目指すwaypointの方が遠い場合
		//if (NextWayPointVectorLength <= WayPointVectorLength)
		//{
		//	CatchNodeNumber++;
		//}
		////走行座標から　今目指してるwaypointよりもその次に目指すwaypointの方が近い場合
		//if (NextWayPointVectorLength > WayPointVectorLength)
		//{
		//	CatchNodeNumber += 2;
		//}
		CatchNodeNumber++;
	}

	//最終ノードの次走行継続させる為、初番ノードへ
	if (NodeMaxNumber <= CatchNodeNumber)
	{
		CatchNodeNumber = 0;
	}	
}

void Car_A_E::AI_AccelMode()
{
	//レイ取得用
	Vector3 out;
	//車両視認可能射程
	float dist = 8.0f + (50 * (speed / 300.0f));
	//車両正面ベクトル
	Vector3 frontVectr;
	frontVectr.x = sinf(angle.y) * dist;
	frontVectr.y = 0.0f;
	frontVectr.z = cosf(angle.y) * dist;
	//合成
	Vector3 Vector_A;
	Vector_A = frontVectr + pos;
	//レイピック
	if (Collision::GetInstance()->getObj()->RayPick(&out, &pos, &frontVectr, &dist) == -1)//何も無い場合
	{
		if (speed <= 140)
		{
			AI_Throttle = true;
			AI_BreakThrottle = false;
		}
		else
		{
			AI_Throttle = false;
			AI_BreakThrottle = false;
		}
	}
	else
	{
		AI_Throttle = false;
		AI_BreakThrottle = true;
	}
}

void Car_A_E::AI_HandleingMode()
{
	static float ControlSpeed;
	//内積によるハンドル調整
	if (cross.y <= -1.0f)
	{
		//ControlSpeed -= 0.02f;

	}
	if (cross.y >= 1.0f)
	{
		//ControlSpeed += 0.02f;
	}
	else  if(cross.z < 1.0f && cross.z>-1.0f)
	{
		//ControlSpeed = 0.0f;
	}

	//限界回転数
	if (ControlSpeed >= 2.0f)ControlSpeed = 2.0f;
	if (ControlSpeed <= -2.0f)ControlSpeed = -2.0f;

	//ハンドル関数
	PowerSteering(ControlSpeed*SpeedHandle);
}

