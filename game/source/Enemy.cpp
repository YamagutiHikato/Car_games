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
	//���J��ϐ��ێ��p
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
	�� = 0.0f;
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
	GearMax = 4;				//�M�A
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
	GearRatio[0] = 2.844f;		//R��
	GearRatio[1] = 2.193f;		//1��
	GearRatio[2] = 1.952f;		//2��
	GearRatio[3] = 1.401f;		//3��
	GearRatio[4] = 1.000f;		//4��
	GearRatio[5] = 0.892f;		//5��

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

	torque = 0.0f;	//�g���N r.p.m

	DRR = 592.4f;	//�^�C���̒��a(�O�a)mm   DynamicRollingRadius

	IC = 0;

	SilinderSpeed = 60.0f;	//�s�X�g�����x
	crankShafter = 30.0f;	//�P�C���̂P�H������񂳂��V���t�g��]��
	MaxPis = 120;
	sum = 0.0f;
	arrayMaxNum = 0;
	averagenumber = 0.0f;
	spinNum = 0;

	/*
	�n���h������
	*/
	HandleBar = 0.0f;
	PowerSlinder = 0.0f;
	KnuckleArm = 0.0f;

	/*
	���������֘A
	*/
	centrifugal = Rad = Fc = �� = RollHeght = tread = Spring = RollStiffness_F = RollStiffness_R = 0.0f;
	��accel = ��brake = 0.0f;

	SpeedHandle = 0;

	RightIndex = LeftIndex = 0;

	/*
	bool
	*/
	return true;

}


/*
�ȈՓ����蔻��
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
�n���h������i�b�N���A�[���֓`���鐧��
(�n���h���̃��A���e�C����̂P��)
*/
float Car_A_E::PowerSteering(float HandlePower)
{
	//���E�؂�ꂽ�Ƃ��̃n���h��
	HandleBar = HandlePower;

	//�n���h���̊p�x����
	HandleBar *= PI / 180;
	HandleBar *= 360;

	//�p���[�V�����_�[�ɐڑ�
	PowerSlinder += HandleBar/1.5f;

	//�p���[�V�����_�[���琧��
	float HalfSilinderLength = MaxPowerSlinderLength / 2;
	if (PowerSlinder > HalfSilinderLength)PowerSlinder = HalfSilinderLength;
	else if (PowerSlinder < -HalfSilinderLength)PowerSlinder = -HalfSilinderLength;

	//�p���[�V�����_�[����i�b�N���A�[���ɐڑ�
	KnuckleArm = PowerSlinder*PI / 360;


	return  KnuckleArm;
}

/*
�^�C���̌��E��������
*/

void Car_A_E::PredictedPosition()
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

