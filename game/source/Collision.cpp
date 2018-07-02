#include "Collision.h"

#define CollisionRange 50.0f
#define CollisionDistRet 25000.0f
#define CollisionPosDist 2.5f

Collision::Collision()
{

}

Collision::~Collision()
{
	delete obj;
}

/*
初期化
*/
bool Collision::Init(char* filename)
{
	obj = new iexMesh(filename);
	obj->SetScale(10);
	if (obj == nullptr) return false;
	return true;

}

bool Collision::Init(iexMesh* OrgObj)
{
	obj = OrgObj;
	if (obj == nullptr) return false;
	return true;

}

//ステージ当たり判定
float Collision::getHeight(const Vector3& pos)
{
	Vector3 p(pos.x, pos.y + 50.0f, pos.z);
	Vector3 v(0, -1.0f, 0);
	Vector3 out;
	float dist = CollisionRange;

	if (obj->RayPick(&out, &p, &v, &dist) == -1) return pos.y;
	return out.y;

}

float Collision::getFront(const Vector3& pos)
{
	Vector3 p(pos.x, pos.y + CollisionPosDist, pos.z - CollisionPosDist);
	Vector3 v(0, 0, 1.0f);
	Vector3 out;
	float dist = CollisionRange;

	if (obj->RayPick(&out, &p, &v, &dist) == -1) return CollisionDistRet;
	return out.z;

}

float Collision::getBack(const Vector3& pos)
{
	Vector3 p(pos.x, pos.y + CollisionPosDist, pos.z + CollisionPosDist);
	Vector3 v(0, 0, -1.0f);
	Vector3 out;
	float dist = CollisionRange;

	if (obj->RayPick(&out, &p, &v, &dist) == -1) return -CollisionDistRet;
	return out.z;

}

float Collision::getRight(const Vector3& pos)
{
	Vector3 p(pos.x - CollisionPosDist, pos.y + CollisionPosDist, pos.z);
	Vector3 v(1.0f, 0, 0);
	Vector3 out;
	float dist = CollisionRange;

	if (obj->RayPick(&out, &p, &v, &dist) == -1) return CollisionDistRet;
	return out.x;

}

float Collision::getLeft(const Vector3& pos)
{
	Vector3 p(pos.x + CollisionPosDist, pos.y + CollisionPosDist, pos.z);
	Vector3 v(-1.0f, 0, 0);
	Vector3 out;
	float dist = CollisionRange;

	if (obj->RayPick(&out, &p, &v, &dist) == -1) return -CollisionDistRet;
	return out.x;
}

bool Collision::ColSphere(Vector3& p1, float r1, Vector3 p2, float r2)
{
	float	d = (p2 - p1).LengthSq();		//	2点間の距離の2乗(ベクトルの長さで代用)

	float	R = r1 + r2;
	R = R * R;							//	半径の和 の2乗

	if (d < R)	return	true;
	return	false;
}