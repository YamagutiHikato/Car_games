#include	 <memory>

#include	"iextreme.h"
#include	"system/system.h"

#include	"system/Framework.h"

#include	"../source/sceneMain.h"

#include    "SceneTitle.h"
#include    "Camera.h"
#include    "Stage.h"
#include    "Player.h"
#include    "Enemy.h"
#include    "SceneLoad.h"
#include    "Collision.h"
#include    "UI_Texture.h"

#include <random>

std::shared_ptr<iexView>view;
iex2DObj*NumberTex;
#define AITEST
/*
	���ݒ�
*/

std::random_device rd;
std::mt19937 mt(rd());

std::uniform_int_distribution<int>windSpeedRd(-20.0f, 20.0f);
std::uniform_real_distribution<float>temp(8.0f, 35.0f);

/*
	�����n���p�O���[�o���ϐ�
*/

Collision* col = nullptr;



#define SHADOW_SIZE 4000
#define PointLightRange 40.0f


bool sceneMain::Initialize()
{

	/*
		�V�F�[�_�[�֘A
	*/
	iexLight::SetFog(100.0f, 100.0f, 0xFFFFFFFF);

	shader3D = new iexShader("DATA\\Shader\\3D.fx");
	shader2D = new iexShader("DATA\\Shader\\2D_Shader.fx");
	shaderD = new iexShader("DATA\\Shader\\deferred.fx");
	shaderDL = new iexShader("DATA\\Shader\\DeferredLight.fx");
	shaderShadow= new iexShader("DATA\\Shader\\shadow.fx");

	//	�t���[���o�b�t�@�̃|�C���^�ۑ�
	iexSystem::GetDevice()->GetRenderTarget(0, &pBackBuffer);
	//	�ꎞ�����_�����O�p�T�[�t�F�C�X
	screen = new iex2DObj(1280, 720, IEX2D_RENDERTARGET);

	shadowBuffer = new iex2DObj(1280, 720, IEX2D_RENDERTARGET);

	//	�������C�e�B���O�ݒ�
	shader3D->SetValue("SkyColor", Vector3(0.3f, 0.3f, 0.3f));
	shader3D->SetValue("GroundColor", Vector3(0.2f, 0.2f, 0.2f));
	shader3D->SetValue("LightDir", Vector3(1.0f, 1.0f, 1.0f));
	shader3D->SetValue("DirLightColor", Vector3(1.0f, 1.0f, 1.0f));

	EnvTex = new iex2DObj("DATA\\Env01.png");
	shader->SetValue("EnvMap", EnvTex);

	//	�|�X�g�G�t�F�N�g�ݒ�
	float contrast = 1.6f;		//	�R���g���X�g
	float saturate = 0.7f;		//	�ʓx
	float brightness = 0.0f;	//	�P�x

	Vector3 screen_color = Vector3(1.0f, 1.0f, 1.0f);
	shader2D->SetValue("contrast", contrast);
	shader2D->SetValue("saturate", saturate);
	shader2D->SetValue("brightness", brightness);
	shader2D->SetValue("ScreenColor", &screen_color);


	/*
	
	*/
	for (int i = 0;i < 100;i++)
	{
		WindSpeed = windSpeedRd(mt);
		tempnum = temp(mt);
	}

	view.reset(new iexView());
	view->SetProjection(0.8f, 0.1f, 300.0f);

	//	���_�����ݒ�
	viewAngle = 0;
	viewHeight = 500;
	viewDist = 100;
	//	���C�g�����ݒ�
	lightAngle = 1;
	lightPower = 0.8f;

	StartTimer = 60 * 3;
	StartCountTimer = 0;
	EndlessTimer = 0;
	GoalInTimer = 0;
	WindSpeed = 0;
	tempnum = 0.0f;

	Camera::GetInstance()->Init();
	Stage::GetInstance()->Init();

	Car_A::GetInstance()->Init();
	Car_A_E::GetInstance()->Init();
	Collision::GetInstance()->Init("DATA\\Stage\\TestStage.IMO");

	UI::GetInstance()->Init();

	NumberTex = new iex2DObj("DATA\\000.png");

	//�f�B�t�@�[�h�ݒ�
	diffuse = new iex2DObj(1280, 720, IEX2D_RENDERTARGET);
	specular = new iex2DObj(1280, 720, IEX2D_RENDERTARGET);
	pos_depth = new iex2DObj(1280, 720, IEX2D_ARGB32F);
	normal = new iex2DObj(1280, 720, IEX2D_ARGB32F);

	light = new iex2DObj(1280, 720, IEX2D_RENDERTARGET);
	light_s = new iex2DObj(1280, 720, IEX2D_RENDERTARGET);

	shader3D->SetValue("DepthBuf", pos_depth);
	shader3D->SetValue("SpecularBuf", specular);
	//�@�V���h�[�}�b�v�쐬
	shadowMapTex = new iex2DObj(SHADOW_SIZE, SHADOW_SIZE, IEX2D_RENDERTARGET);
	//�@�e�pZ�o�b�t�@�쐬
	iexSystem::GetDevice()->CreateDepthStencilSurface(SHADOW_SIZE, SHADOW_SIZE, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, FALSE, &ShadowZ, NULL);

	return true;
}

