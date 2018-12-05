#pragma once

#include "Camera.h"
#include "Collision.h"

#include <vector>


#define Max_SelectMode 1

#define MaxSilinderAve 18

#define MaxTieRodAngle 3.6f

#define MaxPowerSlinderLength 360.0f

#define ZEROVECTOR Vector3(0.0f, 0.0f, 0.0f)

#define Default_LevMeter 1000

#define OverLevMax 6.80f

#define CollisionRangeNumericalValue 8.0f

class Car_A;

/*
	トランスミッションギア比参照
	 float型　GearRatio[配列]
	 [0]	 =バック走行時のギア比
	 [1]~[6] =ミッションのギア比　3.1277等
*/





//base Player
static class B_Player:public iex3DObj
{
protected:
	/*
		classポインター
	*/
	iexMesh*obj;									//モデル
	iex3DObj*obj2;
	iexMesh*obj3;
	iexMesh*obj4;
	iexMesh*obj5;
	iexMesh*obj6;
	/*
		enum
	*/
	enum  GearMode
	{
		AT = 0,
		MT,
	};
	/*
		内部部品
		エンジン(心臓部分
	*/
	struct Engine_Parts
	{
		const int MaxPis = 120;							//シリンダー最大割合
		/*
		ピストンとクランクシャフトを連結し、直線往復運動を回転運動に変換、伝導する役目をします。
		高温、衝撃、高回転のタフな環境下で使用される部品です。
		*/
		const float ConectingRod=24.0f;
		/*
		シリンダーブロックの上に配置し、燃焼ガスの吸気、点火、排気の機能を備えた装置で、コンピュータによる電子制御を行うエンジンが主流です。
		*/
		float CyLinderHead[6];
		/*
		着火、燃焼によるエネルギーをピストンに伝達し、クランクシャフトに回転力として伝える、内燃機関の中心部品です。
		*/
		float SilinderBlock;
		/*
		エンジン動弁系の主要部品であるカムシャフトは、バルブを開閉させるロッカーアームやタベットなどを駆動させるもので、エンジンの形式により、使用数も異なります。
		*/
		float ComShaft;
		/*
		エンジンのピストン内での燃焼・膨張行程によって発生するピストン、コネクティングロッドの直線往復運動を回転運動に変換する役目を果たし、高回転、衝撃環境下にさらされる重要な基幹部品です。
		*/
		float CrankShaft;
		/*
		燃料を霧状に噴射する　空気と燃料を一緒に取り込むもの
		*/
		float Injecter;
		/*
		金属製のエンジンの中の部品へ潤滑剤として流して、金属同士の磨耗を抑えたり、エンジン内で過熱する部品の冷却
		*/
		float EngineOil;
		/*
		一般的な水冷エンジンはエンジンを冷却するために水路を作ってあって、水を流すことでエンジン冷却
		*/
		float Radiator;
		/*
		エンジンが燃焼するときの点火装置へ電気を送るためのもの
		*/
		float Battery[6];
		/*
		クランクシャフトとカムシャフトの動作の「タイミング」を制御するためのパーツです。クランクシャフトが2回転するにつき、カムシャフトがきっちりと1回転できるように調整することで、スムーズで動きの良いエンジンを作り出します
		*/
		float TimingBelt;

		/*
			注意!!
			全てを指定値代入する為
		*/
		void TargetInitialization(float ZeroNum)
		{
			SilinderBlock = ComShaft
				= CrankShaft = Injecter = Radiator
				= TimingBelt = ZeroNum;
			EngineOil = 100;
			CyLinderHead[0] = MaxPis*0.0f;//1
			CyLinderHead[1] = MaxPis*0.8f;//2
			CyLinderHead[2] = MaxPis*0.4f;//3
			CyLinderHead[3] = MaxPis*1.0f;//4
			CyLinderHead[4] = MaxPis*0.2f;//5
			CyLinderHead[5] = MaxPis*0.6f;//6
		}

	}engine_parts;
	struct Engine_GearMissions
	{
		float num, num2;
		//エンジン平均回転数保持変数
		float CrankSpinAverage[18];
		//アイドリングエンジン平均回転数保持変数
		float IdlingCrankSpinAverage[18];
		//上記の格納変数
		int CylinderAverages;
		//配列保管
		float AverageNumber;
		//配列最大数
		int ArrayMaxNumber;
		//配列保管
		float IdlingAverageNumber;
		//配列最大数
		int IdlingArrayMaxNumber;
		//クランクシャフト秒間回転数
		float CrankNumberOfRevolutionsPerSecond;
		//上記のタコメータ反映用
		float UICrankNumberOfRevolutionsPerSecond;
		//アイドリング
		float IdlingBreakSpeed;
		//アイドリング用部品
		float IdlingCrankShaft;
		//走ってない時に空回りできる変数追加
		float StopCrankSpin;
		//初期化
		void TargetInitialize(float ZeroNum)
		{
			 CrankNumberOfRevolutionsPerSecond = UICrankNumberOfRevolutionsPerSecond
				= IdlingBreakSpeed = IdlingCrankShaft = StopCrankSpin = ZeroNum;
			CylinderAverages = ArrayMaxNumber =AverageNumber = IdlingAverageNumber =
				IdlingArrayMaxNumber =(int)ZeroNum;
		}
	}engine_Gearmissions;

