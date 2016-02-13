#pragma once

#include "UtilsHAR.h"
#include <windows.h>
#include <string>	// std::string

class SkeletonReader
{
public:
	SkeletonReader();
	~SkeletonReader();
	actskeleton readSkeleton(const TCHAR* path, size_t numJoints);

private:
	actskeleton matrix2skeleton(double** M, bool** confi, size_t num_frames);
	size_t readMotionMatrix(const TCHAR* path, size_t numJoints, double*** M, bool*** confi);
	int readFrame(std::string fileName, double* M, bool* confi);
	void createMatrixD(double*** matrix, size_t N, size_t M);
	void createMatrixB(bool*** matrix, size_t N, size_t M);
	void deleteMatrix(double** matrix);
	void deleteMatrix(bool** matrix);

	static const unsigned int v[];	// Joint correspondence
};
