#include "UI_Texture.h"

#include "Player.h"
#include "Enemy.h"

//コメントアウトするとPlayerUIへ　逆の場合はEnemyUI
//#define ChangeCarUITexture

UI::UI()
{
	Init();
}

UI::~UI()
{
	delete texture_A;
	delete texture_B;
	delete texture_C;
	delete texture_D;
	delete texture_E;
	delete texture_F;
	delete texture_G;
	delete texture_H;
	delete texture_I;
	delete texture_J;
	delete texture_K;
	delete texture_L;
	delete texture_M;
}
bool UI::Init()
{
	color_A = color_C = color_D = 0xffffffff;
	for(int i=0;i<6;i++)color_B[i] = 0xffff0000;
	

	Player_RoundRace = 0;
	FinalRenderTimer = 60 * 3;
	EndLap = 3;

	texture_A = new iex2DObj("DATA\\HUD_Texture\\metter2.png");
	texture_B = new iex2DObj("DATA\\HUD_Texture\\metter3.png");
	texture_C = new iex2DObj("DATA\\HUD_Texture\\metter4.png");
	texture_D = new iex2DObj("DATA\\HUD_Texture\\000.png");
	texture_E = new iex2DObj("DATA\\HUD_Texture\\metterCobber.png");
	texture_F = new iex2DObj("DATA\\HUD_Texture\\OverLevPoint.png");
	texture_G = new iex2DObj("DATA\\HUD_Texture\\UI_Texture_s2.png");
	texture_H = new iex2DObj("DATA\\HUD_Texture\\3714.png");
	texture_I = new iex2DObj("DATA\\HUD_Texture\\UI_Texture_s1.png");
	texture_J = new iex2DObj("DATA\\HUD_Texture\\ensin.png");
	texture_K = new iex2DObj("DATA\\HUD_Texture\\GoalText.png");
	texture_L = new iex2DObj("DATA\\HUD_Texture\\slash.png");
	texture_M = new iex2DObj("DATA\\DebugTextures\\TestImageTexture.png");

	return false;
}

void UI::Update()
{
	// UI Change Players Race Week now Update
	Player_RoundRace = Car_A::GetInstance()->GetWeeks();
}

void UI::SpeedMetterRender()
{
	NumRenderCenter(1020,640, 32, 16, Car_A::GetInstance()->GetSpeed(), 0xffffffff);
}
void UI::LevMetterRender()
{
	texture_E->Render(890, 500, 256, 256, 0, 0, 512, 512);
	//Tako Metter needle
	texture_A->RenderI(890, 500, 256, 256, 0, 0, 512, 512, Car_A::GetInstance()->GetSpeedAngle());
	//Tako Metter 
	texture_B->Render(890, 500, 256, 256, 0, 0, 512, 512);

	//Gear Texture Render
	NumRenderCenter(1020, 560, 32, 32, Car_A::GetInstance()->GetGear(), 0xffffffff);

	//LevLimit Render Color
	if (Car_A::GetInstance()->GetRpm() >= Car_A::GetInstance()->GetLevLimit() && Car_A::GetInstance()->GetGear() < 5)color_A = 0xffffff00;
	else if (Car_A::GetInstance()->GetRpm() > Car_A::GetInstance()->GetLevLimit() && Car_A::GetInstance()->GetGear() == 5)color_A = 0xffff0000;
	else color_A = 0x77ffffff;
	//Over Cheak LevLimit Render
	texture_F->Render(1050, 620, 32, 32, 0, 0, 512, 512, 0, color_A);
}
void UI::CryRohMetterRender()
{
	//yaw
	texture_G->Render(1150, 450, 128, 128, 0, 0, 256, 256);
	//pitch
	texture_G->Render(1150, 570, 128, 128, 0, 0, 256, 256);
	//yaw Render
	texture_H->RenderI(1178, 475, 64, 64, 0, 0, 480, 480, Car_A::GetInstance()->GetAngle().x * 5);
	//Yaw parallel lines Render
	texture_I->RenderI(1160, 450, 115, 128, 0, 0, 256, 256, Car_A::GetInstance()->GetAngle().x * 5);
	//Pitch parallel lines Render
	texture_I->RenderI(1160, 570, 115, 128, 0, 0, 256, 256, Car_A::GetInstance()->GetAngle().z * -5);
	//pitch Render
	texture_J->RenderI(1181, 598, 64, 64, 0, 0, 512, 512, Car_A::GetInstance()->GetAngle().z * -5);
}
void UI::GoalCheakRender()
{
	if (Player_RoundRace >= EndLap)
	{
		FinalRenderTimer--;
		if (FinalRenderTimer > 0)texture_K->Render(430, 240, 512, 256, 0, 0, 1024, 160);
		if (FinalRenderTimer <= 0)FinalRenderTimer = 0;
	}
	if (Car_A::GetInstance()->GetGoalInChake())texture_K->Render(430, 320, 512, 256, 0, 114, 512, 150);
}
void UI::LapTexRender()
{
	NumRenderCenter(1100, 50, 64, 64, Player_RoundRace, 0xffffffff);//Player Lap
	NumRenderCenter(1200, 50, 64, 64, EndLap, 0xffffffff);	//End 3Lap
	texture_L->Render(1120, 58, 50, 50, 0, 0, 64, 64, 0xffffffff);	// Lap / EndLap
}

