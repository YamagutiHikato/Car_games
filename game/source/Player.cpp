#include "iextreme.h"
#include "Player.h"
#include "UI_Texture.h"

#include <random>

#define DebugDrawText
#define SolidFrameModel
//#define WrieFrameModel

/*
	�G���W���̕ϓ�����
*/
std::random_device randomDevice;
std::mt19937 randomEngine(randomDevice());

std::uniform_real_distribution<float>ExplosionChangeTheNumberOfTimes(30.0f*0.2f, 30.0f*1.0f);
std::uniform_real_distribution<float>AirInjector(0.0f, 100.0f);

/*
		�x�[�X�ƂȂ镔��
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
	������
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
		���[�X�֌W
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
	�������ݒ�
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
	GearMax = 5;				//�M�A

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
	GearRatio[0] = 3.369f;		//R��
	GearRatio[1] = 3.214f;		//1��
	GearRatio[2] = 1.925f;		//2��
	GearRatio[3] = 1.302f;		//3��
	GearRatio[4] = 1.000f;		//4��
	GearRatio[5] = 0.752f;		//5��

	FinalGearRatio = 4.111f;

	scale = 0.5f;

	/*
		�ԑ̕���
	*/
	DRR = 631.0f;			//�^�C���̒��a(�O�a)mm   DynamicRollingRadius
	HalfDRR = DRR / 2;
	weght = 1780.7f;/*1200.0f*/

	RGR = 2.98377f;
	FirnalRGR = 3.43441f;
	GearDelay = 0.0f;
	crankShaft = 0.0f;
	for (int i = 0;i < MaxSilinderAve;i++)CrankSpinAverage[i] = 0.0f;
	/*
		UI����
	*/
	metterAngle = 0.0f;
	/*
		�G���W������
	*/
	IC = 0;
	SilinderSpeed = 60;	//�s�X�g�����x
	spinNum = 0;
	CrankSpinNum = 0;
	crankShafter = ExplosionChangeTheNumberOfTimes(randomEngine);	//�P�C���̂P�H������񂳂��V���t�g��]��
	MaxPis = 120;
	sum = 0.0f;
	arrayMaxNum=0;
	averagenumber = 0.0f;
	torqueMaxOS = 4400.0f;
	/*
		�^�C������
	*/
	RightFrontWheel = LeftFrontWheel = RightRearWheel = LeftRearWheel = 0.0f;
	TheOuterCircumferenceOfTheTire = 0.0f;
	MinLength = 0.0f;
	WheelRpm = 0.0f;
	TaiyaAngle=ZEROVECTOR;
	WheelGrep = 1.0f;
	/*
		�n���h������
	*/
	HandleBar = 0.0f;
	PowerSlinder = 0.0f;
	KnuckleArm = 0.0f;
	/*
		���������֘A
	*/
	centrifugal =Rad =Fc = sita =RollHeight
	=tread =Spring =RollStiffness_F = RollStiffness_R = 0.0f;
	��accel = ��brake = 0.0f;
	 OverBlock = 0;
	 wallWeght = 2300.0f;
	 weghtRef = 1200 * 0.8f;
	 wallRef = wallWeght*0.8f;
	/*
		bool
	*/
	StartMove = false;

	/*
		�G���W�����[��
	*/
	Engine_parts.TargetInitialization(0.0f);
	for (int i = 0;i < 6;i++)Engine_parts.Battery[i] = 0.0f;
	hydraulic = 0.0f;
	/*
		�M�A�ƃ~�b�V�����֌W
	*/
	Engine_Gearmissions.TargetInitialize(0.0f);
	for (int i = 0;i < MaxSilinderAve;i++)
	{
		Engine_Gearmissions.CrankSpinAverage[i] = Engine_Gearmissions.IdlingCrankSpinAverage[i] =0.0f;
	}
	return true;
}

/*
	�ȈՓ����蔻��

	�����蔻��ɂ��@�͂ݏo�����l���犄������
	ver.1.112 2018/02/22
*/

