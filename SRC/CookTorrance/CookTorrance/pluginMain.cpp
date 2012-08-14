
#include "CookTorranceNode.h"

#include <maya/MFnPlugin.h>

MStatus initializePlugin( MObject obj )

{ 
	//���̃m�[�h�̑���
	const MString UserClassify("shader/surface"); 


	//���삷��Maya�̃o�[�W������
	MFnPlugin plugin( obj,  PLUGIN_COMPANY, "4.5", "Any");

//MStatus��Ԃ��֐���CHECK_MSTATUS�֐��ɓ���ăG���[���Ȃ����Ƃ�ۏ؂���
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
