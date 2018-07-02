
//**************************************************************************************************
//																									
//		シェーダーライト	
//
//**************************************************************************************************

//------------------------------------------------------
//		テクスチャサンプラー	
//------------------------------------------------------

texture Texture;
sampler DecaleSamp = sampler_state
{
    Texture = <Texture>;
    MinFilter = POINT;
    MagFilter = POINT;
    MipFilter = NONE;
    AddressU = Wrap;
    AddressV = Wrap;
};

texture PosDepthBuf;	//カメラ空間深度
sampler PosDepthBufSamp = sampler_state
{
    Texture = <PosDepthBuf>;
	MinFilter = POINT;
	MagFilter = POINT;
	MipFilter = NONE;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

texture SpecularBuf;	//カメラ空間深度
sampler SpecularBufSamp = sampler_state
{
	Texture = <SpecularBuf>;
	MinFilter = POINT;
	MagFilter = POINT;
	MipFilter = NONE;
	AddressU = CLAMP;
	AddressV = CLAMP;
};



//**************************************************************************************************
//
//		グローバル変数
//
//**************************************************************************************************
float3 LightVec = { 0.7f,-0.7f,0 };
float3 LightColor = { 1.0f,1.0f,1.0f };

float4x4 InvProj;	//Projectionの逆行列
//--------------------------------
//	ピクセルフォーマット
//--------------------------------
struct POUT_LIGHT
{
	float4 color	:COLOR0;
	float4 spec		:COLOR1;
};

//**************************************************************************************************
//
//		ピクセルシェーダー
//
//**************************************************************************************************
POUT_LIGHT PS_DirLight(float2 Tex:TEXCOORD0)
{
	POUT_LIGHT OUT = (POUT_LIGHT)0;

	float4 n = tex2D(DecaleSamp, Tex);
    float3 normal = n.rgb;// * 2.0f - 1.0f;
	normal = normalize(normal);
    clip(length(normal) - 0.2f);

	//★ディフューズライト
	{
		//float3 L = normalize(LightVec);
		//ライト率
		float r = max(0, dot(normal, -LightVec));
		//
		OUT.color.rgb = r * LightColor; //★★
		OUT.color.a = 1.0f;
	}
	{
		//座標
        float4 pos_depth = tex2D(PosDepthBufSamp, Tex);
        float  depth = pos_depth.w;
        float3 pos = pos_depth.xyz;

		//★スペキュラ
		//視線ベクトル
		float3 E = pos;
		E = normalize(E);

		//ブリン・フォンシェーダー
		float3 H = normalize(-LightVec - E);
		float sp = pow(max(0, dot(H, normal)), 10);

		//スペキュラマップ反映
		float3 sp_tex = tex2D(SpecularBufSamp, Tex);
        sp_tex = 0.2;
		OUT.spec.rgb = sp_tex*sp*LightColor;//★★
		OUT.spec.a = 1.0f;
	}
	return OUT;
}
//------------------------------------------------------
//	テクニック
//------------------------------------------------------
technique dirlight
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

		PixelShader = compile ps_3_0 PS_DirLight();
	}
}

//**************************************************************************************************
//
//		ピクセルシェーダー
//
//**************************************************************************************************
POUT_LIGHT PS_CharaLight(float2 Tex : TEXCOORD0)
{
    POUT_LIGHT OUT = (POUT_LIGHT) 0;

    clip(tex2D(SpecularBufSamp, Tex).a - 0.5);

    float4 n = tex2D(DecaleSamp, Tex);
    float3 normal = n.rgb; // * 2.0f - 1.0f;
    normal = normalize(normal);
    clip(length(normal) - 0.2f);

	//★ディフューズライト
	{
		//float3 L = normalize(LightVec);
		//ライト率
        float r = max(0, dot(normal, -LightVec));
		//
        OUT.color.rgb = r * LightColor; //★★
        OUT.color.a = 1.0f;
    }
	{
		//座標
        float4 pos_depth = tex2D(PosDepthBufSamp, Tex);
        float depth = pos_depth.w;
        float3 pos = pos_depth.xyz;

		//★スペキュラ
		//視線ベクトル
        float3 E = pos;
        E = normalize(E);

		//ブリン・フォンシェーダー
        float3 H = normalize(-LightVec - E);
        float sp = pow(max(0, dot(H, normal)), 10);

		//スペキュラマップ反映
        float3 sp_tex = tex2D(SpecularBufSamp, Tex);
        sp_tex = 0.4;
        OUT.spec.rgb = sp_tex * sp * LightColor; //★★
        OUT.spec.a = 1.0f;
    }
    return OUT;
}
//------------------------------------------------------
//	テクニック
//------------------------------------------------------
technique charalight
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

        PixelShader = compile ps_3_0 PS_CharaLight();
    }
}