void Car_A::ModelCollision()
{
	float work = 0;
	/*
	mv+M�E0=mv'+M
	*/

	OverBlock = (weght * speed + wallWeght -weghtRef + wallRef)/3600;
	//if (OverBlock <= 0.0f)OverBlock = 0.0f;
	//�O��
	work = Collision::GetInstance()->getFront(pos);
	if (pos.z > work - CollisionRangeNumericalValue)
	{		
		Throttle -= OverBlock/1000;
		//speed -= OverBlock;
		pos.z = work - CollisionRangeNumericalValue;
	}

	//���
	work = Collision::GetInstance()->getBack(pos);
	if (pos.z < work + CollisionRangeNumericalValue)
	{
		Throttle -= OverBlock/1000;
		//speed -= OverBlock;
		pos.z = work + CollisionRangeNumericalValue;
	}

	//�E
	work = Collision::GetInstance()->getRight(pos);
	if (pos.x > work - CollisionRangeNumericalValue)
	{
		Throttle -= OverBlock/1000;
		//speed -= OverBlock;
		pos.x = work - CollisionRangeNumericalValue;
	}
	//��
	work = Collision::GetInstance()->getLeft(pos);
	if (pos.x < work + CollisionRangeNumericalValue)
	{
		Throttle -= OverBlock/1000;
		//speed -= OverBlock;
		pos.x = work + CollisionRangeNumericalValue;
	}
}

/*
	���X�e�B�b�N�̌X������n���h���֓`���鐧��n
	ver.1.112 2018/02/22
*/

bool Car_A::MoveContrl(float max)
{
	static float moveSpeed;
	//	����
	moveSpeed += 0.3f;
	if (moveSpeed > max) moveSpeed = max;
	//	���̌X���̎擾
	float axisX = KEY_GetAxisX()*0.002f;
	//�@���̌X���ƒ���
	float d = sqrtf(axisX * axisX);
	//	���̌X���̗V��
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
	//	���̌X���␳
	if (d > 1.0f)
	{ 
		axisX /= d;
	}
	//�n���h���֐��ֈڍs
	PowerSteering(axisX*SpeedHandle);
	return true;
}

/*
	�n���h������i�b�N���A�[���֓`���鐧��
	ver.1.112 2018/02/22
*/

float Car_A::PowerSteering(float HandlePower)
{
	/*
	���E�؂�ꂽ�Ƃ��̃n���h����
	�n���h���V���t�g��ʂ�
	*/
	HandleBar = HandlePower;
	/*
	�n���h���̊p�x����
	�n���h���V���t�g�̉�]�����߂�
	*/
	HandleBar *= PI / 180.0f;
	HandleBar *= 360.0f;	//�������l
	/*
	�p���[�V�����_�[�ɐڑ�
	�n���h���͉�]����̂ɑ΂��A�p���[�V�����_�[�͍��E�ɂ������Ȃ�
	*/
	PowerSlinder += HandleBar*1.2f;
	/*
	�p���[�V�����_�[���琧��
	MaxPowerSlinderLength = �V�����_�[�̒����̔����Ɏw��
	*/
	float HalfSilinderLength = MaxPowerSlinderLength / 2;
	if (PowerSlinder > HalfSilinderLength)PowerSlinder = HalfSilinderLength;
	else if (PowerSlinder < -HalfSilinderLength)PowerSlinder = -HalfSilinderLength;
	//�p���[�V�����_�[����i�b�N���A�[���ɐڑ�
	KnuckleArm = PowerSlinder*PI/360.0f;

	return  KnuckleArm;
}

/*
	�^�C���̌��E��������
	ver.1.112 2018/02/22
*/
void Car_A::PredictedPosition()
{
	//��]�p�x�̐���
	if (angle.y > 360.0f)angle.y = -360.0f;
	if (angle.y < -360.0f)angle.y = 360.0f;
	
	/*
	�^�C���̎֊p	���f�l�𒲐�
	*/
	WheelFrontAngle = angle.y + KnuckleArm*0.30f;
	{
		//����
		Vector3 VecAngle;

		//�`�B�������l
		float TransmissionTimingNumbers = 14.0f;

		VecAngle.x = sinf(angle.y);
		VecAngle.y = 0.0f;
		VecAngle.z = cosf(angle.y);

		//�^�C���̊p�x�ɓ`�B
		TaiyaAngle.x = pos.x + sinf(WheelFrontAngle) * TransmissionTimingNumbers;
		TaiyaAngle.z = pos.z + cosf(WheelFrontAngle) * TransmissionTimingNumbers;

		//���W���f
		pos.x += sinf(angle.y)*(speed*0.03f);
		pos.z += cosf(angle.y)*(speed*0.03f);

		//�^�C���̊p�x�`�B�ōX�V
		TaiyaAngle.x = pos.x + sinf(WheelFrontAngle) * TransmissionTimingNumbers;
		TaiyaAngle.z = pos.z + cosf(WheelFrontAngle) * TransmissionTimingNumbers;

		//�����x�N�g���擾
		Vector3 LengthPos;
		LengthPos = TaiyaAngle - pos;

		//�O�ρE����
		Vector3Cross(cross, VecAngle, LengthPos);

		float dot = Vector3Dot(VecAngle, LengthPos);
		float l1 = sqrtf(pow(VecAngle.x, 2) + pow(VecAngle.z, 2));
		float l2 = sqrtf(pow(LengthPos.x, 2) + pow(LengthPos.z, 2));

		float cosValue = dot / (l1 * l2);

		//�p�x�펞�C��
		float dAngle = 1.0f - cosValue;
		if (dAngle > 0.5f)dAngle = 0.5f;

		//�X�e�A�����O�̋���
		float SteerPower;
		SteerPower = speed * 0.0055f;
		if (SteerPower >= 0.5)SteerPower = 0.5f;
		if (cross.y > .0f)angle.y += dAngle * SteerPower;
		else angle.y -= dAngle * SteerPower;
	}

}

