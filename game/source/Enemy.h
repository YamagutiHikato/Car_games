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
TODO:�]�T������΁A�X�e�[�^�X�l��TextLoader�Ɉڍs
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
	iexMesh*obj;						//���f��
	iex3DObj*obj2;
	iexMesh*obj3;
	iexMesh*obj4;
	iexMesh*obj5;
	iexMesh*obj6;
	Vector3 pointer;

										/*
										Vector3�^
										*/
	Vector3 angle;									//�p�x
	Vector3 Break;									//�u���[�L
	Vector3 Front;									//����
	Vector3 pos;									//���W
	Vector3 traction;								//�g���N�V����
	Vector3 cross;
	Vector3 TaiyaAngle;
	/*
	int�^
	*/
	int HandleMode;									//0:���ʁ@1:���@2:�E
	int Gear;										//�~�b�V�����M�A
	int GearMax;									//�M�A�ō���

	int LevLimit;									//���u���~�b�^�[
	int missionMode;								//AT��MT�ɑI������`��
	int windSpeed;									//����


	unsigned int color, LevColor;

	double idlingBreakSpeed;
	double speed;									//�����x
	double SpeedHandle;
													/*
													float �^
													*/
	float OtationalSpeed;							//��]��
	float BreakingPower;							//�u����L�X���b�g��
	float SubBreakingPower;							//�T�C�h�u���[�L
	float DRR;										//�^�C�����a
	float ERatio;									//�g�����X�~�b�V��������
	float GearDelay;								//�M�A�x��
	float FirnalRGR;								//�t�@�C�i���f�t��
	float HighSpeed;								//AT�@����
	float MaxSpeed;									//�ԗ��ō������x
	float RGR;										//�f�t��
	float scale;									//�傫��
	float SelecterReductionGearRation;				//������@�ݒ�^
	float SlowSpeed;								//AT �ᑬ
	float Throttle;									//�A�N�Z���X���b�g��
	float BackThrottle;
	float weght;									//�d��
	float FinalGearRatio;							//�t�@�C�i���M�A
	float SpeedMeter;								//��]�����n�p�ϐ�
	float rpm;										//�G���W����]��
													/*
													��C��
													�C�ȏ�ł�1013.25hpa
													���x10M�㏸�ɂ��1hpa
													�v�Z��x�m�R���Ŗ�0.7�C���A���x5,500 m �Ŗ�0.5�C���A�G�x���X�g�̒���ł͖�0.3�C��
													*/
	float AtmosphericPressure;
	float temperature;								//�C��
	float DensityOfAir;								//��C�̖��x
	float AirResistanceCoefficient;					//��C��R�W��
	float FrontProjectionAreaOfTheAutomobile;		//�����Ԃ̐��ʓ��e�ʐ�
	float Air_Speed;								//��C��R�p���x�ۊǕϐ�
	float AirResistanceRealValue;					//��C��R���萔�l
	float AcceleratingForce;						//������
	float horsePower;								//�n��
	float Max_HorsePower;							//�ō��n��
	float PowerToWeightRatio;						//�p���[�E�F�C�g���V�I
	float crankShaft;								//�N�����N�V���t�g
	float spinNum;									//�N�����N�V���t�g��]��
	float CrankSpinNum;								//�N�����N�V���t�g�b�ԉ�]��
	float torque;									//�g���N
	float EngineDisplacement;						//�r�C��
	float torqueOtationalSpeed;						//�g���N��]��
	float HalfDRR;									//�^�C���̔��a
	float torqueMaxOS;								//�g���N�ō���]��
	float torquePower;								//�g���N�E�g���N��]��
	float rollingResistance;						//�]�����R�ۊǕϐ�
	float ��;											//���낪���R�W��(��:�~���[
	float num;
	/*
	bool�^
	*/
	bool FinalGear;									//�ŏI�M�A(�t�@�C�i���M�A)�̐ڑ�����
	bool StartMove;									//���i���}
	bool PowerTex;									//���x�E��]�����̃��j�^�[�`�F�b�N

	bool AI_Throttle;					//�A�N�Z���𓥂�ŗǂ����̔���
	bool AI_BreakThrottle;				//�u���[�L�𓥂�ŗǂ����̔���
	bool AI_BackThrottle;


	float HandleBar;//�n���h��
	float metterAngle;		//�^�R���[�^�[
	float WheelFrontAngle;

	/*
		AI�p
	*/
	//���J��ϐ��ێ��p
	int	CatchNodeNumber;
	int testTimer;

	//�f�o�b�N
	Vector3 testNode;
	int ind;

public:
	B_Enemy();
	~B_Enemy();

	/*
	�Z�b�^�[�E�Q�b�^�[
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
		http://ae86.s1.xrea.com/4ag/transmission/transmission.htm ���Q�Ƃɉ���
	*/
	int indexNumber;
	int Inline_Four_Engine[4];	//����4�C���G���W���p�ϐ�
	int step[4];				//4�C���̃V�����_�[
	int MaxPis;			//�V�����_�[�ő劄��
	int arrayMaxNum;	//���ύő�ϐ�
	int IC;				//�V�����_�[�̕��ϊm�F�p�ϐ�
	int SilinderSpeed;	//���b�񂳂��s�X�g��
	int ShiftCheakNum;	//�V�t�g�`�F���W�ɂ��V�t�g�G���[��h���㗝�ϐ�


	float GearRatio[5];//�@AE86 ���r���̃M�A�� ��L�Q��
	float CrankSpinAverage[18];	//�N�����N�V���t�g���ω�]��
	float crankShafter;	//�e�C������V���t�g�։񂷉�]�ϐ�
	float sum;			//���ύ��v�l
	float averagenumber;//���ϕۊǕϐ�

	float RightFrontWheel, LeftFrontWheel, RightRearWheel, LeftRearWheel;//�E�O�ցE���O�ցE�E��ցE�����
	float TheOuterCircumferenceOfTheTire;//�^�C���̊O��
	float MinLength;//�^�C����1���ɐi�ދ���
	float WheelRpm;//�^�C���̉�]��


	float PowerSlinder;//�p���[�V�����_�[
	float KnuckleArm;//�i�b�N���A�[��

	float centrifugal;//�׏d
	float Rad;//����p�x
	float Fc;//���S��
	float ��;//�V�[�^
	float RollHeght;//���[���Z���^�[�Ǝԍ��̒��S
	float tread;//�g���b�h��
	float Spring;//�΂˒萔
	float RollStiffness_F, RollStiffness_R;//���[������Front Rear 
	float ��accel, ��brake;//���[���s�b�`�A�b�v

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
	void PredictedPosition();//�\���ʒu

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
