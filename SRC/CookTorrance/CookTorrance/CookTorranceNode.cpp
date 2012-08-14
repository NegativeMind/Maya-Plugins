

#include "CookTorranceNode.h"


MTypeId CookTorranceNode::id( 0x7ffe );//唯一のID0x81002

//一般パラメータ
MObject CookTorranceNode::aColor;
MObject CookTorranceNode::aTranslucenceCoeff;
MObject CookTorranceNode::aIncandescence;

//出力する色
MObject CookTorranceNode::aOutColor;

//Diffuse強度
MObject CookTorranceNode::aDiffuseReflectivity;

//specularパラメータ
MObject CookTorranceNode::aSpecularity;//強度
MObject CookTorranceNode::aRefractivityRed;//屈折率Red
MObject CookTorranceNode::aRefractivityGreen;//屈折率Green
MObject CookTorranceNode::aRefractivityBlue;//屈折率Blue
MObject CookTorranceNode::aRoughness;//面の粗さ

//Shading用パラメータ
MObject CookTorranceNode::aPointCamera;
MObject CookTorranceNode::aNormalCamera;

//ライトデータ
MObject CookTorranceNode::aLightData;
MObject CookTorranceNode::aLightDirection;
MObject CookTorranceNode::aLightIntensity;

//ライティングフラグ
MObject CookTorranceNode::aLightAmbient;
MObject CookTorranceNode::aLightDiffuse;
MObject CookTorranceNode::aLightSpecular;

//Shadowデータ
MObject CookTorranceNode::aLightShadowFraction;
MObject CookTorranceNode::aPreShadowIntensity;
MObject CookTorranceNode::aLightBlindData;

//RayTrace用パラメータ
MObject CookTorranceNode::aRayOrigin;
MObject CookTorranceNode::aRayDirection;
MObject CookTorranceNode::aObjectId;
MObject CookTorranceNode::aRaySampler;
MObject CookTorranceNode::aRayDepth;

//RayTrace強度
MObject CookTorranceNode::aReflectGain;

//交差判定用面法線
MObject CookTorranceNode::aTriangleNormalCamera;




void CookTorranceNode::postConstructor( )
{
	setMPSafe(true);
}

//コンストラクタ
CookTorranceNode::CookTorranceNode() {}
//デストラクタ
CookTorranceNode::~CookTorranceNode() {}

//クリエータ
void* CookTorranceNode::creator()
{
	return new CookTorranceNode();
}


//アトリビュート設定用マクロ
//Input用
#define MAKE_INPUT(attr)	\
	CHECK_MSTATUS(attr.setKeyable(true));	\
	CHECK_MSTATUS(attr.setStorable(true));	\
	CHECK_MSTATUS(attr.setReadable(true));	\
	CHECK_MSTATUS(attr.setWritable(true));

//Output用
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

	//以下、specularパラメータのアトリビュート設定
    aSpecularity = nAttr.create( "specularity", "spc", MFnNumericData::kFloat);
    MAKE_INPUT(nAttr);
    CHECK_MSTATUS ( nAttr.setMin(0.0f) );
    CHECK_MSTATUS ( nAttr.setMax(1.0f) ) ;
    CHECK_MSTATUS ( nAttr.setDefault(0.5f) );

	//面の粗さ
	aRoughness = nAttr.create( "roughness", "m", MFnNumericData::kFloat);
    MAKE_INPUT(nAttr);
    CHECK_MSTATUS ( nAttr.setMin(0.0f) );
    CHECK_MSTATUS ( nAttr.setMax(1.0f) );
    CHECK_MSTATUS ( nAttr.setDefault(0.5f) );

	//以下、RGB屈折率
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

	//RayTrace強度
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