sceneMain::~sceneMain()
{
	delete screen;
	pBackBuffer->Release();
	delete shader3D;
	delete shader2D;
	delete shaderD;
	delete shaderDL;
	delete shaderShadow;
	//delete ShadowZ;
	delete shadowMapTex;
	delete diffuse;
	delete specular;
	delete pos_depth;
	delete normal;
	delete light;
	delete light_s;
	delete EnvTex;
	delete shadowBuffer;

}

static bool WIRECHANGEMODE = false;
static int Changeing = 0;

void	sceneMain::Update()
{
	if (lightPower > 1.0f) lightPower = 1;
	if (lightPower < 0) lightPower = 0;

	ViewPos = Vector3(sinf(viewAngle)*viewDist, viewHeight, cosf(viewAngle)*viewDist);
	view->Set(ViewPos,Car_A::GetInstance()->GetPos());
	shader3D->SetValue("ViewPos", ViewPos);

	iexLight::DirLight(shader3D, 0, &Vector3(sinf(lightAngle), -0.7f, cosf(lightAngle)), lightPower, lightPower, lightPower);

	EndlessTimer++;
	if (EndlessTimer >= 60)
	{
		WindSpeed = windSpeedRd(mt);
		tempnum = temp(mt);
		EndlessTimer = 0;
		lightAngle += 0.00004f;
	}
	StartTimer--;
	if (StartTimer <= 0)
	{
		Car_A::GetInstance()->SetSMove(true);
		Car_A_E::GetInstance()->SetSMove(true);
		StartTimer = 0;
	}



	Car_A::GetInstance()->SetEnviroment(WindSpeed, tempnum);
	Car_A::GetInstance()->Update();



	Car_A_E::GetInstance()->SetEnviroment(WindSpeed, tempnum);
	Car_A_E::GetInstance()->Update();


	//AI�`�F�b�N�p
#ifndef AITEST
	Car_A::GetInstance()->SetPos(Car_A_E::GetInstance()->GetPos());
	Car_A::GetInstance()->SetAngle(Car_A_E::GetInstance()->GetAngle());
	Car_A::GetInstance()->SetSpeed(Car_A_E::GetInstance()->GetSpeed());

#endif
	UI::GetInstance()->Update();

	Camera::GetInstance()->Update(*Car_A::GetInstance());

	Stage::GetInstance()->Update();

	//
	sceneTitle*newScene = new sceneTitle();
	if (Car_A::GetInstance()->GetGoalInChake() == true)
	{
		GoalInTimer++;
		if (GoalInTimer >= 180)
		{
			MainFrame->ChangeScene(newScene);
			GoalInTimer = 0;
		}
		
	}

	if (KEY_Get(KEY_SELECT) == 3)Changeing++;
	if (Changeing >= 2)Changeing = 0;
	if (Changeing == 0)WIRECHANGEMODE = false;
	if (Changeing == 1) WIRECHANGEMODE = true;
}


