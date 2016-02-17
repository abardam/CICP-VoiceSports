/* Each row is a joint trajectory. Each column is a frame.
*/
#include "PoseMatcher.h"
#include <cmath>
#include <atlstr.h>

const std::vector<std::string> PoseMatcher::poses = { "jodan", "kamae", "sonkyo", "suburi", "tsubazeriai" };
const std::vector<std::string> PoseMatcher::actors = { "antonio", "emi", "enzo", "nunu", "truong", "antonio", "emi", "enzo", "nunu", "truong" };

// Constructor with the reading of the dataset to memory and calculation of heights
PoseMatcher::PoseMatcher()
{
	position average_p;
	double average_c;

	std::string path;
	TCHAR charpath[256];
	std::string rep;

	for (unsigned int p = 0; p < NUM_POSES; ++p)
	{
		for (unsigned int a = 0; a < NUM_ACTORS; ++a)
		{
			rep = (a < 5) ? "front" : "side";

			// Path format: kamae\\antonio_kamae_front\\skeleton
			path = HAR_PATH + poses.at(p) + "\\" + actors.at(a) + "_" + poses.at(p) + "_" + rep + "\\skeleton\\";
			//actskeleton action = Reader.readSkeleton((const TCHAR*)path.c_str(), NUM_JOINTS);
			_tcscpy_s(charpath, CA2T(path.c_str()));
			actskeleton action = Reader.readSkeleton(charpath, NUM_JOINTS);

			// Average the pose
			size_t num_frames = action.poses.size();

			for (unsigned int j = 0; j < NUM_JOINTS; ++j)
			{
				average_p.rightleft = 0;
				average_p.updown = 0;
				average_p.fwdbwd = 0;

				average_c = 0;

				for (unsigned int f = 0; f < num_frames; ++f)
				{
					average_p.rightleft += action.poses.at(f).positions[j].rightleft;
					average_p.updown += action.poses.at(f).positions[j].updown;
					average_p.fwdbwd += action.poses.at(f).positions[j].fwdbwd;

					average_c += (int)action.poses.at(f).confidences[j];
				}
				posedataset[p][a].positions[j].rightleft = average_p.rightleft / num_frames;
				posedataset[p][a].positions[j].updown = average_p.updown / num_frames;
				posedataset[p][a].positions[j].fwdbwd = average_p.fwdbwd / num_frames;

				if ((average_c / num_frames) > 0.5)
				{
					posedataset[p][a].confidences[j] = true;
				}
				else
				{
					posedataset[p][a].confidences[j] = false;
				}
			}
			// Normalize skeleton
			this->normalizeSkeleton(&(posedataset[p][a]));
			// Calculate the height of the actor
			heightdataset[p][a] = this->calculateHeight(posedataset[p][a]);
		}
	}
}

PoseMatcher::~PoseMatcher()
{
}

void PoseMatcher::normalizeSkeleton(posskeleton* skel)
{
	position center = skel->positions[TORSO];
	for (unsigned int j = 0; j < NUM_JOINTS; ++j)
	{
		skel->positions[j].rightleft -= center.rightleft;
		skel->positions[j].updown -= center.updown;
		skel->positions[j].fwdbwd -= center.fwdbwd;
	}
}

bool PoseMatcher::isFrontOrSide(posskeleton skel)
{
	position shoulderL = skel.positions[LSHOULDER];
	position shoulderR = skel.positions[RSHOULDER];
	position torso = skel.positions[TORSO];

	double vec1[3] = { shoulderL.rightleft, shoulderL.updown, shoulderL.fwdbwd };
	double vec2[3] = { shoulderR.rightleft, shoulderR.updown, shoulderR.fwdbwd };
	double normal[3];

	normal[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	normal[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	normal[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];

	return (abs(normal[0]) <= abs(normal[2])) ? true : false;
}

double PoseMatcher::calculateHeight(posskeleton inskel)
{
	return inskel.positions[HEAD].updown - (inskel.positions[RFOOT].updown + inskel.positions[LFOOT].updown) / 2;
}

int PoseMatcher::fitSkeleton(posskeleton inskel, int action, bool frontal)
{
	// Check if the skeleton is frontal or lateral
	//bool frontal = this->isFrontOrSide(inskel);

	// Choose the most appropriate user/skeleton (height)
	double heightskel = this->calculateHeight(inskel);

	int user = 0;
	double diff = 2000;
	if (frontal)
	{
		for (unsigned int u = 0; u < NUM_ACTORS / 2; ++u)
		{
			if (abs(heightskel - heightdataset[action][u]) < diff)
			{
				user = u;
			}
		}
	}
	else
	{
		for (unsigned int u = NUM_ACTORS / 2; u < NUM_ACTORS; ++u)
		{
			if (abs(heightskel - heightdataset[action][u]) < diff)
			{
				user = u;
			}
		}
	}

	return user;
}

void PoseMatcher::weightedPoseMatching(posskeleton inskel, fbskeleton fbjoints, int action, bool frontal, posskeleton* feedback, posskeleton* fitpose)
{
	// Normalize the skeleton with respect to the center
	this->normalizeSkeleton(&inskel);

	// USER + ACTION + FRONTAL = COMPARABLE SKELETON
	int user = this->fitSkeleton(inskel, action, frontal);
	posskeleton compskel = posedataset[action][user];

	// Calculate the feedback for each joint
	for (unsigned int j = 0; j < NUM_JOINTS; j++)
	{
		if (fbjoints.needsCheck[j])
		{
			feedback->positions[j].rightleft = this->filtervalue(inskel.positions[j].rightleft - compskel.positions[j].rightleft);
			feedback->positions[j].updown = this->filtervalue(inskel.positions[j].updown - compskel.positions[j].updown);
			feedback->positions[j].fwdbwd = this->filtervalue(inskel.positions[j].fwdbwd - compskel.positions[j].fwdbwd);
			//feedback->positions[j].rightleft = inskel.positions[j].rightleft - compskel.positions[j].rightleft;
			//feedback->positions[j].updown = inskel.positions[j].updown - compskel.positions[j].updown;
			//feedback->positions[j].fwdbwd = inskel.positions[j].fwdbwd - compskel.positions[j].fwdbwd;
		}
		else
		{
			feedback->positions[j].rightleft = 0;
			feedback->positions[j].updown = 0;
			feedback->positions[j].fwdbwd = 0;
		}
	}

	*fitpose = compskel;
}

int PoseMatcher::filtervalue(double raw)
{
	int filtered = (int)(raw * 100);

	if (filtered < 4)
	{
		filtered = 0;
	}

	return filtered;
}
