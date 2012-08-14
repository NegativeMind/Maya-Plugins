

#include "CookTorranceNode.h"


MTypeId CookTorranceNode::id( 0x7ffe );//�B���ID0x81002

//��ʃp�����[�^
MObject CookTorranceNode::aColor;
MObject CookTorranceNode::aTranslucenceCoeff;
MObject CookTorranceNode::aIncandescence;

//�o�͂���F
MObject CookTorranceNode::aOutColor;

//Diffuse���x
MObject CookTorranceNode::aDiffuseReflectivity;

//specular�p�����[�^
MObject CookTorranceNode::aSpecularity;//���x
MObject CookTorranceNode::aRefractivityRed;//���ܗ�Red
MObject CookTorranceNode::aRefractivityGreen;//���ܗ�Green
MObject CookTorranceNode::aRefractivityBlue;//���ܗ�Blue
MObject CookTorranceNode::aRoughness;//�ʂ̑e��

//Shading�p�p�����[�^
MObject CookTorranceNode::aPointCamera;
MObject CookTorranceNode::aNormalCamera;

//���C�g�f�[�^
MObject CookTorranceNode::aLightData;
MObject CookTorranceNode::aLightDirection;
MObject CookTorranceNode::aLightIntensity;

//���C�e�B���O�t���O
MObject CookTorranceNode::aLightAmbient;
MObject CookTorranceNode::aLightDiffuse;
MObject CookTorranceNode::aLightSpecular;

//Shadow�f�[�^
MObject CookTorranceNode::aLightShadowFraction;
MObject CookTorranceNode::aPreShadowIntensity;
MObject CookTorranceNode::aLightBlindData;

//RayTrace�p�p�����[�^
MObject CookTorranceNode::aRayOrigin;
MObject CookTorranceNode::aRayDirection;
MObject CookTorranceNode::aObjectId;
MObject CookTorranceNode::aRaySampler;
MObject CookTorranceNode::aRayDepth;

//RayTrace���x
MObject CookTorranceNode::aReflectGain;

//��������p�ʖ@��
MObject CookTorranceNode::aTriangleNormalCamera;




void CookTorranceNode::postConstructor( )
{
	setMPSafe(true);
}

//�R���X�g���N�^
CookTorranceNode::CookTorranceNode() {}
//�f�X�g���N�^
CookTorranceNode::~CookTorranceNode() {}

//�N���G�[�^
void* CookTorranceNode::creator()
{
	return new CookTorranceNode();
}


//�A�g���r���[�g�ݒ�p�}�N��
//Input�p
#define MAKE_INPUT(attr)	\
	CHECK_MSTATUS(attr.setKeyable(true));	\
	CHECK_MSTATUS(attr.setStorable(true));	\
	CHECK_MSTATUS(attr.setReadable(true));	\
	CHECK_MSTATUS(attr.setWritable(true));

//Output�p
#define MAKE_OUTPUT(attr)	\
	CHECK_MSTATUS(attr.setKeyable(false));	\
	CHECK_MSTATUS(attr.setStorable(false));	\
	CHECK_MSTATUS(attr.setReadable(true));	\
	CHECK_MSTATUS(attr.setWritable(false));