/*
		����n
		ver.1.112 2018/02/22
*/
void Car_A::OperationSystem(int n)
{
	//�^�C����������
	PredictedPosition();
	/*
	�X���b�g��
	���񂾂Ƃ��̃A�N�Z���X���b�g�����u���[�L�X���b�g���ғ��m�F
	*/

	//�������Ƃ��ɃA�N�Z���X���b�g�������邩�̐ݒ�
	if (GearDelay == false)//�N���b�`���q�����܂ŃX���b�g������
	{
		Throttle += AcceleratingForce * (KEY_GetAxisY3()*0.02f);//�����ׂ̈�2�{�@
		torqueOtationalSpeed += AcceleratingForce  * (KEY_GetAxisY3()*0.01f);
		ThrottleTacoMetter += AcceleratingForce * (KEY_GetAxisY3()*0.02f);
		ShiftCheakNum = Gear;
	}
	else
	{	
		if (ThrottleTacoMetter >= ShiftChangeLevs)
		{
			GearDelay = false;//�N���b�`�q���̐ڑ������܂ł̎���	
		}
	}
	Throttle -= Throttle*0.005f;//�����ĂȂ��������	�������͊������Z
	ThrottleTacoMetter -= ThrottleTacoMetter*0.005f;
	torqueOtationalSpeed -= ThrottleTacoMetter*0.0025f;

	/*
		�u���[�L�̖��C�W��
		�������A�X�t�@���g�܂��̓R���N���[�g	0.7
		�ʂꂽ�R���N���[�g	0.5
		�ʂꂽ�A�X�t�@���g	0.45�`0.6
		�������H	0.55
		��������ܑ����H	0.65
		�ʂꂽ��ܑ����H	0.4�`0.5
		�ł��Ȃ�����	0.15
		�X	0.07
	*/
	//�������Ƃ��Ƀu���[�L�X���b�g�������邩�̐ݒ�

	BreakingPower += (0.8 / (0.7 * 140 * 2))* (KEY_GetAxisX3()*0.001f);	//�����́@
	torqueOtationalSpeed -= BreakingPower;
	Throttle -= BreakingPower;
	ThrottleTacoMetter -= BreakingPower;

	//else BreakingPower = 0.0f;//�����ĂȂ��������

	//�o�b�N
	if (KEY_Get(KEY_D) == 1)
	{
		if (BackCheak == false)
		{
			stackGear = Gear;
			BackCheak = true;
		}

		BackThrottle += AcceleratingForce*8.0f;//�����ׂ̈�2�{�@
		Throttle -= BackThrottle;
		ThrottleTacoMetter = Throttle;
		torqueOtationalSpeed += AcceleratingForce;
		Gear = 0;

	}
	else
	{
		BackThrottle -= BackThrottle*0.025f;//�����ĂȂ��������	�������͊������Z

		if (BackCheak == true)
		{
			BackCheak = false;
		}
	}
	/*
		�ȈՃT�C�h�u���[�L
	*/

	if (KEY_Get(KEY_R2) == 1)
	{
		SubBreakingPower += 0.8 / (0.7 * 140 * 2) / 8;	//�����́@
		Throttle -= SubBreakingPower;
		ThrottleTacoMetter = Throttle;
		torqueOtationalSpeed -= SubBreakingPower;
	}
	else SubBreakingPower = 0.0f;//�����ĂȂ��������

/*
	�O�̃M�A�ƌ��݂̃M�A�����v�Z���邱�ƂŔ��f

	AT����
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

		if (Throttle > OverLevMax)//�V�t�g�A�b�v AT
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

		if (KEY_Get(KEY_L2) == 1 && KEY_Get(KEY_B) == 3)//�V�t�g�A�b�v MT
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
//	TODO :�G���W���쓮�n
//**************************************************************************************

/*
	���������ɂ�肩���񂳂��N�����N�V���t�g�̉�]�����߂�
*/

/*
	����6�C���G���W���̍\���֐�
	ver.1.112 2018/02/22
*/
void Car_A::StraightSixEngine()
{
	//������
	Engine_parts.CrankShaft = 0.0f;
	Engine_parts.ComShaft = 0.0f;
	Engine_Gearmissions.num = Engine_Gearmissions.num2 = 0;

	//num = 0;

	//�G���W���̋N��
	for (int i = 0;i < 6;i++)SilinderUpdate(i, Engine_parts.ConectingRod);

	{
		//�G���W����Ԃ𖈕b�L�^����
		Engine_Gearmissions.CrankSpinAverage[Engine_Gearmissions.CylinderAverages] =
			((2 * (0.25f / 1000)*(Engine_parts.CrankShaft / 360)) * 3600) * 2;
		Engine_Gearmissions.IdlingCrankSpinAverage[Engine_Gearmissions.CylinderAverages] =
			Engine_Gearmissions.CrankSpinAverage[Engine_Gearmissions.CylinderAverages];
		//�����ŉߋ�����z�u�i���ŃR�����g�A�E�g���Ă���)�@���ʁA�G���W���������オ����
		Engine_Gearmissions.CrankSpinAverage[Engine_Gearmissions.CylinderAverages] +=
			(Throttle - BackThrottle);

		if (Engine_Gearmissions.CylinderAverages >= MaxSilinderAve - 1)
			Engine_Gearmissions.CylinderAverages = 0;else Engine_Gearmissions.CylinderAverages++;

		//�z��ő吔
		Engine_Gearmissions.ArrayMaxNumber = sizeof(Engine_Gearmissions.CrankSpinAverage) / sizeof(Engine_Gearmissions.CrankSpinAverage[0]);

		for (int i = 0;i < MaxSilinderAve;i++)
		{
			Engine_Gearmissions.num += Engine_Gearmissions.CrankSpinAverage[i];
			Engine_Gearmissions.num2 += Engine_Gearmissions.IdlingCrankSpinAverage[i];
		}

		//���ς��擾
		Engine_Gearmissions.AverageNumber = Engine_Gearmissions.num / Engine_Gearmissions.ArrayMaxNumber;
		torqueOtationalSpeed = Engine_Gearmissions.AverageNumber / 2;
		Engine_Gearmissions.IdlingAverageNumber = Engine_Gearmissions.num2 / Engine_Gearmissions.ArrayMaxNumber;
		Engine_Gearmissions.CrankNumberOfRevolutionsPerSecond = Engine_Gearmissions.AverageNumber;	//!�N�����N�V���t�g
		Engine_Gearmissions.UICrankNumberOfRevolutionsPerSecond = Engine_Gearmissions.AverageNumber;	//!�^�R���[�^���f
		idlingBreakSpeed = Engine_Gearmissions.IdlingAverageNumber;	//!�A�C�h�����O��Ԕ��f
	}
}


/*
	�g���N�V����
	ver.1.112 2018/02/22
*/
Vector3 Car_A::Traction()
{

	//�O������\�����Ă���P�ʃx�N�g��
	Front.x = sinf(angle.y);
	Front.y = 0.0f;
	Front.z = cosf(angle.y);

	Front.Normalize();

	/*
		�g���N�v�Z
		torque/�g���N�ō���]��4,400rpm
		(36.0f * torque)=(36.0kgf�m)/4400r.p.m =�ő�g���N=353.0N�Em5
	*/
	EngineDisplacement = (86.0f / 2)*(86.0f / 2)*PI*73.7f*6;//�{�A�̔�����2��@�~�@�΁@�~�@�X�g���[�N�@�~�@�C����
	EngineDisplacement /= (int)1000;
	torque = 22 * (EngineDisplacement) * 0.5f / (2 * PI) /pow(9.806652f,2);//(�������ϗL������(22)�j�~�i�r�C�ʁj�~�i������(4�T�C�N���ł����0.5)�j�^�i2�΁j
	MaxTorque = Max_HorsePower * 75.0f * 60.0f / LevLimit * 2 * PI;
	
	/*
	�f�t��(������		ReductionGearRatio
	*/
	if (Gear < GearMax)SelecterReductionGearRation = FirnalRGR;
	else SelecterReductionGearRation = RGR;

	/*
	�g�����X�~�b�V��������
	*/
	if (torqueMaxOS >= OtationalSpeed)		ERatio = SlowSpeed;
	if (torqueMaxOS < OtationalSpeed)		ERatio = HighSpeed;

	/*
		�^�C�����a
	*/
	HalfDRR = DRR / 2;
	/*
	�g���N�V����
	*/

	traction = (Front*(torquePower)*Throttle*GearRatio[Gear] * SelecterReductionGearRation * ERatio) / HalfDRR;

	return traction;

}

/*
	��C��R
	ver.1.112 2018/02/22
*/

Vector3 Car_A::AirResistance()
{
	/*
	��C��R=��C�̖��x*��C��R�W��*�����Ԃ̐��ʓ��e�ʐ�*���x^���x/2
	��C�̖��x = {1.293*��C��(1-0.378�y�����C���z/��C��)}/1+�C��/273.15
	��C��R�W��:	��p��0.3~0.5 �g���b�N:0.4~0.6 �o�X0.5~0.8 ��֎�0.6~0.9
	�����Ԃ̐��ʓ��e�ʐ�:	�g���b�h��*�S�� �܂��́@�S���@* �S�� * 0.8�̂ǂ��炩���g��
	*/
	/*
	��C�̖��x
	*/
	DensityOfAir = AtmosphericPressure / (2.87f*(temperature + 273.15f));
	/*
	��C��R�W��
	*/
	AirResistanceCoefficient = 0.4f;
	/*
	�����Ԃ̐��ʓ��e�ʐ�
	*/
	FrontProjectionAreaOfTheAutomobile = (1.340f * 1.755f * 0.8f);
	/*
	/*
	���x
	*/
	Air_Speed =(float) pow(speed,2);
	/*
	��C��R
	*/
	AirResistanceRealValue = (AirResistanceCoefficient*FrontProjectionAreaOfTheAutomobile*Air_Speed*DensityOfAir) / 2;
	AirResistanceRealValue /= pow(60,3);	//���݋�C��R�y����
	return Vector3(sinf(AirResistanceRealValue), 0.0f, cosf(AirResistanceRealValue));
}

/*
	�]�����R
	ver.1.112 2018/02/22
*/
Vector3 Car_A::RollingResistance()
{
	/*
	���H����								��r
	���������n							��0.25
	���܂��͐ΊD���̓�						��0.17
	�V����������~������					��0.13
	�΂̑����ʉ���						��0.08
	�����̂悢��������					��0.03
	�A�X�t�@���g�܂��̓R���N���[�g��			��0.015
	*/

	myu = 0.015f;//�^���Ɍ������΂��A�Ԃ��l�Ńʂ�ϓ�������ׂ��������A����͕ϓ��Ȃ�
	rollingResistance = myu*weght*9.8f;
	
	return Vector3(sinf(rollingResistance),0,cosf(rollingResistance));
}
/*
	�Î~��
	ver.1.112 2018/02/22
*/
Vector3 Car_A::StaticForce()
{
	return -Traction()*weght*0.05f;
}

/*
	���S��

*/

float Car_A::CentrifugalForce()
{
	//���񔼌a=�z�C�[���x�[�X(M)/sin(���Ǌp)
	Rad = (2.615f) / sin(cross.y);
	//���S��=�ԏd/�d�͉����x*���x2/���񔼌a
	Fc = (weght / 9.8f) * (pow(speed, 2) /Rad);
	Fc /= 10000;
	//���[��
	RollHeight = 1.325f / 3;//���[���Z���^�[����d�S�܂ł̋���
	tread = 1460/1000;//�g���b�h��
	Spring = RollHeight*9.8f;//�T�X�y���V�������[�����g

	RollStiffness_F = (5700*pow(tread, 2)) / 2;//���[������ �O
	RollStiffness_R = (4000*pow(tread, 2)) / 2;//���[������ ��
	
	/*
	���[���A�b�v
	���[�����ʂ͋ɏ�
	*/
	sita = (Fc*RollHeight) / ((RollStiffness_F+ RollStiffness_R) - (Spring*RollHeight));
	
	��accel = (Throttle*RollHeight) / ((4000 * (-4.530f / 2 - 2.615f)*2.625f) - (Spring*RollHeight));
	��brake = (BreakingPower*RollHeight) / ((5700 * (4.530f / 2 - 2.615f)*2.625f) - (Spring*RollHeight));
	//���[�����f
	angle.x = (speed*(��accel - ��brake))* CorneringForce().x;

	//���E�ɗh���p�x(angle.z)�����[���Ŕ��f
	angle.z = sita* CorneringForce().z;//

	//�f�o�b�O�f�[�^
	centrifugal = Fc;

	return Fc;
}
/*
	�R�[�i�����O�p���[
	ver.1.112 2018/02/22
*/
Vector3 Car_A::CorneringForce()
{
	/*
	F=T*Fcp(a)
	T�F�R�[�i�����O�p���[�̓��������D�ԑ̂̐i�s�����ɒ��p
	f�F�R�[�i�����O�p���[���v�Z����֐�[N]
	���F������p
	*/
	Vector3 WouldUpVec(0.0f, 1.0f, 0.0f);//���[���h��̏�x�N�g��

	//�i�s����
	Vector3 Angle;
	Angle.x = sinf(angle.y);
	Angle.z = cosf(angle.y);

	Vector3 CounerPower;
	/*
	�ԑ̐i�s�����Ɛ��E�̏�����x�N�g������R�[�i�����O�p���[�̓����������킩��
	�������O�ςŌv�Z���邱�Ƃŋ��߂邱�Ƃ��\
	�i�s�������x�Ɋւ��Ă͑O�t���[������v�Z�������x�̃x�N�g�����K���ŉ\
	*/
	Vector3Cross(CounerPower, Angle/*���ݎԑ̊p�x*/, WouldUpVec/*������x�N�g��*/);//�R�[�i�����O�p���[�̓������� T
	/*
				   /
				  / ���^�C���̌X���̂Ȃ��p
		-------�^�C��-------->	�i�s����
				/|
			   / | 
				 ���R�[�i�����O�t�H�[�X
	*/
	
	return CounerPower*0.5f;
}

/*
	�~�b�V�����M�A�{�b�N�X
	ver.1.112 2018/02/22
*/
void Car_A::TransMissionCustom(const int n)
{
	switch(n)
	{
		case 0://R-32 Normal Misson
			GearRatio[0] = 3.369f;		//R��
			GearRatio[1] = 3.214f;		//1��
			GearRatio[2] = 1.925f;		//2��
			GearRatio[3] = 1.302f;		//3��
			GearRatio[4] = 1.000f;		//4��
			GearRatio[5] = 0.752f;		//5��
			break;
		case 1://R-35 Normal Misson
			GearRatio[0] = 3.700f;		//R��
			GearRatio[1] = 4.056f;		//1��
			GearRatio[2] = 2.301f;		//2��
			GearRatio[3] = 1.595f;		//3��
			GearRatio[4] = 1.248f;		//4��
			GearRatio[5] = 1.001f;		//5��
			break;
	}
}

/*
	���͌n�̏W������
*/
void Car_A::GearInfo()
{
	
	/*
		TODO: �G���W����RPM
	*/
	rpm = Engine_Gearmissions.CrankNumberOfRevolutionsPerSecond;
	rpm *= 1000;
	/*
		�^�C���`�B
	*/
	WheelProcess();
	/*
		���x�`�B
								�^�C���̊O�����@X�@�G���W���̉�]��(rpm)							  60
		���x(km/h)				-----------------------------------			X		-----------------------
								�M�A��@�@�@�@�@X�@�ŏI������									10�̂U��
	*/
	
	float bunsi_A, bunsi_B, bunbo_A, bunbo_B,SpeedSaved;

	bunsi_A = ((255 * 0.40f * 2 + 17 * 25.4f)*PI*(rpm -(idlingBreakSpeed*1000)));
	//!�V�t�g�`�F���W���ɑO�̌v�Z���l�����̃M�A�ɓn���ăV���t�g���������P����
	bunbo_A = (GearRatio[ShiftCheakNum] * FirnalRGR);
	bunsi_B = 60;
	bunbo_B = pow(10, 6);
	SpeedSaved = (bunsi_A/ bunbo_A) * (bunsi_B/ bunbo_B);
	
	speed = (SpeedSaved)*RollingResistance().Length();
	//�g���N��]��
	torquePower = 2 * PI *torque*(rpm)/60/1000;

	/*
	1.3962kW �� 1.0�n��
	
	*/
	//�n�� PTO���g���N�iKg�Em�j��PTO����]���iRPM�j�w 2�� �^ ( 75 �w 60 )
	horsePower = torque * (torqueOtationalSpeed * 1000) * (2 * PI) / (75 * 60);
	//�ō��n��
	//�i��]�� rpm) �~�i�g���N kgfm�j�^1000 �~ 1.3962
	Max_HorsePower= torque * torqueMaxOS * (2 * PI) / (75 * 60);
	//���肷��g���N�𐧌�
	if (horsePower <= 0.0f)
	{
		PowerToWeightRatio = 0;
	}
	//�p���[�E�F�C�g���V�I	���ׂ����肾�ƃf�[�^�@�����͂ɉe��������̂ł��Ȃ��Ƃ������f
	else
	{
		PowerToWeightRatio = weght / Max_HorsePower;
	}

	//������=�g���N*�d�͉����x*�M�A��/�^�C���̔��a/�ԏd
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
	�V�t�g�ݒ�
	*/
	if ( Gear >= 5)Gear = 5;

	if (Gear <= 1 && BackCheak==false)	Gear = 1;									     //�P���͉����Ȃ�(��ނ͍��x
	else if(Gear <= 1 && BackCheak == true)	Gear = 0;

	if (KEY_Get(KEY_RIGHT) == 3)missionMode = 1;
	if (KEY_Get(KEY_LEFT) == 3)missionMode = 0;


}

/*
	�C������n
	�S�C���E�U�C�����ɑΉ��ł���֐��ɕό`���ꂽ
	ver.1.112 2018/02/22
*/

void Car_A::SilinderUpdate(int n, float CylinderSpeed)
{

	//*************************************************************************************
	//			step 1			�z��
	//*************************************************************************************
	//��C���ߋ��o���u�ŔR���ƍ�����@�o���u�̃p�[�c�͏��O
	if (step[n] == 0)
	{
		Engine_parts.CyLinderHead[n] -= CylinderSpeed;
	}
	//��C���z����A���k�H����
	if (step[n] == 0 && Engine_parts.CyLinderHead[n] < 0.0f)
	{
		step[n]++;

		//�C���W�F�N�^�[�z��	��C�̌v�Z�̓L���������̂�1��0�̓�������
		Engine_parts.Injecter += AirInjector(randomEngine);

		//���W�G�[�^�[�̋z�M
		Engine_parts.Radiator -= Engine_parts.Injecter;

		//�G���W���u���b�N�т��Ȃ��悤�ɐ���
		Engine_parts.CyLinderHead[n] = 0.0f;
	}
	//*************************************************************************************
	//			step 2			���k
	//*************************************************************************************
	//��C�������グ��
	if (step[n] == 1)
	{
		Engine_parts.CyLinderHead[n] += CylinderSpeed;
	}

	if (step[n] == 1 && Engine_parts.CyLinderHead[n] >60.0f)
	{
		step[n]++;

		//�G���W���u���b�N�т��Ȃ��悤�ɐ���
		Engine_parts.CyLinderHead[n] = 60.0f;

	}
	//*************************************************************************************
	//		step 3			�R��
	//*************************************************************************************
	if (step[n] == 2)
	{
		Engine_parts.CyLinderHead[n] -= CylinderSpeed;
	}
	if (step[n] == 2 && Engine_parts.CyLinderHead[n] <0.0f)
	{
		step[n]++;
		//�_�΃v���O�I��
		Engine_parts.Battery[n] = 0.0f;
		//�G���W���u���b�N�т��Ȃ��悤�ɐ���
		Engine_parts.CyLinderHead[n] = 0.0f;
	}
	if(step[n] == 2 && Engine_parts.CyLinderHead[n] >0.0f)
	{
		//�R��=�_�΃v���O���X�p�[�N�@������܂ŉ�]���J��Ԃ�
		Engine_parts.Battery[n] = 1;
		//��]���ɃY�����N�����Ȃ������V���t�g
		Engine_parts.TimingBelt = ExplosionChangeTheNumberOfTimes(randomEngine)*n;
		//�J���V���t�g�ƃN�����N�V���t�g����]
		Engine_parts.CrankShaft += Engine_parts.TimingBelt;
		Engine_parts.ComShaft += Engine_parts.TimingBelt / 2;
		//���x����
		Engine_parts.EngineOil =Engine_parts.TimingBelt;
		Engine_parts.Radiator = Engine_parts.EngineOil;

	}
	//*************************************************************************************
	//		step 4			�r�C
	//*************************************************************************************
	if (step[n] == 3)
	{
		Engine_parts.CyLinderHead[n] += CylinderSpeed;
	}
	if (step[n] == 3 && Engine_parts.CyLinderHead[n] > 60.0f)
	{
		step[n] = 0;
		//�C���W�F�N�^�[�r�C
		Engine_parts.Injecter+= AirInjector(randomEngine);

		//�G���W���u���b�N�т��Ȃ��悤�ɐ���
		Engine_parts.CyLinderHead[n] = 60.0f;

		//���W�G�[�^�̔M�����
		Engine_parts.Radiator += Engine_parts.Injecter;

	}

	//���␧��
	if (Engine_parts.Radiator > 100)Engine_parts.Radiator = 100;
	if (Engine_parts.Radiator < 0)Engine_parts.Radiator = 0;

	//���x����
	if (Engine_parts.EngineOil > 100)Engine_parts.EngineOil = 100;
	if (Engine_parts.EngineOil < 0)Engine_parts.EngineOil = 0;
}

/*
	�^�C���`�B
*/

void Car_A::WheelProcess()
{
	/*
		�^�C���̊O��
	*/
	TheOuterCircumferenceOfTheTire = ((DRR)*PI)/1000;
	/*
		�^�C����1���Ԃɐi�ދ���
	*/
	MinLength += speed*1000/ 216000;
	/*
		�^�C���̉�]��
	*/
	WheelRpm = MinLength / TheOuterCircumferenceOfTheTire;
	int WheelConvert = WheelRpm;
	WheelRpm = WheelRpm - WheelConvert;
	WheelRpm = PI * 2 * WheelRpm;

	RightRearWheel = LeftRearWheel = WheelRpm;
}

/*
	�X�V����
*/
static int DelayTimer = 60;
void Car_A::Update()
{
	Engine_parts.ConectingRod = 24.0f;
	
	Traction();
	SpeedHandle = 1.0f;
	metterAngle = Engine_Gearmissions.UICrankNumberOfRevolutionsPerSecond / 3;
	SpeedMeter  =(float) speed / 90;

	//�d��
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
	//����n�Ăяo��
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

	
	//�E��
	Matrix m = *obj2->GetBone(3);
	m *= obj2->TransMatrix;
	Vector3 p(m._41, m._42, m._43);
	obj3->SetPos(p);
	obj3->SetAngle(angle5);
	obj3->SetScale(0.4f);
	obj3->Update();

	//�E�O
	Matrix m3 = *obj2->GetBone(4);
	m3 *= obj2->TransMatrix;
	Vector3 p3(m3._41, m3._42, m3._43);
	obj5->SetPos(p3);
	obj5->SetAngle(angle3);
	obj5->SetScale(0.4f);
	obj5->Update();

	//�E��
	Matrix m4 = *obj2->GetBone(6);
	m4 *= obj2->TransMatrix;
	Vector3 p4(m4._41, m4._42, m4._43);
	obj6->SetPos(p4);
	obj6->SetAngle(angle2);
	obj6->SetScale(0.45);
	obj6->Update();

	//����
	Matrix m2 = *obj2->GetBone(1);
	m2 *= obj2->TransMatrix;
	Vector3 p2(m2._41, m2._42, m2._43);
	obj4->SetPos(p2);
	obj4->SetAngle(angle4);
	obj4->SetScale(0.4f);
	obj4->Update();

	//�������Ă킩��Ȃ����l��2�b���ɍX�V������
	DelayTimer--;
	if (DelayTimer <= 0)
	{
		DelayCrankShaft = Engine_parts.CrankShaft;
		DelayTimer = 60;
	}
}

/*
	�`��n
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
	���[�X�R�[�X���AI�m�[�h�|�C���g���l�A�m�[�h��u��
	���̂��肾�ƃ|�C���g�̕\�������݂��Ȃ��̂ŃZ�R�����Ƃ��ł��Ȃ����Ƃ��Ȃ����
	ver.1.112 2018/02/22
*/
Vector3	RaceClearNodePoint[] =
{
	{ 26,1,-83},	//�X�^�[�g
	{ 1232,1,4324},
	{ 4185,1,9130 },
	{ 4645,1,7780 },
	{ 1274,1,-3828 },
{ -31,1,3736}

};


const int RaceClearNodeMaxNumber = sizeof RaceClearNodePoint / sizeof RaceClearNodePoint[0];
void Car_A::RaceSystem()
{
	//VectorList��node�m��
	std::vector<Vector3>RacSystemNodePoint;

	//�m�[�h������
	RacSystemNodePoint.resize(RaceClearNodeMaxNumber);

	//�ԍ����킹
	for (int i = 0;i < RaceClearNodeMaxNumber;i++)RacSystemNodePoint[i] = RaceClearNodePoint[i];

	//�m�[�h�ƍ��W�x�N�g��
	Vector3 RaceNodeRange;
	RaceNodeRange = RacSystemNodePoint[NodeSaveNumber] - pos;
	RaceNodeRange.Normalize();
	//�����蔻��
	if (Collision::GetInstance()->ColSphere(pos, 90.0f, RacSystemNodePoint[NodeSaveNumber], 120.0f) == true)NodeSaveNumber++;

	//�Ō�̃m�[�h�ɓ��B���A�������Ǝ��񔻒�
	if (RaceClearNodeMaxNumber == NodeSaveNumber)
	{
		NodeSaveNumber = 0;
		Weeks++;
	}
	//����&�S�[���`�F�b�N
	if (Weeks >UI::GetInstance()->GetEndLap() )
	{
		GoalInCheak = true;
		Weeks = UI::GetInstance()->GetEndLap();
	}
}

/*
	�{�[���ԍ����킩�莟��+�{�[�����Ă���̔��f
	ver.1.112 2018/02/22
*/
void Car_A::BornControl(int num, const Vector3&p)
{
	Update();

	//�s��
	Matrix mat = *GetBone(num)*TransMatrix;
	Vector3 front(mat._21, mat._22, mat._23);
	front.Normalize();

	Vector3 vec = p - Vector3(mat._41, mat._42, mat._43);
	vec.Normalize();
	//�t�s��
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