//このノードの処理
MStatus CookTorranceNode::compute( const MPlug& plug, MDataBlock& block )
{
	//例外処理
	if ((plug != aOutColor) && (plug.parent() != aOutColor)){
                return MS::kUnknownParameter;
	}

	//出力カラーを保持する変数
    MFloatVector resultColor(0.0,0.0,0.0);

    // get sample surface shading parameters(視線ベクトルと法線ベクトルを取得)
    MFloatVector& surfaceNormal = block.inputValue( aNormalCamera ).asFloatVector();
    MFloatVector& cameraPosition = block.inputValue( aPointCamera ).asFloatVector();

        // use for raytracing api enhancement below(RayTrace用のパラメータを取得)
        MFloatVector point = cameraPosition;
        MFloatVector normal = surfaceNormal;

		//視線・法線ベクトルを正規化
		CHECK_MSTATUS( cameraPosition.normalize() );
		CHECK_MSTATUS( surfaceNormal.normalize() );

	//Diffuse用パラメータを取得
    MFloatVector& surfaceColor  = block.inputValue( aColor ).asFloatVector();
    MFloatVector& incandescence = block.inputValue( aIncandescence ).asFloatVector();
    float diffuseReflectivity = block.inputValue( aDiffuseReflectivity ).asFloat();
    // float translucenceCoeff   = block.inputValue( aTranslucenceCoeff ).asFloat();


        // User-defined Reflection Color Gain(RayTrace用の反射強度)
        float reflectGain = block.inputValue( aReflectGain ).asFloat();
  
    //CookTorrance shading attributes(specular用パラーメータの取得)
		float spec = block.inputValue( aSpecularity ).asFloat();//強度
		float roughness = block.inputValue( aRoughness ).asFloat();//面の粗さ
		float refractivityR = block.inputValue( aRefractivityRed ).asFloat();//R屈折率
		float refractivityG = block.inputValue( aRefractivityGreen ).asFloat();//G屈折率
		float refractivityB = block.inputValue( aRefractivityBlue ).asFloat();//B屈折率

    

	//RGBごとのspecular,diffuseの値を格納する変数を全て0.0で初期化
    float specularR, specularG, specularB;
    float diffuseR, diffuseG, diffuseB;
    diffuseR = diffuseG = diffuseB = specularR = specularG = specularB = 0.0;

    // get light list(ライト情報を取得)
    MArrayDataHandle lightData = block.inputArrayValue( aLightData );
    int numLights = lightData.elementCount();
    
    // iterate through light list and get ambient/diffuse values(ライトの数だけループして、ambientとdiffuseを取得)
    for( int count=1; count <= numLights; count++ )
    {
		
        MDataHandle currentLight = lightData.inputValue();//現在のライト
        MFloatVector& lightIntensity = currentLight.child(aLightIntensity).asFloatVector();//ライトの強さ
        
        // Find the blind data(遮蔽情報を取得)
        void*& blindData = currentLight.child( aLightBlindData ).asAddr();
     
		//ライトベクトルを格納
        MFloatVector& lightDirection = currentLight.child(aLightDirection).asFloatVector();

		//ライトの減衰を表す変数
		float lightAttenuation = 1.0;       

		//ライトベクトルと法線ベクトルの内積
		float cosln = lightDirection * surfaceNormal;

		//計算用にライトベクトルを格納する変数
		MFloatVector specLightDirection;

		//視線ベクトルの正規化
        CHECK_MSTATUS( cameraPosition.normalize() );

				//πを定義
				float PI = (float)3.14159265;


		if (blindData == NULL){//blindDataがない場合(例外処理)

			specLightDirection = lightDirection;

		}else{//blindDataがある場合

			//ライトと法線の内積
			cosln = MRenderUtil::diffuseReflectance( blindData, lightDirection, point, surfaceNormal, true );
			specLightDirection =  MRenderUtil::maximumSpecularReflection( blindData,lightDirection, point, surfaceNormal, cameraPosition );

			 //ライトの減衰
			 lightAttenuation = MRenderUtil::lightAttenuation( blindData, point, surfaceNormal, false );   

		}

		 //ambient処理
        if( currentLight.child(aLightAmbient).asBool() ) {//ライトにambientが設定されていれば全体にライトの強度を加算
            diffuseR += lightIntensity[0];
            diffuseG += lightIntensity[1];
            diffuseB += lightIntensity[2];
        }

		//ここから反射計算
		if(cosln > 0.0f){//光源と面している場合のみ計算

			//Diffuse反射計算
			if(currentLight.child(aLightDiffuse).asBool() ){//ライトにdiffuseが設定されている場合

				//Diffuse計算および加算(ライトの減衰をかけ、πで割る)
				diffuseR += lightIntensity[0] * ( cosln * diffuseReflectivity ) * lightAttenuation / PI;
				diffuseG += lightIntensity[1] * ( cosln * diffuseReflectivity ) * lightAttenuation / PI;
				diffuseB += lightIntensity[2] * ( cosln * diffuseReflectivity ) * lightAttenuation / PI;
		}

			//specular反射計算
			if ( currentLight.child(aLightSpecular).asBool() ){//ライトにspecularが設定されている場合

									//各種ベクトルの正規化
									CHECK_MSTATUS( cameraPosition.normalize() );
									CHECK_MSTATUS( specLightDirection.normalize() );
									CHECK_MSTATUS( surfaceNormal.normalize() );


									//光源ベクトルと視線ベクトルのハーフベクトル
									MFloatVector HV = specLightDirection - cameraPosition;
									 CHECK_MSTATUS( HV.normalize() );

									 //法線ベクトルと視線ベクトルの内積
									 float NV = (surfaceNormal) * (-cameraPosition);

									 //微小切片を表す散乱関数D(BeckMann分布)
									 float D = beckMann(HV, surfaceNormal, roughness);

									 //localOcclusion G(幾何減衰)
									 float G = localOcclusion(HV, surfaceNormal, -cameraPosition, specLightDirection);

									 //Fresnel反射(RGBごと)
									 float FR = Fresnel(HV, -cameraPosition, refractivityR) / PI;
									 float FG = Fresnel(HV, -cameraPosition, refractivityG) / PI;
									 float FB = Fresnel(HV, -cameraPosition, refractivityB) / PI;

									 //反射強度計算(CookTorranceからFだけ抜いてある)
									 float s = (D * G / NV) * spec;

									 //specular値の加算
									specularR += lightIntensity[0] * s * FR * lightAttenuation; 
                                    specularG += lightIntensity[1] * s * FG * lightAttenuation; 
                                    specularB += lightIntensity[2] * s * FB * lightAttenuation; 

			}
		}
		

       if( !lightData.next() ) break;
    }

    // factor incident light with surface color and add incandescence自己発光値も足し合わせて結果に格納
		resultColor[0] = ( diffuseR * surfaceColor[0] ) + specularR + incandescence[0];
		resultColor[1] = ( diffuseG * surfaceColor[1] ) + specularG + incandescence[1];
		resultColor[2] = ( diffuseB * surfaceColor[2] ) + specularB + incandescence[2];


        // add the reflection color
        if (reflectGain > 0.0) {//RayTrace用処理(reflectGainが0以上だった場合)

                MStatus status;

				//RayTraceに使う各種値をData blockから取得する

                // required attributes for using raytracer
                // origin, direction, sampler, depth, and object id.
               
				//描画点の位置ベクトルを取得
                MDataHandle originH = block.inputValue( aRayOrigin, &status);
                MFloatVector origin = originH.asFloatVector();

				//視線ベクトルを取得
                MDataHandle directionH = block.inputValue( aRayDirection, &status);
                MFloatVector direction = directionH.asFloatVector();

				//
                MDataHandle samplerH = block.inputValue( aRaySampler, &status);
                void*& samplerPtr = samplerH.asAddr();

				//レイの深さを取得
                MDataHandle depthH = block.inputValue( aRayDepth, &status);
                short depth = depthH.asShort();

				//オブジェクトのIDを取得
                MDataHandle objH = block.inputValue( aObjectId, &status);
                void*& objId = objH.asAddr();

                MFloatVector reflectColor;//鏡面反射の色を格納する変数
                MFloatVector reflectTransparency;


				//三角形の法線を取得
                MFloatVector& triangleNormal = block.inputValue( aTriangleNormalCamera ).asFloatVector();


                // compute reflected ray
                MFloatVector l = -direction;
                float dot = l * normal;
                if( dot < 0.0 ) dot = -dot;
                MFloatVector refVector = 2 * normal * dot - l;  // reflection ray反射ベクトルを求める
                float dotRef = refVector * triangleNormal;
                if( dotRef < 0.0 ) {
                    const float s = 0.01f;
                        MFloatVector mVec = refVector - dotRef * triangleNormal;
                        mVec.normalize();
                        refVector = mVec + s * triangleNormal;
                }

				//反射ベクトルの正規化
                CHECK_MSTATUS ( refVector.normalize() );

				//レイトレーシングを行う関数(?)
                status = MRenderUtil::raytrace(
                                point,          //  origin
                                refVector,  //  direction
                                objId,          //  object id
                                samplerPtr, //  sampler info
                                depth,          //  ray depthレイの深さ(回数？)
                                reflectColor,   // output color and transp
                                reflectTransparency);


				//もし、レイの多重サンプリングが必要ならここでループを書いて加算する

                // add in the reflection color反射色を反射率とかけて結果に加算
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

//BeckMann分布を返す
float CookTorranceNode::beckMann( MFloatVector HV,  MFloatVector N, float m){

	//ハーフベクトルと法線ベクトルの内積
	float HN = HV * N;

	//HNの二乗
	float HN2 = HN * HN;

	float bMann = (1 / (m*m * HN2*HN2) ) * exp(-( (1-HN2) /(m*m*HN2) ));

	return bMann;

}

//幾何減衰を返す
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

//Fresnel計算して返す
float  CookTorranceNode::Fresnel( MFloatVector HV,  MFloatVector V, float n){


	//本来のフレネルは偏光も考慮する。S波とP波の度合い？

	//ハーフベクトルと視線ベクトルの内積
	float c = HV * V;

	//フレネル計算
	float g = (float) sqrt(c * c + n * n - 1.0);
	//計算したフレネル係数
	float F = (((g - c) * (g - c)) / (2 * (g + c) * (g + c))) * //
	(1 + (((c * (g + c) - 1) * (c * (g + c) - 1)) / ((c * (g + c) + 1) * (c * (g + c) + 1))));

return F;
}