//**************************************************************************************************
//
//		ピクセルシェーダー
//
//**************************************************************************************************
//**************************************************************************************************
//	半球ライティング
//**************************************************************************************************
float3 SkyColor = { 0.48f, 0.5f, 0.5f };
float3 GroundColor = { 0.4f, 0.4f, 0.4f };

inline float4 HemiLight(float3 normal)
{
    float4 color;
    float rate = (normal.y * 0.5f) + 0.5f;
    color.rgb = SkyColor * rate;
    color.rgb += GroundColor * (1 - rate);
    color.a = 1.0f;

    return color;
}

POUT_LIGHT PS_HemiSphereLight(float2 Tex : TEXCOORD0)
{
    POUT_LIGHT OUT = (POUT_LIGHT) 0;

    float4 n = tex2D(DecaleSamp, Tex);
    float3 normal = n.rgb; // * 2.0f - 1.0f;
    normal = normalize(normal);
    clip(length(normal) - 0.2f);

    OUT.color = HemiLight(normal)*1.5;

    return OUT;
}
//------------------------------------------------------
//	テクニック
//------------------------------------------------------
technique hemiSpherelight
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

        PixelShader = compile ps_3_0 PS_HemiSphereLight();
    }
}

//**************************************************************************************************
//
//		ピクセルシェーダー
//
//**************************************************************************************************

float3 PointLightPos = {0,3,0};
float3 PointLightColor = {1.0f,1.0f,1.0f};
float PointLightRange = 5.0f;


POUT_LIGHT PS_PointLight(float2 Tex:TEXCOORD0)
{
	POUT_LIGHT OUT = (POUT_LIGHT)0;


		//★カメラ空間変換
		//テクスチャ座標からスクリーン座標へ
    float depth = tex2D(PosDepthBufSamp, Tex).w;
		float4 screen;
		screen.xy = Tex * 2.0f - 1.0f;
		screen.y = -screen.y;
		screen.z = depth;
		screen.w = 1.0f;
		//スクリーン座標からカメラ空間座標へ
		float4 pos = mul(screen, InvProj);
		pos.xyz /= pos.w;

		//ライトベクトル
    float3 PointLightVec = (float3) pos - PointLightPos;

		float dist = length(PointLightVec);
		PointLightVec = normalize(PointLightVec);


		//法線取得
		float4 n = tex2D(DecaleSamp, Tex);
		float3 normal = n.rgb * 2.0f - 1.0f;
		normal = normalize(normal);


		//減衰量
		float intensity = max(0,1.0f - dist / PointLightRange);


		//ライト計算
		float r = max(0, dot(normal, - PointLightVec));

		//ピクセル色決定
		OUT.color.rgb = r*PointLightColor*intensity;
		OUT.color.a = 1.0f;


		//★スペキュラ
		//視線ベクトル
		float3 E = pos.xyz;
		E = normalize(E);

		//ブリン・フォンシェーダー
		float3 H = normalize(-PointLightVec - E);
		float sp = pow(max(0, dot(H, normal)), 10);

		//スペキュラマップ反映
		float3 sp_tex = tex2D(SpecularBufSamp, Tex);
		OUT.spec.rgb = sp_tex * sp * PointLightColor*intensity;
		OUT.spec.a = 1.0f;
	return OUT;
}
//------------------------------------------------------
//	テクニック
//------------------------------------------------------
technique dif_Pointlight
{
	pass P0
	{
		AlphaBlendEnable = true;
		BlendOp = Add;
		SrcBlend = SrcAlpha;
		DestBlend = One;
		CullMode = None;
		ZEnable = false;

		PixelShader = compile ps_3_0 PS_PointLight();
	}
}


