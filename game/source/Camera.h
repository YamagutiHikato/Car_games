#pragma once

#include <memory>
class Car_A;
class Car_A_E;

/*
	TODO: ÉJÉÅÉâÇÃê›íËÇ™ïsè\ï™
*/

class Camera
{
private:
	//class
	std::shared_ptr<iexView>view;			//iexView 

	Camera() = default;						//constructor
	~Camera() = default;					//destructor

	//Vector3
	Vector3 pos;							//position
//	Vector3 angle;							//cameraAngle
	Vector3 target;							//Lookposition

	//float
	float LookSpeed;
	//int
	int timer;
	int mode;

	enum cameraMode
	{
		FreeLook=0,
		FirstPerson,
		ThirdPerson
	};

public:
	bool Init();							//Initialize

	//Copy Constructor this ban
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;
	Camera(Camera&&) = delete;
	Camera& operator=(Camera&&) = delete;

	//				Setter & Getter
	void    SetPos(    Vector3 p) { pos = p;}
	Vector3 GetPos()			  { return pos;}

	void    SetTarget( Vector3 t) { target = t;}
	Vector3 GetTarget()           { return target;}

	void    SetLSpeed(float ls)   { LookSpeed = ls;}
	float   GetLSpeed()			  { return LookSpeed;}

	void ChangeStateMode(int state, Car_A&obj);		//ChangeCameraMode

	void FreeLockCamera	(Car_A&obj);					//0
	void FPSCamera(Car_A&obj);						//1
	void TPSCamera(Car_A&obj);						//2

	void Update(Car_A&obj);							//CameraClassUpdate
	void Render();							//CameraClassRender

	static Camera *GetInstance()			//Singleton 
	{
		static Camera instnce;
		return &instnce;
	}


};