MStatus CookTorranceNode::initialize()		
{
	
    MFnNumericAttribute nAttr; 
    MFnLightDataAttribute lAttr;

    aTranslucenceCoeff = nAttr.create("translucenceCoeff", "tc",MFnNumericData::kFloat);
    MAKE_INPUT(nAttr);

    aDiffuseReflectivity = nAttr.create("diffuseReflectivity", "drfl",MFnNumericData::kFloat);
    MAKE_INPUT(nAttr);
    CHECK_MSTATUS ( nAttr.setDefault(0.8f) );

    aColor = nAttr.createColor( "color", "c" );
    MAKE_INPUT(nAttr);
    CHECK_MSTATUS ( nAttr.setDefault(0.5f, 0.5f, 0.5f) );

    aIncandescence = nAttr.createColor( "incandescence", "ic" );
    MAKE_INPUT(nAttr);

    aOutColor = nAttr.createColor( "outColor", "oc" );
    MAKE_OUTPUT(nAttr);

    aPointCamera = nAttr.createPoint( "pointCamera", "pc" );
    MAKE_INPUT(nAttr);
    CHECK_MSTATUS ( nAttr.setDefault(1.0f, 1.0f, 1.0f) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );

	//�ȉ��Aspecular�p�����[�^�̃A�g���r���[�g�ݒ�
    aSpecularity = nAttr.create( "specularity", "spc", MFnNumericData::kFloat);
    MAKE_INPUT(nAttr);
    CHECK_MSTATUS ( nAttr.setMin(0.0f) );
    CHECK_MSTATUS ( nAttr.setMax(1.0f) ) ;
    CHECK_MSTATUS ( nAttr.setDefault(0.5f) );

	//�ʂ̑e��
	aRoughness = nAttr.create( "roughness", "m", MFnNumericData::kFloat);
    MAKE_INPUT(nAttr);
    CHECK_MSTATUS ( nAttr.setMin(0.0f) );
    CHECK_MSTATUS ( nAttr.setMax(1.0f) );
    CHECK_MSTATUS ( nAttr.setDefault(0.5f) );

	//�ȉ��ARGB���ܗ�
	//Red
	aRefractivityRed = nAttr.create( "refractivityR", "rred", MFnNumericData::kFloat);
    MAKE_INPUT(nAttr);
    CHECK_MSTATUS ( nAttr.setMin(0.0f) );
    CHECK_MSTATUS ( nAttr.setMax(10.0f) );
    CHECK_MSTATUS ( nAttr.setDefault(1.0f) );

	//Green
	aRefractivityGreen = nAttr.create( "refractivityG", "rgreen", MFnNumericData::kFloat);
    MAKE_INPUT(nAttr);
    CHECK_MSTATUS ( nAttr.setMin(0.0f) );
    CHECK_MSTATUS ( nAttr.setMax(10.0f) );
    CHECK_MSTATUS ( nAttr.setDefault(1.0f) );

	//Blue
	aRefractivityBlue = nAttr.create( "refractivityB", "rblue", MFnNumericData::kFloat);
    MAKE_INPUT(nAttr);
    CHECK_MSTATUS ( nAttr.setMin(0.0f) );
    CHECK_MSTATUS ( nAttr.setMax(10.0f) );
    CHECK_MSTATUS ( nAttr.setDefault(1.0f) );

	//RayTrace���x
    aReflectGain = nAttr.create( "reflectionGain", "rg", MFnNumericData::kFloat);
    MAKE_INPUT(nAttr);
    CHECK_MSTATUS ( nAttr.setMin(0.0f) );
    CHECK_MSTATUS ( nAttr.setMax(1.0f) );
    CHECK_MSTATUS ( nAttr.setDefault(0.0f) );


    aNormalCamera = nAttr.createPoint( "normalCamera", "n" );
    MAKE_INPUT(nAttr);
    CHECK_MSTATUS ( nAttr.setDefault(1.0f, 1.0f, 1.0f) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );

    aTriangleNormalCamera = nAttr.createPoint( "triangleNormalCamera", "tn" );
    MAKE_INPUT(nAttr);
    CHECK_MSTATUS ( nAttr.setDefault(1.0f, 1.0f, 1.0f));
    CHECK_MSTATUS ( nAttr.setHidden(true));

    aLightDirection = nAttr.createPoint( "lightDirection", "ld" );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS ( nAttr.setDefault(1.0f, 1.0f, 1.0f) );

    aLightIntensity = nAttr.createColor( "lightIntensity", "li" );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS ( nAttr.setDefault(1.0f, 1.0f, 1.0f) );

    aLightAmbient = nAttr.create( "lightAmbient", "la",MFnNumericData::kBoolean);
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );

    aLightDiffuse = nAttr.create( "lightDiffuse", "ldf", MFnNumericData::kBoolean);
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );

    aLightSpecular = nAttr.create( "lightSpecular", "ls",MFnNumericData::kBoolean);
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );

    aLightShadowFraction = nAttr.create("lightShadowFraction", "lsf",MFnNumericData::kFloat);
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );

    aPreShadowIntensity = nAttr.create("preShadowIntensity", "psi",MFnNumericData::kFloat);
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );

    aLightBlindData = nAttr.createAddr("lightBlindData", "lbld");
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );

    aLightData = lAttr.create( "lightDataArray", "ltd", 
                               aLightDirection, aLightIntensity, aLightAmbient,
                               aLightDiffuse, aLightSpecular, 
                                                           aLightShadowFraction,
                               aPreShadowIntensity,
                               aLightBlindData);
    CHECK_MSTATUS ( lAttr.setArray(true) );
    CHECK_MSTATUS ( lAttr.setStorable(false) );
    CHECK_MSTATUS ( lAttr.setHidden(true) );
    CHECK_MSTATUS ( lAttr.setDefault(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, true, true,
                                         false, 0.0f, 1.0f, NULL) );

        // rayOrigin
        MObject RayX = nAttr.create( "rayOx", "rxo", MFnNumericData::kFloat, 0.0 );
        MObject RayY = nAttr.create( "rayOy", "ryo", MFnNumericData::kFloat, 0.0 );
        MObject RayZ = nAttr.create( "rayOz", "rzo", MFnNumericData::kFloat, 0.0 );
        aRayOrigin = nAttr.create( "rayOrigin", "rog", RayX, RayY, RayZ );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(false) );

        // rayDirection 
        RayX = nAttr.create( "rayDirectionX", "rdx", MFnNumericData::kFloat, 1.0 );
        RayY = nAttr.create( "rayDirectionY", "rdy", MFnNumericData::kFloat, 0.0 );
        RayZ = nAttr.create( "rayDirectionZ", "rdz", MFnNumericData::kFloat, 0.0 );
        aRayDirection = nAttr.create( "rayDirection", "rad", RayX, RayY, RayZ );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(false) );

        // objectId
        aObjectId = nAttr.createAddr( "objectId", "oi" );
    CHECK_MSTATUS ( nAttr.setStorable(false) ); 
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(false) );

        // raySampler
        aRaySampler = nAttr.createAddr("raySampler", "rtr");
    CHECK_MSTATUS ( nAttr.setStorable(false));
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(false) );

        // rayDepth
        aRayDepth = nAttr.create( "rayDepth", "rd", MFnNumericData::kShort, 0.0 );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS  (nAttr.setHidden(true) ) ;
    CHECK_MSTATUS ( nAttr.setReadable(false) );



    CHECK_MSTATUS ( addAttribute(aTranslucenceCoeff) );
    CHECK_MSTATUS ( addAttribute(aDiffuseReflectivity) );
    CHECK_MSTATUS ( addAttribute(aColor) );
    CHECK_MSTATUS ( addAttribute(aIncandescence) );
    CHECK_MSTATUS ( addAttribute(aPointCamera) );
    CHECK_MSTATUS ( addAttribute(aNormalCamera) );
    CHECK_MSTATUS ( addAttribute(aTriangleNormalCamera) );

    CHECK_MSTATUS ( addAttribute(aLightData) );


    CHECK_MSTATUS ( addAttribute(aSpecularity) );
	CHECK_MSTATUS ( addAttribute(aRoughness) );
	CHECK_MSTATUS ( addAttribute(aRefractivityRed) );
	CHECK_MSTATUS ( addAttribute(aRefractivityGreen) );
	CHECK_MSTATUS ( addAttribute(aRefractivityBlue) );

    CHECK_MSTATUS ( addAttribute(aOutColor) );

        CHECK_MSTATUS ( addAttribute(aRayOrigin) );
        CHECK_MSTATUS ( addAttribute(aRayDirection) );
        CHECK_MSTATUS ( addAttribute(aObjectId) );
        CHECK_MSTATUS ( addAttribute(aRaySampler) );
        CHECK_MSTATUS ( addAttribute(aRayDepth) );
    CHECK_MSTATUS ( addAttribute(aReflectGain) );

    CHECK_MSTATUS ( attributeAffects (aTranslucenceCoeff, aOutColor));
    CHECK_MSTATUS ( attributeAffects (aDiffuseReflectivity, aOutColor));

    CHECK_MSTATUS ( attributeAffects (aLightIntensity, aOutColor));
    CHECK_MSTATUS ( attributeAffects (aIncandescence, aOutColor));
    CHECK_MSTATUS ( attributeAffects (aPointCamera, aOutColor));
    CHECK_MSTATUS ( attributeAffects (aNormalCamera, aOutColor));
    CHECK_MSTATUS ( attributeAffects (aTriangleNormalCamera, aOutColor));
    CHECK_MSTATUS ( attributeAffects (aLightData, aOutColor));
    CHECK_MSTATUS ( attributeAffects (aLightAmbient, aOutColor));
    CHECK_MSTATUS ( attributeAffects (aLightSpecular, aOutColor));
    CHECK_MSTATUS ( attributeAffects (aLightDiffuse, aOutColor));
    CHECK_MSTATUS ( attributeAffects (aLightDirection, aOutColor));
    CHECK_MSTATUS ( attributeAffects (aLightShadowFraction, aOutColor));
    CHECK_MSTATUS ( attributeAffects (aPreShadowIntensity, aOutColor));
    CHECK_MSTATUS ( attributeAffects (aLightBlindData, aOutColor));

    
    CHECK_MSTATUS ( attributeAffects (aSpecularity, aOutColor));
	CHECK_MSTATUS ( attributeAffects (aRoughness, aOutColor));
	CHECK_MSTATUS ( attributeAffects (aRefractivityRed, aOutColor));
	CHECK_MSTATUS ( attributeAffects (aRefractivityGreen, aOutColor));
	CHECK_MSTATUS ( attributeAffects (aRefractivityBlue, aOutColor));

    CHECK_MSTATUS ( attributeAffects (aColor, aOutColor));

        CHECK_MSTATUS ( attributeAffects (aRayOrigin,aOutColor));
        CHECK_MSTATUS ( attributeAffects (aRayDirection,aOutColor));
        CHECK_MSTATUS ( attributeAffects (aObjectId,aOutColor));
        CHECK_MSTATUS ( attributeAffects (aRaySampler,aOutColor));
        CHECK_MSTATUS ( attributeAffects (aRayDepth,aOutColor));
    CHECK_MSTATUS ( attributeAffects (aReflectGain,aOutColor) );

    return MS::kSuccess;
	
}

