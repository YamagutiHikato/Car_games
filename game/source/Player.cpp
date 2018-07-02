#include "iextreme.h"
#include "Player.h"
#include "UI_Texture.h"

#include <random>

#define DebugDrawText
#define SolidFrameModel
//#define WrieFrameModel

/*
	エンジンの変動爆発
*/
std::random_device randomDevice;
std::mt19937 randomEngine(randomDevice());

std::uniform_real_distribution<float>ExplosionChangeTheNumberOfTimes(30.0f*0.2f, 30.0f*1.0f);
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
	NodeSaveNumber = 0;
	Gear = GearMax = 1;
	LevLimit = 0;
	SpeedMeter = 0;
	missionMode =0;
	stackGear = 0;

	color = LevColor = 0xffffffff;
	speed = 0.0;
	idlingBreakSpeed = 0.0;
	SpeedHandle = 0;
	FinalLapTime = 60 * 3;
	/*
		float
	*/
	OtationalSpeed = 0.0f;
	BreakingPower = 0.0f;
	SubBreakingPower=0.0f;
	DRR = 0.0f;
	ERatio = 0.0f;
	FirnalRGR = 0.0f;
	HighSpeed = 0.9f;
	MaxSpeed = 0.0f;
	RGR = 0.0f;
	scale = 0.0f;
	SelecterReductionGearRation = 0.0f;
	SlowSpeed = 0.8f;
	Throttle = 0.0f;
	ThrottleTacoMetter = 0.0f;
	weght = 0.0f;
	FinalGearRatio = 0.0f;
	SpeedMeter = 0.0f;
	rpm = 0.0f;
	AtmosphericPressure=1013.25f;
	DensityOfAir = 0.0f;
	AirResistanceCoefficient = 0.0f;
	FrontProjectionAreaOfTheAutomobile = 0.0f;
	Air_Speed = 0.0f;
	AirResistanceRealValue = 0.0f;
	AcceleratingForce = 0.0f;
	horsePower = 0.0f;
	Max_HorsePower = 0.0f;
	PowerToWeightRatio = 0.0f;
	crankShaft = 0.0f;
	spinNum = 0.0f;
	CrankSpinNum = 0.0f;
	torque = 0.0f;
	EngineDisplacement = 0.0f;
	torqueOtationalSpeed = 0.0f;
	HalfDRR = 0.0f;
	MaxTorque = 0.0f;
	torqueMaxOS = 0.0f;
	torquePower = 0.0f;
	rollingResistance = 0.0f;
	myu = 0.0f;
	num = 0.0f;
	
	BackThrottle = 0.0f;
	ShiftChangeLevs=0.0f;

	WheelFrontAngle = 0.0f;

	/*
		bool
	*/

	BackCheak = false;
	FinalGear = false;
	StartMove = false;
	GearDelay = false;
	StartMove = false;
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
	GearMax = 5;				//ギア

	LevLimit = OverLevMax*1000;
	
	Inline_Six_Engine[0] = MaxPis*0.0f;//1
	Inline_Six_Engine[1] = MaxPis*0.8f;//2
	Inline_Six_Engine[2] = MaxPis*0.4f;//3
	Inline_Six_Engine[3] = MaxPis*1.0f;//4
	Inline_Six_Engine[4] = MaxPis*0.2f;//5
	Inline_Six_Engine[5] = MaxPis*0.6f;//6

	for (int i = 0;i < 6;i++) step[i] = 0;
	ShiftCheakNum = 1;
	
	/*
		float
	*/
	GearRatio[0] = 3.369f;		//R速
	GearRatio[1] = 3.214f;		//1速
	GearRatio[2] = 1.925f;		//2速
	GearRatio[3] = 1.302f;		//3速
	GearRatio[4] = 1.000f;		//4速
	GearRatio[5] = 0.752f;		//5速

	FinalGearRatio = 4.111f;

	scale = 0.5f;

	/*
		車体部分
	*/
	DRR = 631.0f;			//タイヤの直径(外径)mm   DynamicRollingRadius
	HalfDRR = DRR / 2;
	weght = 1780.7f;/*1200.0f*/

	RGR = 2.98377f;
	FirnalRGR = 3.43441f;
	GearDelay = 0.0f;
	crankShaft = 0.0f;
	for (int i = 0;i < MaxSilinderAve;i++)CrankSpinAverage[i] = 0.0f;
	/*
		UI部分
	*/
	metterAngle = 0.0f;
	/*
		エンジン部分
	*/
	IC = 0;
	SilinderSpeed = 60;	//ピストン速度
	spinNum = 0;
	CrankSpinNum = 0;
	crankShafter = ExplosionChangeTheNumberOfTimes(randomEngine);	//１気筒の１工程から回されるシャフト回転数
	MaxPis = 120;
	sum = 0.0f;
	arrayMaxNum=0;
	averagenumber = 0.0f;
	torqueMaxOS = 4400.0f;
	/*
		タイヤ部分
	*/
	RightFrontWheel = LeftFrontWheel = RightRearWheel = LeftRearWheel = 0.0f;
	TheOuterCircumferenceOfTheTire = 0.0f;
	MinLength = 0.0f;
	WheelRpm = 0.0f;
	TaiyaAngle=ZEROVECTOR;
	WheelGrep = 1.0f;
	/*
		ハンドル部分
	*/
	HandleBar = 0.0f;
	PowerSlinder = 0.0f;
	KnuckleArm = 0.0f;
	/*
		物理挙動関連
	*/
	centrifugal =Rad =Fc = sita =RollHeight
	=tread =Spring =RollStiffness_F = RollStiffness_R = 0.0f;
	θaccel = θbrake = 0.0f;
	 OverBlock = 0;
	 wallWeght = 2300.0f;
	 weghtRef = 1200 * 0.8f;
	 wallRef = wallWeght*0.8f;
	/*
		bool
	*/
	StartMove = false;

	/*
		エンジンルーム
	*/
	Engine_parts.TargetInitialization(0.0f);
	for (int i = 0;i < 6;i++)Engine_parts.Battery[i] = 0.0f;
	hydraulic = 0.0f;
	/*
		ギアとミッション関係
	*/
	Engine_Gearmissions.TargetInitialize(0.0f);
	for (int i = 0;i < MaxSilinderAve;i++)
	{
		Engine_Gearmissions.CrankSpinAverage[i] = Engine_Gearmissions.IdlingCrankSpinAverage[i] =0.0f;
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

	OverBlock = (weght * speed + wallWeght -weghtRef + wallRef)/3600;
	//if (OverBlock <= 0.0f)OverBlock = 0.0f;
	//前方
	work = Collision::GetInstance()->getFront(pos);
	if (pos.z > work - CollisionRangeNumericalValue)
	{		
		Throttle -= OverBlock/1000;
		//speed -= OverBlock;
		pos.z = work - CollisionRangeNumericalValue;
	}

	//後方
	work = Collision::GetInstance()->getBack(pos);
	if (pos.z < work + CollisionRangeNumericalValue)
	{
		Throttle -= OverBlock/1000;
		//speed -= OverBlock;
		pos.z = work + CollisionRangeNumericalValue;
	}

	//右
	work = Collision::GetInstance()->getRight(pos);
	if (pos.x > work - CollisionRangeNumericalValue)
	{
		Throttle -= OverBlock/1000;
		//speed -= OverBlock;
		pos.x = work - CollisionRangeNumericalValue;
	}
	//左
	work = Collision::GetInstance()->getLeft(pos);
	if (pos.x < work + CollisionRangeNumericalValue)
	{
		Throttle -= OverBlock/1000;
		//speed -= OverBlock;
		pos.x = work + CollisionRangeNumericalValue;
	}
}

