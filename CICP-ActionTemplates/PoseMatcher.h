#include "SkeletonReader.h"

#define NUM_POSES 5	// Number of poses in our dataset
#define NUM_ACTORS 10	// Number of actors in our dataset

class PoseMatcher
{
public:
	PoseMatcher();
	~PoseMatcher();
	posskeleton weightedPoseMatching(posskeleton inskel, fbskeleton fbjoints, int action);

private:
	void normalizeSkeleton(posskeleton* skel);
	bool isFrontOrSide(posskeleton skel);
	double calculateHeight(posskeleton inskel);
	int fitSkeleton(posskeleton inskel, int action);

	posskeleton posedataset[NUM_POSES][NUM_ACTORS];

	double heightdataset[NUM_POSES][NUM_ACTORS];

	static const std::vector<std::string> poses;
	static const std::vector<std::string> actors;

	SkeletonReader Reader;
};
