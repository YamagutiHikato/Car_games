#include "iextreme.h"
#include "Player.h"
#include "UI_Texture.h"

#include <random>

#define DebugDrawText
#define SolidFrameModel

/*
	エンジンの変動爆発
*/
std::random_device randomDevice;
std::mt19937 randomEngine(randomDevice());

std::uniform_real_distribution<float>ExplosionChangeTheNumberOfTimes(30.0f*0.2f, 30.0f*1.0f);//20%~100%
std::uniform_real_distribution<float>AirInjector(0.0f, 100.0f);

/*
		ベースとなる部分
*/
B_Player::B_Player()
{
	Init();
}


B_Player::~B_Player()
{
	delete obj;
}

/*
	初期化
*/

bool B_Player::Init()
{
	/*
		Vector3
	*/
	pos = ZEROVECTOR;
	angle = ZEROVECTOR;
	Front = ZEROVECTOR;
	Break = ZEROVECTOR;
	traction=ZEROVECTOR;
	/*
		int
	*/
	car_systems.NodeSaveNumber = 0;//保持変数初期化
	car_status.Gear = 1;//ギア初期化
	car_status.LevLimit = 0;//レヴ状態無回転
	car_systems.SpeedMeter = 0;//スピード初期化

	car_status.speed = 0.0f;//! double型の理由は分数で速度出す際にfloatだと計算がおかしかった為
	car_systems.idlingBreakSpeed = 0.0f;//静止時のアイドリングの回転数
	car_systems.SpeedHandle = 0.0f;//スムージングハンドリング

	/*
		float
	*/
	car_status.OtationalSpeed = 0.0f;
	car_systems.BreakingPower = 0.0f;
	car_systems.SubBreakingPower=0.0f;
	car_status.DRR = 0.0f;
	car_status.ERatio = 0.0f;
	car_status.FirnalRGR = 0.0f;
	car_status.RGR = 0.0f;
	scale = 0.0f;
	car_systems.SelecterReductionGearRation = 0.0f;
	car_systems.Throttle = 0.0f;
	car_systems.ThrottleTacoMetter = 0.0f;
	car_status.weght = 0.0f;
	car_systems.SpeedMeter = 0.0f;
	car_systems.rpm = 0.0f;
	geometry.AtmosphericPressure=1013.25f;
	geometry.DensityOfAir = 0.0f;
	geometry.AirResistanceCoefficient = 0.0f;
	car_status.FrontProjectionAreaOfTheAutomobile = 0.0f;
	geometry.Air_Speed = 0.0f;
	geometry.AirResistanceRealValue = 0.0f;
	car_systems.AcceleratingForce = 0.0f;
	car_status.horsePower = 0.0f;
	car_status.Max_HorsePower = 0.0f;
	car_status.PowerToWeightRatio = 0.0f;
	car_systems.crankShaft = 0.0f;
	car_systems.spinNum = 0.0f;
	car_systems.CrankSpinNum = 0.0f;
	car_status.torque = 0.0f;
	car_status.EngineDisplacement = 0.0f;
	car_systems.torqueOtationalSpeed = 0.0f;
	car_systems.HalfDRR = 0.0f;
	car_status.MaxTorque = 0.0f;
	car_status.torqueMaxOS = 0.0f;
	car_status.torquePower = 0.0f;
	car_systems.rollingResistance = 0.0f;
	car_systems.myu = 0.0f;
	
	car_systems.BackThrottle = 0.0f;
	car_systems.ShiftChangeLevs=0.0f;

	car_systems.WheelFrontAngle = 0.0f;
	car_systems.AnWheelAngle = 0.0f;

	/*
		bool
	*/

	car_systems.BackCheak = false;
	car_systems.FinalGear = false;
	car_systems.StartMove = false;
	car_systems.GearDelay = false;
	/*
		return
	*/

	/*
		レース関係
	*/
	Weeks = 1;
	GoalInCheak = false;


	return true;
}

Car_A::Car_A()
{
	Init();
}

/*
	初期化設定
*/
bool Car_A::Init()
{
	B_Player::Init();

	/*
		pointer
	*/

	obj  = new iexMesh ("DATA\\CAR\\TestModel_A.IMO");
	obj2 = new iex3DObj("DATA\\CAR\\TestModel_B.IEM");
	obj3 = new iexMesh ("DATA\\CAR\\TestModel_C.IMO");
	obj4 = new iexMesh ("DATA\\CAR\\TestModel_C.IMO");
	obj5 = new iexMesh ("DATA\\CAR\\TestModel_D.IMO");
	obj6 = new iexMesh ("DATA\\CAR\\TestModel_D.IMO");

	/*
		Vector3
	*/
	pos = Vector3(26.0, 1.0f, -83.0f);
	cross = ZEROVECTOR;

	/*
		int
	*/
	car_status.GearMax = 5;				//ギア

	car_status.LevLimit = OverLevMax*1000;

	for (int i = 0;i < Car_cylinder;i++) step[i] = 0;
	car_systems.ShiftCheakNum = 1;
	
	/*
		float
	*/
	GearRatio[0] = 3.369f;		//R速
	GearRatio[1] = 3.214f;		//1速
	GearRatio[2] = 1.925f;		//2速
	GearRatio[3] = 1.302f;		//3速
	GearRatio[4] = 1.000f;		//4速
	GearRatio[5] = 0.752f;		//5速

	FinalGearRatio = 4.111f;//勘違いしていたが、５ギアなどではなく、タイヤに関するギアのこと

	scale = 0.5f;

	/*
		車体部分
	*/
	car_status.DRR = 631.0f;			//タイヤの直径(外径)mm   DynamicRollingRadius
	car_systems.HalfDRR = car_status.DRR / 2;
	car_status.weght = 1780.7f;/*1200.0f*/

	car_status.RGR = 2.98377f;
	car_status.FirnalRGR = 3.43441f;
	car_systems.GearDelay =false;
	car_systems.crankShaft = 0.0f;
	for (int i = 0;i < MaxSilinderAve;i++)engine_Gearmissions.CrankSpinAverage[i] = 0.0f;
	/*
		UI部分
	*/
	car_systems.metterAngle = 0.0f;
	/*
		エンジン部分
	*/
	car_systems.spinNum = 0;
	car_systems.CrankSpinNum = 0;
	car_status.torqueMaxOS = 4400.0f;
	/*
		タイヤ部分
	*/
	car_systems.RightFrontWheel = car_systems.LeftFrontWheel = car_systems.RightRearWheel = car_systems.LeftRearWheel = 0.0f;
	car_status.TheOuterCircumferenceOfTheTire = ((car_status.DRR)*PI) / 1000;
	car_systems.MinLength = 0.0f;
	car_systems.WheelRpm = 0.0f;
	TaiyaAngle=ZEROVECTOR;
	car_systems.WheelGrep = 1.0f;
	/*
		ハンドル部分
	*/
	car_systems.HandleBar = 0.0f;
	car_systems.PowerSlinder = 0.0f;
	car_systems.KnuckleArm = 0.0f;
	/*
		物理挙動関連
	*/
	car_systems.centrifugal = car_systems.Rad = car_systems.Fc = car_systems.sita = car_systems.RollHeight
	= car_systems.tread = car_systems.Spring = car_systems.RollStiffness_F = car_systems.RollStiffness_R = 0.0f;
	car_systems.sitaaccel = car_systems.sitabrake = 0.0f;
	 OverBlock = 0;
	 wallWeght = 2300.0f;
	 weghtRef = 1200 * 0.8f;
	 wallRef = wallWeght*0.8f;
	/*
		bool
	*/
	 car_systems.StartMove = false;

	/*
		エンジンルーム
	*/
	engine_parts.TargetInitialization(0.0f);
	for (int i = 0;i < Car_cylinder;i++)engine_parts.Battery[i] = 0.0f;
	car_systems.hydraulic = 0.0f;
	/*
		ギアとミッション関係
	*/
	engine_Gearmissions.TargetInitialize(0.0f);
	for (int i = 0;i < MaxSilinderAve;i++)
	{
		engine_Gearmissions.CrankSpinAverage[i] = engine_Gearmissions.IdlingCrankSpinAverage[i] =0.0f;
	}
	return true;
}

