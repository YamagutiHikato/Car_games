//*****************************************************************************************************************************
//
//		メインシーン
//
//*****************************************************************************************************************************
#define SHADOW_SIZE 2048
class	sceneMain : public Scene
{
private:
	//iexView*	view;
	int WindSpeed;
	float tempnum ;
	 int StartTimer;
	 int StartCountTimer;
	 int EndlessTimer;
	 int GoalInTimer;
	float	viewAngle;
	float	viewHeight;
	float	viewDist;

	float	lightAngle;
	float	lightPower;
	bool	bHDR;

	iexShader*	shader3D;
	iexShader*	shader2D;
	iexShader* shaderD;
	iexShader* shaderDL;
	iexShader* shaderShadow;


	iex2DObj*	screen;
	Surface*   pBackBuffer;

	Surface*   ShadowZ;
	iex2DObj*  shadowMapTex;
	iex2DObj*  diffuse;
	iex2DObj*  specular;
	iex2DObj*  pos_depth;
	iex2DObj*  normal;
	iex2DObj*  light;
	iex2DObj*  light_s;
	iex2DObj*	EnvTex;
	iex2DObj*	shadowBuffer;

	void RenderShadowBuffer();
	void DirLight(const Vector3& dir, const Vector3& color);
	void CharaLight(const Vector3& color);
	void PointLight(const Vector3& pos, const Vector3& color, float range);
	Vector3		ViewPos;
public:
	~sceneMain();
	//	初期化
	bool Initialize();
	//	更新・描画
	void Update();	//	更新
	void Render();	//	描画

	void NumRenderCenter(int posX, int posY, int size, int move, int num, unsigned int color);
};


