#ifndef _CookTorranceNode
#define _CookTorranceNode

#include <math.h>

#include <maya/MPxNode.h>
#include <maya/MIOStream.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>
#include <maya/MPlug.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MArrayDataHandle.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnLightDataAttribute.h>
#include <maya/MFloatVector.h>

//#include <maya/MGlobal.h>

// add for raytracing api enhancement
#include <maya/MRenderUtil.h>
 
class CookTorranceNode : public MPxNode
{
 public:
                      CookTorranceNode();
    virtual           ~CookTorranceNode();
	virtual MStatus   compute( const MPlug& plug, MDataBlock& data );
	virtual void      postConstructor();

	static float beckMann( MFloatVector HV,  MFloatVector N, float m);
	static float localOcclusion( MFloatVector HV,  MFloatVector N,  MFloatVector V,  MFloatVector L);
	static float Fresnel( MFloatVector HV,  MFloatVector V, float n);

    static void *     creator();
    static MStatus    initialize();
    static MTypeId    id;
	
private:

	static MObject aColor;//入力の色(ライトからの光)

	//一般パラメータ
    static MObject aTranslucenceCoeff;
    static MObject aDiffuseReflectivity;
	static MObject aIncandescence;

	
	static MObject aOutColor;//出力の色

	//Shading用パラメータ
	static MObject aPointCamera;
	static MObject aNormalCamera;
	
	//ライトデータ
	static MObject aLightDirection;
	static MObject aLightIntensity;
	static MObject aLightData;
    
	//Specular用パラメータ
	static MObject aSpecularity;//強度
	static MObject aRefractivityRed;//屈折率Red
	static MObject aRefractivityGreen;//屈折率Green
	static MObject aRefractivityBlue;//屈折率Blue
	static MObject aRoughness;//面の粗さ
    
    
	static MObject aLightAmbient;
    static MObject aLightDiffuse;
    static MObject aLightSpecular;
    
	static MObject aLightShadowFraction;
    static MObject aPreShadowIntensity;
    static MObject aLightBlindData;
    

	//RayTrace用パラメータ
    static MObject aRayOrigin;
    static MObject aRayDirection;

    static MObject aObjectId;
    static MObject aRaySampler;
    static MObject aRayDepth;
    static MObject aReflectGain;
	static MObject aTriangleNormalCamera;



};

#endif
