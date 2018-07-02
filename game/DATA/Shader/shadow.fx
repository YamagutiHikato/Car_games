//#include "3D.fx"
//******************************************************************************
//
//		シャドウマップ作成
//
//******************************************************************************
float4x4 ShadowProjection;
float4x4 TransMatrix; //	変換行列

texture Texture; //	デカールテクスチャ

texture ShadowMap;
sampler ShadowSamp = sampler_state
{
	Texture = <ShadowMap>;
	MinFilter = POINT;
	MagFilter = POINT;
	MipFilter = NONE;

	BorderColor = 0xFFFFFFFF;
	AddressU = BORDER;
	AddressV = BORDER;
};

struct VS_SHADOW
{
	float4 Pos		: POSITION;
	float4 Color	: TEXCOORD0;		// 頂点色
};

//------------------------------------------------------
//		頂点シェーダー
//------------------------------------------------------
VS_SHADOW VS_ShadowBuf( float4 Pos : POSITION )
{
	VS_SHADOW Out;
	
	// 座標変換
	float4x4	mat = mul(TransMatrix, ShadowProjection);
	Out.Pos = mul(Pos, mat);
	Out.Color = Out.Pos.z;
    
	return Out;
}

//------------------------------------------------------
//		ピクセルシェーダー
//------------------------------------------------------
float4 PS_ShadowBuf( VS_SHADOW In) : COLOR
{

	return	In.Color;
}

//------------------------------------------------------
//		テクニック
//------------------------------------------------------
technique ShadowBuf
{
    pass Pass0
	{
		AlphaBlendEnable = false;
		ZWriteEnable      = true;
		CullMode 		   = none;
		
		VertexShader = compile vs_2_0 VS_ShadowBuf();
		PixelShader  = compile ps_2_0 PS_ShadowBuf();
    }
}

//**************************************************************************************************
//
//		ピクセルシェーダー
//
//**************************************************************************************************

texture PosDepthBuf;
sampler PosDepthBufSamp = sampler_state
{
    Texture = <PosDepthBuf>;
    MinFilter = POINT;
    MagFilter = POINT;
    MipFilter = NONE;

    BorderColor = 0xFFFFFFFF;
    AddressU = BORDER;
    AddressV = BORDER;
};

float AdjustValue = -0.004;
float Shadow = 0.6f;

inline float2 GetShadowTex(float4 Pos)
{
    float2 Tex;
    Tex = Pos.xy / Pos.w;

    Tex.y = -Tex.y;
    Tex.xy = 0.5f * Tex.xy + 0.5f;

    return Tex;
}

inline float GetShadow(float2 Tex, float depth)
{
    float d = tex2D(ShadowSamp, Tex.xy).r; // シャドウマップから深度を取り出す
  
    //  物のないところは除外
    if (d < 0.0001)
    {
        return 1.0;
    }
    float l = (d < depth + AdjustValue) ? Shadow : 1;

    return l;
}

float4 PS_ShadowCalc(float2 Tex : TEXCOORD0) : COLOR
{
    float4 pos = tex2D(PosDepthBufSamp, Tex);
    pos.w = 1.0;

    float4 shadowPos = mul(pos, ShadowProjection);
    float depth = shadowPos.z;

    float shadow = GetShadow(GetShadowTex(shadowPos), depth);

    //return float4(GetShadowTex(shadowPos), 1.0, 1.0);
    return float4(shadow, shadow, shadow, 1.0);
}
//------------------------------------------------------
//	テクニック
//------------------------------------------------------
technique shadowCalc
{
    pass P0
    {
        AlphaBlendEnable = true;
        BlendOp = Add;
        SrcBlend = SrcAlpha;
        DestBlend = One;
        CullMode = None;
        ZEnable = false;
        ZWriteEnable = false;

        PixelShader = compile ps_3_0 PS_ShadowCalc();
    }
}

