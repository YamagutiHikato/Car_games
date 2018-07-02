
//**************************************************************************************************
//																									
//		�V�F�[�_�[���C�g	
//
//**************************************************************************************************

//------------------------------------------------------
//		�e�N�X�`���T���v���[	
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

texture PosDepthBuf;	//�J������Ԑ[�x
sampler PosDepthBufSamp = sampler_state
{
    Texture = <PosDepthBuf>;
	MinFilter = POINT;
	MagFilter = POINT;
	MipFilter = NONE;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

texture SpecularBuf;	//�J������Ԑ[�x
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
//		�O���[�o���ϐ�
//
//**************************************************************************************************
float3 LightVec = { 0.7f,-0.7f,0 };
float3 LightColor = { 1.0f,1.0f,1.0f };

float4x4 InvProj;	//Projection�̋t�s��
//--------------------------------
//	�s�N�Z���t�H�[�}�b�g
//--------------------------------
struct POUT_LIGHT
{
	float4 color	:COLOR0;
	float4 spec		:COLOR1;
};

//**************************************************************************************************
//
//		�s�N�Z���V�F�[�_�[
//
//**************************************************************************************************
POUT_LIGHT PS_DirLight(float2 Tex:TEXCOORD0)
{
	POUT_LIGHT OUT = (POUT_LIGHT)0;

	float4 n = tex2D(DecaleSamp, Tex);
    float3 normal = n.rgb;// * 2.0f - 1.0f;
	normal = normalize(normal);
    clip(length(normal) - 0.2f);

	//���f�B�t���[�Y���C�g
	{
		//float3 L = normalize(LightVec);
		//���C�g��
		float r = max(0, dot(normal, -LightVec));
		//
		OUT.color.rgb = r * LightColor; //����
		OUT.color.a = 1.0f;
	}
	{
		//���W
        float4 pos_depth = tex2D(PosDepthBufSamp, Tex);
        float  depth = pos_depth.w;
        float3 pos = pos_depth.xyz;

		//���X�y�L����
		//�����x�N�g��
		float3 E = pos;
		E = normalize(E);

		//�u�����E�t�H���V�F�[�_�[
		float3 H = normalize(-LightVec - E);
		float sp = pow(max(0, dot(H, normal)), 10);

		//�X�y�L�����}�b�v���f
		float3 sp_tex = tex2D(SpecularBufSamp, Tex);
        sp_tex = 0.2;
		OUT.spec.rgb = sp_tex*sp*LightColor;//����
		OUT.spec.a = 1.0f;
	}
	return OUT;
}
//------------------------------------------------------
//	�e�N�j�b�N
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
//		�s�N�Z���V�F�[�_�[
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

	//���f�B�t���[�Y���C�g
	{
		//float3 L = normalize(LightVec);
		//���C�g��
        float r = max(0, dot(normal, -LightVec));
		//
        OUT.color.rgb = r * LightColor; //����
        OUT.color.a = 1.0f;
    }
	{
		//���W
        float4 pos_depth = tex2D(PosDepthBufSamp, Tex);
        float depth = pos_depth.w;
        float3 pos = pos_depth.xyz;

		//���X�y�L����
		//�����x�N�g��
        float3 E = pos;
        E = normalize(E);

		//�u�����E�t�H���V�F�[�_�[
        float3 H = normalize(-LightVec - E);
        float sp = pow(max(0, dot(H, normal)), 10);

		//�X�y�L�����}�b�v���f
        float3 sp_tex = tex2D(SpecularBufSamp, Tex);
        sp_tex = 0.4;
        OUT.spec.rgb = sp_tex * sp * LightColor; //����
        OUT.spec.a = 1.0f;
    }
    return OUT;
}
//------------------------------------------------------
//	�e�N�j�b�N
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
//		�s�N�Z���V�F�[�_�[
//
//**************************************************************************************************
//**************************************************************************************************
//	�������C�e�B���O
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
//	�e�N�j�b�N
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
//		�s�N�Z���V�F�[�_�[
//
//**************************************************************************************************

