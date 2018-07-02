
//**************************************************************************************************
//																									
//		��{�V�F�[�_�[		
//
//**************************************************************************************************

//------------------------------------------------------
//		���֘A
//------------------------------------------------------
float4x4 TransMatrix;	//	�ϊ��s��
float4x4 matView;		//	�ϊ��s��
float4x4 Projection;	//	�ϊ��s��

float3	ViewPos;

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
//		���C�e�B���O
//
//**************************************************************************************************

//**************************************************************************************************
//	�������C�e�B���O
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
//	���s��
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
//	�X�y�L����
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
//	���}�b�v�p
//**************************************************************************************************
texture EnvMap;		//	���e�N�X�`��
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
//		�t���G�t�F�N�g
//
//**************************************************************************************************

//------------------------------------------------------
//	���_�J���[�t�V�F�[�_
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

	// �������C�e�B���O
	Out.Ambient.rgb = HemiLight(N);

	//	���_���[�J�����W�n�Z�o
	float3	vx;
	float3	vy = { 0, 1, 0.001f };
	vx = cross( vy, N );
	vx = normalize( vx );
	vy = cross( vx, N  );
	vy = normalize( vy );

	//	���C�g�x�N�g���␳
	Out.vLight.x = dot(vx, LightDir);
	Out.vLight.y = dot(vy, LightDir);
	Out.vLight.z = dot(N, LightDir);

	// �����x�N�g���␳
    float3 E = (float3) P - ViewPos; // �����x�N�g��
	Out.vE.x = dot(vx, E);
	Out.vE.y = dot(vy, E);
	Out.vE.z = dot(N, E);

	return Out;
}


//**************************************************************************************************
//
//		�X�y�L�����[�`��
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
//	�X�y�L�����v�Z�i�ʏ���L�c�C�j
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
//	���_�V�F�[�_�[
//------------------------------------------------------
VS_HDR VS_Specular( VS_INPUT In )
{
	VS_HDR Out = (VS_HDR)0;

	Out.Pos   = mul(In.Pos, Projection);
	Out.Tex   = In.Tex;

	//	�X�y�L�����v�Z�p���W
	Out.wPos = mul(In.Pos, TransMatrix);
	//	�X�y�L�����v�Z�p�@��
	float3x3 mat = TransMatrix;
	float3 N = mul(In.Normal, mat);
	Out.Normal = normalize(N);

	return Out;
}

//------------------------------------------------------
//	�s�N�Z���V�F�[�_�[	
//------------------------------------------------------
float4 PS_Specular( VS_HDR In) : COLOR
{   
	float4	OUT;

	//	�X�y�L�����v�Z
	float s = HDRSpecular( In.wPos, In.Normal );
	//	
	float4 sp = tex2D( SpecularSamp, In.Tex ) * s;
	//	�s�N�Z���F����
	OUT.rgb = sp*0.5f;
	OUT.a = 1;

	return OUT;
}

//------------------------------------------------------
//	�e�N�j�b�N
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
//		�_�����t���t���G�t�F�N�g
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
//	���_�V�F�[�_
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

	// �������C�e�B���O
	Out.Ambient.rgb = HemiLight(N);

	//	���_���[�J�����W�n�Z�o
	float3	vx;
	float3	vy = { 0, 1, 0.001f };
	vx = cross( vy, N );
	vx = normalize( vx );
	vy = cross( vx, N  );
	vy = normalize( vy );

	//	���C�g�x�N�g���␳
	Out.vLight.x = dot(vx, LightDir);
	Out.vLight.y = dot(vy, LightDir);
	Out.vLight.z = dot(N, LightDir);

	// �����x�N�g���␳
    float3 E = (float3) P - ViewPos; // �����x�N�g��
	Out.vE.x = dot(vx, E);
	Out.vE.y = dot(vy, E);
	Out.vE.z = dot(N, E);

	return Out;
}

//------------------------------------------------------
//		�s�N�Z���V�F�[�_�[	
//------------------------------------------------------
float4 PS_Full( V_FULL In) : COLOR
{   
	float4	OUT;
	float2 Tex = In.Tex;

	//	�p�����b�N�X�f�B�X�v���[�X�����g
	float h = tex2D( HeightSamp, Tex ).r-0.5f;
	float3 E = normalize(In.vE);
	//Tex.x += 0.04f * h * E.x;
	//Tex.y -= 0.04f * h * E.y;

	//	�@���擾
	float3 N = tex2D( NormalSamp, Tex ).xyz * 2.0f - 1.0f;

	//	���C�g�v�Z
	In.vLight   = normalize( In.vLight );
	float3 light = DirLight(In.vLight, N);


	//	�������˃x�N�g��
	float3 R = reflect( -E, N );
	//	�X�y�L�����}�b�v�擾
	float4 sp_tex = tex2D( SpecularSamp, Tex );

	//	���}�b�v
	float3 env = Environment(R) * (1-sp_tex.a);

	//	�s�N�Z���F����
	OUT = In.Color * tex2D( DecaleSamp, Tex );
	OUT.rgb = (OUT.rgb * (light + In.Ambient.rgb) );
	OUT.rgb = OUT.rgb * env + OUT.rgb;

	//	�X�y�L����
	OUT.rgb += pow( max( 0, dot(R, In.vLight) ), 10 ) * sp_tex;

	return OUT;
}

//------------------------------------------------------
//		�����Ȃ�	
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