	//車の基本パラメータ
	struct Car_Status
	{
		int Gear;										//ミッションギア
		int GearMax;									//ギア最高比
		int LevLimit;									//レブリミッター
		double speed;									//加速度
		float OtationalSpeed;							//回転数
		float DRR;										//タイヤ直径
		float ERatio;									//トランスミッション効率
		float FirnalRGR;								//ファイナルデフ比
		float RGR;										//デフ比
		float weght;									//重量
		float horsePower;								//馬力
		float Max_HorsePower;							//最高馬力
		float PowerToWeightRatio;						//パワーウェイトレシオ
		float torque;									//トルク
		float MaxTorque;								//最大トルク
		float EngineDisplacement;						//排気量
		float torqueMaxOS;								//トルク最高回転数
		float torquePower;								//トルク・トルク回転数
		float TheOuterCircumferenceOfTheTire;			//タイヤの外周
		float FrontProjectionAreaOfTheAutomobile;		//自動車の正面投影面積
	}car_status;

	//システム系 主に制御系計算など
	struct Car_Systems
	{
		const float HighSpeed = 0.9f;						//AT　高速
		const float SlowSpeed = 0.8f;						//AT 低速

		int NodeSaveNumber;								//ノード保持変数
		int ShiftCheakNum;								//シフトチェンジによるシフトエラーを防ぐ代理変数
		float idlingBreakSpeed;							//アイドリングによる回転数
		float SpeedHandle;								//スムージングハンドリング
		float BackThrottle;								//ブレーキの強さ
		float ShiftChangeLevs;							//ギアチェンジによる変換保持数
		float BreakingPower;							//ブレｰキスロットル
		float SubBreakingPower;							//サイドブレーキ
		float SelecterReductionGearRation;				//減速比　設定型
		float Throttle;									//アクセルスロットル
		float ThrottleTacoMetter;						//アクセルスロットルのタコメータ反映型
		float SpeedMeter;								//回転数引渡用変数
		float rpm;										//エンジン回転数
		float AcceleratingForce;						//加速力
		float crankShaft;								//クランクシャフト
		float spinNum;									//クランクシャフト回転数
		float CrankSpinNum;								//クランクシャフト秒間回転数
		float torqueOtationalSpeed;						//トルク回転数
		float HalfDRR;									//タイヤの半径
		float rollingResistance;						//転がり抵抗保管変数
		float myu;										//ころがり抵抗係数(読:ミュー
		float metterAngle;								//タコメーター
		float HandleBar;								//ハンドル

		bool FinalGear;									//最終ギア(ファイナルギア)の接続判定
		bool StartMove;									//発進合図
		bool BackCheak;									//後退確認用
		bool GearDelay;									//ギア遅延
		float Spring;									//ばね定数
		float RollStiffness_F, RollStiffness_R;			//ロール剛性Front Rear 
		float sitaaccel, sitabrake;						//ロールピッチアップ	//!θからsitaに変更よろしく
		float WheelGrep;								//タイヤ磨耗度	//!タイヤの設定がまだ
		float hydraulic;								//油圧 //!油圧の設定がまだ
		float WheelFrontAngle;							//フロントタイヤの角度
		float RightFrontWheel, LeftFrontWheel, RightRearWheel, LeftRearWheel;//右前輪・左前輪・右後輪・左後輪
		float MinLength;								//タイヤの1分に進む距離
		float WheelRpm;									//タイヤの回転数
		float PowerSlinder;								//パワーシリンダー
		float KnuckleArm;								//ナックルアーム
		float centrifugal;								//荷重
		float Rad;										//旋回角度
		float Fc;										//遠心力
		float sita;										//シータ
		float RollHeight;								//ロールセンターと車高の中心
		float tread;									//トレッド幅
		float AnWheelAngle;								//タイヤ逆角度
	}car_systems;
	//幾何学
	struct Geometry
	{
		int windSpeed;									//風速
		float AtmosphericPressure;						//大気圧 海綿上では1013.25hpa 高度10M上昇につれて1hpa
		float temperature;								//気温
		float DensityOfAir;								//空気の密度
		float AirResistanceCoefficient;					//空気抵抗係数
		float Air_Speed;								//空気抵抗用速度保管変数
		float AirResistanceRealValue;					//空気抵抗測定数値
	}geometry;
	/*
		Vector3型
	*/
	Vector3 angle;									//角度
	Vector3 Break;									//ブレーキ
	Vector3 Front;									//正面
	Vector3 pos;									//座標
	Vector3 traction;								//トラクション

