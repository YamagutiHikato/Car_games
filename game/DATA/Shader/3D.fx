
//**************************************************************************************************
//																									
//		基本シェーダー		
//
//**************************************************************************************************

//------------------------------------------------------
//		環境関連
//------------------------------------------------------
float4x4 TransMatrix;	//	変換行列
float4x4 matView;		//	変換行列
float4x4 Projection;	//	変換行列

float3	ViewPos;

//------------------------------------------------------
//		テクスチャサンプラー	
//------------------------------------------------------
texture Texture;	//	デカールテクスチャ
sampler DecaleSamp = sampler_state
{
    Texture = <Texture>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Wrap;
    AddressV = Wrap;
};

texture NormalMap;	//	法線マップテクスチャ
sampler NormalSamp = sampler_state
{
    Texture = <NormalMap>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Wrap;
    AddressV = Wrap;
};

texture HeightMap;		//	高さマップテクスチャ
sampler HeightSamp = sampler_state
{
    Texture = <HeightMap>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Wrap;
    AddressV = Wrap;
};

texture SpecularMap;	//	スペキュラマップテクスチャ
sampler SpecularSamp = sampler_state
{
    Texture = <SpecularMap>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Wrap;
    AddressV = Wrap;
};


//**************************************************************************************************
//		頂点フォーマット
//**************************************************************************************************
struct VS_OUTPUT
{
    float4 Pos		: POSITION;
    float4 Color	: COLOR0;
    float2 Tex		: TEXCOORD0;

    float4 Ambient	: COLOR1;
	float4 light	: COLOR2;
	float3 vLight	: TEXCOORD2;
	float3 vE		: TEXCOORD3;
};

struct VS_INPUT
{
    float4 Pos    : POSITION;
    float3 Normal : NORMAL;
    float4 Color  : COLOR0;
    float2 Tex	  : TEXCOORD0;
};


//**************************************************************************************************
//
//		ライティング
//
//**************************************************************************************************

//**************************************************************************************************
//	半球ライティング
//**************************************************************************************************
float3 SkyColor = { 0.48f, 0.5f, 0.5f };
float3 GroundColor = { 0.4f, 0.4f, 0.4f };

inline float4 HemiLight( float3 normal )
{
	float4 color;
	float rate = (normal.y*0.5f) + 0.5f;
	color.rgb = SkyColor * rate;
	color.rgb += GroundColor * (1-rate);
	color.a = 1.0f;

	return color;
}

//**************************************************************************************************
//	平行光
//**************************************************************************************************
float3 LightDir = { 1.0f, -1.0f, 0.0f };
float3 DirLightColor = { 0.6f, 0.6f, 0.6f };

inline float3 DirLight( float3 dir, float3 normal )
{
	float3 light;
	float rate = max( 0.0f, dot( -dir, normal ) );
	light = DirLightColor * rate;
	
	return light;
}

//**************************************************************************************************
//	スペキュラ
//**************************************************************************************************
inline float Specular(float3 pos, float3 normal)
{
    float   sp;

    float3	H = normalize(ViewPos - pos);
    H = normalize(H - LightDir);
    
	sp = dot(normal, H);
	sp = max( 0, sp );
	sp = pow(sp, 10);

    return sp;
}

//**************************************************************************************************
//	環境マップ用
//**************************************************************************************************
texture EnvMap;		//	環境テクスチャ
sampler EnvSamp = sampler_state
{
    Texture = <EnvMap>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Wrap;
    AddressV = Wrap;
};

inline float4 Environment( float3 normal )
{
	float4	color;
	
	float2	uv;
	uv.x =  normal.x*0.5f + 0.5f;
	uv.y = -normal.y*0.5f + 0.5f;

	color = tex2D( EnvSamp, uv );
	return color;
}


//**************************************************************************************************
//
//		フルエフェクト
//
//**************************************************************************************************

//------------------------------------------------------
//	頂点カラー付シェーダ
//------------------------------------------------------
VS_OUTPUT VS_FullFX( VS_INPUT In )
{
	VS_OUTPUT Out = (VS_OUTPUT)0;

	Out.Pos   = mul(In.Pos, Projection);
	Out.Color = In.Color;
	Out.Tex   = In.Tex;

	float4 P = mul(In.Pos, TransMatrix);
	float3x3	mat = TransMatrix;
	float3 N = mul(In.Normal, mat);
	N = normalize(N);

	// 半球ライティング
	Out.Ambient.rgb = HemiLight(N);

	//	頂点ローカル座標系算出
	float3	vx;
	float3	vy = { 0, 1, 0.001f };
	vx = cross( vy, N );
	vx = normalize( vx );
	vy = cross( vx, N  );
	vy = normalize( vy );

	//	ライトベクトル補正
	Out.vLight.x = dot(vx, LightDir);
	Out.vLight.y = dot(vy, LightDir);
	Out.vLight.z = dot(N, LightDir);

	// 視線ベクトル補正
    float3 E = (float3) P - ViewPos; // 視線ベクトル
	Out.vE.x = dot(vx, E);
	Out.vE.y = dot(vy, E);
	Out.vE.z = dot(N, E);

	return Out;
}


//**************************************************************************************************
//
//		スペキュラー描画
//
//**************************************************************************************************
struct VS_HDR
{
    float4 Pos		: POSITION;
    float3 wPos		: TEXCOORD2;
    float3 Normal	: TEXCOORD1;
    float2 Tex		: TEXCOORD0;
};

