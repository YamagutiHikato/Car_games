#include "Enemy.h"


#include <random>
using namespace std;

#define ZEROVECTOR Vector3(0.0f, 0.0f, 0.0f)
#define Default_LevMeter 1000


/*
	Base
*/
B_Enemy::B_Enemy()
{
	Init();
}

B_Enemy::~B_Enemy()
{

}

bool B_Enemy::Init()
{
	/*
		AI
	*/
	//順繰り変数保持用
	CatchNodeNumber = 0;
	testTimer = 0;


	/*
	Vector3
	*/
	pos = ZEROVECTOR;
	angle = ZEROVECTOR;
	Front = ZEROVECTOR;
	Break = ZEROVECTOR;
	traction = ZEROVECTOR;
	TaiyaAngle = ZEROVECTOR;
	cross = ZEROVECTOR;
	/*
		int
	*/
	Gear = GearMax = 1;
	LevLimit = 0;
	SpeedMeter = 0;
	missionMode = 0;

	speed = 0.0;
	idlingBreakSpeed = 0.0;

	/*
		float
	*/
	OtationalSpeed = 0.0f;
	BreakingPower = 0.0f;
	SubBreakingPower = 0.0f;
	DRR = 0.0f;
	ERatio = 0.0f;
	GearDelay = 0.0f;
	FirnalRGR = 0.0f;
	HighSpeed = 0.9f;
	MaxSpeed = 0.0f;
	RGR = 0.0f;
	scale = 0.0f;
	SelecterReductionGearRation = 0.0f;
	SlowSpeed = 0.8f;
	Throttle = 0.0f;
	weght = 0.0f;
	FinalGearRatio = 0.0f;
	SpeedMeter = 0.0f;
	rpm = 0.0f;
	AtmosphericPressure = 1013.25f;
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
	torqueMaxOS = 5900.0f;
	torquePower = 0.0f;
	rollingResistance = 0.0f;
	μ = 0.0f;
	num = 0.0f;
	BackThrottle = 0.0f;
	WheelFrontAngle = 0.0f;
	/*
		bool
	*/
	FinalGear = false;
	StartMove = false;
	AI_Throttle = false;
	AI_BreakThrottle = false;
	AI_BackThrottle = false;
	StartMove = false;


	return true;
}


Car_A_E::Car_A_E()
{
	Init();
}

Car_A_E::~Car_A_E()
{
	delete metterA;
	delete metterB;
	delete metterC;
	delete HandleTex;
	delete obj;
}

bool Car_A_E::Init()
{
	B_Enemy::Init();;
	/*
	pointer
	*/
	obj = new iexMesh("DATA\\CAR\\TestModel_A.IMO");
	obj2 = new iex3DObj("DATA\\CAR\\TestModel_B.IEM");
	obj3 = new iexMesh("DATA\\CAR\\TestModel_C.IMO");
	obj4 = new iexMesh("DATA\\CAR\\TestModel_C.IMO");
	obj5 = new iexMesh("DATA\\CAR\\TestModel_D.IMO");
	obj6 = new iexMesh("DATA\\CAR\\TestModel_D.IMO");

	/*
	Vector3
	*/
	pos = Vector3(2.0f, 1.0f, -53.0f);
	cross = ZEROVECTOR;
	Getcross = ZEROVECTOR;
	/*
	int
	*/
	HandleMode = 0;
	indexNumber = -1000;
	Gear = 1;
	GearMax = 4;				//ギア
	LevLimit = OverLevMax * 1000;

	spinNum = 0;
	CrankSpinNum = 0;

	Inline_Four_Engine[0] = MaxPis*0.80;//1
	Inline_Four_Engine[1] = MaxPis*0.20;//2
	Inline_Four_Engine[2] = MaxPis*0.60;//3
	Inline_Four_Engine[3] = MaxPis*0.40;//4

	for (int i = 0;i < 4;i++)step[i] = 0;
	ShiftCheakNum = 1;

	/*
	float
	*/
	GearRatio[0] = 2.844f;		//R速
	GearRatio[1] = 2.193f;		//1速
	GearRatio[2] = 1.952f;		//2速
	GearRatio[3] = 1.401f;		//3速
	GearRatio[4] = 1.000f;		//4速
	GearRatio[5] = 0.892f;		//5速

	crankShaft = 0.0f;

	for (int i = 0;i < 18;i++)
	{
		CrankSpinAverage[i] = 0.0f;
	}

	scale = 0.5f;

	weght = 1020.9f;

	RGR = 3.885f;
	FirnalRGR = 4.2f;

	GearDelay = 0.1f;

	FinalGearRatio = 4.312f;

	torque = 0.0f;	//トルク r.p.m

	DRR = 592.4f;	//タイヤの直径(外径)mm   DynamicRollingRadius

	IC = 0;

	SilinderSpeed = 60.0f;	//ピストン速度
	crankShafter = 30.0f;	//１気筒の１工程から回されるシャフト回転数
	MaxPis = 120;
	sum = 0.0f;
	arrayMaxNum = 0;
	averagenumber = 0.0f;
	spinNum = 0;

	/*
	ハンドル部分
	*/
	HandleBar = 0.0f;
	PowerSlinder = 0.0f;
	KnuckleArm = 0.0f;

	/*
	物理挙動関連
	*/
	centrifugal = Rad = Fc = θ = RollHeght = tread = Spring = RollStiffness_F = RollStiffness_R = 0.0f;
	θaccel = θbrake = 0.0f;

	SpeedHandle = 0;

	RightIndex = LeftIndex = 0;

	/*
	bool
	*/
	return true;

}