	Vector3 cross;									//計算用 外積
	/*
		float 型
	*/
	float scale;									//大きさ
	
	//押し返し
	float OverBlock;	//押し返しのあがき
	float wallWeght;//壁の重量 とりあえずコンクリートの重量
	float weghtRef;//車両重量の8割 都合上8割で返す
	float wallRef;//壁の重量の8割
	/*
		bool型
	*/

	bool missionMode;								//false:AT true:MT

	/*
	レースのやつ
	*/
	int Weeks;
	bool GoalInCheak;
public:
	B_Player();
	~B_Player();

	/*
		セッター・ゲッター
	*/
	iexMesh* GetObj() { return obj; }

	void    SetSpeed(float s) { car_status.speed = s; }
	float	GetSpeed() { return car_status.speed; }

	void    SetPos(Vector3 p) { pos = p; }
	Vector3 GetPos() { return pos; }

	void    SetAngle(Vector3 a) { angle = a; }
	Vector3 GetAngle() { return angle; }

	void    SetScale(float s) { scale = s; }
	float	GetScale() { return scale; }

	void SetMMode(bool mm) { missionMode = mm; }
	bool GetMMode() { return missionMode;}

	/*
	
	*/
	int	GetGear() { return car_status.Gear; }
	int GetLevLimit() { return car_status.LevLimit; }
	int GetWeeks() { return Weeks; }
	float	GetSpeedMetter() { return car_systems.SpeedMeter; }
	float	GetSpeedAngle() { return car_systems.metterAngle; }
	float	GetHandleBar() { return car_systems.HandleBar; }
	float   GetRpm() { return car_systems.rpm; }
	float   GetThrottle() { return car_systems.Throttle; }
	bool GetGoalInChake() { return GoalInCheak; }
	float GetTacoRenderMetter() { return car_systems.ThrottleTacoMetter; }


	bool Init();									//Initialize
	void SetSMove(bool sm) { car_systems.StartMove = sm; }

	float GetEngine_Battery(int n) { return engine_parts.Battery[n]; }
	float GetEngine_CylinderHead(int n) { return engine_parts.CyLinderHead[n]; }
	float GetEngine_EngineOil() { return engine_parts.EngineOil; }
	float GetEngine_Radiator() { return engine_parts.Radiator; }

	bool GetGearDelayCheak() { return car_systems.GearDelay; }

	int GetHoursePower() { return car_status.Max_HorsePower; }
	float GetTorque() { return car_status.torque; }
	float GetWeght() { return car_status.weght; }
	float GetPowerWeghtRatio() { return car_status.PowerToWeightRatio; }

};

/*

	Car Alpha

	日産: BMR32 を元に改造した車
	最高速度・速度・重量面を高めに設定し、コーナー面を若干低く設定
	初心者向け且、玄人向けの設定にする
*/
#define SHADOW_SIZE 1024
static class Car_A :public B_Player
{
private:
	/*
		http://www.iwami.or.jp/wakaba-s/bo-so-menu/bo-so-bnr32_3.htm 　参照
	*/

	const int Car_cylinder = 6;

	int Inline_Six_Engine[6];	//直列６気筒エンジン用変数
	int step[6];				//６気筒のシリンダー

	float GearRatio[6];//　BMR R-32のギア比 上記参照
	float FinalGearRatio;							//ファイナルギア

	Vector3 pointPos;
	Vector3 TaiyaAngle;



	Car_A();
	~Car_A() = default;
public:

	bool Init();
	bool MoveContrl(float max);

	Vector3 Traction();
	Vector3 AirResistance();
	Vector3 RollingResistance();
	Vector3 StaticForce();
	Vector3 CorneringForce();
	float CentrifugalForce();

	void OperationSystem(int n);
	void StraightSixEngine();
	void GearInfo();
	void WheelProcess();
	void PredictedPosition();//予測位置
	void SetEnviroment(int wind, float temp)
	{
		geometry.windSpeed = wind;
		geometry.temperature = temp;
	}

	float PowerSteering(float HandlePower);

	void SilinderUpdate(int n,float CylinderSpeed);
	void TransMissionCustom(const int n);

	void ModelCollision();

	void Update();
	void Render(iexShader*shader,char*chr);

	/*
		レースシステムを追加するためのやつ
	*/

	void RaceSystem();
	/*
		ブレーキディスクのボーンにタイヤを渡す為のプログラム
	*/
	void BornControl(int num, const Vector3& p);


	static Car_A *GetInstance()				//Singleton 
	{
		static Car_A instnce;
		return &instnce;
	}
};

