#pragma once

int * getKinectJointMap();

#define NUM_SEGMENTS 10

//will return a 1-D array containing NUM_SEGMENTS * 2 elements
//(2n) = first joint of segment n, (2n+1) = second joint of segment n
int * getKinectSegments();