#include "CookTorranceNode.h"

#include <maya/MFnPlugin.h>


/**
 * プラグインの初期化
 **/
MStatus initializePlugin(MObject obj){
	
	const MString UserClassify("shader/surface");//���̃m�[�h�̑���

	MFnPlugin plugin( obj,  PLUGIN_COMPANY, "4.5", "Any");//���삷��Maya�̃o�[�W������


	//MStatus���Ԃ��֐���CHECK_MSTATUS�֐��ɓ����ăG���[���Ȃ����Ƃ��ۏ؂���
	CHECK_MSTATUS(plugin.registerNode( "CookTorranceNode", CookTorranceNode::id,
								CookTorranceNode::creator,
								CookTorranceNode::initialize,
								MPxNode::kDependNode,
								&UserClassify ));

	return MS::kSuccess;
}

/**
 * プラグインの解放
 **/
MStatus uninitializePlugin(MObject obj){
	
	MFnPlugin plugin( obj );

	CHECK_MSTATUS (plugin.deregisterNode( CookTorranceNode::id ));
	
	return MS::kSuccess;
}
