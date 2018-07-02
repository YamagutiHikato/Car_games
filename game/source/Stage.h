#pragma once

/*
	シングルトンでのスマートポインタのラップが上手くできなかったので保留
*/
class Stage
{
private:
	//class 
	iexMesh*obj;
	iexMesh*obj2;
	Stage() = default;		//constructor
	~Stage() = default;		//destructor

	//Vetcor3
	Vector3 pos;

	//float
	float scale;

public:
	//Copy Constructor this ban
	Stage(const Stage&) = delete;
	Stage& operator=(const Stage&) = delete;
	Stage(Stage&&) = delete;
	Stage& operator=(Stage&&) = delete;

	bool Init();		//Initialize

	void Update();		//Update
	void Render(iexShader*shader,char*chr);		//Render
	void Render2();

	static Stage *GetInstance()			//Singleton 
	{
		static Stage instnce;
		return &instnce;
	}
};