//���̃m�[�h�̏���
MStatus CookTorranceNode::compute( const MPlug& plug, MDataBlock& block )
{
	//��O����
	if ((plug != aOutColor) && (plug.parent() != aOutColor)){
                return MS::kUnknownParameter;
	}

	//�o�̓J���[��ێ�����ϐ�
    MFloatVector resultColor(0.0,0.0,0.0);

    // get sample surface shading parameters(�����x�N�g���Ɩ@���x�N�g�����擾)
    MFloatVector& surfaceNormal = block.inputValue( aNormalCamera ).asFloatVector();
    MFloatVector& cameraPosition = block.inputValue( aPointCamera ).asFloatVector();

        // use for raytracing api enhancement below(RayTrace�p�̃p�����[�^���擾)
        MFloatVector point = cameraPosition;
        MFloatVector normal = surfaceNormal;

		//�����E�@���x�N�g���𐳋K��
		CHECK_MSTATUS( cameraPosition.normalize() );
		CHECK_MSTATUS( surfaceNormal.normalize() );

	//Diffuse�p�p�����[�^���擾
    MFloatVector& surfaceColor  = block.inputValue( aColor ).asFloatVector();
    MFloatVector& incandescence = block.inputValue( aIncandescence ).asFloatVector();
    float diffuseReflectivity = block.inputValue( aDiffuseReflectivity ).asFloat();
    // float translucenceCoeff   = block.inputValue( aTranslucenceCoeff ).asFloat();


        // User-defined Reflection Color Gain(RayTrace�p�̔��ˋ��x)
        float reflectGain = block.inputValue( aReflectGain ).asFloat();
  
    //CookTorrance shading attributes(specular�p�p���[���[�^�̎擾)
		float spec = block.inputValue( aSpecularity ).asFloat();//���x
		float roughness = block.inputValue( aRoughness ).asFloat();//�ʂ̑e��
		float refractivityR = block.inputValue( aRefractivityRed ).asFloat();//R���ܗ�
		float refractivityG = block.inputValue( aRefractivityGreen ).asFloat();//G���ܗ�
		float refractivityB = block.inputValue( aRefractivityBlue ).asFloat();//B���ܗ�

    

	//RGB���Ƃ�specular,diffuse�̒l���i�[����ϐ���S��0.0�ŏ�����
    float specularR, specularG, specularB;
    float diffuseR, diffuseG, diffuseB;
    diffuseR = diffuseG = diffuseB = specularR = specularG = specularB = 0.0;

    // get light list(���C�g�����擾)
    MArrayDataHandle lightData = block.inputArrayValue( aLightData );
    int numLights = lightData.elementCount();
    
    // iterate through light list and get ambient/diffuse values(���C�g�̐��������[�v���āAambient��diffuse���擾)
    for( int count=1; count <= numLights; count++ )
    {
		
        MDataHandle currentLight = lightData.inputValue();//���݂̃��C�g
        MFloatVector& lightIntensity = currentLight.child(aLightIntensity).asFloatVector();//���C�g�̋���
        
        // Find the blind data(�Օ������擾)
        void*& blindData = currentLight.child( aLightBlindData ).asAddr();
     
		//���C�g�x�N�g�����i�[
        MFloatVector& lightDirection = currentLight.child(aLightDirection).asFloatVector();

		//���C�g�̌�����\���ϐ�
		float lightAttenuation = 1.0;       

		//���C�g�x�N�g���Ɩ@���x�N�g���̓���
		float cosln = lightDirection * surfaceNormal;

		//�v�Z�p�Ƀ��C�g�x�N�g�����i�[����ϐ�
		MFloatVector specLightDirection;

		//�����x�N�g���̐��K��
        CHECK_MSTATUS( cameraPosition.normalize() );

				//�΂��`
				float PI = (float)3.14159265;


		if (blindData == NULL){//blindData���Ȃ��ꍇ(��O����)

			specLightDirection = lightDirection;

		}else{//blindData������ꍇ

			//���C�g�Ɩ@���̓���
			cosln = MRenderUtil::diffuseReflectance( blindData, lightDirection, point, surfaceNormal, true );
			specLightDirection =  MRenderUtil::maximumSpecularReflection( blindData,lightDirection, point, surfaceNormal, cameraPosition );

			 //���C�g�̌���
			 lightAttenuation = MRenderUtil::lightAttenuation( blindData, point, surfaceNormal, false );   

		}

		 //ambient����
        if( currentLight.child(aLightAmbient).asBool() ) {//���C�g��ambient���ݒ肳��Ă���ΑS�̂Ƀ��C�g�̋��x�����Z
            diffuseR += lightIntensity[0];
            diffuseG += lightIntensity[1];
            diffuseB += lightIntensity[2];
        }

		//�������甽�ˌv�Z
		if(cosln > 0.0f){//�����Ɩʂ��Ă���ꍇ�̂݌v�Z

			//Diffuse���ˌv�Z
			if(currentLight.child(aLightDiffuse).asBool() ){//���C�g��diffuse���ݒ肳��Ă���ꍇ

				//Diffuse�v�Z����щ��Z(���C�g�̌����������A�΂Ŋ���)
				diffuseR += lightIntensity[0] * ( cosln * diffuseReflectivity ) * lightAttenuation / PI;
				diffuseG += lightIntensity[1] * ( cosln * diffuseReflectivity ) * lightAttenuation / PI;
				diffuseB += lightIntensity[2] * ( cosln * diffuseReflectivity ) * lightAttenuation / PI;
		}

			//specular���ˌv�Z
			if ( currentLight.child(aLightSpecular).asBool() ){//���C�g��specular���ݒ肳��Ă���ꍇ

									//�e��x�N�g���̐��K��
									CHECK_MSTATUS( cameraPosition.normalize() );
									CHECK_MSTATUS( specLightDirection.normalize() );
									CHECK_MSTATUS( surfaceNormal.normalize() );


									//�����x�N�g���Ǝ����x�N�g���̃n�[�t�x�N�g��
									MFloatVector HV = specLightDirection - cameraPosition;
									 CHECK_MSTATUS( HV.normalize() );

									 //�@���x�N�g���Ǝ����x�N�g���̓���
									 float NV = (surfaceNormal) * (-cameraPosition);

									 //�����ؕЂ�\���U���֐�D(BeckMann���z)
									 float D = beckMann(HV, surfaceNormal, roughness);

									 //localOcclusion G(�􉽌���)
									 float G = localOcclusion(HV, surfaceNormal, -cameraPosition, specLightDirection);

									 //Fresnel����(RGB����)
									 float FR = Fresnel(HV, -cameraPosition, refractivityR) / PI;
									 float FG = Fresnel(HV, -cameraPosition, refractivityG) / PI;
									 float FB = Fresnel(HV, -cameraPosition, refractivityB) / PI;

									 //���ˋ��x�v�Z(CookTorrance����F���������Ă���)
									 float s = (D * G / NV) * spec;

									 //specular�l�̉��Z
									specularR += lightIntensity[0] * s * FR * lightAttenuation; 
                                    specularG += lightIntensity[1] * s * FG * lightAttenuation; 
                                    specularB += lightIntensity[2] * s * FB * lightAttenuation; 

			}
		}
		

       if( !lightData.next() ) break;
    }

    // factor incident light with surface color and add incandescence���Ȕ����l���������킹�Č��ʂɊi�[
		resultColor[0] = ( diffuseR * surfaceColor[0] ) + specularR + incandescence[0];
		resultColor[1] = ( diffuseG * surfaceColor[1] ) + specularG + incandescence[1];
		resultColor[2] = ( diffuseB * surfaceColor[2] ) + specularB + incandescence[2];


        // add the reflection color
        if (reflectGain > 0.0) {//RayTrace�p����(reflectGain��0�ȏゾ�����ꍇ)

                MStatus status;

				//RayTrace�Ɏg���e��l��Data block����擾����

                // required attributes for using raytracer
                // origin, direction, sampler, depth, and object id.
               
				//�`��_�̈ʒu�x�N�g�����擾
                MDataHandle originH = block.inputValue( aRayOrigin, &status);
                MFloatVector origin = originH.asFloatVector();

				//�����x�N�g�����擾
                MDataHandle directionH = block.inputValue( aRayDirection, &status);
                MFloatVector direction = directionH.asFloatVector();

				//
                MDataHandle samplerH = block.inputValue( aRaySampler, &status);
                void*& samplerPtr = samplerH.asAddr();

				//���C�̐[�����擾
                MDataHandle depthH = block.inputValue( aRayDepth, &status);
                short depth = depthH.asShort();

				//�I�u�W�F�N�g��ID���擾
                MDataHandle objH = block.inputValue( aObjectId, &status);
                void*& objId = objH.asAddr();

                MFloatVector reflectColor;//���ʔ��˂̐F���i�[����ϐ�
                MFloatVector reflectTransparency;


				//�O�p�`�̖@�����擾
                MFloatVector& triangleNormal = block.inputValue( aTriangleNormalCamera ).asFloatVector();


                // compute reflected ray
                MFloatVector l = -direction;
                float dot = l * normal;
                if( dot < 0.0 ) dot = -dot;
                MFloatVector refVector = 2 * normal * dot - l;  // reflection ray���˃x�N�g�������߂�
                float dotRef = refVector * triangleNormal;
                if( dotRef < 0.0 ) {
                    const float s = 0.01f;
                        MFloatVector mVec = refVector - dotRef * triangleNormal;
                        mVec.normalize();
                        refVector = mVec + s * triangleNormal;
                }

				//���˃x�N�g���̐��K��
                CHECK_MSTATUS ( refVector.normalize() );

				//���C�g���[�V���O���s���֐�(?)
                status = MRenderUtil::raytrace(
                                point,          //  origin
                                refVector,  //  direction
                                objId,          //  object id
                                samplerPtr, //  sampler info
                                depth,          //  ray depth���C�̐[��(�񐔁H)
                                reflectColor,   // output color and transp
                                reflectTransparency);


				//�����A���C�̑��d�T���v�����O���K�v�Ȃ炱���Ń��[�v�������ĉ��Z����

                // add in the reflection color���ːF�𔽎˗��Ƃ����Č��ʂɉ��Z
                resultColor[0] += reflectGain * (reflectColor[0]);
                resultColor[1] += reflectGain * (reflectColor[1]);
                resultColor[2] += reflectGain * (reflectColor[2]);
        
        }

    // set ouput color attribute
    MDataHandle outColorHandle = block.outputValue( aOutColor );
    MFloatVector& outColor = outColorHandle.asFloatVector();
    outColor = resultColor;
    outColorHandle.setClean();

    return MS::kSuccess;

}

