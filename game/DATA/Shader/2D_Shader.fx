//********************************************************************
//																									
//		�Q�c�`��p�V�F�[�_�[		
//
//********************************************************************

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

//------------------------------------------------------
//		���_�t�H�[�}�b�g
//------------------------------------------------------
struct VS_2D
{
    float4 Pos		: POSITION;
    float4 Color	: COLOR0;
    float2 Tex		: TEXCOORD0;
};

//********************************************************************
//		�Q�c��{�`��V�F�[�_�[		
//********************************************************************
//------------------------------------------------------
//		���_�V�F�[�_�[	
//------------------------------------------------------
VS_2D VS_Basic( VS_2D In )
{
    return In;
}

//------------------------------------------------------
//		�s�N�Z���V�F�[�_�[	
//------------------------------------------------------
float4 PS_Basic( VS_2D In) : COLOR
{   
	float4	OUT;

	//	�s�N�Z���F����
	OUT = In.Color * tex2D( DecaleSamp, In.Tex );

	return OUT;
}

//------------------------------------------------------
//		�����Ȃ�	
//------------------------------------------------------
technique copy
{
    pass P0
    {
		AlphaBlendEnable = true;
		BlendOp          = Add;
		SrcBlend         = SrcAlpha;
		DestBlend        = InvSrcAlpha;
		CullMode         = None;
		ZEnable          = false;

		VertexShader = compile vs_1_1 VS_Basic();
		PixelShader  = compile ps_2_0 PS_Basic();
    }
}

//------------------------------------------------------
//		���Z����
//------------------------------------------------------
technique add
{
    pass P0
    {
		AlphaBlendEnable = true;
		BlendOp          = Add;
		SrcBlend         = SrcAlpha;
		DestBlend        = One;
		CullMode         = None;
		ZEnable          = false;

		VertexShader = compile vs_1_1 VS_Basic();
		PixelShader  = compile ps_2_0 PS_Basic();
    }
}
//------------------------------------------------------
//		���Z����
//------------------------------------------------------
technique sub
{
    pass P0
    {
		AlphaBlendEnable = true;
		BlendOp          = RevSubtract;
		SrcBlend         = SrcAlpha;
		DestBlend        = One;
		CullMode         = None;
		ZEnable          = false;

		VertexShader = compile vs_1_1 VS_Basic();
		PixelShader  = compile ps_2_0 PS_Basic();
    }
}




//********************************************************************
//		�X�N���[���t�B���^
//********************************************************************
float	contrast = 1.8f;
float	saturate = .6f;
float3	ScreenColor = { 1.2f, 1.1f, 0.8f };
float	brightness = .0f;

//------------------------------------------------------
//		�s�N�Z���V�F�[�_�[	
//------------------------------------------------------
float4 PS_Filter( VS_2D In) : COLOR
{   
	float4	OUT;

	float3	col = In.Color.rgb * tex2D( DecaleSamp, In.Tex );
	//	�P�x����
	col += brightness;
	//	�R���g���X�g����
	col = ((col-0.5f)*contrast) + 0.5f;
	//	�ʓx����
	float	avr = (col.r + col.g + col.b) / 3;
	col = (col-avr) * saturate + avr;
	//	�J���[�o�����X����
	col *= ScreenColor;

	//	�s�N�Z���F����
	OUT.rgb = col;
	OUT.w = In.Color.a;
	
	return OUT;
}

//------------------------------------------------------
//		�t�B���^
//------------------------------------------------------
technique filter
{
    pass P0
    {
		AlphaBlendEnable = true;
		BlendOp          = Add;
		SrcBlend         = SrcAlpha;
		DestBlend        = InvSrcAlpha;
		CullMode         = None;
		ZEnable          = false;

		VertexShader = compile vs_2_0 VS_Basic();
		PixelShader  = compile ps_2_0 PS_Filter();
    }
}

//********************************************************************
//		��ʊE�[�x
//********************************************************************
texture DepthTex;

sampler DepthSamp = sampler_state
{
    Texture = <DepthTex>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Wrap;
    AddressV = Wrap;
};

float	FocusDist  = 10.0f;	//	�œ_����
float	FocusRange = 5.0f;	//	�͈�

//------------------------------------------------------
//		�s�N�Z���V�F�[�_�[	
//------------------------------------------------------
float4 PS_Focus( VS_2D In) : COLOR
{   
	float4	OUT;

	//	�s�N�Z���F����
	OUT = In.Color * tex2D( DecaleSamp, In.Tex );
	
	//	�[�x�E�œ_�E�͈͂����ɓ����x�v�Z
	float	a = tex2D( DepthSamp, In.Tex ).r;
	a = abs(a - FocusDist) / FocusRange;
	OUT.a *= a > 1 ? 1 : a;

	return OUT;
}
//------------------------------------------------------
//
//------------------------------------------------------
technique focus
{
    pass P0
    {
		AlphaBlendEnable = true;
		BlendOp          = Add;
		SrcBlend         = SrcAlpha;
		DestBlend        = InvSrcAlpha;
		CullMode         = None;
		ZEnable          = false;

		PixelShader  = compile ps_2_0 PS_Focus();
    }
}
