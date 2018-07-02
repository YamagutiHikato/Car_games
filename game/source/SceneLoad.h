#pragma once
#include <memory>
#include "Camera.h"

class sceneLoad :public Scene
{
private:
	Scene* newScene;
	HANDLE hThread;
	static bool	bThreadActive;
	static void LoadingThread(void* arg);
	
	iexView*	view;
	iex2DObj*LoadTex_A;
	iex2DObj*LoadTex_B;

	float TextureAngle;

public:
	sceneLoad(Scene* scene);
	~sceneLoad() = default;
	//	初期化
	bool Initialize();
	//	更新・描画

	void Update();	//	更新
	void Render();	//	描画
};
