
#include "iextreme.h"

#include "Camera.h"
#include "Player.h"
#include "Enemy.h"

//Initialize
bool Camera::Init()
{
	view.reset(new iexView());

	pos = Vector3(-164.0f, 35.0f, -786.0f);		//back
	target = Vector3(0.0f, 0.0f, 0.0f);	//forward
	LookSpeed = 1.0f;

	timer = 60 * 2;
	mode = FreeLook;

	return true;
}

//ChangeingCameraState looking for ???
void Camera::ChangeStateMode(int state, Car_A&obj)
{
	switch (mode)
	{
	case FreeLook:		FreeLockCamera(obj);	break;	//FreeLook
	case FirstPerson:	FPSCamera(obj);		break;	//FPS
	case ThirdPerson:	TPSCamera(obj);		break;	//TPS
	default:			state = 0;			break;	//if over mode  this ZERO
	}

	mode = state;
}


/*
	Free Camera
	とりあえずこちらメイン固定
*/

void Camera::FreeLockCamera(Car_A&obj)
{

	timer--;
	if (timer <= 0)
	{
		Vector3 CarAngle;
		CarAngle.x = sinf(obj.GetAngle().y);
		CarAngle.z = cosf(obj.GetAngle().y);


		target.x = obj.GetPos().x - CarAngle.x;
		target.y = obj.GetPos().y +10;
		target.z = obj.GetPos().z - CarAngle.z;



		pos.x = matView._11*CarAngle.x;
		pos.y = matView._21+10;
		pos.z = matView._31*CarAngle.z;

		Vector3 v;
		v = (pos - target);
		v.Normalize();

		pos.x = target.x  + v.x + CarAngle.x * -35;
		pos.y= target.y + v.y * 35;
		pos.z = target.z + v.z + CarAngle.z * -35 ;
	}
	else
	{
		Vector3 CarAngle;
		CarAngle.x = sinf(obj.GetAngle().y);
		CarAngle.z = cosf(obj.GetAngle().y);


		target.x = obj.GetPos().x - CarAngle.x;
		target.y = obj.GetPos().y + 10;
		target.z = obj.GetPos().z - CarAngle.z;



		pos.x = matView._11;
		pos.y = matView._21 + 10;
		pos.z = matView._31;

		Vector3 v;
		v = (pos - target) ;
		v.Normalize();

		pos.x = (timer)+target.x + v.x * -35;
		pos.y = target.y + v.y * 35;
		pos.z = (timer)+target.z + v.z * -35;
	}
}

//FPS Camera 
void Camera::FPSCamera(Car_A&obj)
{
	////
	float h = 5.0f;

	Vector3 p(obj.GetPos().x, obj.GetPos().y + h, obj.GetPos().z);				//　プレイヤーの位置
	Vector3 f(sinf(obj.GetAngle().y), 0, cosf(obj.GetAngle().y));			//　前方向
	Vector3 r(cosf(obj.GetAngle().y), 0, -sinf(obj.GetAngle().y));			//　右方向

	pos = p + -f * 6 + r * 10;

	target = pos + f;

}

//TPS Camera 
void Camera::TPSCamera(Car_A&obj)
{
	Vector3 CarAngle;
	CarAngle.x = sinf(obj.GetAngle().y);
	CarAngle.z = cosf(obj.GetAngle().y);

	pos.x = obj.GetPos().x + CarAngle.x*-2;
	pos.y = 10;
	pos.z = obj.GetPos().z + CarAngle.z*-2;

	target.x = obj.GetPos().x+30* (sinf(obj.GetAngle().y));
	target.y = 4.5;
	target.z = obj.GetPos().z+30 * (cosf(obj.GetAngle().y));

}

//Update
int i=0;
void Camera::Update(Car_A&obj)
{
	if (KEY_Get(KEY_START) == 3)i++;
	if (i > 2)i = 0;
	ChangeStateMode(i,obj);
	view->Set(pos, target);
}

//Render
void Camera::Render()
{
	view->SetViewport();
	view->Activate();
	view->Clear(0x000000);	
}