/*
簡易当たり判定
*/

void Car_A_E::ModelCollision()
{
	float work = 0;
	
	work = Collision::GetInstance()->getFront(pos);
	if (pos.z > work - CollisionRangeNumericalValue)
	{
		pos.z = work - CollisionRangeNumericalValue;
	}

	work = Collision::GetInstance()->getBack(pos);
	if (pos.z < work + CollisionRangeNumericalValue)
	{
		pos.z = work + CollisionRangeNumericalValue;
	}

	work = Collision::GetInstance()->getRight(pos);
	if (pos.x > work - CollisionRangeNumericalValue)
	{
		pos.x = work - CollisionRangeNumericalValue;
	}
	work = Collision::GetInstance()->getLeft(pos);
	if (pos.x < work + CollisionRangeNumericalValue)
	{
		pos.x = work + CollisionRangeNumericalValue;
	}
}


/*
ハンドルからナックルアームへ伝える制御
(ハンドルのリアリテイ制御の１つ)
*/
float Car_A_E::PowerSteering(float HandlePower)
{
	//左右切られたときのハンドル
	HandleBar = HandlePower;

	//ハンドルの角度調整
	HandleBar *= PI / 180;
	HandleBar *= 360;

	//パワーシリンダーに接続
	PowerSlinder += HandleBar/1.5f;

	//パワーシリンダーから制御
	float HalfSilinderLength = MaxPowerSlinderLength / 2;
	if (PowerSlinder > HalfSilinderLength)PowerSlinder = HalfSilinderLength;
	else if (PowerSlinder < -HalfSilinderLength)PowerSlinder = -HalfSilinderLength;

	//パワーシリンダーからナックルアームに接続
	KnuckleArm = PowerSlinder*PI / 360;


	return  KnuckleArm;
}

/*
タイヤの限界挙動制御
*/

void Car_A_E::PredictedPosition()
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

*/
void Car_A_E::OperationSystem()
{
	PredictedPosition();

	/*
	スロットル
	踏んだときのアクセルスロットルかブレーキスロットル稼動確認
	*/
	//GearDelay -= 1;//クラッチ繋ぎの接続完了までの時間

				   //押したときにアクセルスロットルが入るかの設定
	if (AI_Throttle==true)
	{
			Throttle += AcceleratingForce*20.0f;
			torqueOtationalSpeed += AcceleratingForce*20.0f;

	}
	else
	{
		Throttle -= Throttle*0.005f;//押してなかったら空	抜け方は割合減算
		torqueOtationalSpeed -= torqueOtationalSpeed;
	}

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
	if (AI_BreakThrottle==true)
	{
		BreakingPower += 0.8 / (0.7 * 140 * 2)*20.0f;	//制動力　
		torqueOtationalSpeed -= BreakingPower;
		Throttle -= BreakingPower;
	}
	else BreakingPower = 0.0f;//押してなかったら空
	if (AI_BackThrottle == true)
	{
		BackThrottle += AcceleratingForce*8.0f;//調整の為に2倍　
		Throttle -= BackThrottle;
		torqueOtationalSpeed += AcceleratingForce;
		Gear = 0;
	}

	/*
	TODO:バグ
	スロットル回した後でシフトダウンで高回転が
	シフト時に速度低下

	前のギアと現在のギア等を計算することで反映

	AT完成
	*/

		if (Throttle <= (torqueMaxOS / 1000) / GearRatio[Gear - 1] * GearRatio[Gear])
		{
			if (Gear > 1)
			{
				Gear--;
				Throttle = Throttle / GearRatio[Gear + 1] * GearRatio[Gear];
				torqueOtationalSpeed = torqueOtationalSpeed / GearRatio[Gear + 1] * GearRatio[Gear];
			}
		}

		if (Throttle > OverLevMax-0.2f)//シフトアップ AT
		{
			if (Gear < 4)
			{

				Gear += 1;
				Throttle = Throttle / GearRatio[Gear - 1] * GearRatio[Gear];
				torqueOtationalSpeed = torqueOtationalSpeed / GearRatio[Gear - 1] * GearRatio[Gear];
			}
		}

	
	//if (Throttle >OverLevMax+0.2f)Throttle = OverLevMax;
	if (Throttle < 0.00f)Throttle = 0.00f;	//Max 0%

	if (BreakingPower > 0.05f)BreakingPower = 0.05f;	//100%
	if (BreakingPower < 0.001f)BreakingPower = 0.001f;	//0%

	if (torqueOtationalSpeed > 6.6f)torqueOtationalSpeed = 6.6f;
	if (torqueOtationalSpeed <= 0.0f)torqueOtationalSpeed = 0.0f;

}