/*
	簡易当たり判定

	当たり判定による　はみ出た数値から割合減速
	ver.1.112 2018/02/22
*/

void Car_A::ModelCollision()
{
	float work = 0;
	/*
	mv+M・0=mv'+M
	*/

	OverBlock = (car_status.weght * car_status.speed + wallWeght -weghtRef + wallRef)/3600;
	//if (OverBlock <= 0.0f)OverBlock = 0.0f;
	//前方
	work = Collision::GetInstance()->getFront(pos);
	if (pos.z > work - CollisionRangeNumericalValue)
	{		
		car_systems.Throttle -= OverBlock/1000;
		//speed -= OverBlock;
		pos.z = work - CollisionRangeNumericalValue;
	}

	//後方
	work = Collision::GetInstance()->getBack(pos);
	if (pos.z < work + CollisionRangeNumericalValue)
	{
		car_systems.Throttle -= OverBlock/1000;
		//speed -= OverBlock;
		pos.z = work + CollisionRangeNumericalValue;
	}

	//右
	work = Collision::GetInstance()->getRight(pos);
	if (pos.x > work - CollisionRangeNumericalValue)
	{
		car_systems.Throttle -= OverBlock/1000;
		//speed -= OverBlock;
		pos.x = work - CollisionRangeNumericalValue;
	}
	//左
	work = Collision::GetInstance()->getLeft(pos);
	if (pos.x < work + CollisionRangeNumericalValue)
	{
		car_systems.Throttle -= OverBlock/1000;
		//speed -= OverBlock;
		pos.x = work + CollisionRangeNumericalValue;
	}
}

/*
	左スティックの傾きからハンドルへ伝える制御系
	ver.1.112 2018/02/22
*/
float namakon;
bool Car_A::MoveContrl(float max)
{
	static float moveSpeed;
	//	加速
	moveSpeed += 1.0f;
	if (moveSpeed > max) moveSpeed = max;
	//	軸の傾きの取得
	float axisX = KEY_GetAxisX()*0.002f;
	namakon = KEY_GetAxisX()*0.002f;
	//　軸の傾きと長さ
	float d = sqrtf(axisX * axisX);
	//	軸の傾きの遊び
	if (d < 0.3f) 
	{
		moveSpeed = 0;
		car_systems.HandleBar = 0.0f;

		if (car_systems.PowerSlinder > 5.0f)car_systems.PowerSlinder -= 9.0f;
		if (car_systems.PowerSlinder < -5.0f)car_systems.PowerSlinder += 9.0f;
		else if (car_systems.PowerSlinder <= 5.0f && car_systems.PowerSlinder >= -5.0f)car_systems.PowerSlinder = 0.0f;

		if (car_systems.KnuckleArm > 0.05f)car_systems.KnuckleArm -= 0.05f;
		if (car_systems.KnuckleArm < -0.05f)car_systems.KnuckleArm += 0.05f;
		else if (car_systems.KnuckleArm <= 0.05f && car_systems.KnuckleArm >= -0.05f)car_systems.KnuckleArm = 0.0f;
		
		return  false; 
	}
	//	軸の傾き補正
	if (d > 1.0f)
	{ 
		axisX /= d;
	}
	//ハンドル関数へ移行
	PowerSteering(axisX*car_systems.SpeedHandle);
	return true;
}

/*
	ハンドルからナックルアームへ伝える制御
	ver.1.112 2018/02/22
*/

float Car_A::PowerSteering(float HandlePower)
{
	/*
	左右切られたときのハンドルが
	ハンドルシャフトを通る
	*/
	car_systems.HandleBar = HandlePower;
	/*
	ハンドルの角度調整
	ハンドルシャフトの回転を求める
	*/
	car_systems.HandleBar *= PI / 180.0f;
	car_systems.HandleBar *= 360.0f;	//調整数値
	/*
	パワーシリンダーに接続
	ハンドルは回転するのに対し、パワーシリンダーは左右にしかゆれない
	*/
	car_systems.PowerSlinder += car_systems.HandleBar*1.5f;//25.5%の補正かけて少しゲーム性を与える
	/*
	パワーシリンダーから制御
	MaxPowerSlinderLength = シリンダーの長さの半分に指定
	*/
	float HalfSilinderLength = MaxPowerSlinderLength / 2;
	if (car_systems.PowerSlinder > HalfSilinderLength)car_systems.PowerSlinder = HalfSilinderLength;
	else if (car_systems.PowerSlinder < -HalfSilinderLength)car_systems.PowerSlinder = -HalfSilinderLength;
	//パワーシリンダーからナックルアームに接続
	car_systems.KnuckleArm = car_systems.PowerSlinder*PI/360.0f;

	return  car_systems.KnuckleArm;
}

