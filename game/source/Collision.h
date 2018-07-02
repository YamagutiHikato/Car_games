#pragma once
#include "iextreme.h"

#include "Player.h"
#include "Enemy.h"

/*
“–‚½‚è”»’è
*/
class Collision;

class Collision
{
private:
	iexMesh* obj;

public:
	Collision();
	~Collision();
	bool Init(char* filename);
	bool Init(iexMesh* obj);
	float getHeight(const Vector3& pos);
	float getFront(const Vector3& pos);
	float getBack(const Vector3& pos);
	float getRight(const Vector3& pos);
	float getLeft(const Vector3& pos);
	void SetColObjScale(Vector3 scale) { obj->SetScale(scale); }
	bool ColSphere(Vector3& p1, float r1, Vector3 p2, float r2);

	iexMesh* getObj() { return obj; }

	static Collision *GetInstance()				//Singleton 
	{
		static Collision instnce;
		return &instnce;
	}

};