/*
直列4気筒エンジンの構造関数
*/
void Car_A_E::StraightFourEngine()
{
	//初期化
	crankShaft = 0.0f;		//クランクシャフト伝動回転変数
	spinNum = 0.0f;			//クランクシャフト回転変数
	num = 0;				//平均加算変数

							/*
							TODO:	クランクシャフト回転関係
							クランクシャフトが1回転したら　回転変数に渡す
							6気筒型は4工程でクランクシャフトが2回転(720°)される
							*/
	for (int i = 0;i < 4;i++)SilinderUpdate(i);	//4気筒の為　4回回す

	spinNum = crankShaft / 360;			//秒毎にクランクシャフトの回転結果を報告する

										/*
										ピストン上下運動(2回)*クランクシャフトのストローク長/1000(mmをmに直す為)*回転数
										*/
	CrankSpinAverage[IC] = (2 * 0.38f / 1000 * spinNum) * 3600;
	CrankSpinAverage[IC] *= 2;
	//平均巡回
	if (IC >= MaxSilinderAve - 1)IC = 0;		else IC++;

	//平均
	//配列最大数値取得
	arrayMaxNum = sizeof(CrankSpinAverage) / sizeof(CrankSpinAverage[0]);

	for (int i = 0;i < MaxSilinderAve;i++) num += CrankSpinAverage[i];
	//平均を取得
	averagenumber = num / arrayMaxNum;
	CrankSpinNum = averagenumber;
	idlingBreakSpeed = averagenumber;
	//TODO: アクセルふめないようにしてる

	CrankSpinNum += Throttle;
}


/*
トラクション
*/
Vector3 Car_A_E::Traction()
{

	//前向きを表現している単位ベクトル
	Front.x = sinf(angle.y);
	Front.y = 0.0f;
	Front.z = cosf(angle.y);

	Front.Normalize();

	/*
	トルク計算
	torque;//トルク最高回転数4,400rpm
	(36.0f * torque)=(36.0kgf･m)/4400r.p.m =最大トルク=353.0N・m5
	*/
	EngineDisplacement = (81.0f / 2)*(81.0f / 2)*PI*77.0f * 4;
	EngineDisplacement /= (int)1000;
	torque = 22 * (EngineDisplacement) * 0.5f / (2 * PI) / pow(9.806652f, 2);

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
*/

Vector3 Car_A_E::AirResistance()
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
	AirResistanceCoefficient = 0.3f;
	/*
	自動車の正面投影面積
	*/
	FrontProjectionAreaOfTheAutomobile = (1.335 * 1.625 * 0.8f);
	/*
	/*
	速度
	*/
	Air_Speed = (float)pow(speed, 2);
	/*
	空気抵抗
	*/
	AirResistanceRealValue = (AirResistanceCoefficient*FrontProjectionAreaOfTheAutomobile*Air_Speed*DensityOfAir) / 2;
	AirResistanceRealValue /= pow(60, 2);	//現在空気抵抗軽減無
	return Vector3(sinf(AirResistanceRealValue), 0, cosf(AirResistanceRealValue));
}

/*
転がり抵抗
*/
Vector3 Car_A_E::RollingResistance()
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

	μ = 0.015f;
	rollingResistance = μ*weght*9.8f;

	return Vector3(sinf(rollingResistance), 0, cosf(rollingResistance));
}

