//**************************************************************************************************
//																									
//		�V�F�[�_�[		
//
//**************************************************************************************************

//------------------------------------------------------
//		���֘A
//------------------------------------------------------
float4x4 TransMatrix;	//	�ϊ��s��
float4x4 matView;		//	�ϊ��s��
float4x4 Projection;	//	�ϊ��s��

float3	ViewPos;
float Mask;

//------------------------------------------------------
//		�e�N�X�`���T���v���[	
//------------------------------------------------------
texture Texture;	//	�f�J�[���e�N�X�`��
sampler DecaleSamp = sampler_state
{
	Texture = <Texture>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;

	AddressU = Wrap;
	AddressV = Wrap;
};

texture NormalMap;	//	�@���}�b�v�e�N�X�`��
sampler NormalSamp = sampler_state
{
	Texture = <NormalMap>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;

	AddressU = Wrap;
	AddressV = Wrap;
};

texture HeightMap;		//	�����}�b�v�e�N�X�`��
sampler HeightSamp = sampler_state
{
	Texture = <HeightMap>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;

	AddressU = Wrap;
	AddressV = Wrap;
};

texture SpecularMap;	//	�X�y�L�����}�b�v�e�N�X�`��
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
//		���_�t�H�[�}�b�g
//**************************************************************************************************
struct VS_OUTPUT
{
	float4 Pos		: POSITION;
	float4 Color	: COLOR0;
	float2 Tex		: TEXCOORD0;
	float4 wPos		: TEXCOORD1;

	float3 T		: TEXCOORD2;//X��
	float3 B		: TEXCOORD3;//Y��
	float3 N		: TEXCOORD4;//Z��
	
};

struct VS_INPUT
{
	float4 Pos    : POSITION;
	float3 Normal : NORMAL;
	float4 Color  : COLOR0;
	float2 Tex	  : TEXCOORD0;
};

struct PS_OUTPUT
{
	float4 color	: COLOR;
	float4 spec		: COLOR1;
	float4 pos_depth: COLOR2;
	float4 normal	: COLOR3;
};

//**************************************************************************************************
//
//		���_�V�F�[�_�[
//
//**************************************************************************************************


VS_OUTPUT VS_Deferred(VS_INPUT In)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;

	Out.Pos = mul(In.Pos, Projection);
	Out.Tex = In.Tex;
	Out.Color = 1.0f;

    Out.wPos = mul(In.Pos, TransMatrix);

	//�J������ԍ��W�n
	float3x3 mat = (float3x3)mul(TransMatrix, matView);
    mat = TransMatrix;
	Out.N = mul(In.Normal, mat);
	Out.N = normalize(Out.N);//Y��
	float3 vy = { 0.0f, 1.0f, 0.001f };
	Out.T = cross(vy, Out.N);
	Out.T = normalize(Out.T);//X��
	Out.B = cross(Out.N, Out.T);
	Out.B = normalize(Out.B);//Z��


	return Out;
}
//**************************************************************************************************
//
//		�s�N�Z���V�F�[�_�[
//
//**************************************************************************************************


PS_OUTPUT PS_Deferred(VS_OUTPUT In)
{
	PS_OUTPUT	OUT;

	float2 Tex = In.Tex;

	//	�f�B�t���[�Y�F
	OUT.color =tex2D(DecaleSamp, Tex);

	//	�X�y�L����
	OUT.spec = tex2D(SpecularSamp, Tex);
	OUT.spec.a = Mask;

    //  ���W
    OUT.pos_depth.rgb = In.wPos.xyz;
	//	�[�x
    OUT.pos_depth.a = In.wPos.z / In.wPos.w;

	// ���_��ԁ[���J�������
	float3x3 ToView;
	ToView[0] = normalize(In.T);
	ToView[1] = normalize(In.B);
	ToView[2] = normalize(In.N);
	// �@���ϊ�
	float3 N = tex2D(NormalSamp, Tex).xyz - 0.5f;
    N = float3(0, 1, 0);
	float3 normal = normalize(mul(N, ToView));
    normal = In.N;
	//normal = normal * 0.5f + 0.5f;
	// �J������Ԗ@��
    OUT.normal.rgb = normal;
	OUT.normal.a = 1.0f;


	return OUT;
}
//------------------------------------------------------
//	�e�N�j�b�N
//------------------------------------------------------
technique deferred
{
	pass P0
	{
		AlphaBlendEnable = false;
		BlendOp = Add;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
        ZEnable = true;
		ZWriteEnable = true;

		VertexShader = compile vs_3_0 VS_Deferred();
		PixelShader = compile ps_3_0 PS_Deferred();
	}
}