/*
	タイヤの限界挙動制御
	ver.1.112 2018/02/22
*/
void Car_A::PredictedPosition()
{
	//回転角度の制御
	if (angle.y > 360.0f)angle.y = -360.0f;
	if (angle.y < -360.0f)angle.y = 360.0f;

	/*
	タイヤの蛇角	反映値を調整
	*/
	car_systems.WheelFrontAngle = angle.y + car_systems.KnuckleArm*0.30f;
	//正面
	Vector3 VecAngle;

	//伝達調整数値
	float TransmissionTimingNumbers = 14.0f;

	VecAngle.x = sinf(angle.y);
	VecAngle.y = 0.0f;
	VecAngle.z = cosf(angle.y);

	//タイヤの角度に伝達
	TaiyaAngle.x = pos.x + sinf(car_systems.WheelFrontAngle) * TransmissionTimingNumbers;
	TaiyaAngle.z = pos.z + cosf(car_systems.WheelFrontAngle) * TransmissionTimingNumbers;

	//座標反映
	pos.x += sinf(angle.y)*(car_status.speed*0.03f);
	pos.z += cosf(angle.y)*(car_status.speed*0.03f);

	//Vector3 UnVec;
	//UnVec.x = sinf(angle.y)*car_systems.AnWheelAngle*(car_status.speed*0.03f);
	//UnVec.y = 0.0f;
	//UnVec.z = cosf(angle.y)*car_systems.AnWheelAngle*(car_status.speed*0.03f);
	//pos += UnVec;

	//タイヤの角度伝達最更新
	TaiyaAngle.x = pos.x + sinf(car_systems.WheelFrontAngle) * TransmissionTimingNumbers;
	TaiyaAngle.z = pos.z + cosf(car_systems.WheelFrontAngle) * TransmissionTimingNumbers;

	//距離ベクトル取得
	Vector3 LengthPos;
	LengthPos = TaiyaAngle - pos;

	//外積・内積
	Vector3Cross(cross, VecAngle, LengthPos);

	float dot = Vector3Dot(VecAngle, LengthPos);
	float l1 = sqrtf(pow(VecAngle.x, 2) + pow(VecAngle.z, 2));
	float l2 = sqrtf(pow(LengthPos.x, 2) + pow(LengthPos.z, 2));

	float cosValue = dot / (l1 * l2);

	//角度常時修正
	float dAngle = 1.0f - cosValue;
	if (dAngle > 0.5f)dAngle = 0.5f;

	//ステアリングの強さ
	float handlePower = car_status.speed / car_systems.rollingResistance;
	if (handlePower <= 0.0f)handlePower = 0.0f;
	else if (0.099f <= handlePower)handlePower = 0.099f;
	
	if (cross.y > .0f)
	{
		angle.y += dAngle * handlePower;
		car_systems.AnWheelAngle -= dAngle * handlePower;
	}
	else
	{
		angle.y -= dAngle * handlePower;
		car_systems.AnWheelAngle += dAngle * handlePower;
	}
	car_status.OtationalSpeed -= CorneringForce().Length();
	

}

