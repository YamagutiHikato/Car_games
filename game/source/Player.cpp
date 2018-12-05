#include "iextreme.h"
#include "Player.h"
#include "UI_Texture.h"

#include <random>

#define DebugDrawText
#define SolidFrameModel

/*
	�G���W���̕ϓ�����
*/
std::random_device randomDevice;
std::mt19937 randomEngine(randomDevice());

std::uniform_real_distribution<float>ExplosionChangeTheNumberOfTimes(30.0f*0.2f, 30.0f*1.0f);//20%~100%
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
	car_systems.NodeSaveNumber = 0;//�ێ��ϐ�������
	car_status.Gear = 1;//�M�A������
	car_status.LevLimit = 0;//������Ԗ���]
	car_systems.SpeedMeter = 0;//�X�s�[�h������

	car_status.speed = 0.0f;//! double�^�̗��R�͕����ő��x�o���ۂ�float���ƌv�Z����������������
	car_systems.idlingBreakSpeed = 0.0f;//�Î~���̃A�C�h�����O�̉�]��
	car_systems.SpeedHandle = 0.0f;//�X���[�W���O�n���h�����O

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
	car_status.GearMax = 5;				//�M�A

	car_status.LevLimit = OverLevMax*1000;

	for (int i = 0;i < Car_cylinder;i++) step[i] = 0;
	car_systems.ShiftCheakNum = 1;
	
	/*
		float
	*/
	GearRatio[0] = 3.369f;		//R��
	GearRatio[1] = 3.214f;		//1��
	GearRatio[2] = 1.925f;		//2��
	GearRatio[3] = 1.302f;		//3��
	GearRatio[4] = 1.000f;		//4��
	GearRatio[5] = 0.752f;		//5��

	FinalGearRatio = 4.111f;//���Ⴂ���Ă������A�T�M�A�Ȃǂł͂Ȃ��A�^�C���Ɋւ���M�A�̂���

	scale = 0.5f;

	/*
		�ԑ̕���
	*/
	car_status.DRR = 631.0f;			//�^�C���̒��a(�O�a)mm   DynamicRollingRadius
	car_systems.HalfDRR = car_status.DRR / 2;
	car_status.weght = 1780.7f;/*1200.0f*/

	car_status.RGR = 2.98377f;
	car_status.FirnalRGR = 3.43441f;
	car_systems.GearDelay =false;
	car_systems.crankShaft = 0.0f;
	for (int i = 0;i < MaxSilinderAve;i++)engine_Gearmissions.CrankSpinAverage[i] = 0.0f;
	/*
		UI����
	*/
	car_systems.metterAngle = 0.0f;
	/*
		�G���W������
	*/
	car_systems.spinNum = 0;
	car_systems.CrankSpinNum = 0;
	car_status.torqueMaxOS = 4400.0f;
	/*
		�^�C������
	*/
	car_systems.RightFrontWheel = car_systems.LeftFrontWheel = car_systems.RightRearWheel = car_systems.LeftRearWheel = 0.0f;
	car_status.TheOuterCircumferenceOfTheTire = ((car_status.DRR)*PI) / 1000;
	car_systems.MinLength = 0.0f;
	car_systems.WheelRpm = 0.0f;
	TaiyaAngle=ZEROVECTOR;
	car_systems.WheelGrep = 1.0f;
	/*
		�n���h������
	*/
	car_systems.HandleBar = 0.0f;
	car_systems.PowerSlinder = 0.0f;
	car_systems.KnuckleArm = 0.0f;
	/*
		���������֘A
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
		�G���W�����[��
	*/
	engine_parts.TargetInitialization(0.0f);
	for (int i = 0;i < Car_cylinder;i++)engine_parts.Battery[i] = 0.0f;
	car_systems.hydraulic = 0.0f;
	/*
		�M�A�ƃ~�b�V�����֌W
	*/
	engine_Gearmissions.TargetInitialize(0.0f);
	for (int i = 0;i < MaxSilinderAve;i++)
	{
		engine_Gearmissions.CrankSpinAverage[i] = engine_Gearmissions.IdlingCrankSpinAverage[i] =0.0f;
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

	OverBlock = (car_status.weght * car_status.speed + wallWeght -weghtRef + wallRef)/3600;
	//if (OverBlock <= 0.0f)OverBlock = 0.0f;
	//�O��
	work = Collision::GetInstance()->getFront(pos);
	if (pos.z > work - CollisionRangeNumericalValue)
	{		
		car_systems.Throttle -= OverBlock/1000;
		//speed -= OverBlock;
		pos.z = work - CollisionRangeNumericalValue;
	}

	//���
	work = Collision::GetInstance()->getBack(pos);
	if (pos.z < work + CollisionRangeNumericalValue)
	{
		car_systems.Throttle -= OverBlock/1000;
		//speed -= OverBlock;
		pos.z = work + CollisionRangeNumericalValue;
	}

	//�E
	work = Collision::GetInstance()->getRight(pos);
	if (pos.x > work - CollisionRangeNumericalValue)
	{
		car_systems.Throttle -= OverBlock/1000;
		//speed -= OverBlock;
		pos.x = work - CollisionRangeNumericalValue;
	}
	//��
	work = Collision::GetInstance()->getLeft(pos);
	if (pos.x < work + CollisionRangeNumericalValue)
	{
		car_systems.Throttle -= OverBlock/1000;
		//speed -= OverBlock;
		pos.x = work + CollisionRangeNumericalValue;
	}
}

