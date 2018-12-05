#include	"iextreme.h"
#include	"system/system.h"

#include	"SceneLoad.h"
#include	"sceneMain.h"
#include	"system/Framework.h"

#include	<process.h>

#define textureSize 512
#define resolutionSize 128
#define TextureAngleSpeed 0.25f;

sceneLoad::sceneLoad(Scene* scene)
{
	newScene = scene;
}

void sceneLoad::LoadingThread(void* arg)
{
	Scene* scene = (Scene*)arg;
	scene->Initialize();
	bThreadActive = false;
	_endthread();
}
bool sceneLoad::bThreadActive = false;
bool sceneLoad::Initialize()
{
	iexLight::SetAmbient(0x808080);
	iexLight::SetFog(800, 1000, 0);
	view = new iexView();
	LoadTex_A = new iex2DObj("DATA\\Load\\Loading.png");
	LoadTex_B = new iex2DObj("DATA\\HUD_Texture\\metter2.png");


	bThreadActive = true;
	TextureAngle = 0.0f;

	//	•ÊƒXƒŒƒbƒhì¬
	bThreadActive = true;
	_beginthread(LoadingThread, 0, (void*)newScene);
	return true;
}


//*****************************************************************************************************************************
//
//		Žåˆ—
//
//*****************************************************************************************************************************



void	sceneLoad::Update()
{
	
		if (bThreadActive == false)
		{
			MainFrame->ChangeScene(newScene);
			return;
		}
		else
		{
			TextureAngle += TextureAngleSpeed;
		}
}

//*****************************************************************************************************************************
//
//		•`‰æŠÖ˜A
//
//*****************************************************************************************************************************

//------------------------------------------------------
//		•`‰æ
//------------------------------------------------------

void	sceneLoad::Render()
{
	view->Activate();
	view->Clear(0x000000);

	LoadTex_A->Render(900, 600, resolutionSize * 2, resolutionSize, 0, 0, textureSize, textureSize / 2);
	LoadTex_B->RenderI(1140, 600, resolutionSize, resolutionSize, 0, 0, textureSize, textureSize, TextureAngle);
}