////******************************************************************************
////
////		シャドウマップ採用
////
////******************************************************************************
//struct V_FULL_S
//{
//    float4 Pos		: POSITION;
//    float4 Color	: COLOR0;
//    float2 Tex		: TEXCOORD0;
//    float4 Ambient	: COLOR1;
//	float4 light	: COLOR2;
//	float3 vLight	: TEXCOORD1;
//	float3 vE		: TEXCOORD2;
//	float3 plight	: TEXCOORD3;

//	float3 vShadow  : TEXCOORD4;
//};


////------------------------------------------------------
////	頂点シェーダ
////------------------------------------------------------
//V_FULL_S VS_FullS( VS_INPUT In )
//{
//	V_FULL_S Out = (V_FULL_S)0;

//	Out.Pos   = mul(In.Pos, Projection);
//	Out.Color = 1;//In.Color;
//	Out.Tex   = In.Tex;

//	float4 P = mul(In.Pos, TransMatrix);
//	float3x3	mat = TransMatrix;
//	float3 N = mul(In.Normal, mat);
//	N = normalize(N);

//	// 半球ライティング
//	Out.Ambient.rgb = HemiLight(N);

//	//	頂点ローカル座標系算出
//	float3	vx;
//	float3	vy = { 0, 1, 0.001f };
//	vx = cross( vy, N );
//	vx = normalize( vx );
//	vy = cross( vx, N  );
//	vy = normalize( vy );

//	//	ライトベクトル補正
//	Out.vLight.x = dot(vx, LightDir);
//	Out.vLight.y = dot(vy, LightDir);
//	Out.vLight.z = dot(N, LightDir);

//	// 視線ベクトル補正
//	float3 E = P - ViewPos;   // 視線ベクトル
//	Out.vE.x = dot(vx, E);
//	Out.vE.y = dot(vy, E);
//	Out.vE.z = dot(N, E);
//	//	シャドウマップ
//	Out.vShadow = GetShadowTex(P);

//	return Out;
//}

////------------------------------------------------------
////		ピクセルシェーダー	
////------------------------------------------------------
//float4 PS_FullS( V_FULL_S In) : COLOR
//{   
//	float4	OUT;
//	float2 Tex = In.Tex;

//	//	パララックスディスプレースメント
//	float h = tex2D( HeightSamp, Tex ).r-0.5f;
//	float3 E = normalize(In.vE);
//	Tex.x += 0.04f * h * E.x;
//	Tex.y -= 0.04f * h * E.y;


//	//	法線取得
//	float3 N = tex2D( NormalSamp, Tex ).xyz * 2.0f - 1.0f;

//	//	ライト計算
//	In.vLight   = normalize( In.vLight );
//	float3 light = DirLight(In.vLight, N);


//	//	視線反射ベクトル
//	float3 R = reflect( -E, N );
//	//	スペキュラマップ取得
//	float4 sp_tex = tex2D( SpecularSamp, Tex );

//	//	環境マップ
//	float3 env = Environment(R) * (1-sp_tex.a);

//	//	ピクセル色決定
//	OUT = In.Color * tex2D( DecaleSamp, Tex );
//	OUT.rgb = (OUT.rgb * (light + In.Ambient.rgb) );
//	OUT.rgb = OUT.rgb * env + OUT.rgb;

//	//	スペキュラ
//	OUT.rgb += pow( max( 0, dot(R, In.vLight) ), 10 ) * sp_tex;
//		//	シャドウマップ適用
//    OUT.rgb *= GetShadow(In.vShadow.xy, In.vShadow.z);


//	return OUT;
//}

////------------------------------------------------------
////		合成なし	
////------------------------------------------------------
//technique full_s
//{
//    pass P0
//    {
//		AlphaBlendEnable = true;
//		BlendOp          = Add;
//		SrcBlend         = SrcAlpha;
//		DestBlend        = InvSrcAlpha;
//		ZWriteEnable     = true;

//		VertexShader = compile vs_3_0 VS_FullS();
//		PixelShader  = compile ps_3_0 PS_FullS();
//    }
//}