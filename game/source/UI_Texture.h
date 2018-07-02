#pragma once

#include "iextreme.h"

#include <memory>

class UI
{
private:
	unsigned int color_A,color_B[6],color_C,color_D;
	int Player_RoundRace;
	int FinalRenderTimer;
	int EndLap;

private:
	iex2DObj* texture_A;
	iex2DObj* texture_B;
	iex2DObj* texture_C;
	iex2DObj* texture_D;
	iex2DObj* texture_E;
	iex2DObj* texture_F;
	iex2DObj* texture_G;
	iex2DObj* texture_H;
	iex2DObj* texture_I;
	iex2DObj* texture_J;
	iex2DObj* texture_K;
	iex2DObj* texture_L;
	iex2DObj* texture_M;

	Vector3 pos;

public:
	UI();
	~UI();

	bool Init();

	void Update();
	void Render();

	void NumRenderCenter(int posX, int posY, int size, int move, int num, unsigned int color);
	void SpeedMetterRender();
	void LevMetterRender();
	void CryRohMetterRender();
	void GoalCheakRender();
	void LapTexRender();
	void DesplayDebugRender();

	int GetEndLap() { return EndLap; }

	static UI *GetInstance()				//Singleton 
	{
		static UI instnce;
		return &instnce;
	}
};