float3 PointLightPos = {0,3,0};
float3 PointLightColor = {1.0f,1.0f,1.0f};
float PointLightRange = 5.0f;


POUT_LIGHT PS_PointLight(float2 Tex:TEXCOORD0)
{
	POUT_LIGHT OUT = (POUT_LIGHT)0;


		//���J������ԕϊ�
		//�e�N�X�`�����W����X�N���[�����W��
    float depth = tex2D(PosDepthBufSamp, Tex).w;
		float4 screen;
		screen.xy = Tex * 2.0f - 1.0f;
		screen.y = -screen.y;
		screen.z = depth;
		screen.w = 1.0f;
		//�X�N���[�����W����J������ԍ��W��
		float4 pos = mul(screen, InvProj);
		pos.xyz /= pos.w;

		//���C�g�x�N�g��
    float3 PointLightVec = (float3) pos - PointLightPos;

		float dist = length(PointLightVec);
		PointLightVec = normalize(PointLightVec);


		//�@���擾
		float4 n = tex2D(DecaleSamp, Tex);
		float3 normal = n.rgb * 2.0f - 1.0f;
		normal = normalize(normal);


		//������
		float intensity = max(0,1.0f - dist / PointLightRange);


		//���C�g�v�Z
		float r = max(0, dot(normal, - PointLightVec));

		//�s�N�Z���F����
		OUT.color.rgb = r*PointLightColor*intensity;
		OUT.color.a = 1.0f;


		//���X�y�L����
		//�����x�N�g��
		float3 E = pos.xyz;
		E = normalize(E);

		//�u�����E�t�H���V�F�[�_�[
		float3 H = normalize(-PointLightVec - E);
		float sp = pow(max(0, dot(H, normal)), 10);

		//�X�y�L�����}�b�v���f
		float3 sp_tex = tex2D(SpecularBufSamp, Tex);
		OUT.spec.rgb = sp_tex * sp * PointLightColor*intensity;
		OUT.spec.a = 1.0f;
	return OUT;
}
//------------------------------------------------------
//	�e�N�j�b�N
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
//    float4 Color : TEXCOORD0; // ���_�F
//};

////------------------------------------------------------
////		���_�V�F�[�_�[
////------------------------------------------------------
//VS_SHADOW VS_ShadowBuf(float4 Pos : POSITION)
//{
//    VS_SHADOW Out;
//	// ���W�ϊ�
//    float4x4 mat = mul(TransMatrix, ShadowProjection);

//    Out.Pos = mul(Pos, mat);
//    Out.Color = Out.Pos.z;
//    return Out;
//}

////------------------------------------------------------
////		�s�N�Z���V�F�[�_�[
////------------------------------------------------------
//float4 PS_ShadowBuf(VS_SHADOW In) : COLOR
//{
//    return In.Color;
//}

////------------------------------------------------------
////		�e�N�j�b�N
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
////		�V���h�[�}�b�v
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
//	// �e�N�X�`�����W�v�Z
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
//	// �V���h�E�}�b�v����[�x�����o��
//    float d = tex2D(ShadowSamp, Tex.xy).r;
	
//// �e�p�̌����������߂�
//    float l = (d < Tex.z + AdjustValue) ? Shadow : 1.0;

//    return l;
//}

//float4 PS_Shadow(float2 Tex : TEXCOORD0) : COLOR
//{
//    float4 OUT = (float4) 0;

//	// ���摜
//    OUT = tex2D(DecaleSamp, Tex);

//	//	�J������ԕϊ�
//    float depth = tex2D(DepthBufSamp, Tex).r;
//    float4 screen;

//    screen.xy = Tex * 2 - 1;
//    screen.y = -screen.y;

//    screen.z = depth;
//    screen.w = 1;

//	//�@�X�N���[�����W����J�������W��

//    float4 pos = mul(screen, InvProj);
//    pos.xyz /= pos.w;

//	//�@�e�ݒ�
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