*/
void Car_A_E::OperationSystem()
{
	PredictedPosition();

	/*
	�X���b�g��
	���񂾂Ƃ��̃A�N�Z���X���b�g�����u���[�L�X���b�g���ғ��m�F
	*/
	//GearDelay -= 1;//�N���b�`�q���̐ڑ������܂ł̎���

				   //�������Ƃ��ɃA�N�Z���X���b�g�������邩�̐ݒ�
	if (AI_Throttle==true)
	{
			Throttle += AcceleratingForce*20.0f;
			torqueOtationalSpeed += AcceleratingForce*20.0f;

	}
	else
	{
		Throttle -= Throttle*0.005f;//�����ĂȂ��������	�������͊������Z
		torqueOtationalSpeed -= torqueOtationalSpeed;
	}

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
	if (AI_BreakThrottle==true)
	{
		BreakingPower += 0.8 / (0.7 * 140 * 2)*20.0f;	//�����́@
		torqueOtationalSpeed -= BreakingPower;
		Throttle -= BreakingPower;
	}
	else BreakingPower = 0.0f;//�����ĂȂ��������
	if (AI_BackThrottle == true)
	{
		BackThrottle += AcceleratingForce*8.0f;//�����ׂ̈�2�{�@
		Throttle -= BackThrottle;
		torqueOtationalSpeed += AcceleratingForce;
		Gear = 0;
	}

	/*
	TODO:�o�O
	�X���b�g���񂵂���ŃV�t�g�_�E���ō���]��
	�V�t�g���ɑ��x�ቺ

	�O�̃M�A�ƌ��݂̃M�A�����v�Z���邱�ƂŔ��f

	AT����
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

		if (Throttle > OverLevMax-0.2f)//�V�t�g�A�b�v AT
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
����4�C���G���W���̍\���֐�
*/
void Car_A_E::StraightFourEngine()
{
	//������
	crankShaft = 0.0f;		//�N�����N�V���t�g�`����]�ϐ�
	spinNum = 0.0f;			//�N�����N�V���t�g��]�ϐ�
	num = 0;				//���ω��Z�ϐ�

							/*
							TODO:	�N�����N�V���t�g��]�֌W
							�N�����N�V���t�g��1��]������@��]�ϐ��ɓn��
							6�C���^��4�H���ŃN�����N�V���t�g��2��](720��)�����
							*/
	for (int i = 0;i < 4;i++)SilinderUpdate(i);	//4�C���ׁ̈@4���

	spinNum = crankShaft / 360;			//�b���ɃN�����N�V���t�g�̉�]���ʂ�񍐂���

										/*
										�s�X�g���㉺�^��(2��)*�N�����N�V���t�g�̃X�g���[�N��/1000(mm��m�ɒ�����)*��]��
										*/
	CrankSpinAverage[IC] = (2 * 0.38f / 1000 * spinNum) * 3600;
	CrankSpinAverage[IC] *= 2;
	//���Ϗ���
	if (IC >= MaxSilinderAve - 1)IC = 0;		else IC++;

	//����
	//�z��ő吔�l�擾
	arrayMaxNum = sizeof(CrankSpinAverage) / sizeof(CrankSpinAverage[0]);

	for (int i = 0;i < MaxSilinderAve;i++) num += CrankSpinAverage[i];
	//���ς��擾
	averagenumber = num / arrayMaxNum;
	CrankSpinNum = averagenumber;
	idlingBreakSpeed = averagenumber;
	//TODO: �A�N�Z���ӂ߂Ȃ��悤�ɂ��Ă�

	CrankSpinNum += Throttle;
}


/*
�g���N�V����
*/
Vector3 Car_A_E::Traction()
{

	//�O������\�����Ă���P�ʃx�N�g��
	Front.x = sinf(angle.y);
	Front.y = 0.0f;
	Front.z = cosf(angle.y);

	Front.Normalize();

	/*
	�g���N�v�Z
	torque;//�g���N�ō���]��4,400rpm
	(36.0f * torque)=(36.0kgf�m)/4400r.p.m =�ő�g���N=353.0N�Em5
	*/
	EngineDisplacement = (81.0f / 2)*(81.0f / 2)*PI*77.0f * 4;
	EngineDisplacement /= (int)1000;
	torque = 22 * (EngineDisplacement) * 0.5f / (2 * PI) / pow(9.806652f, 2);

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
*/

Vector3 Car_A_E::AirResistance()
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
	AirResistanceCoefficient = 0.3f;
	/*
	�����Ԃ̐��ʓ��e�ʐ�
	*/
	FrontProjectionAreaOfTheAutomobile = (1.335 * 1.625 * 0.8f);
	/*
	/*
	���x
	*/
	Air_Speed = (float)pow(speed, 2);
	/*
	��C��R
	*/
	AirResistanceRealValue = (AirResistanceCoefficient*FrontProjectionAreaOfTheAutomobile*Air_Speed*DensityOfAir) / 2;
	AirResistanceRealValue /= pow(60, 2);	//���݋�C��R�y����
	return Vector3(sinf(AirResistanceRealValue), 0, cosf(AirResistanceRealValue));
}

/*
�]�����R
*/
Vector3 Car_A_E::RollingResistance()
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

	�� = 0.015f;
	rollingResistance = ��*weght*9.8f;

	return Vector3(sinf(rollingResistance), 0, cosf(rollingResistance));
}