/*
	���X�e�B�b�N�̌X������n���h���֓`���鐧��n
	ver.1.112 2018/02/22
*/
float namakon;
bool Car_A::MoveContrl(float max)
{
	static float moveSpeed;
	//	����
	moveSpeed += 1.0f;
	if (moveSpeed > max) moveSpeed = max;
	//	���̌X���̎擾
	float axisX = KEY_GetAxisX()*0.002f;
	namakon = KEY_GetAxisX()*0.002f;
	//�@���̌X���ƒ���
	float d = sqrtf(axisX * axisX);
	//	���̌X���̗V��
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
	//	���̌X���␳
	if (d > 1.0f)
	{ 
		axisX /= d;
	}
	//�n���h���֐��ֈڍs
	PowerSteering(axisX*car_systems.SpeedHandle);
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
	car_systems.HandleBar = HandlePower;
	/*
	�n���h���̊p�x����
	�n���h���V���t�g�̉�]�����߂�
	*/
	car_systems.HandleBar *= PI / 180.0f;
	car_systems.HandleBar *= 360.0f;	//�������l
	/*
	�p���[�V�����_�[�ɐڑ�
	�n���h���͉�]����̂ɑ΂��A�p���[�V�����_�[�͍��E�ɂ������Ȃ�
	*/
	car_systems.PowerSlinder += car_systems.HandleBar*1.5f;//25.5%�̕␳�����ď����Q�[������^����
	/*
	�p���[�V�����_�[���琧��
	MaxPowerSlinderLength = �V�����_�[�̒����̔����Ɏw��
	*/
	float HalfSilinderLength = MaxPowerSlinderLength / 2;
	if (car_systems.PowerSlinder > HalfSilinderLength)car_systems.PowerSlinder = HalfSilinderLength;
	else if (car_systems.PowerSlinder < -HalfSilinderLength)car_systems.PowerSlinder = -HalfSilinderLength;
	//�p���[�V�����_�[����i�b�N���A�[���ɐڑ�
	car_systems.KnuckleArm = car_systems.PowerSlinder*PI/360.0f;

	return  car_systems.KnuckleArm;
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
	car_systems.WheelFrontAngle = angle.y + car_systems.KnuckleArm*0.30f;
	//����
	Vector3 VecAngle;

	//�`�B�������l
	float TransmissionTimingNumbers = 14.0f;

	VecAngle.x = sinf(angle.y);
	VecAngle.y = 0.0f;
	VecAngle.z = cosf(angle.y);

	//�^�C���̊p�x�ɓ`�B
	TaiyaAngle.x = pos.x + sinf(car_systems.WheelFrontAngle) * TransmissionTimingNumbers;
	TaiyaAngle.z = pos.z + cosf(car_systems.WheelFrontAngle) * TransmissionTimingNumbers;

	//���W���f
	pos.x += sinf(angle.y)*(car_status.speed*0.03f);
	pos.z += cosf(angle.y)*(car_status.speed*0.03f);

	//Vector3 UnVec;
	//UnVec.x = sinf(angle.y)*car_systems.AnWheelAngle*(car_status.speed*0.03f);
	//UnVec.y = 0.0f;
	//UnVec.z = cosf(angle.y)*car_systems.AnWheelAngle*(car_status.speed*0.03f);
	//pos += UnVec;

	//�^�C���̊p�x�`�B�ōX�V
	TaiyaAngle.x = pos.x + sinf(car_systems.WheelFrontAngle) * TransmissionTimingNumbers;
	TaiyaAngle.z = pos.z + cosf(car_systems.WheelFrontAngle) * TransmissionTimingNumbers;

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
	if (car_systems.GearDelay == false)//�N���b�`���q�����܂ŃX���b�g������
	{
		car_systems.Throttle += car_systems.AcceleratingForce * (KEY_GetAxisY3()*0.02f);//�����ׂ̈�2�{�@
		car_systems.torqueOtationalSpeed += car_systems.AcceleratingForce  * (KEY_GetAxisY3()*0.01f);
		car_systems.ThrottleTacoMetter += car_systems.AcceleratingForce * (KEY_GetAxisY3()*0.02f);
		car_systems.ShiftCheakNum = car_status.Gear;
	}
	else
	{	
		if (car_systems.ThrottleTacoMetter >= car_systems.ShiftChangeLevs)
		{
			car_systems.GearDelay = false;//�N���b�`�q���̐ڑ������܂ł̎���	
		}
	}
	car_systems.Throttle -= car_systems.Throttle*0.005f;//�����ĂȂ��������	�������͊������Z
	car_systems.ThrottleTacoMetter -= car_systems.ThrottleTacoMetter*0.005f;
	car_systems.torqueOtationalSpeed -= car_systems.ThrottleTacoMetter*0.0025f;

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

	car_systems.BreakingPower += (0.8 / (0.7 * 140 * 2))* (KEY_GetAxisX3()*0.001f);	//�����́@
	car_systems.torqueOtationalSpeed -= car_systems.BreakingPower;
	car_systems.Throttle -= car_systems.BreakingPower;
	car_systems.ThrottleTacoMetter -= car_systems.BreakingPower;

	//else BreakingPower = 0.0f;//�����ĂȂ��������

	//�o�b�N
	if (KEY_Get(KEY_D) == 1)
	{
		if (car_systems.BackCheak == false)
		{
			car_systems.BackCheak = true;
		}

		car_systems.BackThrottle += car_systems.AcceleratingForce*8.0f;//�����ׂ̈�2�{�@
		car_systems.Throttle -= car_systems.BackThrottle;
		car_systems.ThrottleTacoMetter = car_systems.Throttle;
		car_systems.torqueOtationalSpeed += car_systems.AcceleratingForce;
		car_status.Gear = 0;

	}
	else
	{
		car_systems.BackThrottle -= car_systems.BackThrottle*0.025f;//�����ĂȂ��������	�������͊������Z

		if (car_systems.BackCheak == true)
		{
			car_systems.BackCheak = false;
		}
	}
	/*
		�ȈՃT�C�h�u���[�L
	*/

	if (KEY_Get(KEY_B) == 1)
	{
		car_systems.SubBreakingPower += 0.8 / (0.7 * 140 * 2) / 8;	//�����́@
		car_systems.Throttle -= car_systems.SubBreakingPower;
		car_systems.ThrottleTacoMetter = car_systems.Throttle;
		car_systems.torqueOtationalSpeed -= car_systems.SubBreakingPower;
	}
	else car_systems.SubBreakingPower = 0.0f;//�����ĂȂ��������

/*
	�O�̃M�A�ƌ��݂̃M�A�����v�Z���邱�ƂŔ��f

	AT����
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

		if (car_systems.Throttle > OverLevMax)//�V�t�g�A�b�v AT
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

		if (KEY_Get(KEY_R1) == 1)//�V�t�g�A�b�v MT
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
	engine_parts.CrankShaft = 0.0f;
	engine_parts.ComShaft = 0.0f;
	engine_Gearmissions.num = engine_Gearmissions.num2 = 0;

	//num = 0;

	//�G���W���̋N��
	for (int i = 0;i < 6;i++)SilinderUpdate(i, engine_parts.ConectingRod);

	{
		//�G���W����Ԃ𖈕b�L�^����
		engine_Gearmissions.CrankSpinAverage[engine_Gearmissions.CylinderAverages] =
			((2 * (0.25f / 1000)*(engine_parts.CrankShaft / 360)) * 3600) * 2;
		engine_Gearmissions.IdlingCrankSpinAverage[engine_Gearmissions.CylinderAverages] =
			engine_Gearmissions.CrankSpinAverage[engine_Gearmissions.CylinderAverages];
		//�����ŉߋ�����z�u�i���ŃR�����g�A�E�g���Ă���)�@���ʁA�G���W���������オ����
		engine_Gearmissions.CrankSpinAverage[engine_Gearmissions.CylinderAverages] +=
			(car_systems.Throttle - car_systems.BackThrottle);

		if (engine_Gearmissions.CylinderAverages >= MaxSilinderAve - 1)
			engine_Gearmissions.CylinderAverages = 0;else engine_Gearmissions.CylinderAverages++;

		//�z��ő吔
		engine_Gearmissions.ArrayMaxNumber = sizeof(engine_Gearmissions.CrankSpinAverage) / sizeof(engine_Gearmissions.CrankSpinAverage[0]);

		for (int i = 0;i < MaxSilinderAve;i++)
		{
			engine_Gearmissions.num += engine_Gearmissions.CrankSpinAverage[i];
			engine_Gearmissions.num2 += engine_Gearmissions.IdlingCrankSpinAverage[i];
		}

		//���ς��擾
		engine_Gearmissions.AverageNumber = engine_Gearmissions.num / engine_Gearmissions.ArrayMaxNumber;
		car_systems.torqueOtationalSpeed = engine_Gearmissions.AverageNumber / 2;
		engine_Gearmissions.IdlingAverageNumber = engine_Gearmissions.num2 / engine_Gearmissions.ArrayMaxNumber;
		engine_Gearmissions.CrankNumberOfRevolutionsPerSecond = engine_Gearmissions.AverageNumber;	//!�N�����N�V���t�g
		engine_Gearmissions.UICrankNumberOfRevolutionsPerSecond = engine_Gearmissions.AverageNumber;	//!�^�R���[�^���f
		car_systems.idlingBreakSpeed = engine_Gearmissions.IdlingAverageNumber;	//!�A�C�h�����O��Ԕ��f
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
	car_status.EngineDisplacement = (86.0f / 2)*(86.0f / 2)*PI*73.7f*6;//�{�A�̔�����2��@�~�@�΁@�~�@�X�g���[�N�@�~�@�C����
	car_status.EngineDisplacement /= (int)1000;
	car_status.torque = 22 * (car_status.EngineDisplacement) * 0.5f / (2 * PI) /pow(9.806652f,2);//(�������ϗL������(22)�j�~�i�r�C�ʁj�~�i������(4�T�C�N���ł����0.5)�j�^�i2�΁j
	car_status.MaxTorque = car_status.Max_HorsePower * 75.0f * 60.0f / car_status.LevLimit * 2 * PI;
	
	/*
	�f�t��(������		ReductionGearRatio
	*/
	if (car_status.Gear < car_status.GearMax)car_systems.SelecterReductionGearRation = car_status.FirnalRGR;
	else car_systems.SelecterReductionGearRation = car_status.RGR;

	/*
	�g�����X�~�b�V��������
	*/
	if (car_status.torqueMaxOS >= car_status.OtationalSpeed)		car_status.ERatio = car_systems.SlowSpeed;
	if (car_status.torqueMaxOS < car_status.OtationalSpeed)		car_status.ERatio = car_systems.HighSpeed;

	/*
		�^�C�����a
	*/
	car_systems.HalfDRR = car_status.DRR / 2;
	/*
	�g���N�V����
	*/

	traction = (Front*(car_status.torquePower)*car_systems.Throttle*GearRatio[car_status.Gear] * car_systems.SelecterReductionGearRation * car_status.ERatio) / car_systems.HalfDRR;

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
	geometry.DensityOfAir = geometry.AtmosphericPressure / (2.87f*(geometry.temperature + 273.15f));
	/*
	��C��R�W��
	*/
	geometry.AirResistanceCoefficient = 0.4f;
	/*
	�����Ԃ̐��ʓ��e�ʐ�
	*/
	car_status.FrontProjectionAreaOfTheAutomobile = (1.340f * 1.755f * 0.8f);
	/*
	/*
	���x
	*/
	geometry.Air_Speed =(float) pow(car_status.speed,2);
	/*
	��C��R
	*/
	geometry.AirResistanceRealValue = (geometry.AirResistanceCoefficient*car_status.FrontProjectionAreaOfTheAutomobile*geometry.Air_Speed*geometry.DensityOfAir) / 2;
	geometry.AirResistanceRealValue /= pow(60,3);	//���݋�C��R�y����
	return Vector3(sinf(geometry.AirResistanceRealValue), 0.0f, cosf(geometry.AirResistanceRealValue));
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

	car_systems.myu = 0.015f;//�^���Ɍ������΂��A�Ԃ��l�Ńʂ�ϓ�������ׂ��������A����͕ϓ��Ȃ�
	car_systems.rollingResistance = car_systems.myu* car_status.weght*9.8f;
	
	return Vector3(sinf(car_systems.rollingResistance),0,cosf(car_systems.rollingResistance));
}
/*
	�Î~��
	ver.1.112 2018/02/22
*/
Vector3 Car_A::StaticForce()
{
	return -Traction()*car_status.weght*0.05f;
}

