#include	"iextreme.h"
#include	"system/system.h"
#include	"system/Framework.h"
#include	"sceneTitle.h"

#include	"sceneMain.h"
#include    "SceneLoad.h"

#include    "Player.h"

#include <random>
std::random_device random_d;
std::mt19937_64 randomSpin(random_d());
std::uniform_real_distribution<double>spinTimers(30, 180);

bool sceneTitle::Initialize()
{
	iexLight::SetFog(800, 1000, 0);
	iexLight::SetAmbient(0xffffff);

	view = new iexView();

	c_obj = new TitleCamera();

	P_obj = new iexMesh("DATA\\CAR\\TestModel_A.IMO");
	P_obj2 = new iex3DObj("DATA\\CAR\\TestModel_B.IEM");
	P_obj3 = new iexMesh("DATA\\CAR\\TestModel_C.IMO");
	P_obj4 = new iexMesh("DATA\\CAR\\TestModel_C.IMO");
	P_obj5 = new iexMesh("DATA\\CAR\\TestModel_D.IMO");
	P_obj6 = new iexMesh("DATA\\CAR\\TestModel_D.IMO");

	s_obj = new iexMesh("DATA//BG//STAGE//stage01.x");
	titleTex = new iex2DObj("DATA\\Title\\Title.png");
	buttonTex = new iex2DObj("DATA\\Title\\PushButton.png");


	lightingUpColor = 0x00ffffff;
	state = false;

	P_obj ->SetPos(0, 5, 30);
	P_obj2->SetPos(0, 5, 30);

	P_obj3->SetPos(-1.8, 5.6, 32.7);
	P_obj4->SetPos(-1.8, 5.6, 27.5);
	P_obj5->SetPos(1.8, 5.6, 32.8);
	P_obj6->SetPos(1.8, 5.6, 27.5);

	P_obj  ->SetAngle(0.0f);
	P_obj2 ->SetAngle(0.0f);
	P_obj3 ->SetAngle(0.0f);
	P_obj4 ->SetAngle(0.0f);
	P_obj5 ->SetAngle(3.2f);
	P_obj6 ->SetAngle(3.2f);

	P_obj	->SetScale(0.2f);
	P_obj2	->SetScale(0.2f);
	P_obj3	->SetScale(0.2f);
	P_obj4	->SetScale(0.2f);
	P_obj5	->SetScale(0.2f);
	P_obj6	->SetScale(0.2f);


	s_obj->SetPos(0, 0, 0);
	s_obj->SetScale(1.0f);

	stateTimer = 0;
	stopTime = 180;
	startTime = 180;
	rpm = 0;

	CheckTransMission = false;
	StateMode = 0;
	missionTime = 10;
	return 0;
}



void sceneTitle::LightUp()
{
	if (state == false)
	{
		if (lightingUpColor != 0xffffffff)lightingUpColor += 0x03000000;
		if (lightingUpColor == 0xffffffff)
		{
			lightingUpColor = 0xffffffff;
			state = true;
		}
	}
	else
	{
		if (lightingUpColor != 0x00ffffff)lightingUpColor -= 0x03000000;
		if (lightingUpColor == 0x00ffffff)
		{
			lightingUpColor = 0x00ffffff;
			state = false;
		}
	}

}

void sceneTitle::Update()
{
	LightUp();

	c_obj->Update(P_obj2->GetPos());

	if (stateTimer == 0)
	{
		startTime = spinTimers(random_d);
		stopTime--;
		if (stopTime <= 0)
		{
			stateTimer++;
		}
	}
	if (stateTimer == 1)
	{
		stopTime = spinTimers(random_d);
		startTime--;
		rpm += WheelSpeed;
		P_obj4->SetAngle(rpm, 0, 0);
		P_obj6->SetAngle(-rpm, 3.2, 0);

		P_obj3->SetAngle(rpm, 0, 0);
		P_obj5->SetAngle(-rpm, 3.2, 0);
		if (startTime <= 0)
		{
			stateTimer--;
		}
	}


	P_obj	->Update();
	P_obj2	->Update();
	P_obj3	->Update();
	P_obj4	->Update();
	P_obj5	->Update();
	P_obj6	->Update();


	MainGameTransMission();


}

void sceneTitle::MainGameTransMission()
{
	missionTime--;
	if (KEY_Get(KEY_B) == 3 && StateMode == 0 && missionTime<=0)
	{
		StateMode = 1;
		missionTime = 10;
	}
	if (StateMode == 1 && missionTime<=0)
	{
		if (KEY_Get(KEY_UP) == 3)
		{
			CheckTransMission = false;
			missionTime = 10;
		}
		else if (KEY_Get(KEY_DOWN) == 3 && missionTime<=0)
		{
			CheckTransMission = true;
			missionTime = 10;
		}
		if (KEY_Get(KEY_B) == 3 && missionTime<=0)
		{
			sceneMain*newScene = new sceneMain();
			Car_A::GetInstance()->SetMMode(CheckTransMission);
			MainFrame->ChangeScene(new sceneLoad(newScene));
			missionTime = 0;
		}
		missionTime = 0;
	}
}

void sceneTitle::Render()
{
	view->Activate();
	view->Clear(0x000000);

	c_obj->Render();
	
	P_obj	->Render();
	P_obj2	->Render();
	P_obj3	->Render();
	P_obj4	->Render();
	P_obj5	->Render();
	P_obj6	->Render();

	s_obj->Render();

	titleTex->Render(360, 120, TextureSize*2, TextureSize, 0, 0, TextureSize*2, TextureSize);
	buttonTex->Render(380, 480, TextureSize*2, TextureSize, 0, 0, TextureSize*2, TextureSize,NULL,lightingUpColor);

	char str[256];
	if(CheckTransMission==false)sprintf(str, "ミッション選択\n"
		"AT:\n");
	if (CheckTransMission)sprintf(str, "ミッション選択\n"
		"MT:\n");
	IEX_DrawText(str, 300, 500, 1920, 1080, 0xffffffff);
}


TitleCamera::TitleCamera()
{
	Init();
}


bool TitleCamera::Init()
{
	view.reset(new iexView());

	pos = Vector3(0, 1, -2);
	target = Vector3(0, 0, 0);

	angle = 0.0f;

	return true;
}

void TitleCamera::Update(const Vector3 car_pos)
{
	angle += CameraSpeed;
	target = car_pos;

	pos.x = target.x+sinf(angle)*CameraMovement;
	pos.y = target.y;
	pos.z = target.z+cosf(angle)*CameraMovement;

	view->Set(pos, target);
}

void TitleCamera::Render()
{
	view->Activate();
	view->Clear(0x000000);

}