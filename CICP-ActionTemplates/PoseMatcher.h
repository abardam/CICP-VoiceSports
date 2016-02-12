#include "SkeletonReader.h"

#define NUM_POSES 5	// Number of poses in our dataset
#define NUM_ACTORS 10	// Number of actors in our dataset

// The order of the actions is:
#define JODAN 0
#define KAMAE 1
#define SONKYO 2
#define SUBURI 3
#define TSUBAZERIAI 4

class PoseMatcher
{
public:
	PoseMatcher();
	~PoseMatcher();
	void weightedPoseMatching(posskeleton inskel, fbskeleton fbjoints, int action, posskeleton* feedback, posskeleton* fitpose);

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