/*
		操作系
		ver.1.112 2018/02/22
*/
void Car_A::OperationSystem(int n)
{
	//タイヤ挙動制御
	PredictedPosition();
	/*
	スロットル
	踏んだときのアクセルスロットルかブレーキスロットル稼動確認
	*/

	//押したときにアクセルスロットルが入るかの設定
	if (car_systems.GearDelay == false)//クラッチが繋がれるまでスロットル制御
	{
		car_systems.Throttle += car_systems.AcceleratingForce * (KEY_GetAxisY3()*0.02f);//調整の為に2倍　
		car_systems.torqueOtationalSpeed += car_systems.AcceleratingForce  * (KEY_GetAxisY3()*0.01f);
		car_systems.ThrottleTacoMetter += car_systems.AcceleratingForce * (KEY_GetAxisY3()*0.02f);
		car_systems.ShiftCheakNum = car_status.Gear;
	}
	else
	{	
		if (car_systems.ThrottleTacoMetter >= car_systems.ShiftChangeLevs)
		{
			car_systems.GearDelay = false;//クラッチ繋ぎの接続完了までの時間	
		}
	}
	car_systems.Throttle -= car_systems.Throttle*0.005f;//押してなかったら空	抜け方は割合減算
	car_systems.ThrottleTacoMetter -= car_systems.ThrottleTacoMetter*0.005f;
	car_systems.torqueOtationalSpeed -= car_systems.ThrottleTacoMetter*0.0025f;

	/*
		ブレーキの摩擦係数
		乾いたアスファルトまたはコンクリート	0.7
		ぬれたコンクリート	0.5
		ぬれたアスファルト	0.45～0.6
		砂利道路	0.55
		乾いた非舗装道路	0.65
		ぬれた非舗装道路	0.4～0.5
		固くなった雪	0.15
		氷	0.07
	*/
	//押したときにブレーキスロットルが入るかの設定

	car_systems.BreakingPower += (0.8 / (0.7 * 140 * 2))* (KEY_GetAxisX3()*0.001f);	//制動力　
	car_systems.torqueOtationalSpeed -= car_systems.BreakingPower;
	car_systems.Throttle -= car_systems.BreakingPower;
	car_systems.ThrottleTacoMetter -= car_systems.BreakingPower;

	//else BreakingPower = 0.0f;//押してなかったら空

	//バック
	if (KEY_Get(KEY_D) == 1)
	{
		if (car_systems.BackCheak == false)
		{
			car_systems.BackCheak = true;
		}

		car_systems.BackThrottle += car_systems.AcceleratingForce*8.0f;//調整の為に2倍　
		car_systems.Throttle -= car_systems.BackThrottle;
		car_systems.ThrottleTacoMetter = car_systems.Throttle;
		car_systems.torqueOtationalSpeed += car_systems.AcceleratingForce;
		car_status.Gear = 0;

	}
	else
	{
		car_systems.BackThrottle -= car_systems.BackThrottle*0.025f;//押してなかったら空	抜け方は割合減算

		if (car_systems.BackCheak == true)
		{
			car_systems.BackCheak = false;
		}
	}
	/*
		簡易サイドブレーキ
	*/

	if (KEY_Get(KEY_B) == 1)
	{
		car_systems.SubBreakingPower += 0.8 / (0.7 * 140 * 2) / 8;	//制動力　
		car_systems.Throttle -= car_systems.SubBreakingPower;
		car_systems.ThrottleTacoMetter = car_systems.Throttle;
		car_systems.torqueOtationalSpeed -= car_systems.SubBreakingPower;
	}
	else car_systems.SubBreakingPower = 0.0f;//押してなかったら空

/*
	前のギアと現在のギア等を計算することで反映

	AT完成
*/
	if (n == GearMode::AT)
	{
		if (car_systems.Throttle<= (car_status.torqueMaxOS / 1000) / GearRatio[car_status.Gear - 1] * GearRatio[car_status.Gear])
		{
			if (car_status.Gear > 1)
			{
				car_status.Gear--;
				car_systems.Throttle = car_systems.Throttle / GearRatio[car_status.Gear + 1] * GearRatio[car_status.Gear];
				car_systems.ThrottleTacoMetter = car_systems.ThrottleTacoMetter / GearRatio[car_status.Gear + 1] * GearRatio[car_status.Gear];
				car_systems.torqueOtationalSpeed = car_systems.torqueOtationalSpeed / GearRatio[car_status.Gear + 1] * GearRatio[car_status.Gear];
			}
		}

		if (car_systems.Throttle > OverLevMax)//シフトアップ AT
		{
			if (car_status.Gear < 5)
			{
				car_status.Gear ++;
				car_systems.Throttle = car_systems.Throttle / GearRatio[car_status.Gear - 1] * GearRatio[car_status.Gear];
				car_systems.ShiftChangeLevs = car_systems.ThrottleTacoMetter / GearRatio[car_status.Gear - 1] * GearRatio[car_status.Gear];
				car_systems.ThrottleTacoMetter= car_systems.ThrottleTacoMetter / GearRatio[car_status.Gear - 1] * GearRatio[car_status.Gear];
				car_systems.torqueOtationalSpeed = car_systems.torqueOtationalSpeed / GearRatio[car_status.Gear - 1] * GearRatio[car_status.Gear];
				car_systems.GearDelay = true;

			}
		}
	}

	else if (n == GearMode::MT)
	{
		if (KEY_Get(KEY_L1) == 1)
		{
			if (car_status.Gear > 1)
			{
				car_status.Gear--;
				car_systems.Throttle = car_systems.Throttle / GearRatio[car_status.Gear + 1] * GearRatio[car_status.Gear];
				car_systems.ThrottleTacoMetter = car_systems.ThrottleTacoMetter / GearRatio[car_status.Gear + 1] * GearRatio[car_status.Gear];
				car_systems.torqueOtationalSpeed = car_systems.torqueOtationalSpeed / GearRatio[car_status.Gear + 1] * GearRatio[car_status.Gear];
			}
		}

		if (KEY_Get(KEY_R1) == 1)//シフトアップ MT
		{
			if (car_status.Gear < 5)
			{
				car_status.Gear++;
				car_systems.Throttle = car_systems.Throttle / GearRatio[car_status.Gear - 1] * GearRatio[car_status.Gear];
				car_systems.ShiftChangeLevs = car_systems.ThrottleTacoMetter / GearRatio[car_status.Gear - 1] * GearRatio[car_status.Gear];
				car_systems.ThrottleTacoMetter = car_systems.ThrottleTacoMetter / GearRatio[car_status.Gear - 1] * GearRatio[car_status.Gear];
				car_systems.torqueOtationalSpeed = car_systems.torqueOtationalSpeed / GearRatio[car_status.Gear - 1] * GearRatio[car_status.Gear];
				car_systems.GearDelay = true;
			}
		}
	}

	if (car_systems.Throttle > (OverLevMax + 0.2f) && car_status.Gear<=4)car_systems.Throttle = OverLevMax - 0.2f;
	if (car_systems.Throttle < 0.0f)car_systems.Throttle = 0.0f;	//Max 0%
	if (car_systems.ThrottleTacoMetter > (OverLevMax + 0.3f))car_systems.ThrottleTacoMetter = OverLevMax;
	if (car_systems.ThrottleTacoMetter < 0.00f)car_systems.ThrottleTacoMetter = 0.00f;

	if (car_systems.BackThrottle > (OverLevMax - 6))	car_systems.BackThrottle = OverLevMax - 6;
	if (car_systems.BackThrottle < 0.00f)car_systems.BackThrottle = 0.00f;	//Max 0%

	if (car_systems.BreakingPower > 0.05f)car_systems.BreakingPower = 0.05f;	//100%
	if (car_systems.BreakingPower < 0.001f)car_systems.BreakingPower = 0.001f;	//0%

	if (car_systems.torqueOtationalSpeed > 4.4f)car_systems.torqueOtationalSpeed = 4.4f;
	if (car_systems.torqueOtationalSpeed <= 0.0f)car_systems.torqueOtationalSpeed = 0.0f;
}

//**************************************************************************************
//	TODO :エンジン駆動系
//**************************************************************************************

/*
	内部爆発によりかき回されるクランクシャフトの回転を求める
*/

/*
	直列6気筒エンジンの構造関数
	ver.1.112 2018/02/22
*/
void Car_A::StraightSixEngine()
{
	//初期化
	engine_parts.CrankShaft = 0.0f;
	engine_parts.ComShaft = 0.0f;
	engine_Gearmissions.num = engine_Gearmissions.num2 = 0;

	//num = 0;

	//エンジンの起動
	for (int i = 0;i < 6;i++)SilinderUpdate(i, engine_parts.ConectingRod);

	{
		//エンジン状態を毎秒記録する
		engine_Gearmissions.CrankSpinAverage[engine_Gearmissions.CylinderAverages] =
			((2 * (0.25f / 1000)*(engine_parts.CrankShaft / 360)) * 3600) * 2;
		engine_Gearmissions.IdlingCrankSpinAverage[engine_Gearmissions.CylinderAverages] =
			engine_Gearmissions.CrankSpinAverage[engine_Gearmissions.CylinderAverages];
		//ここで過給圧を配置（下でコメントアウトしてるやつ)　結果、エンジン効率が上がった
		engine_Gearmissions.CrankSpinAverage[engine_Gearmissions.CylinderAverages] +=
			(car_systems.Throttle - car_systems.BackThrottle);

		if (engine_Gearmissions.CylinderAverages >= MaxSilinderAve - 1)
			engine_Gearmissions.CylinderAverages = 0;else engine_Gearmissions.CylinderAverages++;

		//配列最大数
		engine_Gearmissions.ArrayMaxNumber = sizeof(engine_Gearmissions.CrankSpinAverage) / sizeof(engine_Gearmissions.CrankSpinAverage[0]);

		for (int i = 0;i < MaxSilinderAve;i++)
		{
			engine_Gearmissions.num += engine_Gearmissions.CrankSpinAverage[i];
			engine_Gearmissions.num2 += engine_Gearmissions.IdlingCrankSpinAverage[i];
		}

		//平均を取得
		engine_Gearmissions.AverageNumber = engine_Gearmissions.num / engine_Gearmissions.ArrayMaxNumber;
		car_systems.torqueOtationalSpeed = engine_Gearmissions.AverageNumber / 2;
		engine_Gearmissions.IdlingAverageNumber = engine_Gearmissions.num2 / engine_Gearmissions.ArrayMaxNumber;
		engine_Gearmissions.CrankNumberOfRevolutionsPerSecond = engine_Gearmissions.AverageNumber;	//!クランクシャフト
		engine_Gearmissions.UICrankNumberOfRevolutionsPerSecond = engine_Gearmissions.AverageNumber;	//!タコメータ反映
		car_systems.idlingBreakSpeed = engine_Gearmissions.IdlingAverageNumber;	//!アイドリング状態反映
	}
}


