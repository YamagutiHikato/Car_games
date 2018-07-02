#include <memory>
#include "iextreme.h"

#include "Stage.h"
bool Stage::Init()
{
	pos = Vector3(0.0f,0.0f, 0.0f);

	scale = 1;

	obj  =new iexMesh("DATA/Stage//TestStage.IMO");
	obj2 = new iexMesh("DATA\\BG\\stage\\Sky.x");

	return true;
}

void Stage::Update()
{
	obj->Update();
	obj->SetPos(pos);
	obj->SetScale(scale);

	obj2->Update();
	obj2->SetPos(pos);
	obj2->SetScale(scale*15.0f);

}

void Stage::Render(iexShader*shader,char *chr)
{
		//iexSystem::Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		//iexSystem::Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		obj->Render(shader, chr);
		//iexSystem::Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

}

void Stage::Render2()
{
	obj2->Render();
}