void	sceneMain::RenderShadowBuffer()
{
	shadowMapTex->RenderTarget();
	//	Z�o�b�t�@�ݒ�
	Surface*	orgZ;
	iexSystem::GetDevice()->GetDepthStencilSurface(&orgZ);
	iexSystem::GetDevice()->SetDepthStencilSurface(ShadowZ);
	//	���C�g����
	Vector3 dir(sinf(lightAngle), -1.7f, cosf(lightAngle));
	dir.Normalize();

	//	�V���h�E�쐬
	Vector3	target(0,0,0);
	target = Car_A::GetInstance()->GetPos();

	Vector3 pos ;
	pos = target - dir*300;
	
	Vector3 up(0, 1, 0);
	D3DXMATRIX	ShadowMat, work;
	LookAtLH(ShadowMat, pos, target, up);
	D3DXMatrixOrthoLH(&work, 1000, 1000, 50, 450);	//	���s���e�s��(�͈�x100)
	ShadowMat *= work;

	shaderShadow->SetValue("ShadowProjection", &ShadowMat);

	D3DVIEWPORT9 vp = { 0,0,SHADOW_SIZE,SHADOW_SIZE, 0, 1.0f };
	iexSystem::GetDevice()->SetViewport(&vp);
	//	�����_�����O
	iexSystem::GetDevice()->Clear(0, NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);

	//	�`��
	Stage::GetInstance()->Render(shaderShadow, "ShadowBuf");
	Car_A::GetInstance()->Render(shaderShadow, "ShadowBuf");
	Car_A_E::GetInstance()->Render(shaderShadow, "ShadowBuf");

	//	������V���h�E�e�N�X�`�����V�F�[�_�[�ɃZ�b�g
	shaderShadow->SetValue("ShadowMap", shadowMapTex);
	//	�����_�[�^�[�Q�b�g�̕���
	iexSystem::GetDevice()->SetRenderTarget(0, pBackBuffer);
	iexSystem::GetDevice()->SetDepthStencilSurface(orgZ);




}

void sceneMain::DirLight(const Vector3& dir, const Vector3& color)
{
	Matrix mat = matView;
	Vector3 LightDir;
	Vector3 Dir = dir;
	Dir.Normalize();
	LightDir = Dir;

	//	�V�F�[�_�[�ݒ�
	shaderDL->SetValue("LightVec", LightDir);
	shaderDL->SetValue("LightColor", (Vector3)color);
	shaderDL->SetValue("PosDepthBuf",pos_depth->GetTexture());

	//	�����_�����O
	normal->Render(shaderDL, "dirlight");
}

void sceneMain::CharaLight(const Vector3& color)
{
	Matrix mat = matView;
	Vector3 LightDir = view->GetTarget() - view->GetPos();
	LightDir *= -1.0f;
	LightDir.Normalize();

	//	�V�F�[�_�[�ݒ�
	shaderDL->SetValue("LightVec", LightDir);
	shaderDL->SetValue("LightColor", (Vector3)color);
	shaderDL->SetValue("PosDepthBuf", pos_depth->GetTexture());

	//	�����_�����O
	normal->Render(shaderDL, "charalight");
}

//*****************************************************************************************************************************
//
//		�_����
//
//*****************************************************************************************************************************

void sceneMain::PointLight(const Vector3& pos, const Vector3& color, float range)
{
	//�ϊ��s��ݒ�
	Matrix InvProj;
	D3DXMatrixInverse(&InvProj, NULL, &matProjection);
	shaderDL->SetValue("InvProj", InvProj);

	Matrix mat = matView;
	//�J������ԕϊ�
	Vector3 LightPos;
	LightPos.x = pos.x * mat._11 + pos.y * mat._21 + pos.z * mat._31 + mat._41;
	LightPos.y = pos.x * mat._12 + pos.y * mat._22 + pos.z * mat._32 + mat._42;
	LightPos.z = pos.x * mat._13 + pos.y * mat._23 + pos.z * mat._33 + mat._43;

	//�V�F�[�_�\�ݒ�
	shaderDL->SetValue("PointLightPos", LightPos);
	shaderDL->SetValue("PointLightColor", (Vector3)color);
	shaderDL->SetValue("PointLightRange", range);

	//�����_�����O
	normal->Render(shaderDL, "dif_Pointlight");

}