//------------------------------------------------------
//	スペキュラ計算（通常よりキツイ）
//------------------------------------------------------
float HDRSpecular(float3 pos, float3 normal)
{
    float   sp;

    float3	H = normalize(ViewPos - pos);
    H = normalize(H - LightDir);

	sp = dot(normal, H);
	sp = max( 0, sp );
	sp = pow(sp, 50);

    return sp;
}

//------------------------------------------------------
//	頂点シェーダー
//------------------------------------------------------
VS_HDR VS_Specular( VS_INPUT In )
{
	VS_HDR Out = (VS_HDR)0;

	Out.Pos   = mul(In.Pos, Projection);
	Out.Tex   = In.Tex;

	//	スペキュラ計算用座標
	Out.wPos = mul(In.Pos, TransMatrix);
	//	スペキュラ計算用法線
	float3x3 mat = TransMatrix;
	float3 N = mul(In.Normal, mat);
	Out.Normal = normalize(N);

	return Out;
}

//------------------------------------------------------
//	ピクセルシェーダー	
//------------------------------------------------------
float4 PS_Specular( VS_HDR In) : COLOR
{   
	float4	OUT;

	//	スペキュラ計算
	float s = HDRSpecular( In.wPos, In.Normal );
	//	
	float4 sp = tex2D( SpecularSamp, In.Tex ) * s;
	//	ピクセル色決定
	OUT.rgb = sp*0.5f;
	OUT.a = 1;

	return OUT;
}

//------------------------------------------------------
//	テクニック
//------------------------------------------------------
technique specular
{
    pass P0
    {
		AlphaBlendEnable = true;
		BlendOp          = Add;
		SrcBlend         = SrcAlpha;
		DestBlend        = InvSrcAlpha;
		ZWriteEnable     = true;

		VertexShader = compile vs_2_0 VS_Specular();
		PixelShader  = compile ps_2_0 PS_Specular();
    }
}

//**************************************************************************************************
//
//		点光源付きフルエフェクト
//
//**************************************************************************************************

struct V_FULL
{
    float4 Pos		: POSITION;
    float4 Color	: COLOR0;
    float2 Tex		: TEXCOORD0;

    float4 Ambient	: COLOR1;
	float4 light	: COLOR2;
	float3 vLight	: TEXCOORD1;
	float3 vE		: TEXCOORD2;
};

//------------------------------------------------------
//	頂点シェーダ
//------------------------------------------------------
V_FULL VS_Full( VS_INPUT In )
{
	V_FULL Out = (V_FULL)0;

	Out.Pos   = mul(In.Pos, Projection);
	Out.Color = 1;//In.Color;
	Out.Tex   = In.Tex;

	float4 P = mul(In.Pos, TransMatrix);
	float3x3	mat = TransMatrix;
	float3 N = mul(In.Normal, mat);
	N = normalize(N);

	// 半球ライティング
	Out.Ambient.rgb = HemiLight(N);

	//	頂点ローカル座標系算出
	float3	vx;
	float3	vy = { 0, 1, 0.001f };
	vx = cross( vy, N );
	vx = normalize( vx );
	vy = cross( vx, N  );
	vy = normalize( vy );

	//	ライトベクトル補正
	Out.vLight.x = dot(vx, LightDir);
	Out.vLight.y = dot(vy, LightDir);
	Out.vLight.z = dot(N, LightDir);

	// 視線ベクトル補正
    float3 E = (float3) P - ViewPos; // 視線ベクトル
	Out.vE.x = dot(vx, E);
	Out.vE.y = dot(vy, E);
	Out.vE.z = dot(N, E);

	return Out;
}

//------------------------------------------------------
//		ピクセルシェーダー	
//------------------------------------------------------
float4 PS_Full( V_FULL In) : COLOR
{   
	float4	OUT;
	float2 Tex = In.Tex;

	//	パララックスディスプレースメント
	float h = tex2D( HeightSamp, Tex ).r-0.5f;
	float3 E = normalize(In.vE);
	//Tex.x += 0.04f * h * E.x;
	//Tex.y -= 0.04f * h * E.y;

	//	法線取得
	float3 N = tex2D( NormalSamp, Tex ).xyz * 2.0f - 1.0f;

	//	ライト計算
	In.vLight   = normalize( In.vLight );
	float3 light = DirLight(In.vLight, N);


	//	視線反射ベクトル
	float3 R = reflect( -E, N );
	//	スペキュラマップ取得
	float4 sp_tex = tex2D( SpecularSamp, Tex );

	//	環境マップ
	float3 env = Environment(R) * (1-sp_tex.a);

	//	ピクセル色決定
	OUT = In.Color * tex2D( DecaleSamp, Tex );
	OUT.rgb = (OUT.rgb * (light + In.Ambient.rgb) );
	OUT.rgb = OUT.rgb * env + OUT.rgb;

	//	スペキュラ
	OUT.rgb += pow( max( 0, dot(R, In.vLight) ), 10 ) * sp_tex;

	return OUT;
}

//------------------------------------------------------
//		合成なし	
//------------------------------------------------------
technique full
{
    pass P0
    {
		AlphaBlendEnable = true;
		BlendOp          = Add;
		SrcBlend         = SrcAlpha;
		DestBlend        = InvSrcAlpha;
		ZWriteEnable     = true;

		VertexShader = compile vs_3_0 VS_Full();
		PixelShader  = compile ps_3_0 PS_Full();
    }
}

//#include "shadow.fx"