void UI::DesplayDebugRender()
{
	for (int i = 0;i<6;i++)
	{
		if (Car_A::GetInstance()->GetEngine_Battery(i) == 1)color_B[i] = 0xffff0000;
		else color_B[i] = 0xffffffff;
	}
	if(Car_A::GetInstance()->GetEngine_EngineOil()>75.0f)color_C = 0xffffa500;
	else color_C = 0xff00ff00;
	if(Car_A::GetInstance()->GetEngine_Radiator()>75.0f)color_D = 0xffff0000;
	else color_D = 0xff87ceeb;
	{
	texture_M->Render(0, 0, 16, 64 -  Car_A::GetInstance()->GetEngine_CylinderHead(0), 0, 0, 64, 64 - Car_A::GetInstance()->GetEngine_CylinderHead(0),0,  color_B[0]);
	texture_M->Render(16, 0, 16, 64 - Car_A::GetInstance()->GetEngine_CylinderHead(1), 0, 0, 64, 64 - Car_A::GetInstance()->GetEngine_CylinderHead(1), 0, color_B[1]);
	texture_M->Render(32, 0, 16, 64 - Car_A::GetInstance()->GetEngine_CylinderHead(2), 0, 0, 64, 64 - Car_A::GetInstance()->GetEngine_CylinderHead(2), 0, color_B[2]);
	texture_M->Render(48, 0, 16, 64 - Car_A::GetInstance()->GetEngine_CylinderHead(3), 0, 0, 64, 64 - Car_A::GetInstance()->GetEngine_CylinderHead(3), 0, color_B[3]);
	texture_M->Render(64, 0, 16, 64 - Car_A::GetInstance()->GetEngine_CylinderHead(4), 0, 0, 64, 64 - Car_A::GetInstance()->GetEngine_CylinderHead(4), 0, color_B[4]);
	texture_M->Render(80, 0, 16, 64 - Car_A::GetInstance()->GetEngine_CylinderHead(5), 0, 0, 64, 64 - Car_A::GetInstance()->GetEngine_CylinderHead(5), 0, color_B[5]);
	
	texture_M->Render(96, 0, 16, 64 , 0, 0, 64, 64 , 0, color_C);
	texture_M->Render(110, 0, 16, 64 , 0, 0, 64, 64 , 0, color_D);
	}
}
void UI::Render()
{

#ifndef ChangeCarUITexture
	//LevLimit Render Option
	LevMetterRender();
	//Metter Render Option
	SpeedMetterRender();
	//Cry Roh Meter Render Option
	CryRohMetterRender();
	//Goal Cheak Render
	GoalCheakRender();
	// Lap Texture
	LapTexRender();
	//Debug Render
	DesplayDebugRender();
#endif 
	/*
	UI作るのも苦労するものもあるので、DebugTextを使ってディスプレイで表示
	シミュレーションで主に変化起きる・起こせるものなどを表示
	*/
	//char str[256];
	//sprintf(str,
	//	"車両情報:\n"
	//	"クランクシャフト平均回転数(アイドリング時の回転数):%d\n"
	//	"馬力(クルマの強さ):%d\n"
	//	"トルク(kgf):%f\n"
	//	"重量(ボディ等の重さ):%f\n"
	//	"パワーウェイトレシオ(重量/馬力):%f\n",
	//	Car_A::GetInstance()->GetCrankShaft(),
	//	Car_A::GetInstance()->GetHoursePower(),
	//	Car_A::GetInstance()->GetTorque(),
	//	Car_A::GetInstance()->GetWeght(),
	//	Car_A::GetInstance()->GetPowerWeghtRatio()
	//);

	//IEX_DrawText(str, 0, 300, 1920, 1080, 0xffffffff);
}

//Render Texture Number
void UI::NumRenderCenter(int posX, int posY, int size, int move, int num, unsigned int color)
{
	int number = num;
	int s_pos = posX - move;
	int moveSize = move / 2;
	int x = 0;
	while (1) {
		s_pos += moveSize;
		number /= 10;
		if (number <= 0)break;
	}
	while (1)
	{
		texture_D->Render(s_pos - x, posY, size, size, ((num % 10) % 4) * 128, ((num % 10) / 4) * 128, 128, 128, 0, color);
		x += move;
		num /= 10;
		if (num <= 0)break;
	}
}