//�V�F�[�_�[���s����Ȑ݌v�ׁ̈@�e��؂��Ă�
void	sceneMain::Render()
{
	//�J�E���^�[
	StartCountTimer = (StartTimer / 60) + 1;

	//	�V���h�E�}�b�v�쐬
	RenderShadowBuffer();

	//�X�N���[���֐؂�ւ�
	screen->RenderTarget();

	
	//	�ꎞ�o�b�t�@�֐؂�ւ�
	view->SetViewport();
	view->Activate();
	view->Clear(0xffffff);

	shaderD->SetValue("matView", matView);

	////�ϊ��s��ݒ�
	Matrix InvProj;
	D3DXMatrixInverse(&InvProj, nullptr, &matProjection);
	shader3D->SetValue("InvProj", InvProj);
	shaderD->SetValue("InvProj", InvProj);

	{
		iexSystem::Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		iexSystem::Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		Camera::GetInstance()->Render();
		Stage::GetInstance()->Render2();
		Stage::GetInstance()->Render(shader3D, "full_s");
		Car_A_E::GetInstance()->Render(shader3D, "full");
		Car_A::GetInstance()->Render(shader3D, "full");
		iexSystem::Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	

	}


	//	�ȉ��f�B�t�@�[�h
	{
		view->Clear(0xffffff);

		if (StartTimer > 0)NumRenderCenter(640, 300, 64, 32, StartCountTimer, 0xffffffff);
		else 	StartTimer = 0;

		//�f�B�t�@�[�h�ݒ�
		//GBuffer��������
		diffuse->RenderTarget();
		specular->RenderTarget(1);
		pos_depth->RenderTarget(2);
		normal->RenderTarget(3);

		Camera::GetInstance()->Render();
		shaderD->SetValue("Mask", 0.0f);
		Stage::GetInstance()->Render(shaderD, "deferred");
		shaderD->SetValue("Mask", 1.0f);
		
		Car_A_E::GetInstance()->Render(shaderD, "deferred");
		Car_A::GetInstance()->Render(shaderD, "deferred");
		
		//���C�g�o�b�t�@�Ƀ��C�g��������
		light->RenderTarget();
		light_s->RenderTarget(1);
		iexSystem::Device->SetRenderTarget(2, nullptr);
		iexSystem::Device->SetRenderTarget(3, nullptr);
		view->SetViewport();
		view->Activate();
		view->Clear(0x000000);

		Matrix InvmatViewProj;
		D3DXMatrixInverse(&InvmatViewProj, nullptr, &(matView*matProjection));

		shaderDL->SetValue("InvProj", InvmatViewProj);

		DirLight(Vector3(-0.2f, -1, 0), Vector3(0.8,0.8,0.8));
		CharaLight(Vector3(0.6, 0.6, 0.6));
		//DirLight(Vector3(-1, -1, 0), Vector3(0, 0, 1));

		//	�������C�g
		normal->Render(shaderDL, "hemiSpherelight");

		//	�e�`��
		shadowBuffer->RenderTarget();
		iexSystem::Device->SetRenderTarget(1, nullptr);
		view->SetViewport();
		view->Activate();
		view->Clear(0x000000);

		shaderShadow->SetValue("PosDepthBuf", pos_depth->GetTexture());

		normal->Render(shaderShadow, "shadowCalc");
		

			//�o�b�N�o�b�t�@�֐؂�ւ�
		screen->RenderTarget();
		view->SetViewport();
		view->Activate();
		view->Clear(0x000000);


		//�e������
		//�f�B�t�@�[�h�`��
		diffuse->Render(0, 0, 1280, 720, 0, 0, 1280, 720, shader2D, "copy");
		light->Render(0, 0, 1280, 720, 0, 0, 1280, 720, RS_MUL, 0xFFFFFFFF);
		light_s->Render(0, 0, 1280, 720, 0, 0, 1280, 720, RS_ADD, 0xFFFFFFFF);

		shadowBuffer->Render(0, 0, 1280, 720, 0, 0, 1280, 720, RS_MUL, 0xFFFFFFFF);


		//�K���X����ŕ`��
		//GBuffer�쐬����Z�o�b�t�@���g�p����
		Stage::GetInstance()->Render2();
	}

		//�t���[���o�b�t�@�֐؂�ւ�
	iexSystem::GetDevice()->SetRenderTarget(0, pBackBuffer);
		//�|�X�g�G�t�F�N�g�̗p
	screen->Render(0, 0, 1280, 720, 0, 0, 1280, 720, shader2D, "filter");
	if (KEY_Get(KEY_C))
	{
		diffuse->Render(0, 0, 320, 180, 0, 0, 1280, 720, shader2D, "copy");
		normal->Render(320, 0, 320, 180, 0, 0, 1280, 720, shader2D, "copy");
		light->Render(640, 0, 320, 180, 0, 0, 1280, 720, shader2D, "copy");
		light_s->Render(960, 0, 320, 180, 0, 0, 1280, 720, shader2D, "copy");
		pos_depth->Render(960, 180, 320, 180, 0, 0, 1280, 720, shader2D, "copy");
		shadowMapTex->Render(0, 320, 400, 400, 0, 0, SHADOW_SIZE, SHADOW_SIZE, shader2D, "copy");
		shadowBuffer->Render(960, 540, 320, 180, 0, 0, 1280, 720, shader2D, "copy");
	}
	UI::GetInstance()->Render();
	
	
}

void sceneMain::NumRenderCenter(int posX, int posY, int size, int move, int num, unsigned int color)
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
	iexSystem::Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	while (1)
	{
		NumberTex->Render(s_pos - x, posY, size, size, ((num % 10) % 4) * 128, ((num % 10) / 4) * 128, 128, 128, 0, color);
		x += move;
		num /= 10;
		if (num <= 0)break;
	}
}