//BeckMann���z��Ԃ�
float CookTorranceNode::beckMann( MFloatVector HV,  MFloatVector N, float m){

	//�n�[�t�x�N�g���Ɩ@���x�N�g���̓���
	float HN = HV * N;

	//HN�̓��
	float HN2 = HN * HN;

	float bMann = (1 / (m*m * HN2*HN2) ) * exp(-( (1-HN2) /(m*m*HN2) ));

	return bMann;

}

//�􉽌�����Ԃ�
float CookTorranceNode::localOcclusion( MFloatVector HV,  MFloatVector N,  MFloatVector V,  MFloatVector L){

	float HVN = HV*N;
	
	float VN = V*N;

	float LN = L*N;

	float HVV = HV*V;

	float Gr = 2.0f * (HVN * VN) / (HVV) ;
	float Gi = 2.0f * (HVN * LN) / (HVV) ;

	//Gr = abs(Gr);
	//Gi = abs(Gi);

	float lOcclusion = min(min(Gr,Gi), 1.0f);

	return lOcclusion;

}

//Fresnel�v�Z���ĕԂ�
float  CookTorranceNode::Fresnel( MFloatVector HV,  MFloatVector V, float n){


	//�{���̃t���l���͕Ό����l������BS�g��P�g�̓x�����H

	//�n�[�t�x�N�g���Ǝ����x�N�g���̓���
	float c = HV * V;

	//�t���l���v�Z
	float g = (float) sqrt(c * c + n * n - 1.0);
	//�v�Z�����t���l���W��
	float F = (((g - c) * (g - c)) / (2 * (g + c) * (g + c))) * //
	(1 + (((c * (g + c) - 1) * (c * (g + c) - 1)) / ((c * (g + c) + 1) * (c * (g + c) + 1))));

return F;
}


