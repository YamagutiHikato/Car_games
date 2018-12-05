#pragma once
#include "iextreme.h"
#include "system\Scene.h"

#include <memory>

class TitleCamera;
using TitleCameraObj = TitleCamera;
#define WheelSpeed 0.25f
#define CameraSpeed 0.0025f
#define CameraMovement 10
#define TextureSize 256

class sceneTitle :public Scene
{
private:
	//pointer
	iexView*	view;
	TitleCameraObj*c_obj;

	iexMesh*	P_obj;									//モデル
	iex3DObj*	P_obj2;
	iexMesh*	P_obj3;
	iexMesh*	P_obj4;
	iexMesh*	P_obj5;
	iexMesh*	P_obj6;

	iexMesh*s_obj;

	iex2DObj *titleTex;
	iex2DObj*buttonTex;


	unsigned int lightingUpColor;
	bool state;
	int stateTimer;
	int stopTime;
	int startTime;
	double rpm;

	bool CheckTransMission;//false:AT True :MT
	int StateMode;
	int missionTime;

public:
	sceneTitle() = default;
	~sceneTitle() = default;

	bool Initialize();	//Initialize

	void LightUp();

	void MainGameTransMission();

	//	更新・描画
	void Update();	//	更新
	void Render();	//	描画

};

class TitleCamera
{
private:
	std::shared_ptr<iexView>view;

	Vector3 pos;
	Vector3 target;

	float angle;
public:
	TitleCamera();
	~TitleCamera() = default;

	bool Init();
	void Update(const Vector3 car_pos);
	void Render();
};