/*
	トラクション
	ver.1.112 2018/02/22
*/
Vector3 Car_A::Traction()
{

	//前向きを表現している単位ベクトル
	Front.x = sinf(angle.y);
	Front.y = 0.0f;
	Front.z = cosf(angle.y);

	Front.Normalize();

	/*
		トルク計算
		torque/トルク最高回転数4,400rpm
		(36.0f * torque)=(36.0kgf･m)/4400r.p.m =最大トルク=353.0N・m5
	*/
	car_status.EngineDisplacement = (86.0f / 2)*(86.0f / 2)*PI*73.7f*6;//ボアの半分の2乗　×　π　×　ストローク　×　気筒数
	car_status.EngineDisplacement /= (int)1000;
	car_status.torque = 22 * (car_status.EngineDisplacement) * 0.5f / (2 * PI) /pow(9.806652f,2);//(正味平均有効圧力(22)）×（排気量）×（爆発回数(4サイクルであれば0.5)）／（2π）
	car_status.MaxTorque = car_status.Max_HorsePower * 75.0f * 60.0f / car_status.LevLimit * 2 * PI;
	
	/*
	デフ比(減速比		ReductionGearRatio
	*/
	if (car_status.Gear < car_status.GearMax)car_systems.SelecterReductionGearRation = car_status.FirnalRGR;
	else car_systems.SelecterReductionGearRation = car_status.RGR;

	/*
	トランスミッション効率
	*/
	if (car_status.torqueMaxOS >= car_status.OtationalSpeed)		car_status.ERatio = car_systems.SlowSpeed;
	if (car_status.torqueMaxOS < car_status.OtationalSpeed)		car_status.ERatio = car_systems.HighSpeed;

	/*
		タイヤ半径
	*/
	car_systems.HalfDRR = car_status.DRR / 2;
	/*
	トラクション
	*/

	traction = (Front*(car_status.torquePower)*car_systems.Throttle*GearRatio[car_status.Gear] * car_systems.SelecterReductionGearRation * car_status.ERatio) / car_systems.HalfDRR;

	return traction;

}

/*
	空気抵抗
	ver.1.112 2018/02/22
*/

Vector3 Car_A::AirResistance()
{
	/*
	空気抵抗=空気の密度*空気抵抗係数*自動車の正面投影面積*速度^速度/2
	空気の密度 = {1.293*大気圧(1-0.378【水蒸気圧】/大気圧)}/1+気温/273.15
	空気抵抗係数:	乗用車0.3~0.5 トラック:0.4~0.6 バス0.5~0.8 二輪車0.6~0.9
	自動車の正面投影面積:	トレッド幅*全高 または　全高　* 全幅 * 0.8のどちらかを使う
	*/
	/*
	空気の密度
	*/
	geometry.DensityOfAir = geometry.AtmosphericPressure / (2.87f*(geometry.temperature + 273.15f));
	/*
	空気抵抗係数
	*/
	geometry.AirResistanceCoefficient = 0.4f;
	/*
	自動車の正面投影面積
	*/
	car_status.FrontProjectionAreaOfTheAutomobile = (1.340f * 1.755f * 0.8f);
	/*
	/*
	速度
	*/
	geometry.Air_Speed =(float) pow(car_status.speed,2);
	/*
	空気抵抗
	*/
	geometry.AirResistanceRealValue = (geometry.AirResistanceCoefficient*car_status.FrontProjectionAreaOfTheAutomobile*geometry.Air_Speed*geometry.DensityOfAir) / 2;
	geometry.AirResistanceRealValue /= pow(60,3);	//現在空気抵抗軽減無
	return Vector3(sinf(geometry.AirResistanceRealValue), 0.0f, cosf(geometry.AirResistanceRealValue));
}

/*
	転がり抵抗
	ver.1.112 2018/02/22
*/
Vector3 Car_A::RollingResistance()
{
	/*
	道路条件								μr
	乾いた砂地							約0.25
	砂または石灰質の道						約0.17
	新しく砂利を敷いた道					約0.13
	石の多い凸凹道						約0.08
	手入れのよい小砂利道					約0.03
	アスファルトまたはコンクリート道			約0.015
	*/

	car_systems.myu = 0.015f;//真下に光線を飛ばし、返し値でμを変動させるべき所だが、今回は変動なし
	car_systems.rollingResistance = car_systems.myu* car_status.weght*9.8f;
	
	return Vector3(sinf(car_systems.rollingResistance),0,cosf(car_systems.rollingResistance));
}
/*
	静止力
	ver.1.112 2018/02/22
*/
Vector3 Car_A::StaticForce()
{
	return -Traction()*car_status.weght*0.05f;
}

/*
	遠心力

*/