/*
	左スティックの傾きからハンドルへ伝える制御系
	ver.1.112 2018/02/22
*/

bool Car_A::MoveContrl(float max)
{
	static float moveSpeed;
	//	加速
	moveSpeed += 0.3f;
	if (moveSpeed > max) moveSpeed = max;
	//	軸の傾きの取得
	float axisX = KEY_GetAxisX()*0.002f;
	//　軸の傾きと長さ
	float d = sqrtf(axisX * axisX);
	//	軸の傾きの遊び
	if (d < 0.3f) 
	{
		moveSpeed = 0;
		HandleBar = 0.0f;

		if (PowerSlinder > 5.0f)PowerSlinder -= 9.0f;
		if (PowerSlinder < -5.0f)PowerSlinder += 9.0f;
		else if (PowerSlinder <= 5.0f && PowerSlinder >= -5.0f)PowerSlinder = 0.0f;

		if (KnuckleArm > 0.05f)KnuckleArm -= 0.05f;
		if (KnuckleArm < -0.05f)KnuckleArm += 0.05f;
		else if (KnuckleArm <= 0.05f && KnuckleArm >= -0.05f)KnuckleArm = 0.0f;
		
		return  false; 
	}
	//	軸の傾き補正
	if (d > 1.0f)
	{ 
		axisX /= d;
	}
	//ハンドル関数へ移行
	PowerSteering(axisX*SpeedHandle);
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
	HandleBar = HandlePower;
	/*
	ハンドルの角度調整
	ハンドルシャフトの回転を求める
	*/
	HandleBar *= PI / 180.0f;
	HandleBar *= 360.0f;	//調整数値
	/*
	パワーシリンダーに接続
	ハンドルは回転するのに対し、パワーシリンダーは左右にしかゆれない
	*/
	PowerSlinder += HandleBar*1.2f;
	/*
	パワーシリンダーから制御
	MaxPowerSlinderLength = シリンダーの長さの半分に指定
	*/
	float HalfSilinderLength = MaxPowerSlinderLength / 2;
	if (PowerSlinder > HalfSilinderLength)PowerSlinder = HalfSilinderLength;
	else if (PowerSlinder < -HalfSilinderLength)PowerSlinder = -HalfSilinderLength;
	//パワーシリンダーからナックルアームに接続
	KnuckleArm = PowerSlinder*PI/360.0f;

	return  KnuckleArm;
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
	WheelFrontAngle = angle.y + KnuckleArm*0.30f;
	{
		//正面
		Vector3 VecAngle;

		//伝達調整数値
		float TransmissionTimingNumbers = 14.0f;

		VecAngle.x = sinf(angle.y);
		VecAngle.y = 0.0f;
		VecAngle.z = cosf(angle.y);

		//タイヤの角度に伝達
		TaiyaAngle.x = pos.x + sinf(WheelFrontAngle) * TransmissionTimingNumbers;
		TaiyaAngle.z = pos.z + cosf(WheelFrontAngle) * TransmissionTimingNumbers;

		//座標反映
		pos.x += sinf(angle.y)*(speed*0.03f);
		pos.z += cosf(angle.y)*(speed*0.03f);

		//タイヤの角度伝達最更新
		TaiyaAngle.x = pos.x + sinf(WheelFrontAngle) * TransmissionTimingNumbers;
		TaiyaAngle.z = pos.z + cosf(WheelFrontAngle) * TransmissionTimingNumbers;

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
		float SteerPower;
		SteerPower = speed * 0.0055f;
		if (SteerPower >= 0.5)SteerPower = 0.5f;
		if (cross.y > .0f)angle.y += dAngle * SteerPower;
		else angle.y -= dAngle * SteerPower;
	}

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
	if (GearDelay == false)//クラッチが繋がれるまでスロットル制御
	{
		Throttle += AcceleratingForce * (KEY_GetAxisY3()*0.02f);//調整の為に2倍　
		torqueOtationalSpeed += AcceleratingForce  * (KEY_GetAxisY3()*0.01f);
		ThrottleTacoMetter += AcceleratingForce * (KEY_GetAxisY3()*0.02f);
		ShiftCheakNum = Gear;
	}
	else
	{	
		if (ThrottleTacoMetter >= ShiftChangeLevs)
		{
			GearDelay = false;//クラッチ繋ぎの接続完了までの時間	
		}
	}
	Throttle -= Throttle*0.005f;//押してなかったら空	抜け方は割合減算
	ThrottleTacoMetter -= ThrottleTacoMetter*0.005f;
	torqueOtationalSpeed -= ThrottleTacoMetter*0.0025f;

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

	BreakingPower += (0.8 / (0.7 * 140 * 2))* (KEY_GetAxisX3()*0.001f);	//制動力　
	torqueOtationalSpeed -= BreakingPower;
	Throttle -= BreakingPower;
	ThrottleTacoMetter -= BreakingPower;

	//else BreakingPower = 0.0f;//押してなかったら空

	//バック
	if (KEY_Get(KEY_D) == 1)
	{
		if (BackCheak == false)
		{
			stackGear = Gear;
			BackCheak = true;
		}

		BackThrottle += AcceleratingForce*8.0f;//調整の為に2倍　
		Throttle -= BackThrottle;
		ThrottleTacoMetter = Throttle;
		torqueOtationalSpeed += AcceleratingForce;
		Gear = 0;

	}
	else
	{
		BackThrottle -= BackThrottle*0.025f;//押してなかったら空	抜け方は割合減算

		if (BackCheak == true)
		{
			BackCheak = false;
		}
	}
	/*
		簡易サイドブレーキ
	*/

	if (KEY_Get(KEY_R2) == 1)
	{
		SubBreakingPower += 0.8 / (0.7 * 140 * 2) / 8;	//制動力　
		Throttle -= SubBreakingPower;
		ThrottleTacoMetter = Throttle;
		torqueOtationalSpeed -= SubBreakingPower;
	}
	else SubBreakingPower = 0.0f;//押してなかったら空

/*
	前のギアと現在のギア等を計算することで反映

	AT完成
*/
	if (n == GearMode::AT)
	{
		if (Throttle<= (torqueMaxOS / 1000) / GearRatio[Gear - 1] * GearRatio[Gear])
		{
			if (Gear > 1)
			{
				Gear--;
				Throttle = Throttle / GearRatio[Gear + 1] * GearRatio[Gear];
				ThrottleTacoMetter = ThrottleTacoMetter / GearRatio[Gear + 1] * GearRatio[Gear];
				torqueOtationalSpeed = torqueOtationalSpeed / GearRatio[Gear + 1] * GearRatio[Gear];
			}
		}

		if (Throttle > OverLevMax)//シフトアップ AT
		{
			if (Gear < 5)
			{
				Gear ++;
				Throttle = Throttle / GearRatio[Gear - 1] * GearRatio[Gear];
				ShiftChangeLevs = ThrottleTacoMetter / GearRatio[Gear - 1] * GearRatio[Gear];
				ThrottleTacoMetter=ThrottleTacoMetter / GearRatio[Gear - 1] * GearRatio[Gear];
				torqueOtationalSpeed = torqueOtationalSpeed / GearRatio[Gear - 1] * GearRatio[Gear];
				GearDelay = true;

			}
		}
	}

	else if (n == GearMode::MT)
	{
		if (KEY_Get(KEY_L2) == 1 && KEY_Get(KEY_A) == 3)
		{
			if (Gear > 1)
			{
				Gear--;
				Throttle = Throttle / GearRatio[Gear + 1] * GearRatio[Gear];
				ThrottleTacoMetter = ThrottleTacoMetter / GearRatio[Gear + 1] * GearRatio[Gear];
				torqueOtationalSpeed = torqueOtationalSpeed / GearRatio[Gear + 1] * GearRatio[Gear];
			}
		}

		if (KEY_Get(KEY_L2) == 1 && KEY_Get(KEY_B) == 3)//シフトアップ MT
		{
			if (Gear < 5)
			{
				Gear++;
				Throttle = Throttle / GearRatio[Gear - 1] * GearRatio[Gear];
				ShiftChangeLevs = ThrottleTacoMetter / GearRatio[Gear - 1] * GearRatio[Gear];
				ThrottleTacoMetter = ThrottleTacoMetter / GearRatio[Gear - 1] * GearRatio[Gear];
				torqueOtationalSpeed = torqueOtationalSpeed / GearRatio[Gear - 1] * GearRatio[Gear];
				GearDelay = true;
			}
		}
	}

	if (Throttle > (OverLevMax + 0.2f) && Gear<=4)Throttle = OverLevMax - 0.2f;
	if (Throttle < 0.0f)Throttle = 0.0f;	//Max 0%
	if (ThrottleTacoMetter > (OverLevMax + 0.3f))ThrottleTacoMetter = OverLevMax;
	if (ThrottleTacoMetter < 0.00f)ThrottleTacoMetter = 0.00f;

	if (BackThrottle > (OverLevMax - 6))	BackThrottle = OverLevMax - 6;
	if (BackThrottle < 0.00f)BackThrottle = 0.00f;	//Max 0%

	if (BreakingPower > 0.05f)BreakingPower = 0.05f;	//100%
	if (BreakingPower < 0.001f)BreakingPower = 0.001f;	//0%

	if (torqueOtationalSpeed > 4.4f)torqueOtationalSpeed = 4.4f;
	if (torqueOtationalSpeed <= 0.0f)torqueOtationalSpeed = 0.0f;
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
	Engine_parts.CrankShaft = 0.0f;
	Engine_parts.ComShaft = 0.0f;
	Engine_Gearmissions.num = Engine_Gearmissions.num2 = 0;

	//num = 0;

	//エンジンの起動
	for (int i = 0;i < 6;i++)SilinderUpdate(i, Engine_parts.ConectingRod);

	{
		//エンジン状態を毎秒記録する
		Engine_Gearmissions.CrankSpinAverage[Engine_Gearmissions.CylinderAverages] =
			((2 * (0.25f / 1000)*(Engine_parts.CrankShaft / 360)) * 3600) * 2;
		Engine_Gearmissions.IdlingCrankSpinAverage[Engine_Gearmissions.CylinderAverages] =
			Engine_Gearmissions.CrankSpinAverage[Engine_Gearmissions.CylinderAverages];
		//ここで過給圧を配置（下でコメントアウトしてるやつ)　結果、エンジン効率が上がった
		Engine_Gearmissions.CrankSpinAverage[Engine_Gearmissions.CylinderAverages] +=
			(Throttle - BackThrottle);

		if (Engine_Gearmissions.CylinderAverages >= MaxSilinderAve - 1)
			Engine_Gearmissions.CylinderAverages = 0;else Engine_Gearmissions.CylinderAverages++;

		//配列最大数
		Engine_Gearmissions.ArrayMaxNumber = sizeof(Engine_Gearmissions.CrankSpinAverage) / sizeof(Engine_Gearmissions.CrankSpinAverage[0]);

		for (int i = 0;i < MaxSilinderAve;i++)
		{
			Engine_Gearmissions.num += Engine_Gearmissions.CrankSpinAverage[i];
			Engine_Gearmissions.num2 += Engine_Gearmissions.IdlingCrankSpinAverage[i];
		}

		//平均を取得
		Engine_Gearmissions.AverageNumber = Engine_Gearmissions.num / Engine_Gearmissions.ArrayMaxNumber;
		torqueOtationalSpeed = Engine_Gearmissions.AverageNumber / 2;
		Engine_Gearmissions.IdlingAverageNumber = Engine_Gearmissions.num2 / Engine_Gearmissions.ArrayMaxNumber;
		Engine_Gearmissions.CrankNumberOfRevolutionsPerSecond = Engine_Gearmissions.AverageNumber;	//!クランクシャフト
		Engine_Gearmissions.UICrankNumberOfRevolutionsPerSecond = Engine_Gearmissions.AverageNumber;	//!タコメータ反映
		idlingBreakSpeed = Engine_Gearmissions.IdlingAverageNumber;	//!アイドリング状態反映
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
	EngineDisplacement = (86.0f / 2)*(86.0f / 2)*PI*73.7f*6;//ボアの半分の2乗　×　π　×　ストローク　×　気筒数
	EngineDisplacement /= (int)1000;
	torque = 22 * (EngineDisplacement) * 0.5f / (2 * PI) /pow(9.806652f,2);//(正味平均有効圧力(22)）×（排気量）×（爆発回数(4サイクルであれば0.5)）／（2π）
	MaxTorque = Max_HorsePower * 75.0f * 60.0f / LevLimit * 2 * PI;
	
	/*
	デフ比(減速比		ReductionGearRatio
	*/
	if (Gear < GearMax)SelecterReductionGearRation = FirnalRGR;
	else SelecterReductionGearRation = RGR;

	/*
	トランスミッション効率
	*/
	if (torqueMaxOS >= OtationalSpeed)		ERatio = SlowSpeed;
	if (torqueMaxOS < OtationalSpeed)		ERatio = HighSpeed;

	/*
		タイヤ半径
	*/
	HalfDRR = DRR / 2;
	/*
	トラクション
	*/

	traction = (Front*(torquePower)*Throttle*GearRatio[Gear] * SelecterReductionGearRation * ERatio) / HalfDRR;

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
	DensityOfAir = AtmosphericPressure / (2.87f*(temperature + 273.15f));
	/*
	空気抵抗係数
	*/
	AirResistanceCoefficient = 0.4f;
	/*
	自動車の正面投影面積
	*/
	FrontProjectionAreaOfTheAutomobile = (1.340f * 1.755f * 0.8f);
	/*
	/*
	速度
	*/
	Air_Speed =(float) pow(speed,2);
	/*
	空気抵抗
	*/
	AirResistanceRealValue = (AirResistanceCoefficient*FrontProjectionAreaOfTheAutomobile*Air_Speed*DensityOfAir) / 2;
	AirResistanceRealValue /= pow(60,3);	//現在空気抵抗軽減無
	return Vector3(sinf(AirResistanceRealValue), 0.0f, cosf(AirResistanceRealValue));
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

	myu = 0.015f;//真下に光線を飛ばし、返し値でμを変動させるべき所だが、今回は変動なし
	rollingResistance = myu*weght*9.8f;
	
	return Vector3(sinf(rollingResistance),0,cosf(rollingResistance));
}
/*
	静止力
	ver.1.112 2018/02/22
*/
Vector3 Car_A::StaticForce()
{
	return -Traction()*weght*0.05f;
}

/*
	遠心力

*/

float Car_A::CentrifugalForce()
{
	//旋回半径=ホイールベース(M)/sin(実舵角)
	Rad = (2.615f) / sin(cross.y);
	//遠心力=車重/重力加速度*速度2/旋回半径
	Fc = (weght / 9.8f) * (pow(speed, 2) /Rad);
	Fc /= 10000;
	//ロール
	RollHeight = 1.325f / 3;//ロールセンターから重心までの距離
	tread = 1460/1000;//トレッド幅
	Spring = RollHeight*9.8f;//サスペンションモーメント

	RollStiffness_F = (5700*pow(tread, 2)) / 2;//ロール剛性 前
	RollStiffness_R = (4000*pow(tread, 2)) / 2;//ロール剛性 後
	
	/*
	ロールアップ
	ロール効果は極小
	*/
	sita = (Fc*RollHeight) / ((RollStiffness_F+ RollStiffness_R) - (Spring*RollHeight));
	
	θaccel = (Throttle*RollHeight) / ((4000 * (-4.530f / 2 - 2.615f)*2.625f) - (Spring*RollHeight));
	θbrake = (BreakingPower*RollHeight) / ((5700 * (4.530f / 2 - 2.615f)*2.625f) - (Spring*RollHeight));
	//ロール反映
	angle.x = (speed*(θaccel - θbrake))* CorneringForce().x;

	//左右に揺れる角度(angle.z)をロールで反映
	angle.z = sita* CorneringForce().z;//

	//デバッグデータ
	centrifugal = Fc;

	return Fc;
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
	rpm = Engine_Gearmissions.CrankNumberOfRevolutionsPerSecond;
	rpm *= 1000;
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

	bunsi_A = ((255 * 0.40f * 2 + 17 * 25.4f)*PI*(rpm -(idlingBreakSpeed*1000)));
	//!シフトチェンジ時に前の計算数値を次のギアに渡してシャフト抜けを改善する
	bunbo_A = (GearRatio[ShiftCheakNum] * FirnalRGR);
	bunsi_B = 60;
	bunbo_B = pow(10, 6);
	SpeedSaved = (bunsi_A/ bunbo_A) * (bunsi_B/ bunbo_B);
	
	speed = (SpeedSaved)*RollingResistance().Length();
	//トルク回転数
	torquePower = 2 * PI *torque*(rpm)/60/1000;

	/*
	1.3962kW ＝ 1.0馬力
	
	*/
	//馬力 PTO軸トルク（Kg・m）＊PTO軸回転数（RPM）Ｘ 2π ／ ( 75 Ｘ 60 )
	horsePower = torque * (torqueOtationalSpeed * 1000) * (2 * PI) / (75 * 60);
	//最高馬力
	//（回転数 rpm) ×（トルク kgfm）／1000 × 1.3962
	Max_HorsePower= torque * torqueMaxOS * (2 * PI) / (75 * 60);
	//空回りするトルクを制御
	if (horsePower <= 0.0f)
	{
		PowerToWeightRatio = 0;
	}
	//パワーウェイトレシオ	調べた限りだとデータ　加速力に影響するものでもないという判断
	else
	{
		PowerToWeightRatio = weght / Max_HorsePower;
	}

	//加速力=トルク*重力加速度*ギア比/タイヤの半径/車重
	if (Gear <= 4)
	{
		AcceleratingForce = ((torquePower* 9.8f*(GearRatio[Gear] * RGR) / (HalfDRR / 1000)) / weght) - AirResistanceRealValue;
	}
	if (Gear == 5)
	{
		AcceleratingForce = ((torquePower* 9.8f*(GearRatio[Gear] * FirnalRGR) / (HalfDRR / 1000)) / weght) - AirResistanceRealValue;
	}

	AcceleratingForce /= 900;

	/*x
	シフト設定
	*/
	if ( Gear >= 5)Gear = 5;

	if (Gear <= 1 && BackCheak==false)	Gear = 1;									     //１速は下回らない(後退は今度
	else if(Gear <= 1 && BackCheak == true)	Gear = 0;

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
		Engine_parts.CyLinderHead[n] -= CylinderSpeed;
	}
	//空気を吸入後、圧縮工程へ
	if (step[n] == 0 && Engine_parts.CyLinderHead[n] < 0.0f)
	{
		step[n]++;

		//インジェクター吸引	空気の計算はキリが無いので1か0の動きだけ
		Engine_parts.Injecter += AirInjector(randomEngine);

		//ラジエーターの吸熱
		Engine_parts.Radiator -= Engine_parts.Injecter;

		//エンジンブロック貫かないように制限
		Engine_parts.CyLinderHead[n] = 0.0f;
	}
	//*************************************************************************************
	//			step 2			圧縮
	//*************************************************************************************
	//空気を押し上げる
	if (step[n] == 1)
	{
		Engine_parts.CyLinderHead[n] += CylinderSpeed;
	}

	if (step[n] == 1 && Engine_parts.CyLinderHead[n] >60.0f)
	{
		step[n]++;

		//エンジンブロック貫かないように制限
		Engine_parts.CyLinderHead[n] = 60.0f;

	}
	//*************************************************************************************
	//		step 3			燃焼
	//*************************************************************************************
	if (step[n] == 2)
	{
		Engine_parts.CyLinderHead[n] -= CylinderSpeed;
	}
	if (step[n] == 2 && Engine_parts.CyLinderHead[n] <0.0f)
	{
		step[n]++;
		//点火プラグ終了
		Engine_parts.Battery[n] = 0.0f;
		//エンジンブロック貫かないように制限
		Engine_parts.CyLinderHead[n] = 0.0f;
	}
	if(step[n] == 2 && Engine_parts.CyLinderHead[n] >0.0f)
	{
		//燃焼=点火プラグをスパーク　抜けるまで回転を繰り返す
		Engine_parts.Battery[n] = 1;
		//回転数にズレを起こさない調整シャフト
		Engine_parts.TimingBelt = ExplosionChangeTheNumberOfTimes(randomEngine)*n;
		//カムシャフトとクランクシャフトが回転
		Engine_parts.CrankShaft += Engine_parts.TimingBelt;
		Engine_parts.ComShaft += Engine_parts.TimingBelt / 2;
		//温度調整
		Engine_parts.EngineOil =Engine_parts.TimingBelt;
		Engine_parts.Radiator = Engine_parts.EngineOil;

	}
	//*************************************************************************************
	//		step 4			排気
	//*************************************************************************************
	if (step[n] == 3)
	{
		Engine_parts.CyLinderHead[n] += CylinderSpeed;
	}
	if (step[n] == 3 && Engine_parts.CyLinderHead[n] > 60.0f)
	{
		step[n] = 0;
		//インジェクター排気
		Engine_parts.Injecter+= AirInjector(randomEngine);

		//エンジンブロック貫かないように制限
		Engine_parts.CyLinderHead[n] = 60.0f;

		//ラジエータの熱を解放
		Engine_parts.Radiator += Engine_parts.Injecter;

	}

	//水冷制限
	if (Engine_parts.Radiator > 100)Engine_parts.Radiator = 100;
	if (Engine_parts.Radiator < 0)Engine_parts.Radiator = 0;

	//温度制限
	if (Engine_parts.EngineOil > 100)Engine_parts.EngineOil = 100;
	if (Engine_parts.EngineOil < 0)Engine_parts.EngineOil = 0;
}

