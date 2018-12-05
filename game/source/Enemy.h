#pragma once
#include "iextreme.h"
#include "Collision.h"

#define Max_SelectMode 1

#define MaxSilinderAve 18

#define MaxTieRodAngle 3.6f

#define MaxPowerSlinderLength 360.0f

#define ZEROVECTOR Vector3(0.0f, 0.0f, 0.0f)

#define Default_LevMeter 1000

#define OverLevMax 10.8f

#define CollisionRangeNumericalValue 8.0f

/*
TODO:余裕があれば、ステータス値はTextLoaderに移行
*/

//base Player
class B_Enemy
{
protected:
	iex2DObj*metterA;
	iex2DObj*metterB;
	iex2DObj*metterC;
	iex2DObj*HandleTex;
	/*
		Pointer
	*/
	iexMesh*obj;						//モデル
	iex3DObj*obj2;
	iexMesh*obj3;
	iexMesh*obj4;
	iexMesh*obj5;
	iexMesh*obj6;
	Vector3 pointer;

										/*
										Vector3型
										*/
	Vector3 angle;									//角度
	Vector3 Break;									//ブレーキ
	Vector3 Front;									//正面
	Vector3 pos;									//座標
	Vector3 traction;								//トラクション
	Vector3 cross;
	Vector3 TaiyaAngle;
	/*
	int型
	*/
	int HandleMode;									//0:正面　1:左　2:右
	int Gear;										//ミッションギア
	int GearMax;									//ギア最高比

	int LevLimit;									//レブリミッター
	int missionMode;								//ATかMTに選択する形式
	int windSpeed;									//風速


	unsigned int color, LevColor;

	double idlingBreakSpeed;
	double speed;									//加速度
	double SpeedHandle;
													/*
													float 型
													*/
	float OtationalSpeed;							//回転数
	float BreakingPower;							//ブレｰキスロットル
	float SubBreakingPower;							//サイドブレーキ
	float DRR;										//タイヤ半径
	float ERatio;									//トランスミッション効率
	float GearDelay;								//ギア遅延
	float FirnalRGR;								//ファイナルデフ比
	float HighSpeed;								//AT　高速
	float MaxSpeed;									//車両最高加速度
	float RGR;										//デフ比
	float scale;									//大きさ
	float SelecterReductionGearRation;				//減速比　設定型
	float SlowSpeed;								//AT 低速
	float Throttle;									//アクセルスロットル
	float BackThrottle;
	float weght;									//重量
	float FinalGearRatio;							//ファイナルギア
	float SpeedMeter;								//回転数引渡用変数
	float rpm;										//エンジン回転数
													/*
													大気圧
													海綿上では1013.25hpa
													高度10M上昇につれて1hpa
													計算上富士山頂で約0.7気圧、高度5,500 m で約0.5気圧、エベレストの頂上では約0.3気圧
													*/
	float AtmosphericPressure;
	float temperature;								//気温
	float DensityOfAir;								//空気の密度
	float AirResistanceCoefficient;					//空気抵抗係数
	float FrontProjectionAreaOfTheAutomobile;		//自動車の正面投影面積
	float Air_Speed;								//空気抵抗用速度保管変数
	float AirResistanceRealValue;					//空気抵抗測定数値
	float AcceleratingForce;						//加速力
	float horsePower;								//馬力
	float Max_HorsePower;							//最高馬力
	float PowerToWeightRatio;						//パワーウェイトレシオ
	float crankShaft;								//クランクシャフト
	float spinNum;									//クランクシャフト回転数
	float CrankSpinNum;								//クランクシャフト秒間回転数
	float torque;									//トルク
	float EngineDisplacement;						//排気量
	float torqueOtationalSpeed;						//トルク回転数
	float HalfDRR;									//タイヤの半径
	float torqueMaxOS;								//トルク最高回転数
	float torquePower;								//トルク・トルク回転数
	float rollingResistance;						//転がり抵抗保管変数
	float μ;											//ころがり抵抗係数(読:ミュー
	float num;
	/*
	bool型
	*/
	bool FinalGear;									//最終ギア(ファイナルギア)の接続判定
	bool StartMove;									//発進合図
	bool PowerTex;									//速度・回転数等のモニターチェック

	bool AI_Throttle;					//アクセルを踏んで良いかの判定
	bool AI_BreakThrottle;				//ブレーキを踏んで良いかの判定
	bool AI_BackThrottle;