float Car_A::CentrifugalForce()
{
	//旋回半径=ホイールベース(M)/sin(実舵角)
	car_systems.Rad = (2.615f) / sin(cross.y);
	//遠心力=車重/重力加速度*速度2/旋回半径
	car_systems.Fc = (car_status.weght / 9.8f) * (pow(car_status.speed, 2) / car_systems.Rad);
	car_systems.Fc /= 10000;
	//ロール
	car_systems.RollHeight = 1.325f / 3;//ロールセンターから重心までの距離
	car_systems.tread = 1460/1000;//トレッド幅
	car_systems.Spring = car_systems.RollHeight*9.8f;//サスペンションモーメント

	car_systems.RollStiffness_F = (5700*pow(car_systems.tread, 2)) / 2;//ロール剛性 前
	car_systems.RollStiffness_R = (4000*pow(car_systems.tread, 2)) / 2;//ロール剛性 後
	
	/*
	ロールアップ
	ロール効果は極小
	*/
	car_systems.sita = (car_systems.Fc*car_systems.RollHeight) / ((car_systems.RollStiffness_F+ car_systems.RollStiffness_R) - (car_systems.Spring*car_systems.RollHeight));
	
	car_systems.sitaaccel = (car_systems.Throttle*car_systems.RollHeight) / ((4000 * (-4.530f / 2 - 2.615f)*2.625f) - (car_systems.Spring*car_systems.RollHeight));
	car_systems.sitabrake = (car_systems.BreakingPower*car_systems.RollHeight) / ((5700 * (4.530f / 2 - 2.615f)*2.625f) - (car_systems.Spring*car_systems.RollHeight));
	//ロール反映
	angle.x = (car_status.speed*(car_systems.sitaaccel - car_systems.sitabrake))* CorneringForce().x;

	//左右に揺れる角度(angle.z)をロールで反映
	angle.z = car_systems.sita* CorneringForce().z;//

	//デバッグデータ
	car_systems.centrifugal = car_systems.Fc;

	return car_systems.Fc;
}
/*
	コーナリングパワー
	ver.1.112 2018/02/22
*/
Vector3 Car_A::CorneringForce()
{
	/*
	F=T*Fcp(a)
	T：コーナリングパワーの働く方向．車体の進行方向に直角
	f：コーナリングパワーを計算する関数[N]
	α：横滑り角
	*/
	Vector3 WouldUpVec(0.0f, 1.0f, 0.0f);//ワールド上の上ベクトル

	//進行方向
	Vector3 Angle;
	Angle.x = sinf(angle.y);
	Angle.z = cosf(angle.y);

	Vector3 CounerPower;
	/*
	車体進行方向と世界の上向きベクトルからコーナリングパワーの働く方向がわかる
	これらを外積で計算することで求めることが可能
	進行方向速度に関しては前フレームから計算した速度のベクトル正規化で可能
	*/
	Vector3Cross(CounerPower, Angle/*現在車体角度*/, WouldUpVec/*上向きベクトル*/);//コーナリングパワーの働く方向 T
	/*
				   /
				  / αタイヤの傾きのなす角
		-------タイヤ-------->	進行方向
				/|
			   / | 
				 ↓コーナリングフォース
	*/
	
	return CounerPower*0.5f;
}

/*
	ミッションギアボックス
	ver.1.112 2018/02/22
*/
void Car_A::TransMissionCustom(const int n)
{
	switch(n)
	{
		case 0://R-32 Normal Misson
			GearRatio[0] = 3.369f;		//R速
			GearRatio[1] = 3.214f;		//1速
			GearRatio[2] = 1.925f;		//2速
			GearRatio[3] = 1.302f;		//3速
			GearRatio[4] = 1.000f;		//4速
			GearRatio[5] = 0.752f;		//5速
			break;
		case 1://R-35 Normal Misson
			GearRatio[0] = 3.700f;		//R速
			GearRatio[1] = 4.056f;		//1速
			GearRatio[2] = 2.301f;		//2速
			GearRatio[3] = 1.595f;		//3速
			GearRatio[4] = 1.248f;		//4速
			GearRatio[5] = 1.001f;		//5速

		case 2://original Misson
			GearRatio[0] = 3.177f;		//R速
			GearRatio[1] = 3.200f;		//1速
			GearRatio[2] = 2.031f;		//2速
			GearRatio[3] = 1.422f;		//3速
			GearRatio[4] = 1.000f;		//4速
			GearRatio[5] = 0.833f;		//5速
			break;
	}
}

/*
	動力系の集合制御
*/
void Car_A::GearInfo()
{
	
	/*
		TODO: エンジンのRPM
	*/
	car_systems.rpm = engine_Gearmissions.CrankNumberOfRevolutionsPerSecond;
	car_systems.rpm *= 1000;
	/*
		タイヤ伝達
	*/
	WheelProcess();
	/*
		速度伝達
								タイヤの外周長　X　エンジンの回転数(rpm)							  60
		速度(km/h)				-----------------------------------			X		-----------------------
								ギア比　　　　　X　最終減速比									10の６乗
	*/
	
	float bunsi_A, bunsi_B, bunbo_A, bunbo_B,SpeedSaved;

	bunsi_A = ((255 * 0.40f * 2 + 17 * 25.4f)*PI*(car_systems.rpm -(car_systems.idlingBreakSpeed*1000)));
	//!シフトチェンジ時に前の計算数値を次のギアに渡してシャフト抜けを改善する
	bunbo_A = (GearRatio[car_systems.ShiftCheakNum] * car_status.FirnalRGR);
	bunsi_B = 60.0f;
	bunbo_B = pow(10, 6);
	SpeedSaved = (bunsi_A/ bunbo_A) * (bunsi_B/ bunbo_B);
	
	car_status.speed = (SpeedSaved)*RollingResistance().Length();
	//トルク回転数
	car_status.torquePower = 2 * PI *car_status.torque*(car_systems.rpm)/60/1000;

	/*
	1.3962kW ＝ 1.0馬力
	
	*/
	//馬力 PTO軸トルク（Kg・m）＊PTO軸回転数（RPM）Ｘ 2π ／ ( 75 Ｘ 60 )
	car_status.horsePower = car_status.torque * (car_systems.torqueOtationalSpeed * 1000) * (2 * PI) / (75 * 60);
	//最高馬力
	//（回転数 rpm) ×（トルク kgfm）／1000 × 1.3962
	car_status.Max_HorsePower= car_status.torque * car_status.torqueMaxOS * (2 * PI) / (75 * 60);

	//パワーウェイトレシオ	調べた限りだとデータ　加速力に影響するものでもないという判断
	car_status.PowerToWeightRatio = car_status.weght / car_status.Max_HorsePower;

	//加速力=トルク*重力加速度*ギア比/タイヤの半径/車重
	//ギアの重みの為、ラストギアまでの重みを変える
	if (car_status.Gear <= car_status.GearMax - 1)
	{
		car_systems.AcceleratingForce = ((car_status.torquePower* 9.8f*(GearRatio[car_status.Gear] * car_status.RGR) / (car_systems.HalfDRR / 1000)) / car_status.weght) - geometry.AirResistanceRealValue;
	}
	if (car_status.Gear == car_status.GearMax)
	{
		car_systems.AcceleratingForce = ((car_status.torquePower* 9.8f*(GearRatio[car_status.Gear] * car_status.FirnalRGR) / (car_systems.HalfDRR / 1000)) / car_status.weght) - geometry.AirResistanceRealValue;
	}

	car_systems.AcceleratingForce /= 900;//調整

	/*x
	シフト設定
	*/
	if (car_status.Gear >= car_status.GearMax)car_status.Gear = 5;

	if (car_status.Gear <= 1 && car_systems.BackCheak==false)	car_status.Gear = 1;									     //１速は下回らない(後退は今度
	else if(car_status.Gear <= 1 && car_systems.BackCheak == true)	car_status.Gear = 0;

	if (KEY_Get(KEY_RIGHT) == 3)missionMode = 1;
	if (KEY_Get(KEY_LEFT) == 3)missionMode = 0;


}