//texture ShadowMap;

//sampler ShadowSamp = sampler_state
//{
//    Texture = <ShadowMap>;
//    MinFilter = POINT;
//    MagFilter = POINT;
//    MipFilter = NONE;

//    BorderColor = 0xFFFFFFFF;
//    AddressU = BORDER;
//    AddressV = BORDER;
//};
//struct VS_SHADOW
//{
//    float4 Pos : POSITION;
//    float4 Color : TEXCOORD0; // 頂点色
//};

////------------------------------------------------------
////		頂点シェーダー
////------------------------------------------------------
//VS_SHADOW VS_ShadowBuf(float4 Pos : POSITION)
//{
//    VS_SHADOW Out;
//	// 座標変換
//    float4x4 mat = mul(TransMatrix, ShadowProjection);

//    Out.Pos = mul(Pos, mat);
//    Out.Color = Out.Pos.z;
//    return Out;
//}

////------------------------------------------------------
////		ピクセルシェーダー
////------------------------------------------------------
//float4 PS_ShadowBuf(VS_SHADOW In) : COLOR
//{
//    return In.Color;
//}

////------------------------------------------------------
////		テクニック
////------------------------------------------------------
//technique ShadowBuf
//{
//    pass Pass0
//    {
//        AlphaBlendEnable = false;
//        ZWriteEnable = true;
//        CullMode = none;
//        VertexShader = compile vs_2_0 VS_ShadowBuf();
//        PixelShader = compile ps_2_0 PS_ShadowBuf();
//    }
//}

////------------------------------------------------------
////		シャドーマップ
////------------------------------------------------------

//texture ShadowMap;
//sampler ShadowSamp = sampler_state
//{
//    Texture = <ShadowMap>;
//    MinFilter = POINT;
//    MagFilter = POINT;
//    MipFilter = NONE;

//    BorderColor = 0xFFFFFFFF;
//    AddressU = BORDER;
//    AddressV = BORDER;
//};

//float AdjustValue = -0.001f;
//float Shadow = 0.4f;

//inline float3 GetShadowTex(float3 Pos)
//{
//    float3 Tex;
//	// テクスチャ座標計算
//    float4 ppp;
//    ppp.xyz = Pos;
//    ppp.w = 1;
//    Tex = mul(ppp, ShadowProjection);

//    Tex.y = -Tex.y;
//    Tex.xy = 0.5f * Tex.xy + 0.5f;

//    return Tex;
//}

//inline float GetShadow(float3 Tex)
//{
//	// シャドウマップから深度を取り出す
//    float d = tex2D(ShadowSamp, Tex.xy).r;
	
//// 影用の減衰率を決める
//    float l = (d < Tex.z + AdjustValue) ? Shadow : 1.0;

//    return l;
//}

//float4 PS_Shadow(float2 Tex : TEXCOORD0) : COLOR
//{
//    float4 OUT = (float4) 0;

//	// 元画像
//    OUT = tex2D(DecaleSamp, Tex);

//	//	カメラ空間変換
//    float depth = tex2D(DepthBufSamp, Tex).r;
//    float4 screen;

//    screen.xy = Tex * 2 - 1;
//    screen.y = -screen.y;

//    screen.z = depth;
//    screen.w = 1;

//	//　スクリーン座標からカメラ座標へ

//    float4 pos = mul(screen, InvProj);
//    pos.xyz /= pos.w;

//	//　影設定
//    pos.w = 1.0f;
//    float4 work = mul(pos, InvmatView);

//    float4 shadowPos = mul(work, ShadowProjection);
//    shadowPos.xyz /= shadowPos.w;
//    shadowPos.y = -shadowPos.y;
//    shadowPos.xy = shadowPos.xy * 0.5f + 0.5f;
	
//    OUT.rgb *= GetShadow(shadowPos.xyz);
//    OUT.a = 1.0f;

//    return OUT;
//}

//technique def_Shadow
//{
//    pass P0
//    {
//        AlphaBlendEnable = false;
		
//        PixelShader = compile ps_2_0 PS_Shadow();
//    }
//}
