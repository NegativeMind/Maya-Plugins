
#include "CookTorranceNode.h"

#include <maya/MFnPlugin.h>

MStatus initializePlugin( MObject obj )

{ 
	//このノードの属性
	const MString UserClassify("shader/surface"); 


	//動作するMayaのバージョン等
	MFnPlugin plugin( obj,  PLUGIN_COMPANY, "4.5", "Any");

//MStatusを返す関数をCHECK_MSTATUS関数に入れてエラーがないことを保証する
CHECK_MSTATUS(plugin.registerNode( "CookTorranceNode", CookTorranceNode::id,
									CookTorranceNode::creator,
									CookTorranceNode::initialize,
									MPxNode::kDependNode,
									&UserClassify ));

	return MS::kSuccess;
}

MStatus uninitializePlugin( MObject obj)

{
	MFnPlugin plugin( obj );

	CHECK_MSTATUS (plugin.deregisterNode( CookTorranceNode::id ));
	
	return MS::kSuccess;
}