/*
	気筒制御系
	４気筒・６気筒等に対応できる関数に変形された
	ver.1.112 2018/02/22
*/

void Car_A::SilinderUpdate(int n, float CylinderSpeed)
{

	//*************************************************************************************
	//			step 1			吸入
	//*************************************************************************************
	//空気を過給バルブで燃料と混ぜる　バルブのパーツは除外
	if (step[n] == 0)
	{
		engine_parts.CyLinderHead[n] -= CylinderSpeed;
	}
	//空気を吸入後、圧縮工程へ
	if (step[n] == 0 && engine_parts.CyLinderHead[n] < 0.0f)
	{
		step[n]++;

		//インジェクター吸引	空気の計算はキリが無いので1か0の動きだけ
		engine_parts.Injecter += AirInjector(randomEngine);

		//ラジエーターの吸熱
		engine_parts.Radiator -= engine_parts.Injecter;

		//エンジンブロック貫かないように制限
		engine_parts.CyLinderHead[n] = 0.0f;
	}
	//*************************************************************************************
	//			step 2			圧縮
	//*************************************************************************************
	//空気を押し上げる
	if (step[n] == 1)
	{
		engine_parts.CyLinderHead[n] += CylinderSpeed;
	}

	if (step[n] == 1 && engine_parts.CyLinderHead[n] >60.0f)
	{
		step[n]++;

		//エンジンブロック貫かないように制限
		engine_parts.CyLinderHead[n] = 60.0f;

	}
	//*************************************************************************************
	//		step 3			燃焼
	//*************************************************************************************
	if (step[n] == 2)
	{
		engine_parts.CyLinderHead[n] -= CylinderSpeed;
	}
	if (step[n] == 2 && engine_parts.CyLinderHead[n] <0.0f)
	{
		step[n]++;
		//点火プラグ終了
		engine_parts.Battery[n] = 0.0f;
		//エンジンブロック貫かないように制限
		engine_parts.CyLinderHead[n] = 0.0f;
	}
	if(step[n] == 2 && engine_parts.CyLinderHead[n] >0.0f)
	{
		//燃焼=点火プラグをスパーク　抜けるまで回転を繰り返す
		engine_parts.Battery[n] = 1;
		//回転数にズレを起こさない調整シャフト
		engine_parts.TimingBelt = ExplosionChangeTheNumberOfTimes(randomEngine)*n;
		//カムシャフトとクランクシャフトが回転
		engine_parts.CrankShaft += engine_parts.TimingBelt;
		engine_parts.ComShaft += engine_parts.TimingBelt / 2;
		//温度調整
		engine_parts.EngineOil =engine_parts.TimingBelt;
		engine_parts.Radiator = engine_parts.EngineOil;

	}
	//*************************************************************************************
	//		step 4			排気
	//*************************************************************************************
	if (step[n] == 3)
	{
		engine_parts.CyLinderHead[n] += CylinderSpeed;
	}
	if (step[n] == 3 && engine_parts.CyLinderHead[n] > 60.0f)
	{
		step[n] = 0;
		//インジェクター排気
		engine_parts.Injecter+= AirInjector(randomEngine);

		//エンジンブロック貫かないように制限
		engine_parts.CyLinderHead[n] = 60.0f;

		//ラジエータの熱を解放
		engine_parts.Radiator += engine_parts.Injecter;

	}

	//水冷制限
	if (engine_parts.Radiator > 100)engine_parts.Radiator = 100;
	if (engine_parts.Radiator < 0)engine_parts.Radiator = 0;

	//温度制限
	if (engine_parts.EngineOil > 100)engine_parts.EngineOil = 100;
	if (engine_parts.EngineOil < 0)engine_parts.EngineOil = 0;
}

/*
	タイヤ伝達
*/

void Car_A::WheelProcess()
{

	/*
		タイヤの1分間に進む距離
	*/
	car_systems.MinLength += car_status.speed*1000/ 216000;
	/*
		タイヤの回転数
	*/
	car_systems.WheelRpm = car_systems.MinLength / car_status.TheOuterCircumferenceOfTheTire;
	int WheelConvert = car_systems.WheelRpm;
	car_systems.WheelRpm = car_systems.WheelRpm - WheelConvert;
	car_systems.WheelRpm = PI * 2 * car_systems.WheelRpm;

	car_systems.RightRearWheel = car_systems.LeftRearWheel = car_systems.WheelRpm;
}