/*
静止力
*/
Vector3 Car_A_E::StaticForce()
{
	return -Traction()*weght*0.05f;
}

/*
遠心力
*/

float Car_A_E::CentrifugalForce()
{
	//旋回半径=ホイールベース(M)/sin(実舵角)
	Rad = (2.4f) / sin(cross.y);
	//遠心力=車重/重力加速度*速度2/旋回半径
	Fc = (weght / 9.8f) * (pow(speed, 2) / Rad);
	Fc /= 10000;
	//ロール
	RollHeght = 1.335f / 2;//ロールセンターから重心までの距離
	tread = 1335 / 1000;//トレッド幅
	Spring = RollHeght*9.8f;//サスペンションモーメント

	RollStiffness_F = (4300 * pow(tread, 2)) / 2;//ロール剛性 前
	RollStiffness_R = (3200 * pow(tread, 2)) / 2;//ロール剛性 後

	 /*
	 ロールアップ
	 ロール効果は極小
	 */
	θ = (Fc*RollHeght) / ((RollStiffness_F + RollStiffness_R) - (Spring*RollHeght));

	θaccel = (Throttle*RollHeght) / ((4000 * (-4.215 / 2 - 1.345)*1.345) - (Spring*RollHeght));
	θbrake = (BreakingPower*RollHeght) / ((5700 * (4.215 / 2 - 1.355)*1.355) - (Spring*RollHeght));
	//ロール反映
	angle.x = θaccel - θbrake;

	//左右に揺れる角度(angle.z)をロールで反映
	angle.z = θ;

	//デバッグデータ
	centrifugal = Fc;

	return Fc;
}
/*
コーナリングパワー
*/
Vector3 Car_A_E::CorneringForce()
{
	/*
	F=T*Fcp(a)
	T：コーナリングパワーの働く方向．車体の進行方向に直角
	f：コーナリングパワーを計算する関数[N]
	α：横滑り角
	*/
	Vector3 WouldUpVec(0, 1, 0);//ワールド上の上ベクトル

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


	return CounerPower;
}


void Car_A_E::GearInfo()
{

	/*
	TODO: エンジンのRPM
	*/
	rpm = CrankSpinNum;
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

	float bunsi_A, bunsi_B, bunbo_A, bunbo_B, SpeedSaved;

	bunsi_A = ((255 * 0.40f * 2 + 17 * 25.4f)*PI*(rpm - (idlingBreakSpeed * 1000)));
	//!シフトチェンジ時に前の計算数値を次のギアに渡してシャフト抜けを改善する
	bunbo_A = (GearRatio[Gear] * FirnalRGR);
	bunsi_B = 60;
	bunbo_B = pow(10, 6);
	SpeedSaved = (bunsi_A / bunbo_A) * (bunsi_B / bunbo_B);

	speed = (SpeedSaved)*RollingResistance().Length();
	//トルク回転数
	torquePower = 2 * PI *torque*(rpm) / 60 / 1000;

	/*
	1.3962kW ＝ 1.0馬力

	*/
	//馬力 PTO軸トルク（Kg・m）＊PTO軸回転数（RPM）Ｘ 2π ／ ( 75 Ｘ 60 )
	horsePower = torque * (torqueOtationalSpeed * 1000) * (2 * PI) / (75 * 60);
	//最高馬力
	//（回転数 rpm) ×（トルク kgfm）／1000 × 1.3962
	Max_HorsePower = torque * torqueMaxOS * (2 * PI) / (75 * 60);
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
	if (Gear <= 3)
	{
		AcceleratingForce = ((torquePower* 9.8f*(GearRatio[Gear] * RGR) / (HalfDRR / 1000)) / weght) - AirResistanceRealValue;
	}
	if (Gear == 4)
	{
		AcceleratingForce = ((torquePower* 9.8f*(GearRatio[Gear] * FirnalRGR) / (HalfDRR / 1000)) / weght) - AirResistanceRealValue;
	}

	AcceleratingForce /= 900;
	/*
	シフト設定
	*/
	if (Gear >= 4)Gear = 4;

	if (Gear <= 1)	Gear = 1;									     //１速は下回らない(後退は今度

}