/*
	���S��

*/

float Car_A::CentrifugalForce()
{
	//���񔼌a=�z�C�[���x�[�X(M)/sin(���Ǌp)
	car_systems.Rad = (2.615f) / sin(cross.y);
	//���S��=�ԏd/�d�͉����x*���x2/���񔼌a
	car_systems.Fc = (car_status.weght / 9.8f) * (pow(car_status.speed, 2) / car_systems.Rad);
	car_systems.Fc /= 10000;
	//���[��
	car_systems.RollHeight = 1.325f / 3;//���[���Z���^�[����d�S�܂ł̋���
	car_systems.tread = 1460/1000;//�g���b�h��
	car_systems.Spring = car_systems.RollHeight*9.8f;//�T�X�y���V�������[�����g

	car_systems.RollStiffness_F = (5700*pow(car_systems.tread, 2)) / 2;//���[������ �O
	car_systems.RollStiffness_R = (4000*pow(car_systems.tread, 2)) / 2;//���[������ ��
	
	/*
	���[���A�b�v
	���[�����ʂ͋ɏ�
	*/
	car_systems.sita = (car_systems.Fc*car_systems.RollHeight) / ((car_systems.RollStiffness_F+ car_systems.RollStiffness_R) - (car_systems.Spring*car_systems.RollHeight));
	
	car_systems.sitaaccel = (car_systems.Throttle*car_systems.RollHeight) / ((4000 * (-4.530f / 2 - 2.615f)*2.625f) - (car_systems.Spring*car_systems.RollHeight));
	car_systems.sitabrake = (car_systems.BreakingPower*car_systems.RollHeight) / ((5700 * (4.530f / 2 - 2.615f)*2.625f) - (car_systems.Spring*car_systems.RollHeight));
	//���[�����f
	angle.x = (car_status.speed*(car_systems.sitaaccel - car_systems.sitabrake))* CorneringForce().x;

	//���E�ɗh���p�x(angle.z)�����[���Ŕ��f
	angle.z = car_systems.sita* CorneringForce().z;//

	//�f�o�b�O�f�[�^
	car_systems.centrifugal = car_systems.Fc;

	return car_systems.Fc;
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

		case 2://original Misson
			GearRatio[0] = 3.177f;		//R��
			GearRatio[1] = 3.200f;		//1��
			GearRatio[2] = 2.031f;		//2��
			GearRatio[3] = 1.422f;		//3��
			GearRatio[4] = 1.000f;		//4��
			GearRatio[5] = 0.833f;		//5��
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
	car_systems.rpm = engine_Gearmissions.CrankNumberOfRevolutionsPerSecond;
	car_systems.rpm *= 1000;
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

	bunsi_A = ((255 * 0.40f * 2 + 17 * 25.4f)*PI*(car_systems.rpm -(car_systems.idlingBreakSpeed*1000)));
	//!�V�t�g�`�F���W���ɑO�̌v�Z���l�����̃M�A�ɓn���ăV���t�g���������P����
	bunbo_A = (GearRatio[car_systems.ShiftCheakNum] * car_status.FirnalRGR);
	bunsi_B = 60.0f;
	bunbo_B = pow(10, 6);
	SpeedSaved = (bunsi_A/ bunbo_A) * (bunsi_B/ bunbo_B);
	
	car_status.speed = (SpeedSaved)*RollingResistance().Length();
	//�g���N��]��
	car_status.torquePower = 2 * PI *car_status.torque*(car_systems.rpm)/60/1000;

	/*
	1.3962kW �� 1.0�n��
	
	*/
	//�n�� PTO���g���N�iKg�Em�j��PTO����]���iRPM�j�w 2�� �^ ( 75 �w 60 )
	car_status.horsePower = car_status.torque * (car_systems.torqueOtationalSpeed * 1000) * (2 * PI) / (75 * 60);
	//�ō��n��
	//�i��]�� rpm) �~�i�g���N kgfm�j�^1000 �~ 1.3962
	car_status.Max_HorsePower= car_status.torque * car_status.torqueMaxOS * (2 * PI) / (75 * 60);

	//�p���[�E�F�C�g���V�I	���ׂ����肾�ƃf�[�^�@�����͂ɉe��������̂ł��Ȃ��Ƃ������f
	car_status.PowerToWeightRatio = car_status.weght / car_status.Max_HorsePower;

	//������=�g���N*�d�͉����x*�M�A��/�^�C���̔��a/�ԏd
	//�M�A�̏d�ׁ݂̈A���X�g�M�A�܂ł̏d�݂�ς���
	if (car_status.Gear <= car_status.GearMax - 1)
	{
		car_systems.AcceleratingForce = ((car_status.torquePower* 9.8f*(GearRatio[car_status.Gear] * car_status.RGR) / (car_systems.HalfDRR / 1000)) / car_status.weght) - geometry.AirResistanceRealValue;
	}
	if (car_status.Gear == car_status.GearMax)
	{
		car_systems.AcceleratingForce = ((car_status.torquePower* 9.8f*(GearRatio[car_status.Gear] * car_status.FirnalRGR) / (car_systems.HalfDRR / 1000)) / car_status.weght) - geometry.AirResistanceRealValue;
	}

	car_systems.AcceleratingForce /= 900;//����

	/*x
	�V�t�g�ݒ�
	*/
	if (car_status.Gear >= car_status.GearMax)car_status.Gear = 5;

	if (car_status.Gear <= 1 && car_systems.BackCheak==false)	car_status.Gear = 1;									     //�P���͉����Ȃ�(��ނ͍��x
	else if(car_status.Gear <= 1 && car_systems.BackCheak == true)	car_status.Gear = 0;

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
		engine_parts.CyLinderHead[n] -= CylinderSpeed;
	}
	//��C���z����A���k�H����
	if (step[n] == 0 && engine_parts.CyLinderHead[n] < 0.0f)
	{
		step[n]++;

		//�C���W�F�N�^�[�z��	��C�̌v�Z�̓L���������̂�1��0�̓�������
		engine_parts.Injecter += AirInjector(randomEngine);

		//���W�G�[�^�[�̋z�M
		engine_parts.Radiator -= engine_parts.Injecter;

		//�G���W���u���b�N�т��Ȃ��悤�ɐ���
		engine_parts.CyLinderHead[n] = 0.0f;
	}
	//*************************************************************************************
	//			step 2			���k
	//*************************************************************************************
	//��C�������グ��
	if (step[n] == 1)
	{
		engine_parts.CyLinderHead[n] += CylinderSpeed;
	}

	if (step[n] == 1 && engine_parts.CyLinderHead[n] >60.0f)
	{
		step[n]++;

		//�G���W���u���b�N�т��Ȃ��悤�ɐ���
		engine_parts.CyLinderHead[n] = 60.0f;

	}
	//*************************************************************************************
	//		step 3			�R��
	//*************************************************************************************
	if (step[n] == 2)
	{
		engine_parts.CyLinderHead[n] -= CylinderSpeed;
	}
	if (step[n] == 2 && engine_parts.CyLinderHead[n] <0.0f)
	{
		step[n]++;
		//�_�΃v���O�I��
		engine_parts.Battery[n] = 0.0f;
		//�G���W���u���b�N�т��Ȃ��悤�ɐ���
		engine_parts.CyLinderHead[n] = 0.0f;
	}
	if(step[n] == 2 && engine_parts.CyLinderHead[n] >0.0f)
	{
		//�R��=�_�΃v���O���X�p�[�N�@������܂ŉ�]���J��Ԃ�
		engine_parts.Battery[n] = 1;
		//��]���ɃY�����N�����Ȃ������V���t�g
		engine_parts.TimingBelt = ExplosionChangeTheNumberOfTimes(randomEngine)*n;
		//�J���V���t�g�ƃN�����N�V���t�g����]
		engine_parts.CrankShaft += engine_parts.TimingBelt;
		engine_parts.ComShaft += engine_parts.TimingBelt / 2;
		//���x����
		engine_parts.EngineOil =engine_parts.TimingBelt;
		engine_parts.Radiator = engine_parts.EngineOil;

	}
	//*************************************************************************************
	//		step 4			�r�C
	//*************************************************************************************
	if (step[n] == 3)
	{
		engine_parts.CyLinderHead[n] += CylinderSpeed;
	}
	if (step[n] == 3 && engine_parts.CyLinderHead[n] > 60.0f)
	{
		step[n] = 0;
		//�C���W�F�N�^�[�r�C
		engine_parts.Injecter+= AirInjector(randomEngine);

		//�G���W���u���b�N�т��Ȃ��悤�ɐ���
		engine_parts.CyLinderHead[n] = 60.0f;

		//���W�G�[�^�̔M�����
		engine_parts.Radiator += engine_parts.Injecter;

	}

	//���␧��
	if (engine_parts.Radiator > 100)engine_parts.Radiator = 100;
	if (engine_parts.Radiator < 0)engine_parts.Radiator = 0;

	//���x����
	if (engine_parts.EngineOil > 100)engine_parts.EngineOil = 100;
	if (engine_parts.EngineOil < 0)engine_parts.EngineOil = 0;
}