/*
	更新処理
*/
void Car_A::Update()
{
	
	Traction();
	car_systems.SpeedHandle = 1.0f;
	car_systems.metterAngle = engine_Gearmissions.UICrankNumberOfRevolutionsPerSecond / 3;
	car_systems.SpeedMeter  =(float)car_status.speed / 90;

	//重力
	static float GravityZero,Gravity;
	Gravity -= 9.8f;
	pos.y += Gravity;
	GravityZero = Collision::GetInstance()->getHeight(pos);
	if (pos.y < GravityZero)
	{
		pos.y = GravityZero;
		Gravity = 0;
	}
	//*
	//操作系呼び出し
	//*/

	TransMissionCustom(2);
	StraightSixEngine();

	AirResistance();
	if (car_systems.StartMove == true)
	{
		if (GoalInCheak == false)
		{
			MoveContrl(1.0f);	
		}
		OperationSystem(GetMMode());
	}
	GearInfo();
	RaceSystem();
	ModelCollision();
	StaticForce();
	CorneringForce();
	CentrifugalForce();

	obj->SetPos(pos);
	obj->SetAngle(angle);
	obj->SetScale(scale);
	obj->Update();

	obj2->SetPos(pos);
	obj2->SetAngle(angle);
	obj2->SetScale(scale);
	obj2->Update();


	Vector3 angle2(car_systems.WheelRpm, car_systems.WheelFrontAngle, angle.z);
	Vector3 angle3(-car_systems.WheelRpm, car_systems.WheelFrontAngle -135, angle.z);

	Vector3 angle4(car_systems.WheelRpm, angle.y, angle.z);
	Vector3 angle5(-car_systems.WheelRpm, angle.y - 135, angle.z);

	
	//右後
	Matrix m = *obj2->GetBone(3);
	m *= obj2->TransMatrix;
	Vector3 p(m._41, m._42, m._43);
	obj3->SetPos(p);
	obj3->SetAngle(angle5);
	obj3->SetScale(0.4f);
	obj3->Update();

	//右前
	Matrix m3 = *obj2->GetBone(4);
	m3 *= obj2->TransMatrix;
	Vector3 p3(m3._41, m3._42, m3._43);
	obj5->SetPos(p3);
	obj5->SetAngle(angle3);
	obj5->SetScale(0.4f);
	obj5->Update();

	//右後
	Matrix m4 = *obj2->GetBone(6);
	m4 *= obj2->TransMatrix;
	Vector3 p4(m4._41, m4._42, m4._43);
	obj6->SetPos(p4);
	obj6->SetAngle(angle2);
	obj6->SetScale(0.45);
	obj6->Update();

	//左後
	Matrix m2 = *obj2->GetBone(1);
	m2 *= obj2->TransMatrix;
	Vector3 p2(m2._41, m2._42, m2._43);
	obj4->SetPos(p2);
	obj4->SetAngle(angle4);
	obj4->SetScale(0.4f);
	obj4->Update();
}

/*
	描画系
	ver.1.112 2018/02/22
*/

void Car_A::Render(iexShader*shader,char*chr)
{
	obj->Update();
#ifdef WrieFrameModel
	iexSystem::Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	iexSystem::Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	obj->Render(shader, chr);
	obj2->Render(shader, chr);
	obj3->Render(shader, chr);
	obj4->Render(shader, chr);
	obj5->Render(shader, chr);
	obj6->Render(shader, chr);

	iexSystem::Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

#endif	
	obj->Render(shader, chr);
	obj2->Render(shader, chr);
	obj3->Render(shader, chr);
	obj4->Render(shader, chr);
	obj5->Render(shader, chr);
	obj6->Render(shader, chr);

	char str[256];
	sprintf(str, "%f\n", namakon);
	IEX_DrawText(str, 800, 500, 1920, 1080, 0xffffffff);
}




/*
	レースコース上にAIノードポイント同様、ノードを置く
	今のつくりだとポイントの表裏が存在しないのでセコいことができないこともない状態
	ver.1.112 2018/02/22
*/
Vector3	RaceClearNodePoint[] =
{
	{ 26,1,-83},	//スタート
	{ 1232,1,4324},
	{ 4185,1,9130 },
	{ 4645,1,7780 },
	{ 1274,1,-3828 },
{ -31,1,3736}

};


const int RaceClearNodeMaxNumber = sizeof RaceClearNodePoint / sizeof RaceClearNodePoint[0];
void Car_A::RaceSystem()
{
	//VectorListでnode確保
	std::vector<Vector3>RacSystemNodePoint;

	//ノード初期化
	RacSystemNodePoint.resize(RaceClearNodeMaxNumber);

	//番号あわせ
	for (int i = 0;i < RaceClearNodeMaxNumber;i++)RacSystemNodePoint[i] = RaceClearNodePoint[i];

	//ノードと座標ベクトル
	Vector3 RaceNodeRange;
	RaceNodeRange = RacSystemNodePoint[car_systems.NodeSaveNumber] - pos;
	RaceNodeRange.Normalize();
	//当たり判定
	if (Collision::GetInstance()->ColSphere(pos, 90.0f, RacSystemNodePoint[car_systems.NodeSaveNumber], 120.0f) == true)car_systems.NodeSaveNumber++;

	//最後のノードに到達時、初期化と周回判定
	if (RaceClearNodeMaxNumber == car_systems.NodeSaveNumber)
	{
		car_systems.NodeSaveNumber = 0;
		Weeks++;
	}
	//周回&ゴールチェック
	if (Weeks >UI::GetInstance()->GetEndLap() )
	{
		GoalInCheak = true;
		Weeks = UI::GetInstance()->GetEndLap();
	}
}

/*
	ボーン番号がわかり次第+ボーンつけてからの判断
	ver.1.112 2018/02/22
*/
void Car_A::BornControl(int num, const Vector3&p)
{
	Update();

	//行列
	Matrix mat = *GetBone(num)*TransMatrix;
	Vector3 front(mat._21, mat._22, mat._23);
	front.Normalize();

	Vector3 vec = p - Vector3(mat._41, mat._42, mat._43);
	vec.Normalize();
	//逆行列
	D3DXMatrixInverse(&mat, NULL, &mat);
	Vector3 frontL, vecL;
	frontL.x = front.x*mat._11 + front.y*mat._21 + front.z*mat._31 + 0 * mat._41;
	frontL.y = front.x*mat._12 + front.y*mat._22 + front.z*mat._32 + 0 * mat._42;
	frontL.z = front.x*mat._13 + front.y*mat._23 + front.z*mat._33 + 0 * mat._43;

	vecL.x = vec.x*mat._11 + vec.y*mat._21 + vec.z*mat._31;
	vecL.y = vec.x*mat._12 + vec.y*mat._22 + vec.z*mat._32;
	vecL.z = vec.x*mat._13 + vec.y*mat._23 + vec.z*mat._33;

	frontL.Normalize();
	vecL.Normalize();

	Vector3 axis;
	Vector3Cross(axis, frontL, vecL);
	axis.Normalize();

	float c = Vector3Dot(frontL, vecL);
	float rad = acosf(c);

	Quaternion q;
	q.x = axis.x*sin(rad / 2);
	q.y = axis.y*sin(rad / 2);
	q.z = axis.z*sin(rad / 2);
	q.w = cos(rad / 2);

	CurPose[num] *= q;
	UpdateBoneMatrix();
	UpdateSkinMesh();
}