/*
	タイヤ伝達
*/

void Car_A::WheelProcess()
{
	/*
		タイヤの外周
	*/
	TheOuterCircumferenceOfTheTire = ((DRR)*PI)/1000;
	/*
		タイヤの1分間に進む距離
	*/
	MinLength += speed*1000/ 216000;
	/*
		タイヤの回転数
	*/
	WheelRpm = MinLength / TheOuterCircumferenceOfTheTire;
	int WheelConvert = WheelRpm;
	WheelRpm = WheelRpm - WheelConvert;
	WheelRpm = PI * 2 * WheelRpm;

	RightRearWheel = LeftRearWheel = WheelRpm;
}

/*
	更新処理
*/
static int DelayTimer = 60;
void Car_A::Update()
{
	Engine_parts.ConectingRod = 24.0f;
	
	Traction();
	SpeedHandle = 1.0f;
	metterAngle = Engine_Gearmissions.UICrankNumberOfRevolutionsPerSecond / 3;
	SpeedMeter  =(float) speed / 90;

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

	TransMissionCustom(AT);
	StraightSixEngine();

	AirResistance();
	if (StartMove == true)
	{
		if (GoalInCheak == false)
		{
			MoveContrl(1.0f);	
		}
		OperationSystem(missionMode);
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


	Vector3 angle2(WheelRpm, WheelFrontAngle, angle.z);
	Vector3 angle3(-WheelRpm, WheelFrontAngle -135, angle.z);

	Vector3 angle4(WheelRpm, angle.y, angle.z);
	Vector3 angle5(-WheelRpm, angle.y - 135, angle.z);

	
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

	//早すぎてわからない数値を2秒枚に更新させる
	DelayTimer--;
	if (DelayTimer <= 0)
	{
		DelayCrankShaft = Engine_parts.CrankShaft;
		DelayTimer = 60;
	}
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
	obj->Render (shader, chr);
	obj2->Render(shader, chr);
	obj3->Render(shader, chr);
	obj4->Render(shader, chr);
	obj5->Render(shader, chr);
	obj6->Render(shader, chr);

	iexSystem::Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
#endif

#ifdef SolidFrameModel
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
	RaceNodeRange = RacSystemNodePoint[NodeSaveNumber] - pos;
	RaceNodeRange.Normalize();
	//当たり判定
	if (Collision::GetInstance()->ColSphere(pos, 90.0f, RacSystemNodePoint[NodeSaveNumber], 120.0f) == true)NodeSaveNumber++;

	//最後のノードに到達時、初期化と周回判定
	if (RaceClearNodeMaxNumber == NodeSaveNumber)
	{
		NodeSaveNumber = 0;
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