/*
	�^�C���`�B
*/

void Car_A::WheelProcess()
{

	/*
		�^�C����1���Ԃɐi�ދ���
	*/
	car_systems.MinLength += car_status.speed*1000/ 216000;
	/*
		�^�C���̉�]��
	*/
	car_systems.WheelRpm = car_systems.MinLength / car_status.TheOuterCircumferenceOfTheTire;
	int WheelConvert = car_systems.WheelRpm;
	car_systems.WheelRpm = car_systems.WheelRpm - WheelConvert;
	car_systems.WheelRpm = PI * 2 * car_systems.WheelRpm;

	car_systems.RightRearWheel = car_systems.LeftRearWheel = car_systems.WheelRpm;
}

/*
	�X�V����
*/
void Car_A::Update()
{
	
	Traction();
	car_systems.SpeedHandle = 1.0f;
	car_systems.metterAngle = engine_Gearmissions.UICrankNumberOfRevolutionsPerSecond / 3;
	car_systems.SpeedMeter  =(float)car_status.speed / 90;

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
	RaceNodeRange = RacSystemNodePoint[car_systems.NodeSaveNumber] - pos;
	RaceNodeRange.Normalize();
	//�����蔻��
	if (Collision::GetInstance()->ColSphere(pos, 90.0f, RacSystemNodePoint[car_systems.NodeSaveNumber], 120.0f) == true)car_systems.NodeSaveNumber++;

	//�Ō�̃m�[�h�ɓ��B���A�������Ǝ��񔻒�
	if (RaceClearNodeMaxNumber == car_systems.NodeSaveNumber)
	{
		car_systems.NodeSaveNumber = 0;
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