/*
�Î~��
*/
Vector3 Car_A_E::StaticForce()
{
	return -Traction()*weght*0.05f;
}

/*
���S��
*/

float Car_A_E::CentrifugalForce()
{
	//���񔼌a=�z�C�[���x�[�X(M)/sin(���Ǌp)
	Rad = (2.4f) / sin(cross.y);
	//���S��=�ԏd/�d�͉����x*���x2/���񔼌a
	Fc = (weght / 9.8f) * (pow(speed, 2) / Rad);
	Fc /= 10000;
	//���[��
	RollHeght = 1.335f / 2;//���[���Z���^�[����d�S�܂ł̋���
	tread = 1335 / 1000;//�g���b�h��
	Spring = RollHeght*9.8f;//�T�X�y���V�������[�����g

	RollStiffness_F = (4300 * pow(tread, 2)) / 2;//���[������ �O
	RollStiffness_R = (3200 * pow(tread, 2)) / 2;//���[������ ��

	 /*
	 ���[���A�b�v
	 ���[�����ʂ͋ɏ�
	 */
	�� = (Fc*RollHeght) / ((RollStiffness_F + RollStiffness_R) - (Spring*RollHeght));

	��accel = (Throttle*RollHeght) / ((4000 * (-4.215 / 2 - 1.345)*1.345) - (Spring*RollHeght));
	��brake = (BreakingPower*RollHeght) / ((5700 * (4.215 / 2 - 1.355)*1.355) - (Spring*RollHeght));
	//���[�����f
	angle.x = ��accel - ��brake;

	//���E�ɗh���p�x(angle.z)�����[���Ŕ��f
	angle.z = ��;

	//�f�o�b�O�f�[�^
	centrifugal = Fc;

	return Fc;
}
/*
�R�[�i�����O�p���[
*/
Vector3 Car_A_E::CorneringForce()
{
	/*
	F=T*Fcp(a)
	T�F�R�[�i�����O�p���[�̓��������D�ԑ̂̐i�s�����ɒ��p
	f�F�R�[�i�����O�p���[���v�Z����֐�[N]
	���F������p
	*/
	Vector3 WouldUpVec(0, 1, 0);//���[���h��̏�x�N�g��

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


	return CounerPower;
}


void Car_A_E::GearInfo()
{

	/*
	TODO: �G���W����RPM
	*/
	rpm = CrankSpinNum;
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

	float bunsi_A, bunsi_B, bunbo_A, bunbo_B, SpeedSaved;

	bunsi_A = ((255 * 0.40f * 2 + 17 * 25.4f)*PI*(rpm - (idlingBreakSpeed * 1000)));
	//!�V�t�g�`�F���W���ɑO�̌v�Z���l�����̃M�A�ɓn���ăV���t�g���������P����
	bunbo_A = (GearRatio[Gear] * FirnalRGR);
	bunsi_B = 60;
	bunbo_B = pow(10, 6);
	SpeedSaved = (bunsi_A / bunbo_A) * (bunsi_B / bunbo_B);

	speed = (SpeedSaved)*RollingResistance().Length();
	//�g���N��]��
	torquePower = 2 * PI *torque*(rpm) / 60 / 1000;

	/*
	1.3962kW �� 1.0�n��

	*/
	//�n�� PTO���g���N�iKg�Em�j��PTO����]���iRPM�j�w 2�� �^ ( 75 �w 60 )
	horsePower = torque * (torqueOtationalSpeed * 1000) * (2 * PI) / (75 * 60);
	//�ō��n��
	//�i��]�� rpm) �~�i�g���N kgfm�j�^1000 �~ 1.3962
	Max_HorsePower = torque * torqueMaxOS * (2 * PI) / (75 * 60);
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
	�V�t�g�ݒ�
	*/
	if (Gear >= 4)Gear = 4;

	if (Gear <= 1)	Gear = 1;									     //�P���͉����Ȃ�(��ނ͍��x

}

