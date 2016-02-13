#include "antonio_skeleton_util.h"
#include "stdafx.h"
#include <Kinect.h>
#include "../CICP-ActionTemplates/UtilsHAR.h"

int kinectJointMap[NUM_JOINTS] = { JointType_Head, JointType_Neck, JointType_ShoulderLeft, JointType_ElbowLeft, JointType_HandLeft,
JointType_ShoulderRight, JointType_ElbowRight, JointType_HandRight, JointType_SpineMid, JointType_HipLeft, JointType_KneeLeft,
JointType_FootLeft, JointType_HipRight, JointType_KneeRight, JointType_FootRight };

int * getKinectJointMap()
{
	return kinectJointMap;
}