void Car_A_E::SilinderUpdate(int n)
{
	//*************************************************************************************
	//			step 1			吸入
	//*************************************************************************************
	//空気を吸入する
	if (step[n] == 0)Inline_Four_Engine[n] -= SilinderSpeed;

	//各シリンダーが吸入したらそれぞれ圧縮工程へ
	if (step[n] == 0 && Inline_Four_Engine[n] < 0)
	{
		step[n] = 1;
		//最後尾のシリンダーが吸入したらクランクシャフトが回転
		crankShaft += crankShafter;
		Inline_Four_Engine[n] = 0;
	}

	//*************************************************************************************
	//			step 2			圧縮
	//*************************************************************************************
	//空気を圧縮する
	if (step[n] == 1)Inline_Four_Engine[n] += SilinderSpeed;

	//各シリンダーが圧縮したらそれぞれ燃焼工程へ
	if (step[n] == 1 && Inline_Four_Engine[n] > MaxPis)
	{
		step[n] = 2;
		//シリンダーが吸入したらクランクシャフトが回転
		crankShaft += crankShafter;
		Inline_Four_Engine[n] = MaxPis;
	}
	//*************************************************************************************
	//		step 3			燃焼
	//*************************************************************************************
	//圧縮した空気を燃焼する
	if (step[n] == 2)Inline_Four_Engine[n] -= SilinderSpeed;

	//各シリンダーが燃焼したらそれぞれ排気工程へ
	if (step[n] == 2 && Inline_Four_Engine[n] < 0)
	{
		step[n] = 3;
		//各シリンダーが吸入したらクランクシャフトが回転
		crankShaft += crankShafter;
		Inline_Four_Engine[n] = 0;
	}
	//*************************************************************************************
	//		step 4			排気
	//*************************************************************************************
	//燃焼された空気を排気する
	if (step[n] == 3)Inline_Four_Engine[n] += SilinderSpeed;

	//各シリンダーが吸入したらそれぞれ圧縮工程へ
	if (step[n] == 3 && Inline_Four_Engine[n] > MaxPis)
	{
		step[n] = 0;
		//各のシリンダーが吸入したらクランクシャフトが回転
		crankShaft += crankShafter;
		Inline_Four_Engine[n] = MaxPis;
	}
}

/*
タイヤ伝達
*/
void Car_A_E::WheelProcess()
{
	/*
	タイヤの外周
	*/
	TheOuterCircumferenceOfTheTire = ((DRR)*PI) / 1000;
	/*
	タイヤの1分間に進む距離
	*/
	MinLength += speed * 1000 / 216000;
	/*
	タイヤの回転数
	*/
	WheelRpm = MinLength / TheOuterCircumferenceOfTheTire;
	int WheelConvert = WheelRpm;
	WheelRpm = WheelRpm - WheelConvert;
	WheelRpm = PI * 2 * WheelRpm;

	RightRearWheel = LeftRearWheel = WheelRpm;

}

void Car_A_E::Update()
{
	SpeedHandle = 2.0f;
	//車体の力
	Vector3 F = Traction() + AirResistance() + RollingResistance() + StaticForce() + CorneringForce()*CentrifugalForce();
	Vector3 a = F / weght;

	static float GravityZero, Gravity;
	Gravity -= 9.8f;
	pos.y += Gravity;
	GravityZero = Collision::GetInstance()->getHeight(pos);
	if (pos.y < GravityZero)
	{
		pos.y = GravityZero;
		Gravity = 0;
	}

	//
	metterAngle = (CrankSpinNum) / 3;
	SpeedMeter = (float)speed / 90;

	/*
	操作系呼び出し
	*/
	StraightFourEngine();

	AirResistance();
	if (StartMove == true)
	{
		OperationSystem();
		GearInfo();
		AI_System();

	}
	


	ModelCollision();
	obj->SetPos(pos);
	obj->SetAngle(angle);
	obj->SetScale(scale);
	obj->Update();

	obj2->SetPos(pos);
	obj2->SetAngle(angle);
	obj2->SetScale(scale);
	obj2->Update();

	Vector3 angle2(WheelRpm, WheelFrontAngle, angle.z);
	Vector3 angle3(-WheelRpm, WheelFrontAngle - 135, angle.z);

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

}


void Car_A_E::Render(iexShader*shader, char*chr)
{

	obj->Update();
	//プレイヤー
	obj->Render(shader, chr);
	obj2->Render(shader, chr);
	obj3->Render(shader, chr);
	obj4->Render(shader, chr);
	obj5->Render(shader, chr);
	obj6->Render(shader, chr);

	char str[256];
	sprintf(str, "のーど座標:\n"
		"X:%f\nZ:%f\n"
		"座標:\n"
		"X:%f\nZ:%f\n"
		"%f\n"

		, testNode.x, testNode.z, pos.x, pos.z,Getcross.y
	);
	IEX_DrawText(str, 300, 500, 1920, 1080, 0xffffffff);

}