void Car_A_E::SilinderUpdate(int n)
{
	//*************************************************************************************
	//			step 1			�z��
	//*************************************************************************************
	//��C���z������
	if (step[n] == 0)Inline_Four_Engine[n] -= SilinderSpeed;

	//�e�V�����_�[���z�������炻�ꂼ�ꈳ�k�H����
	if (step[n] == 0 && Inline_Four_Engine[n] < 0)
	{
		step[n] = 1;
		//�Ō���̃V�����_�[���z��������N�����N�V���t�g����]
		crankShaft += crankShafter;
		Inline_Four_Engine[n] = 0;
	}

	//*************************************************************************************
	//			step 2			���k
	//*************************************************************************************
	//��C�����k����
	if (step[n] == 1)Inline_Four_Engine[n] += SilinderSpeed;

	//�e�V�����_�[�����k�����炻�ꂼ��R�čH����
	if (step[n] == 1 && Inline_Four_Engine[n] > MaxPis)
	{
		step[n] = 2;
		//�V�����_�[���z��������N�����N�V���t�g����]
		crankShaft += crankShafter;
		Inline_Four_Engine[n] = MaxPis;
	}
	//*************************************************************************************
	//		step 3			�R��
	//*************************************************************************************
	//���k������C��R�Ă���
	if (step[n] == 2)Inline_Four_Engine[n] -= SilinderSpeed;

	//�e�V�����_�[���R�Ă����炻�ꂼ��r�C�H����
	if (step[n] == 2 && Inline_Four_Engine[n] < 0)
	{
		step[n] = 3;
		//�e�V�����_�[���z��������N�����N�V���t�g����]
		crankShaft += crankShafter;
		Inline_Four_Engine[n] = 0;
	}
	//*************************************************************************************
	//		step 4			�r�C
	//*************************************************************************************
	//�R�Ă��ꂽ��C��r�C����
	if (step[n] == 3)Inline_Four_Engine[n] += SilinderSpeed;

	//�e�V�����_�[���z�������炻�ꂼ�ꈳ�k�H����
	if (step[n] == 3 && Inline_Four_Engine[n] > MaxPis)
	{
		step[n] = 0;
		//�e�̃V�����_�[���z��������N�����N�V���t�g����]
		crankShaft += crankShafter;
		Inline_Four_Engine[n] = MaxPis;
	}
}

/*
�^�C���`�B
*/
void Car_A_E::WheelProcess()
{
	/*
	�^�C���̊O��
	*/
	TheOuterCircumferenceOfTheTire = ((DRR)*PI) / 1000;
	/*
	�^�C����1���Ԃɐi�ދ���
	*/
	MinLength += speed * 1000 / 216000;
	/*
	�^�C���̉�]��
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
	//�ԑ̗̂�
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
	����n�Ăяo��
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

}


void Car_A_E::Render(iexShader*shader, char*chr)
{

	obj->Update();
	//�v���C���[
	obj->Render(shader, chr);
	obj2->Render(shader, chr);
	obj3->Render(shader, chr);
	obj4->Render(shader, chr);
	obj5->Render(shader, chr);
	obj6->Render(shader, chr);

	char str[256];
	sprintf(str, "�́[�Ǎ��W:\n"
		"X:%f\nZ:%f\n"
		"���W:\n"
		"X:%f\nZ:%f\n"
		"%f\n"

		, testNode.x, testNode.z, pos.x, pos.z,Getcross.y
	);
	IEX_DrawText(str, 300, 500, 1920, 1080, 0xffffffff);

}