	float HandleBar;//ハンドル
	float metterAngle;		//タコメーター
	float WheelFrontAngle;

	/*
		AI用
	*/
	//順繰り変数保持用
	int	CatchNodeNumber;
	int testTimer;

	//デバック
	Vector3 testNode;
	int ind;

public:
	B_Enemy();
	~B_Enemy();

	/*
	セッター・ゲッター
	*/
	iexMesh* GetObj() { return obj; }

	void    SetSpeed(float s) { speed = s; }
	float	GetSpeed() { return speed; }

	void    SetPos(Vector3 p) { pos = p; }
	Vector3 GetPos() { return pos; }

	void    SetAngle(Vector3 a) { angle = a; }
	Vector3 GetAngle() { return angle; }

	void    SetScale(float s) { scale = s; }
	float	GetScale() { return scale; }

	bool Init();									//Initialize
	void SetSMove(bool sm) { StartMove = sm; }

	//int	GetEngine_Engine_Engine_Gearmissions.Gearmissions.Engine_Gearmissions.Gearmissions.() { return Engine_Engine_Engine_Gearmissions.Gearmissions.Engine_Gearmissions.Gearmissions.; }
	int GetLevLimit() { return LevLimit; }

	float	GetSpeedMetter() { return SpeedMeter; }
	float	GetSpeedAngle() { return metterAngle; }
	float	GetHandleBar() { return HandleBar; }
	float   GetRpm() { return rpm; }
	float   GetThrottle() { return Throttle; }

};

/*
	Car Alpha Enemy
*/
class Car_A_E :public B_Enemy
{
private:
	/*
		http://ae86.s1.xrea.com/4ag/transmission/transmission.htm を参照に改造
	*/
	int indexNumber;
	int Inline_Four_Engine[4];	//直列4気筒エンジン用変数
	int step[4];				//4気筒のシリンダー
	int MaxPis;			//シリンダー最大割合
	int arrayMaxNum;	//平均最大変数
	int IC;				//シリンダーの平均確認用変数
	int SilinderSpeed;	//毎秒回されるピストン
	int ShiftCheakNum;	//シフトチェンジによるシフトエラーを防ぐ代理変数


	float GearRatio[5];//　AE86 レビンのギア比 上記参照
	float CrankSpinAverage[18];	//クランクシャフト平均回転数
	float crankShafter;	//各気筒からシャフトへ回す回転変数
	float sum;			//平均合計値
	float averagenumber;//平均保管変数

	float RightFrontWheel, LeftFrontWheel, RightRearWheel, LeftRearWheel;//右前輪・左前輪・右後輪・左後輪
	float TheOuterCircumferenceOfTheTire;//タイヤの外周
	float MinLength;//タイヤの1分に進む距離
	float WheelRpm;//タイヤの回転数


	float PowerSlinder;//パワーシリンダー
	float KnuckleArm;//ナックルアーム

	float centrifugal;//荷重
	float Rad;//旋回角度
	float Fc;//遠心力
	float θ;//シータ
	float RollHeght;//ロールセンターと車高の中心
	float tread;//トレッド幅
	float Spring;//ばね定数
	float RollStiffness_F, RollStiffness_R;//ロール剛性Front Rear 
	float θaccel, θbrake;//ロールピッチアップ

	int RightIndex;

	int LeftIndex;

	Vector3 pointPos;
	Vector3 WheelAngle;
	
	Vector3 Getcross;

public:
	Car_A_E();
	~Car_A_E();

	bool Init();

	Vector3 Traction();
	Vector3 AirResistance();
	Vector3 RollingResistance();
	Vector3 StaticForce();
	Vector3 CorneringForce();
	float CentrifugalForce();

	void OperationSystem();
	void StraightFourEngine();
	void GearInfo();
	void WheelProcess();
	void PredictedPosition();//予測位置

	void SetEnviroment(int wind, float temp)
	{
		windSpeed = wind;
		temperature = temp;
	}
	float PowerSteering(float HandlePower);

	void SilinderUpdate(int n);

	void ModelCollision();

	void AI_System();					//Artificial Intelligent Systems
	void AI_NodeSystem();
	void AI_AccelMode();
	void AI_HandleingMode();
	void AI_HandleControlMode(Vector3 inputNodeVector);


	void Update();						//Update
	void Render(iexShader*shader, char*chr);						//Render

	static Car_A_E *GetInstance()				//Singleton 
	{
		static Car_A_E instnce;
		return &instnce;
	}

};
