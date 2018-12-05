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
	�g�����X�~�b�V�����M�A��Q��
	 float�^�@GearRatio[�z��]
	 [0]	 =�o�b�N���s���̃M�A��
	 [1]~[6] =�~�b�V�����̃M�A��@3.1277��
*/





//base Player
static class B_Player:public iex3DObj
{
protected:
	/*
		class�|�C���^�[
	*/
	iexMesh*obj;									//���f��
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
		�������i
		�G���W��(�S������
	*/
	struct Engine_Parts
	{
		const int MaxPis = 120;							//�V�����_�[�ő劄��
		/*
		�s�X�g���ƃN�����N�V���t�g��A�����A���������^������]�^���ɕϊ��A�`�������ڂ����܂��B
		�����A�Ռ��A����]�̃^�t�Ȋ����Ŏg�p����镔�i�ł��B
		*/
		const float ConectingRod=24.0f;
		/*
		�V�����_�[�u���b�N�̏�ɔz�u���A�R�ăK�X�̋z�C�A�_�΁A�r�C�̋@�\����������u�ŁA�R���s���[�^�ɂ��d�q������s���G���W�����嗬�ł��B
		*/
		float CyLinderHead[6];
		/*
		���΁A�R�Ăɂ��G�l���M�[���s�X�g���ɓ`�B���A�N�����N�V���t�g�ɉ�]�͂Ƃ��ē`����A���R�@�ւ̒��S���i�ł��B
		*/
		float SilinderBlock;
		/*
		�G���W�����ٌn�̎�v���i�ł���J���V���t�g�́A�o���u���J�����郍�b�J�[�A�[����^�x�b�g�Ȃǂ��쓮��������̂ŁA�G���W���̌`���ɂ��A�g�p�����قȂ�܂��B
		*/
		float ComShaft;
		/*
		�G���W���̃s�X�g�����ł̔R�āE�c���s���ɂ���Ĕ�������s�X�g���A�R�l�N�e�B���O���b�h�̒��������^������]�^���ɕϊ������ڂ��ʂ����A����]�A�Ռ������ɂ��炳���d�v�Ȋ���i�ł��B
		*/
		float CrankShaft;
		/*
		�R���𖶏�ɕ��˂���@��C�ƔR�����ꏏ�Ɏ�荞�ނ���
		*/
		float Injecter;
		/*
		�������̃G���W���̒��̕��i�֏����܂Ƃ��ė����āA�������m�̖��Ղ�}������A�G���W�����ŉߔM���镔�i�̗�p
		*/
		float EngineOil;
		/*
		��ʓI�Ȑ���G���W���̓G���W�����p���邽�߂ɐ��H������Ă����āA���𗬂����ƂŃG���W����p
		*/
		float Radiator;
		/*
		�G���W�����R�Ă���Ƃ��̓_�Α��u�֓d�C�𑗂邽�߂̂���
		*/
		float Battery[6];
		/*
		�N�����N�V���t�g�ƃJ���V���t�g�̓���́u�^�C�~���O�v�𐧌䂷�邽�߂̃p�[�c�ł��B�N�����N�V���t�g��2��]����ɂ��A�J���V���t�g�����������1��]�ł���悤�ɒ������邱�ƂŁA�X���[�Y�œ����̗ǂ��G���W�������o���܂�
		*/
		float TimingBelt;

		/*
			����!!
			�S�Ă��w��l��������
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
		//�G���W�����ω�]���ێ��ϐ�
		float CrankSpinAverage[18];
		//�A�C�h�����O�G���W�����ω�]���ێ��ϐ�
		float IdlingCrankSpinAverage[18];
		//��L�̊i�[�ϐ�
		int CylinderAverages;
		//�z��ۊ�
		float AverageNumber;
		//�z��ő吔
		int ArrayMaxNumber;
		//�z��ۊ�
		float IdlingAverageNumber;
		//�z��ő吔
		int IdlingArrayMaxNumber;
		//�N�����N�V���t�g�b�ԉ�]��
		float CrankNumberOfRevolutionsPerSecond;
		//��L�̃^�R���[�^���f�p
		float UICrankNumberOfRevolutionsPerSecond;
		//�A�C�h�����O
		float IdlingBreakSpeed;
		//�A�C�h�����O�p���i
		float IdlingCrankShaft;
		//�����ĂȂ����ɋ���ł���ϐ��ǉ�
		float StopCrankSpin;
		//������
		void TargetInitialize(float ZeroNum)
		{
			 CrankNumberOfRevolutionsPerSecond = UICrankNumberOfRevolutionsPerSecond
				= IdlingBreakSpeed = IdlingCrankShaft = StopCrankSpin = ZeroNum;
			CylinderAverages = ArrayMaxNumber =AverageNumber = IdlingAverageNumber =
				IdlingArrayMaxNumber =(int)ZeroNum;
		}
	}engine_Gearmissions;

	//�Ԃ̊�{�p�����[�^
	struct Car_Status
	{
		int Gear;										//�~�b�V�����M�A
		int GearMax;									//�M�A�ō���
		int LevLimit;									//���u���~�b�^�[
		double speed;									//�����x
		float OtationalSpeed;							//��]��
		float DRR;										//�^�C�����a
		float ERatio;									//�g�����X�~�b�V��������
		float FirnalRGR;								//�t�@�C�i���f�t��
		float RGR;										//�f�t��
		float weght;									//�d��
		float horsePower;								//�n��
		float Max_HorsePower;							//�ō��n��
		float PowerToWeightRatio;						//�p���[�E�F�C�g���V�I
		float torque;									//�g���N
		float MaxTorque;								//�ő�g���N
		float EngineDisplacement;						//�r�C��
		float torqueMaxOS;								//�g���N�ō���]��
		float torquePower;								//�g���N�E�g���N��]��
		float TheOuterCircumferenceOfTheTire;			//�^�C���̊O��
		float FrontProjectionAreaOfTheAutomobile;		//�����Ԃ̐��ʓ��e�ʐ�
	}car_status;

	//�V�X�e���n ��ɐ���n�v�Z�Ȃ�
	struct Car_Systems
	{
		const float HighSpeed = 0.9f;						//AT�@����
		const float SlowSpeed = 0.8f;						//AT �ᑬ

		int NodeSaveNumber;								//�m�[�h�ێ��ϐ�
		int ShiftCheakNum;								//�V�t�g�`�F���W�ɂ��V�t�g�G���[��h���㗝�ϐ�
		float idlingBreakSpeed;							//�A�C�h�����O�ɂ���]��
		float SpeedHandle;								//�X���[�W���O�n���h�����O
		float BackThrottle;								//�u���[�L�̋���
		float ShiftChangeLevs;							//�M�A�`�F���W�ɂ��ϊ��ێ���
		float BreakingPower;							//�u����L�X���b�g��
		float SubBreakingPower;							//�T�C�h�u���[�L
		float SelecterReductionGearRation;				//������@�ݒ�^
		float Throttle;									//�A�N�Z���X���b�g��
		float ThrottleTacoMetter;						//�A�N�Z���X���b�g���̃^�R���[�^���f�^
		float SpeedMeter;								//��]�����n�p�ϐ�
		float rpm;										//�G���W����]��
		float AcceleratingForce;						//������
		float crankShaft;								//�N�����N�V���t�g
		float spinNum;									//�N�����N�V���t�g��]��
		float CrankSpinNum;								//�N�����N�V���t�g�b�ԉ�]��
		float torqueOtationalSpeed;						//�g���N��]��
		float HalfDRR;									//�^�C���̔��a
		float rollingResistance;						//�]�����R�ۊǕϐ�
		float myu;										//���낪���R�W��(��:�~���[
		float metterAngle;								//�^�R���[�^�[
		float HandleBar;								//�n���h��

		bool FinalGear;									//�ŏI�M�A(�t�@�C�i���M�A)�̐ڑ�����
		bool StartMove;									//���i���}
		bool BackCheak;									//��ފm�F�p
		bool GearDelay;									//�M�A�x��
		float Spring;									//�΂˒萔
		float RollStiffness_F, RollStiffness_R;			//���[������Front Rear 
		float sitaaccel, sitabrake;						//���[���s�b�`�A�b�v	//!�Ƃ���sita�ɕύX��낵��
		float WheelGrep;								//�^�C�����Փx	//!�^�C���̐ݒ肪�܂�
		float hydraulic;								//���� //!�����̐ݒ肪�܂�
		float WheelFrontAngle;							//�t�����g�^�C���̊p�x
		float RightFrontWheel, LeftFrontWheel, RightRearWheel, LeftRearWheel;//�E�O�ցE���O�ցE�E��ցE�����
		float MinLength;								//�^�C����1���ɐi�ދ���
		float WheelRpm;									//�^�C���̉�]��
		float PowerSlinder;								//�p���[�V�����_�[
		float KnuckleArm;								//�i�b�N���A�[��
		float centrifugal;								//�׏d
		float Rad;										//����p�x
		float Fc;										//���S��
		float sita;										//�V�[�^
		float RollHeight;								//���[���Z���^�[�Ǝԍ��̒��S
		float tread;									//�g���b�h��
		float AnWheelAngle;								//�^�C���t�p�x
	}car_systems;
	//�􉽊w
	struct Geometry
	{
		int windSpeed;									//����
		float AtmosphericPressure;						//��C�� �C�ȏ�ł�1013.25hpa ���x10M�㏸�ɂ��1hpa
		float temperature;								//�C��
		float DensityOfAir;								//��C�̖��x
		float AirResistanceCoefficient;					//��C��R�W��
		float Air_Speed;								//��C��R�p���x�ۊǕϐ�
		float AirResistanceRealValue;					//��C��R���萔�l
	}geometry;
	/*
		Vector3�^
	*/
	Vector3 angle;									//�p�x
	Vector3 Break;									//�u���[�L
	Vector3 Front;									//����
	Vector3 pos;									//���W
	Vector3 traction;								//�g���N�V����

	Vector3 cross;									//�v�Z�p �O��
	/*
		float �^
	*/
	float scale;									//�傫��
	
	//�����Ԃ�
	float OverBlock;	//�����Ԃ��̂�����
	float wallWeght;//�ǂ̏d�� �Ƃ肠�����R���N���[�g�̏d��
	float weghtRef;//�ԗ��d�ʂ�8�� �s����8���ŕԂ�
	float wallRef;//�ǂ̏d�ʂ�8��
	/*
		bool�^
	*/

	bool missionMode;								//false:AT true:MT

	/*
	���[�X�̂��
	*/
	int Weeks;
	bool GoalInCheak;
public:
	B_Player();
	~B_Player();

	/*
		�Z�b�^�[�E�Q�b�^�[
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

	���Y: BMR32 �����ɉ���������
	�ō����x�E���x�E�d�ʖʂ����߂ɐݒ肵�A�R�[�i�[�ʂ��኱�Ⴍ�ݒ�
	���S�Ҍ������A���l�����̐ݒ�ɂ���
*/
#define SHADOW_SIZE 1024
static class Car_A :public B_Player
{
private:
	/*
		http://www.iwami.or.jp/wakaba-s/bo-so-menu/bo-so-bnr32_3.htm �@�Q��
	*/

	const int Car_cylinder = 6;

	int Inline_Six_Engine[6];	//����U�C���G���W���p�ϐ�
	int step[6];				//�U�C���̃V�����_�[

	float GearRatio[6];//�@BMR R-32�̃M�A�� ��L�Q��
	float FinalGearRatio;							//�t�@�C�i���M�A

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
	void PredictedPosition();//�\���ʒu
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
		���[�X�V�X�e����ǉ����邽�߂̂��
	*/

	void RaceSystem();
	/*
		�u���[�L�f�B�X�N�̃{�[���Ƀ^�C����n���ׂ̃v���O����
	*/
	void BornControl(int num, const Vector3& p);


	static Car_A *GetInstance()				//Singleton 
	{
		static Car_A instnce;
		return &instnce;
	}
};

